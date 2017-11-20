/*
   Copyright (C) 2017-2018 Stefan Masuch

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef HTTP2PIPELINE_HPP
#define HTTP2PIPELINE_HPP

#include "include/utils/logger.hpp"
#include "include/http2/http2transportqueue.hpp"
#include "include/http2/http2connection.hpp"
#include "include/http2/http2pipelineinterface.hpp"
#include "include/http2/pipelineconnectinfo.hpp"
#include "include/http2/http2headerinfo.hpp"

#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

using namespace AVS;

namespace http2
{

    typedef void (*HTTP2ResHeaderCallback)( const void * name , size_t name_size , const void * value , size_t value_size , int32_t stream_id , void * custom_pip );
    typedef void (*HTTP2ResContentCallback)( void * content , size_t size , int32_t stream_id , void * custom_pip );
    typedef void (*HTTP2ResHeaderBeginCallback)( int32_t stream_id , void * custom_pip );
    typedef void (*HTTP2ResHeaderEndCallback)( int32_t stream_id , void * custom_pip );
    typedef void (*HTTP2EventError)( void * custom_pip  );

    /*!
     * \brief The ChunkDataBuffer class
     */
    class ChunkDataBuffer
    {
        public:
            ChunkDataBuffer() = default;
            ~ChunkDataBuffer();

            void set( uint8_t * data );
            void setSize( size_t size );
            bool empty(void);

            uint8_t * get(void);
            size_t getSize(void);
            void cleanUp(void);

         private:
            uint8_t * m_data;
            size_t m_data_size;
    };

    /*!
     * \brief The HTTP2StreamDataInfo class
     */
    class HTTP2StreamDataInfo
    {
        public:
            HTTP2StreamDataInfo() = default;
            ~HTTP2StreamDataInfo() = default;

            HTTP2StreamDataInfo * setProvider( nghttp2_data_provider * provider );
            HTTP2StreamDataInfo * setHeader( nghttp2_nv * header );
            HTTP2StreamDataInfo * setSrcLength( size_t source_length );
            HTTP2StreamDataInfo * setSrcOffsetLength( size_t source_offset_length );
            HTTP2StreamDataInfo * setHeaderLength( size_t header_length );
            HTTP2StreamDataInfo * setChunkDataBuffer( ChunkDataBuffer * buffer );
            HTTP2StreamDataInfo * setStreamID( int32_t id );

            nghttp2_data_provider * p_provider;
            nghttp2_nv * p_header;
            ChunkDataBuffer * p_chunk_buffer;
            size_t  p_src_length;
            size_t  p_src_offset_length;
            size_t  p_header_length;
            int32_t p_stream_id;
    };

    /*!
     * \brief The HTTP2SessionInfo class
     */
    class HTTP2SessionInfo
    {
         public:
            HTTP2SessionInfo() = default;
            ~HTTP2SessionInfo() = default;

            HTTP2SessionInfo * setSession( nghttp2_session * session     );
            HTTP2SessionInfo * setDnsBase( struct evdns_base * dns_base  );
            HTTP2SessionInfo * setBufferEvent( struct bufferevent * bev );
            HTTP2SessionInfo * setStreamDataInfo( HTTP2StreamDataInfo * streamdata_info );
            HTTP2SessionInfo * setResHeaderCallback( HTTP2ResHeaderCallback callback );
            HTTP2SessionInfo * setResContentCallback( HTTP2ResContentCallback callback );
            HTTP2SessionInfo * setResHeaderBeginCallback( HTTP2ResHeaderBeginCallback callback );
            HTTP2SessionInfo * setResHeaderEndCallback( HTTP2ResHeaderEndCallback callback );
            HTTP2SessionInfo * setEventErrorCallback( HTTP2EventError callback);

            HTTP2SessionInfo * setCustomPipeline( void * custom_pip );

            nghttp2_session     * p_session;
            struct evdns_base   * p_dns_base;
            struct bufferevent  * p_bev;
            HTTP2StreamDataInfo * p_streamdata_info;
            HTTP2ResHeaderCallback p_header_callback;
            HTTP2ResContentCallback p_content_callback;
            HTTP2ResHeaderBeginCallback p_header_begin_callback;
            HTTP2ResHeaderEndCallback p_header_end_callback;
            HTTP2EventError p_event_error_callback;
            void * p_custom_pipeline;
    };

    /*!
     * \brief The HTTP2ConnectionInfo class
     */
    class HTTP2ConnectionInfo
    {
        public:
         HTTP2ConnectionInfo() = default;
         ~HTTP2ConnectionInfo() = default;

         HTTP2ConnectionInfo * setEventBase( struct event_base * evbase );
         HTTP2ConnectionInfo * setSSLCTX( SSL_CTX * ssl_ctx );
         HTTP2ConnectionInfo * setHost( const char * host );
         HTTP2ConnectionInfo * setPort( uint16_t port );
         HTTP2ConnectionInfo * setSessionInfo( HTTP2SessionInfo * session_info );
         HTTP2ConnectionInfo * setConnectionStatus( bool status );
         HTTP2ConnectionInfo * setEventBaseTimer( long timer );

         bool getConnectionStatus(void);

         struct event_base * p_evbase;
         SSL_CTX * p_ssl_ctx;
         const char * p_host;
         uint16_t p_port;
         HTTP2SessionInfo * p_session_info;
         long p_event_base_timer;

       private:
            bool m_status;
    };


    /*!
     * \brief The HTTP2 class
     */
    class HTTP2
    {
        public:
            HTTP2() = default;
            ~HTTP2() = default;

            /*!
             * \brief create_ssl_ctx
             * \return
             */
            static SSL_CTX * create_ssl_ctx(void);

            /*!
             * \brief initiate_connection
             * \param connection_info
             */
            static void initiate_connection( HTTP2ConnectionInfo * connection_info );

            /*!
             * \brief create_http2_session_data
             * \param dnsbase
             * \return
             */
            static HTTP2SessionInfo * create_http2_session_data( struct evdns_base * dnsbase );

            /*!
             * \brief create_http2_connection_session_data
             * \param evbase
             * \return
             */
            static HTTP2SessionInfo * create_http2_connection_session_data( struct event_base * evbase );

            /*!
             * Callback function for create_ssl_ctx
             * \brief select_next_proto_cb : callback function
             * \param ssl
             * \param out
             * \param outlen
             * \param in
             * \param inlen
             * \param arg
             * \return
             */
            static int select_next_proto_cb( SSL *ssl ,
                                             unsigned char **out     ,
                                             unsigned char *outlen   ,
                                             const unsigned char *in ,
                                             unsigned int inlen     ,
                                             void *arg
                                           );

            /*!
             * Create SSL function
             * Invoke from : NgHTTP2API::initiate_connection
             * \brief create_ssl
             * \param ssl_ctx
             * \return
             */
            static SSL * create_ssl( SSL_CTX * ssl_ctx );

            /*!
             * BufferEvent - Managed Events
             *
             * BEV_EVENT_CONNECTED
             * BEV_EVENT_EOF
             * BEV_EVENT_ERROR
             * BEV_EVENT_TIMEOUT
             *
             * \brief eventcb : callback function
             * \param bev
             * \param events
             * \param ptr     : http_session_data
             */
            static void eventcb( struct bufferevent * bev ,
                                 short events ,
                                 void * ptr
                              );

            /*!
             * incoming data from the remote peer
             * \brief readcb : callback function
             * \param bev
             * \param ptr    : http_session_data
             */
            static void readcb( struct bufferevent * bev , void * ptr);

            /*!
             * send data to the remote peer
             * \brief writecb : callback function
             * \param bev
             * \param ptr     : http_session_data
             */
            static void writecb( struct bufferevent * bev , void  * ptr);

            /*!
             * Create nghttp2_session
             *
             * and setup callbacks
             * \brief initialize_nghttp2_session
             * \param session_data
             */
            static void initialize_nghttp2_session( HTTP2SessionInfo * session_info );

            /*!
             * \brief send_client_connection_header
             * \param session_data
             */
            static void send_client_connection_header(  HTTP2SessionInfo * session_info  );

            /*!
             * make stream id
             */
            static void submit_request( HTTP2SessionInfo * session_info  );

            /*!
             * send all data to the remote peer
             * invoke: send_callback
             *
             * \brief session_send
             * \param session_data
             * \return
             */
            static int session_send( HTTP2SessionInfo * session_info );


            /*!
             * \brief delete_http2_session_data
             * \param session_info
             */
            static void delete_http2_session_data( HTTP2SessionInfo * session_info );

            /*!
             * Read Data Source ( Body Request )
             *
             * \brief data_source_read_callback : callback function
             * \param session
             * \param stream_id
             * \param buf
             * \param length
             * \param data_flags
             * \param source
             * \param user_data : http2_session_data
             * \return
             */
            static ssize_t data_source_read_callback( nghttp2_session * session ,
                                                      int32_t stream_id ,
                                                      uint8_t * buf     ,
                                                      size_t length     ,
                                                      uint32_t * data_flags ,
                                                      nghttp2_data_source * source ,
                                                      void * user_data
                                                    );

            /*!
             * send all data to the remote peer
             * invoke: bufferevent_write
             *
             * \brief send_callback : callback function
             * \param session
             * \param data
             * \param length
             * \param flags
             * \param user_data : http2_session_data
             * \return
             */
            static ssize_t send_callback( nghttp2_session * session ,
                                          const uint8_t * data ,
                                          size_t length ,
                                          int flags ,
                                          void * user_data
                                       );


            /*!
             * Callback function invoked when a header name/value pair
             * is received for the frame.
             *
             * \brief on_header_callback : callback function
             * \param session
             * \param frame
             * \param name
             * \param namelen
             * \param value
             * \param valuelen
             * \param flags
             * \param user_data : http2_session_data
             * \return
             */
            static int on_header_callback( nghttp2_session * session ,
                                           const nghttp2_frame * frame ,
                                           const uint8_t * name ,
                                           size_t namelen ,
                                           const uint8_t * value ,
                                           size_t valuelen ,
                                           uint8_t flags ,
                                           void * user_data
                                         );
           /*!
            * Callback function invoked by nghttp2_session_recv() and
            * nghttp2_session_mem_recv() when a frame is received.
            *
            * \brief on_frame_recv_callback : callback function
            * \param session
            * \param frame
            * \param user_data : http2_session_data
            * \return
            */
           static int on_frame_recv_callback( nghttp2_session * session ,
                                              const nghttp2_frame * frame ,
                                              void * user_data
                                            );

           static int on_frame_send_callback( nghttp2_session * session ,
                                             const nghttp2_frame * fame ,
                                             void * user_data
                                            );
           /*!
            * Callback function invoked when a chunk of data in DATA frame is received.
            *
            * \brief on_data_chunk_recv_callback : callback function
            * \param session
            * \param flags
            * \param stream_id
            * \param data
            * \param len
            * \param user_data : http2_session_data
            * \return
            */
           static int on_data_chunk_recv_callback( nghttp2_session * session ,
                                                   uint8_t flags ,
                                                   int32_t stream_id ,
                                                   const uint8_t * data ,
                                                   size_t len ,
                                                   void * user_data
                                                 );
           /*!
            * Callback function invoked when the stream stream_id is closed
            *
            * \brief on_stream_close_callback
            * \param session
            * \param stream_id
            * \param error_code
            * \param user_data : http2_session_data
            * \return
            */
           static int on_stream_close_callback( nghttp2_session * session ,
                                                int32_t stream_id ,
                                                uint32_t error_code ,
                                                void * user_data
                                              );
           /*!
            * Callback function invoked when the reception of header block in HEADERS or PUSH_PROMISE is started.
            * Each header name/value pair will be emitted by nghttp2_on_header_callback.
            *
            * \brief on_begin_headers_callback : callback function
            * \param session
            * \param frame
            * \param user_data : http2_session_data
            * \return
            */
           static int on_begin_headers_callback( nghttp2_session * session   ,
                                                 const nghttp2_frame * frame ,
                                                 void * user_data
                                                 );
    };

    class HTTP2Pipeline : public HTTP2PipelineInterface , public HTTP2TransportQueue, public HTTP2Connection
    {
        public:
            HTTP2Pipeline() = default;
            ~HTTP2Pipeline() = default;

            void initialize( void );
            void connect( PipelineConnectInfo * info ) override final;
            void connectionLoop(void) override final;
            void disconnect(void) override final ;

            void setTransportData( HTTP2TransportData * transport_data ) override final;
            void performStream(void) override final ;

            virtual void onResponseProcessingEvent( HTTP2Response * response_data ) = 0;
            virtual void onResponseHeaderProcessingEvent( SharedHeaderInfo info )=0;

            void onResponseEvent(void *content, size_t size, int32_t stream_id ) override final;
            void onResponseHeaderEvent(const void *name, size_t name_size, const void *value, size_t value_size , int32_t stream_id ) override final;
            void onResponseHeaderBeginEvent( int32_t stream_id ) override final;
            void onResponseHeaderEndEvent( int32_t stream_id ) override final;
            void onEventBaseErrorEvent(void);
            bool isPipelineReady(void);

        protected:

            static void onResponseEventCallback( void * content, size_t size, int32_t stream_id, void * custom_pipeline);
            static void onResponseHeaderEventCallback( const void * name  , size_t name_size , const void * value , size_t value_size , int32_t stream_id , void * custom_pipeline );
            static void onResponseHeaderBeginCallback( int32_t stream_id , void * custom_pipeline );
            static void onResponseHeaderEndCallback( int32_t stream_id , void * custom_pipeline );
            static void onEventErrorCallback( void * custom_pip );
            static void onTransportProcessingThread( HTTP2Pipeline * pipeline );

            void onEventLoop( event_base * base );
            void onEventDispatch( event_base * base , long seconds );
            void onEventLoopExit(void);
            bool isEventLoopRunning(void);

        private:

            std::unique_ptr<HTTP2ConnectionInfo> m_connection_unique_info;
            HTTP2TransportData  * m_temp_transport_data;
            std::list< SharedHeaderInfo > m_header_infos;
            boost::mutex m_event_base_mutex;
            boost::condition_variable m_event_base_cv;
            bool m_connection_loop;
            bool m_event_loop_exit_flag;
            bool m_event_loop_cancel;
            bool m_pipeline_ready;
    };


}

#endif // HTTP2PIPELINE_HPP

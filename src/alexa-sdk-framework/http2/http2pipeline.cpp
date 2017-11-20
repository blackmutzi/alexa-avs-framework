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
#include "include/http2/http2pipeline.hpp"

using namespace http2;

ChunkDataBuffer::~ChunkDataBuffer()
{
    if( !empty() )
            free( m_data );
}

void ChunkDataBuffer::set(uint8_t *data)
{
    m_data = data;
}

void ChunkDataBuffer::setSize(size_t size)
{
    m_data_size = size;
}

uint8_t * ChunkDataBuffer::get(void)
{
    return m_data;
}

bool ChunkDataBuffer::empty(void)
{
    return getSize() == 0 ? true : false;
}

size_t ChunkDataBuffer::getSize(void)
{
    return m_data_size;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setProvider(nghttp2_data_provider *provider)
{
    p_provider = provider;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setHeader(nghttp2_nv *header)
{
    p_header = header;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setSrcLength(size_t source_length)
{
    p_src_length = source_length;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setSrcOffsetLength(size_t source_offset_length)
{
    p_src_offset_length = source_offset_length;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setHeaderLength(size_t header_length)
{
    p_header_length = header_length;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setChunkDataBuffer(ChunkDataBuffer *buffer)
{
    p_chunk_buffer = buffer;
    return this;
}

HTTP2StreamDataInfo * HTTP2StreamDataInfo::setStreamID(int32_t id)
{
    p_stream_id = id;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setSession(nghttp2_session *session)
{
    p_session = session;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setDnsBase(evdns_base *dns_base)
{
    p_dns_base = dns_base;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setBufferEvent(bufferevent *bev)
{
    p_bev = bev;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setStreamDataInfo(HTTP2StreamDataInfo *streamdata_info)
{
    p_streamdata_info = streamdata_info;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setResHeaderCallback(HTTP2ResHeaderCallback callback)
{
    p_header_callback = callback;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setResContentCallback(HTTP2ResContentCallback callback)
{
    p_content_callback = callback;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setResHeaderBeginCallback(HTTP2ResHeaderBeginCallback callback)
{
    p_header_begin_callback = callback;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setResHeaderEndCallback(HTTP2ResHeaderEndCallback callback)
{
    p_header_end_callback = callback;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setEventErrorCallback(HTTP2EventError callback)
{
    p_event_error_callback = callback;
    return this;
}

HTTP2SessionInfo * HTTP2SessionInfo::setCustomPipeline(void *custom_pip)
{
    p_custom_pipeline = custom_pip;
    return this;
}


HTTP2ConnectionInfo * HTTP2ConnectionInfo::setEventBase(event_base *evbase)
{
    p_evbase = evbase;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setSSLCTX(SSL_CTX *ssl_ctx)
{
    p_ssl_ctx = ssl_ctx;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setHost(const char *host)
{
    p_host = host;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setPort(uint16_t port)
{
    p_port = port;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setSessionInfo(HTTP2SessionInfo *session_info)
{
    p_session_info = session_info;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setConnectionStatus(bool status)
{
    m_status = status;
    return this;
}

HTTP2ConnectionInfo * HTTP2ConnectionInfo::setEventBaseTimer(long timer)
{
    p_event_base_timer = timer;
    return this;
}

bool HTTP2ConnectionInfo::getConnectionStatus(void)
{
    return m_status;
}

int HTTP2::select_next_proto_cb(SSL *ssl, unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg)
{
    (void)ssl;
    (void)arg;

    if( nghttp2_select_next_protocol(out , outlen , in , inlen) <= 0)
    {
         Logger::instance().error("Server did not advertise");
    }

    return SSL_TLSEXT_ERR_OK;
}

SSL_CTX * HTTP2::create_ssl_ctx(void)
{
    SSL_CTX *ssl_ctx = SSL_CTX_new( SSLv23_client_method() );

    if (!ssl_ctx)
    {
        stringstream error;
        error << "Could not create SSL/TLS context: ";
        error << ERR_error_string(ERR_get_error(), NULL);
        Logger::instance().error( error.str() );

    } else {

        stringstream info;
        info << " SSL/TLS context successfully created ";
        Logger::instance().info( info.str() );

        SSL_CTX_set_options(ssl_ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 |
                                     SSL_OP_NO_COMPRESSION |
                                     SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION);
        SSL_CTX_set_next_proto_select_cb(ssl_ctx ,&HTTP2::select_next_proto_cb, NULL );

        #if OPENSSL_VERSION_NUMBER >= 0x10002000L
        SSL_CTX_set_alpn_protos(ssl_ctx, (const unsigned char *)"\x02h2", 3);
        #endif // OPENSSL_VERSION_NUMBER >= 0x10002000L

    }

    return ssl_ctx;
}

SSL * HTTP2::create_ssl(SSL_CTX *ssl_ctx)
{
    SSL * ssl = SSL_new(ssl_ctx);

    if (!ssl)
    {
        stringstream error;
        error << "Could not create SSL/TLS session object: ";
        error << ERR_error_string(ERR_get_error(), NULL);
        Logger::instance().error( error.str() );

    } else {

        stringstream info;
        info << " SSL/TLS session successfully created " << SSL_get_version( ssl );
        Logger::instance().info( info.str() );
    }

    return ssl;
}

void HTTP2::initiate_connection( HTTP2ConnectionInfo * con_info )
{
    int rv;
    struct bufferevent *bev;
    SSL *ssl;

    ssl = create_ssl( con_info->p_ssl_ctx );
    bev = bufferevent_openssl_socket_new( con_info->p_evbase , -1, ssl, BUFFEREVENT_SSL_CONNECTING, BEV_OPT_DEFER_CALLBACKS | BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, &HTTP2::readcb, &HTTP2::writecb, &HTTP2::eventcb , con_info->p_session_info );

    rv = bufferevent_socket_connect_hostname(bev, con_info->p_session_info->p_dns_base, AF_UNSPEC, con_info->p_host, con_info->p_port );

    if (rv != 0)
    {
        stringstream error;
        error << "Could not connect to the remote host: " << con_info->p_host;
        Logger::instance().error( error.str() );

    } else {

        stringstream info;
        info << "Connected to Host: " << con_info->p_host << " Port: " << con_info->p_port;
        Logger::instance().info( info.str() );

        con_info->p_session_info->setBufferEvent( bev );
    }
}

void HTTP2::eventcb(bufferevent *bev, short events, void *ptr)
{
      HTTP2SessionInfo *session_info = ( HTTP2SessionInfo *) ptr;

      int fd = bufferevent_getfd(bev);
      int val = 1;
      const unsigned char *alpn = NULL;
      unsigned int alpnlen = 0;
      SSL *ssl;

      // BEV_EVENT_CONNECTED ...
      if (events & BEV_EVENT_CONNECTED)
      {
            stringstream debug;
            debug << "BEV_EVENT_CONNECTED event has started ";
            Logger::instance().debug( "HTTP2::eventcb" , debug.str() );

            ssl = bufferevent_openssl_get_ssl( session_info->p_bev );
            SSL_get0_next_proto_negotiated(ssl, &alpn, &alpnlen);

            #if OPENSSL_VERSION_NUMBER >= 0x10002000L
            if (alpn == NULL) {
                SSL_get0_alpn_selected(ssl, &alpn, &alpnlen);
            }
            #endif // OPENSSL_VERSION_NUMBER >= 0x10002000L

            if (alpn == NULL || alpnlen != 2 || memcmp("h2", alpn, 2) != 0)
            {
                stringstream error;
                error << "ALPN protocol: h2 is not negotiated";
                Logger::instance().error( error.str() );

                delete_http2_session_data(session_info);
                return;
            }

            setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&val, sizeof(val));
            initialize_nghttp2_session(session_info);
            send_client_connection_header(session_info);
            submit_request(session_info);
            session_send( session_info);

            return;
      }

      // BEV_EVENT_EOF
      if (events & BEV_EVENT_EOF)
      {
          stringstream debug;
          debug << "BEV_EVENT_EOF event has started ";
          Logger::instance().debug( "HTTP2::eventcb" , debug.str() );
          Logger::instance().warn("Disconnected from the remote host");

          delete_http2_session_data(session_info);
          session_info->p_event_error_callback( session_info->p_custom_pipeline );
          return;
      }

      // BEV_EVENT_ERROR
      if (events & BEV_EVENT_ERROR)
      {
          stringstream debug;
          debug << "BEV_EVENT_ERROR event has started ";
          Logger::instance().debug( "HTTP2::eventcb" , debug.str() );
          Logger::instance().warn("Network Error");

          delete_http2_session_data(session_info);
          session_info->p_event_error_callback( session_info->p_custom_pipeline );
          return;
      }

      // BEV_EVENT_TIMEOUT
      if (events & BEV_EVENT_TIMEOUT)
      {
          stringstream debug;
          debug << "BEV_EVENT_TIMEOUT event has started ";
          Logger::instance().debug( "HTTP2::eventcb" , debug.str() );
          Logger::instance().warn("Timeout");

          delete_http2_session_data(session_info);
          session_info->p_event_error_callback( session_info->p_custom_pipeline );
          return;
      }
}

void HTTP2::initialize_nghttp2_session(HTTP2SessionInfo *session_info)
{
    nghttp2_session_callbacks *callbacks;

    nghttp2_session_callbacks_new( &callbacks );
    nghttp2_session_callbacks_set_send_callback(callbacks, &HTTP2::send_callback );
    nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks, &HTTP2::on_frame_recv_callback);
    nghttp2_session_callbacks_set_on_frame_send_callback( callbacks , &HTTP2::on_frame_send_callback);
    nghttp2_session_callbacks_set_on_data_chunk_recv_callback( callbacks, &HTTP2::on_data_chunk_recv_callback);
    nghttp2_session_callbacks_set_on_stream_close_callback( callbacks, &HTTP2::on_stream_close_callback);
    nghttp2_session_callbacks_set_on_header_callback(callbacks, &HTTP2::on_header_callback);
    nghttp2_session_callbacks_set_on_begin_headers_callback( callbacks, &HTTP2::on_begin_headers_callback);
    nghttp2_session_client_new(&session_info->p_session, callbacks, session_info );
    nghttp2_session_callbacks_del(callbacks);

    stringstream debug;
    debug << "nghttp2_session created ";
    Logger::instance().debug( "HTTP2::initialize_nghttp2_session" , debug.str() );
}

void HTTP2::send_client_connection_header(HTTP2SessionInfo *session_info)
{
    //TODO: make it dynamic via settings ...
    nghttp2_settings_entry iv[1] = { {NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, 1000} };

    int rv = 0;
    /* client 24 bytes magic string will be sent by nghttp2 library */
    rv = nghttp2_submit_settings( session_info->p_session, NGHTTP2_FLAG_NONE, iv, ARRLEN(iv) );

    if (rv != 0)
    {
        stringstream error;
        error << "Could not submit settings: ";
        error << nghttp2_strerror(rv);
        Logger::instance().error( error.str() );

    } else {

        stringstream info;
        info << "Submit Settings confirmed";
        Logger::instance().debug("connection_header",info.str() );

    }
}

void HTTP2::submit_request(HTTP2SessionInfo *session_info)
{
    int32_t stream_id = 0;
    HTTP2StreamDataInfo * stream_data_info = session_info->p_streamdata_info;

    /* set data_src_read_callback if provider is not nullptr */
    if( stream_data_info->p_provider != nullptr )
    {
        stringstream debug;
        debug << "Set Data Source Read Callback";
        Logger::instance().debug( "HTTP2::submit_request " , debug.str() );

        stream_data_info->p_provider->read_callback = &HTTP2::data_source_read_callback;
    }

    stream_id = nghttp2_submit_request( session_info->p_session,            // nghttp2_session
                                        NULL,                               // nghttp2_priority_spec
                                        stream_data_info->p_header,         // nghttp2_nv
                                        stream_data_info->p_header_length , // size of nghttp2_nv
                                        stream_data_info->p_provider      , // nghttp2_data_provider
                                        stream_data_info);                  // http2streamdatainfo

    if (stream_id < 0)
    {
        stringstream error;
        error << "Could not submit request: ";
        error << nghttp2_strerror( stream_id );
        Logger::instance().error( error.str() );

    } else {

        stringstream info;
        info << "submit request successfully (" << stream_id << ")";
        Logger::instance().info( info.str() );

        stream_data_info->p_stream_id = stream_id;
    }
}


void HTTP2::readcb(bufferevent *bev, void *ptr)
{
    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)ptr;
    ssize_t readlen = 0;
    struct evbuffer *input = bufferevent_get_input(bev);
    size_t datalen         = evbuffer_get_length(input);
    unsigned char *data    = evbuffer_pullup(input, -1);

    readlen = nghttp2_session_mem_recv(session_info->p_session, data, datalen);

    if (readlen < 0) {
        Logger::instance().warn( nghttp2_strerror((int)readlen) );
        delete_http2_session_data(session_info);
        return;
    }

    if (evbuffer_drain(input, (size_t)readlen) != 0) {
        Logger::instance().warn("Fatal error: evbuffer_drain failed");
        delete_http2_session_data(session_info);
        return;
    }

    if (session_send(session_info) != 0) {
        delete_http2_session_data(session_info);
        return;
    }
}

void HTTP2::writecb(bufferevent *bev, void *ptr)
{
    (void) bev;
    // NgHTTP2API::session_send contained nghttp2_session_send function
    // nghttp2_session_send function => invoke NgHTTP2API::send_callback was contained bufferevent_write
    // bufferevent_write    function => invoke this callback function ( i think so )

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)ptr;

    // if session wants to receive data from the remote peer.
    int read  = nghttp2_session_want_read(session_info->p_session);

    // if session wants to send data to the remote peer.
    int write = nghttp2_session_want_write(session_info->p_session);

    if ( read == 0 && write == 0 && evbuffer_get_length( bufferevent_get_output(session_info->p_bev)) == 0)
    {
        //if both nghttp2_session_want_read() and nghttp2_session_want_write() return 0, the application should drop the connection
        delete_http2_session_data(session_info);
    }
}

int HTTP2::session_send(HTTP2SessionInfo *session_info)
{
    int rv = 0;
    rv = nghttp2_session_send( session_info->p_session );

    if (rv != 0) {
        Logger::instance().warn( nghttp2_strerror(rv) );
        return -1;
    }

   return 0;
}

ssize_t HTTP2::data_source_read_callback(nghttp2_session *session, int32_t stream_id, uint8_t *buf, size_t length, uint32_t *data_flags, nghttp2_data_source *source, void *user_data)
{
    (void)session;

    HTTP2SessionInfo    * session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;

    if (stream_info->p_stream_id == stream_id )
    {
        // The implementation of this function must read at most length bytes of data from source
        // and store them in buf and return number of data stored in buf.
        // If EOF is reached, set NGHTTP2_DATA_FLAG_EOF flag in *data_flags.

        void * data = source->ptr;
        size_t data_source_len        =  stream_info->p_src_length;
        size_t data_source_offset_len =  stream_info->p_src_offset_length;
        ssize_t nread = 0;

        if( data != NULL || data != nullptr )
        {
              // clear the buf
              memset( buf , 0 , length );

              if( length < ( data_source_len - data_source_offset_len ) )
              {
                  memcpy( buf , (char*) data + data_source_offset_len , length );

              } else {

                  length = data_source_len - data_source_offset_len;
                  memcpy( buf , (char*)data + data_source_offset_len , length );
              }

              // add length to data_source_offset
              stream_info->p_src_offset_length += length;

              // EOF is reached
              if( stream_info->p_src_offset_length >= data_source_len )
              {
                 *data_flags |= NGHTTP2_DATA_FLAG_EOF;
              }

              // return number of data stored in buf
              nread = length;
              return nread;
        }
    }

  return 0;
}

ssize_t HTTP2::send_callback(nghttp2_session *session, const uint8_t *data, size_t length, int flags, void *user_data)
{
    (void)session;
    (void)flags;

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    struct bufferevent *bev = session_info->p_bev;
    bufferevent_write(bev, data, length);

    stringstream debug;
    debug << "write bufferevent with size of bytes: " << length;
    Logger::instance().debug("HTTP2::send_callback", debug.str() );

    return (ssize_t)length;
}

int HTTP2::on_header_callback(nghttp2_session *session, const nghttp2_frame *frame, const uint8_t *name, size_t namelen, const uint8_t *value, size_t valuelen, uint8_t flags, void *user_data)
{
    (void) session;
    (void) flags;

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;

    switch (frame->hd.type) {

        case NGHTTP2_HEADERS:

            if (frame->headers.cat == NGHTTP2_HCAT_RESPONSE && stream_info->p_stream_id == frame->hd.stream_id)
            {
                stringstream debug;
                debug << "trigger header callback by streamId=" << frame->hd.stream_id;
                Logger::instance().debug("HTTP2::on_header_callback", debug.str() );
                session_info->p_header_callback( name , namelen , value , valuelen , stream_info->p_stream_id , session_info->p_custom_pipeline );
            }

        break;
    }

    return 0;
}

int HTTP2::on_frame_recv_callback(nghttp2_session *session, const nghttp2_frame *frame, void *user_data)
{
    (void) session;

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;

    switch (frame->hd.type)
    {
        case NGHTTP2_HEADERS:
                    if (frame->headers.cat == NGHTTP2_HCAT_RESPONSE && stream_info->p_stream_id == frame->hd.stream_id) {
                        Logger::instance().debug("HTTP2::on_frame_recv_callback", "HEADER FRAME received");
                        session_info->p_header_end_callback( stream_info->p_stream_id , session_info->p_custom_pipeline );
                    }
        break;

        case NGHTTP2_DATA:
                    Logger::instance().debug("HTTP2::on_frame_recv_callback","DATA FRAME received");
        break;

    }
   return 0;
}

int HTTP2::on_frame_send_callback(nghttp2_session *session, const nghttp2_frame *frame, void *user_data)
{
    (void) session;

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;

    switch (frame->hd.type)
    {
        case NGHTTP2_HEADERS:
                    if (frame->headers.cat == NGHTTP2_HCAT_REQUEST && stream_info->p_stream_id == frame->hd.stream_id) {

                          nghttp2_nv * header_ptr = frame->headers.nva;
                          size_t  header_len      = frame->headers.nvlen;
                          nghttp2_nv * show_ptr   = header_ptr;
                          stringstream show_stream;
                          unsigned int counter = 0;

                          show_stream << "::Show (Send) Headers::" << std::endl;
                          while( show_ptr < header_ptr + header_len )
                          {
                              show_stream << "< " << (const char *) show_ptr->name << "(" << show_ptr->namelen << ") ";
                              show_stream << (const char *) show_ptr->value << " (" << show_ptr->valuelen << ")";

                              show_ptr++;
                              counter++;

                              if( counter != header_len )
                                     show_stream << std::endl;
                          }
                          Logger::instance().debug("HTTP2::on_frame_send_callback" , show_stream.str() );
                          Logger::instance().debug("HTTP2::on_frame_send_callback", "send header frame");
                    }
        break;

        case NGHTTP2_DATA:

                    if( stream_info->p_stream_id == frame->hd.stream_id )
                    {
                        Logger::instance().debug("HTTP2::on_frame_send_callback", "send data frame");
                    }
        break;

    }

    return 0;
}

int HTTP2::on_data_chunk_recv_callback(nghttp2_session *session, uint8_t flags, int32_t stream_id, const uint8_t *data, size_t len, void *user_data)
{
    (void) session;
    (void) flags;

    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;
    ChunkDataBuffer * res_buffer = stream_info->p_chunk_buffer;

    if (stream_info->p_stream_id == stream_id )
    {
        // Callback function invoked when a chunk of data in DATA frame is received.
        // The flags is the flags of DATA frame which this data chunk is contained.

        if( res_buffer->empty() )
        {
            uint8_t * chunk_buffer = (uint8_t *) malloc ( sizeof( uint8_t ) * len ); // allocate new buffer 
            memset( chunk_buffer , 0 , len );										 // clean allocated space 
            memcpy( chunk_buffer , data , len );									 // write data into chunk_buffer
			
            res_buffer->set( chunk_buffer );										 // save chunk_buffer ptr 
            res_buffer->setSize( len );												 // save chunk_buffer ptr size 

        } else {

            size_t last_buffer_size = res_buffer->getSize();
            size_t new_buffer_size  = last_buffer_size + len;
			
			uint8_t * buffer = res_buffer->get();			 						       // current chunk_buffer ptr 
            buffer = ( uint8_t * ) realloc( buffer , sizeof( uint8_t) * new_buffer_size ); // realloc chunk_buffer with new_buffer_size 
		    memcpy( buffer + last_buffer_size , data , len );							   // add new data to chunk_buffer ptr 	
			
			res_buffer->set( buffer );													   // save chunk_buffer ptr ( not required )
			res_buffer->setSize( new_buffer_size );            							   // save chunk_buffer ptr size ( required )
        }
    }

   return 0;
}


int HTTP2::on_begin_headers_callback(nghttp2_session *session, const nghttp2_frame *frame, void *user_data)
{
    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;
    (void)session;

      switch (frame->hd.type)
      {
            case NGHTTP2_HEADERS:
                    if (frame->headers.cat == NGHTTP2_HCAT_RESPONSE && stream_info->p_stream_id == frame->hd.stream_id)
                    {
                        stringstream debug;
                        debug << "response headers incoming by streamId=" << frame->hd.stream_id;
                        Logger::instance().debug( "HTTP2::on_begin_headers_callback" , debug.str() );
                        session_info->p_header_begin_callback( stream_info->p_stream_id , session_info->p_custom_pipeline );
                    }
            break;
      }

   return 0;
}

int HTTP2::on_stream_close_callback(nghttp2_session *session, int32_t stream_id, uint32_t error_code, void *user_data)
{
    HTTP2SessionInfo *session_info = (HTTP2SessionInfo *)user_data;
    HTTP2StreamDataInfo * stream_info  = session_info->p_streamdata_info;
    ChunkDataBuffer * res_buffer = stream_info->p_chunk_buffer;
    int rv = 0;

      if (stream_info->p_stream_id == stream_id)
      {
          stringstream debug;
          debug << "streamId=" << stream_id << " closed -- trigger response callback now ...";
          Logger::instance().debug("HTTP2::on_stream_close_callback", debug.str() );

          session_info->p_content_callback( res_buffer->get() , res_buffer->getSize() , stream_id , session_info->p_custom_pipeline );
      }
      else if( stream_info->p_stream_id == 1 )
      {
          stringstream debug;
          debug << "downchannel stream closed & terminate http2_session ";
          Logger::instance().debug("HTTP2::on_stream_close_callback" , debug.str() );
          return 0;

          rv = nghttp2_session_terminate_session( session, error_code );
          delete_http2_session_data( session_info );

          if (rv != 0) {
              return NGHTTP2_ERR_CALLBACK_FAILURE;
          }
      }

   return 0;
}

HTTP2SessionInfo * HTTP2::create_http2_connection_session_data(event_base *evbase)
{
    HTTP2SessionInfo * session_info = new HTTP2SessionInfo();
    session_info->setDnsBase( evdns_base_new( evbase , 1) );
    return session_info;
}

HTTP2SessionInfo * HTTP2::create_http2_session_data(evdns_base *dnsbase)
{
    HTTP2SessionInfo * session_info = new HTTP2SessionInfo();
    session_info->setDnsBase( dnsbase );
    return session_info;
}

void HTTP2::delete_http2_session_data(HTTP2SessionInfo *session_info)
{
    stringstream debug;
    debug << "http2_session_data deleted";
    Logger::instance().debug( "HTTP2::delete_http2_session_data" , debug.str() );

    SSL *ssl = bufferevent_openssl_get_ssl(session_info->p_bev);

    if (ssl) {
      SSL_shutdown(ssl);
    }


    bufferevent_free(session_info->p_bev);
    session_info->p_bev = nullptr;

    evdns_base_free( session_info->p_dns_base , 1);
    session_info->p_dns_base = nullptr;

    nghttp2_session_del( session_info->p_session );
    session_info->p_session = nullptr;
}

void HTTP2Pipeline::initialize(void)
{
    SSL_load_error_strings();
    SSL_library_init();

    HTTP2TransportQueue::initialize();
    m_temp_transport_data = nullptr;

    m_connection_unique_info = std::unique_ptr<HTTP2ConnectionInfo>( new HTTP2ConnectionInfo() );
    HTTP2ConnectionInfo * connection_info = m_connection_unique_info.get();

    connection_info->setSSLCTX( HTTP2::create_ssl_ctx() );
    connection_info->setEventBase( event_base_new() );
    connection_info->setPort( 443 ); //default port
    connection_info->setSessionInfo( HTTP2::create_http2_connection_session_data( connection_info->p_evbase ) );
    connection_info->p_session_info->setCustomPipeline( this );
    connection_info->p_session_info->setResHeaderCallback(  &HTTP2Pipeline::onResponseHeaderEventCallback );
    connection_info->p_session_info->setResContentCallback( &HTTP2Pipeline::onResponseEventCallback );
    connection_info->p_session_info->setResHeaderBeginCallback( &HTTP2Pipeline::onResponseHeaderBeginCallback );
    connection_info->p_session_info->setResHeaderEndCallback( &HTTP2Pipeline::onResponseHeaderEndCallback );
    connection_info->p_session_info->setEventErrorCallback( &HTTP2Pipeline::onEventErrorCallback);
    m_pipeline_ready = false;
}

void HTTP2Pipeline::connect( PipelineConnectInfo * info )
{
    auto stream_data = std::unique_ptr<HTTP2StreamDataInfo>( new HTTP2StreamDataInfo() );
    auto chunk_data  = std::unique_ptr<ChunkDataBuffer>( new ChunkDataBuffer() );

    HTTP2TransportData  * downchannel_data = info->p_data;
    HTTP2StreamDataInfo * master_stream    = stream_data.get();
    HTTP2ConnectionInfo * connection_info  = m_connection_unique_info.get();
    HTTP2SessionInfo    * session_info     = connection_info->p_session_info;

    master_stream->setChunkDataBuffer( chunk_data.get() );
    master_stream->setHeader( downchannel_data->getHTTP2HeaderInfo()->get() );
    master_stream->setHeaderLength( downchannel_data->getHTTP2HeaderInfo()->getSize() );
    master_stream->setProvider( nullptr );
    master_stream->setSrcLength( 0 );
    master_stream->setSrcOffsetLength( 0 );
    master_stream->setStreamID( 0 );

    session_info->setStreamDataInfo( master_stream );

    connection_info->setHost( info->p_host );                        // set host ip
    connection_info->setPort( info->p_port );                        // set host port
    connection_info->setConnectionStatus( info->p_connection_loop ); // set connection loop status ( true )
    connection_info->setEventBaseTimer( info->p_response_timer );

    boost::thread response_processing_thread( &HTTP2Pipeline::onTransportProcessingThread , this );
    bool first_time = true;
    while( connection_info->getConnectionStatus() )
    {
        if( first_time )
        {
            HTTP2::initiate_connection( connection_info );
            onEventDispatch( connection_info->p_evbase , 1 );
            onEventLoop( connection_info->p_evbase );
            first_time = false;

        } else{

            if( session_info->p_session == nullptr )
            {
                connection_info->setConnectionStatus( false );
                break;
            }

            Logger::instance().info("[ Main Thread ] waiting...");
            boost::unique_lock< boost::mutex > mutex_lock( m_event_base_mutex );
            m_event_base_cv.wait( mutex_lock );
            onEventLoop( connection_info->p_evbase );
        }
    }

    event_base_free( connection_info->p_evbase );
    SSL_CTX_free( connection_info->p_ssl_ctx);
    stream_data.reset();
    chunk_data.reset();
    delete connection_info->p_session_info;
    m_connection_unique_info.reset();
    HTTP2TransportQueue::cleanUp();
}

void HTTP2Pipeline::onEventLoop( event_base * base )
{
    m_event_loop_exit_flag = true;
    m_event_loop_cancel = false;

    Logger::instance().info("[ Main Thread ] pipeline is ready ");
    while( m_event_loop_exit_flag )
    {
        m_pipeline_ready = true;
        event_base_loop( base , EVLOOP_NONBLOCK );
    }

    m_event_loop_cancel = true;
    m_pipeline_ready = false;
}

void HTTP2Pipeline::onEventDispatch( event_base * base , long seconds )
{
    struct timeval loop_exit_timer;
    loop_exit_timer.tv_sec  = seconds;
    loop_exit_timer.tv_usec = 0;

    event_base_loopexit( base , &loop_exit_timer );
    event_base_dispatch( base );
}

void HTTP2Pipeline::onEventLoopExit(void)
{
    while( !m_pipeline_ready ){}
    m_event_loop_exit_flag = false;
}

bool HTTP2Pipeline::isEventLoopRunning(void)
{
    return m_event_loop_cancel;
}

bool HTTP2Pipeline::isPipelineReady(void)
{
    return m_pipeline_ready;
}

void HTTP2Pipeline::onTransportProcessingThread(HTTP2Pipeline *pipeline)
{
    pipeline->connectionLoop();
}

void HTTP2Pipeline::disconnect(void)
{
    m_connection_loop = false;
}

void HTTP2Pipeline::connectionLoop(void)
{
     HTTP2ConnectionInfo * connection_info  = m_connection_unique_info.get();
     while( connection_info->getConnectionStatus() )
     {
         HTTP2TransportQueue::queue_transport_processing( this );
     }
}

void HTTP2Pipeline::setTransportData(HTTP2TransportData *transport_data)
{
    m_temp_transport_data = transport_data;
}

void HTTP2Pipeline::performStream(void)
{
   auto stream_data = std::unique_ptr<HTTP2StreamDataInfo>( new HTTP2StreamDataInfo() );
   auto chunk_data  = std::unique_ptr<ChunkDataBuffer>( new ChunkDataBuffer() );
   auto provider    = std::unique_ptr<nghttp2_data_provider>( new nghttp2_data_provider() );

   HTTP2ConnectionInfo * connection_info    = m_connection_unique_info.get();
   HTTP2SessionInfo    * session_info       = connection_info->p_session_info;
   HTTP2StreamDataInfo * master_stream_info = session_info->p_streamdata_info;
   HTTP2StreamDataInfo * stream_info        = stream_data.get();

   stream_info->setProvider( provider.get() );
   stream_info->setChunkDataBuffer( chunk_data.get() );
   stream_info->setHeader( m_temp_transport_data->getHTTP2HeaderInfo()->get() );
   stream_info->setHeaderLength( m_temp_transport_data->getHTTP2HeaderInfo()->getSize() );
   stream_info->setSrcLength( m_temp_transport_data->getHTTP2ContentInfo()->getSize() );
   stream_info->setSrcOffsetLength( 0 );
   stream_info->setStreamID(0);
   stream_info->p_provider->source.ptr = (void*) m_temp_transport_data->getHTTP2ContentInfo()->get();

   session_info->setStreamDataInfo( stream_info );

   // is not EVENT_ERROR or EVENT_TIMEOUT
   if( session_info->p_session != nullptr )
   {
       onEventLoopExit();
       while( isPipelineReady() ){}

       Logger::instance().info("[ Stream Thread ] dispatch ... ");
       HTTP2::submit_request( session_info );
       HTTP2::session_send( session_info );

       onEventDispatch( connection_info->p_evbase , connection_info->p_event_base_timer);
       m_event_base_cv.notify_one();
   }

   /* clean up here */
   chunk_data.reset();
   provider.reset();
   stream_data.reset();

   /* restore master_stream_info */
   session_info->setStreamDataInfo( master_stream_info);
}

void HTTP2Pipeline::onResponseEventCallback(void *content, size_t size, int32_t stream_id, void *custom_pipeline)
{
    HTTP2Pipeline * pipeline = (HTTP2Pipeline *) custom_pipeline;
    pipeline->onResponseEvent( content , size , stream_id );
}

void HTTP2Pipeline::onResponseHeaderEventCallback(const void *name, size_t name_size, const void *value, size_t value_size, int32_t stream_id , void *custom_pipeline)
{
    HTTP2Pipeline * pipeline = (HTTP2Pipeline *) custom_pipeline;
    pipeline->onResponseHeaderEvent( name , name_size , value , value_size , stream_id );
}

void HTTP2Pipeline::onResponseHeaderBeginCallback(int32_t stream_id, void *custom_pipeline)
{
    HTTP2Pipeline * pipeline = (HTTP2Pipeline *) custom_pipeline;
    pipeline->onResponseHeaderBeginEvent( stream_id );
}

void HTTP2Pipeline::onResponseHeaderEndCallback(int32_t stream_id, void *custom_pipeline)
{
    HTTP2Pipeline * pipeline = (HTTP2Pipeline *) custom_pipeline;
    pipeline->onResponseHeaderEndEvent( stream_id );
}

void HTTP2Pipeline::onEventErrorCallback(void *custom_pipeline)
{
    HTTP2Pipeline * pipeline = (HTTP2Pipeline *) custom_pipeline;
    pipeline->onEventBaseErrorEvent();
}

void HTTP2Pipeline::onResponseEvent(void *content, size_t size , int32_t stream_id )
{
    /* Response Save Location */
    SharedResponse  response_ptr( new HTTP2Response() );
    HTTP2Response * response_data = response_ptr.get();

    /* make a copy of data  */
    size_t memory_size = size + 1;
    char * memory = new char[ memory_size ];
    memset( memory , 0 , memory_size );
    memcpy( memory , content , size );

    /* set data */
    response_data->set( memory );
    response_data->setSize( memory_size );
    response_data->setStreamId( stream_id );

    stringstream debug;
    debug << "push_response size(" << memory_size << ")";
    Logger::instance().debug( "HTTP2Pipeline::onResponseEvent" , debug.str() );

    /* push data */
    HTTP2TransportQueue::push_response( response_ptr );
}

void HTTP2Pipeline::onResponseHeaderEvent(const void *name, size_t name_size, const void *value, size_t value_size , int32_t stream_id )
{
    (void) name_size;
    (void) value_size;

    stringstream header_info_stream;
    header_info_stream << (const char*) name << " " << (const char*) value;
    Logger::instance().debug( "ResponseHeaderEvent" , header_info_stream.str() );

    for( SharedHeaderInfo info : m_header_infos )
    {
        HTTP2HeaderInfo * data = info.get();

        if( data->getStreamId() == stream_id && data->isActive() )
        {
            data->addHeaderLine( (const char*) name , (const char*) value );
            break;
        }
    }
}

void HTTP2Pipeline::onResponseHeaderBeginEvent(int32_t stream_id)
{
    SharedHeaderInfo sharedinfo( new HTTP2HeaderInfo() );
    HTTP2HeaderInfo * header_info = sharedinfo.get();

    stringstream convert_id_to_string;
    convert_id_to_string << stream_id;
    std::string stream_id_string = convert_id_to_string.str();

    header_info->setActivedState( true );
    header_info->setStreamId( stream_id );
    header_info->addHeaderLine("streamid", stream_id_string.c_str() );

    m_header_infos.push_back( sharedinfo );
}

void HTTP2Pipeline::onResponseHeaderEndEvent(int32_t stream_id)
{
    for( SharedHeaderInfo info : m_header_infos )
    {
        HTTP2HeaderInfo * data = info.get();

        if( data->getStreamId() == stream_id )
        {
            data->setActivedState( false );
            onResponseHeaderProcessingEvent( info );
            m_header_infos.remove( info );
            break;
        }
    }
}

void HTTP2Pipeline::onEventBaseErrorEvent(void)
{
     onEventLoopExit();
     Logger::instance().debug("onEventBaseErrorEvent", "started");
}







#ifndef GPLAYBACK_HPP
#define GPLAYBACK_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "utils/logger.hpp"

namespace AVS
{
    class GPlayback
    {
        public:
            GPlayback();
            ~GPlayback() = default;

            void initialize(int argc , char * argv[]);
            void release(void);
            void push_buffer( AlexaEvent::TransportInfo * mp3_info );
			void remove_buffer( void );
            void play(void);
            void stop(void);
            void pause(void);

            bool isPlaying(void);
            gint64 getPosition(void);
            void setPosition( gint64 pos );
            GstElement * getPipeline(void);

        protected:

             static gboolean cb_print_position ( GPlayback * instance );
             static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data);
             static AlexaEvent::TransportInfo * binary_loader( const char * filename );

        private:

             GstElement * m_pipeline;
             GstElement * m_source;
             GMainLoop  * m_loop;
			 GstBuffer  * m_last_buffer;

             bool m_state_playing;
             gint64 m_current_position;
    };
}

#endif // GPLAYBACK_HPP

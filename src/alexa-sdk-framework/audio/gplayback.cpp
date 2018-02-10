#include "audio/gplayback.hpp"

using namespace AVS;

GPlayback::GPlayback()
    : m_pipeline( nullptr ) ,
      m_source( nullptr ) ,
      m_loop( nullptr ),
      m_last_buffer( nullptr ) ,
      m_state_playing( false ) ,
      m_current_position(0)
{}

void GPlayback::initialize(int argc , char * argv[] )
{
    /*!
     * Create GStreamer Pipeline
     * \brief decoder
     */
    GstElement *decoder , *sink;
    GstBus *bus;
    guint bus_watch_id;

    gst_init( &argc , &argv );

    m_source   = gst_element_factory_make("appsrc", "source");
    decoder    = gst_element_factory_make("mad","decoder");
    sink       = gst_element_factory_make("autoaudiosink", "sink");
    m_pipeline = gst_pipeline_new("audio-pipeline");
    m_loop     = g_main_loop_new(NULL, FALSE);

    bus = gst_element_get_bus( m_pipeline );
    bus_watch_id = gst_bus_add_watch( bus , &GPlayback::bus_call , m_loop );
    gst_object_unref (bus);

    gst_bin_add_many (GST_BIN (m_pipeline), m_source, decoder , sink, NULL);
    gst_element_link_many( m_source , decoder , sink , NULL );

    m_state_playing = false;
    g_timeout_add (200, (GSourceFunc) &GPlayback::cb_print_position, this );
    g_main_loop_run( m_loop );

    /* free resources */
    gst_element_set_state (m_pipeline, GST_STATE_NULL);
    g_source_remove (bus_watch_id);
    gst_object_unref (m_pipeline);
}

void GPlayback::play(void)
{
    GstStateChangeReturn ret;

    /* Start playing */
    ret = gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (m_pipeline);
        return;
    }

    m_state_playing = true;
}

void GPlayback::release(void)
{
    g_main_loop_quit( m_loop );
}

void GPlayback::stop(void)
{
    GstStateChangeReturn ret;

    /* stop playing */
    ret = gst_element_set_state (m_pipeline, GST_STATE_READY);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (m_pipeline);
        return;
    }

    //flush pipeline - deletet all buffer maybe ...
    gst_element_send_event(GST_ELEMENT (m_pipeline) , gst_event_new_flush_start() );
    gst_element_send_event(GST_ELEMENT (m_pipeline) , gst_event_new_flush_stop(FALSE) );
    gst_element_send_event(GST_ELEMENT (m_pipeline) , gst_event_new_seek (1.0 , GST_FORMAT_TIME, static_cast< GstSeekFlags > ( GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE ) , GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0));

    m_state_playing = false;
    m_current_position = 0;
}

void GPlayback::pause(void)
{
    GstStateChangeReturn ret;

    /* Start playing */
    ret = gst_element_set_state (m_pipeline, GST_STATE_PAUSED);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (m_pipeline);
        return;
    }
}

void GPlayback::push_buffer(AlexaEvent::TransportInfo *mp3_info)
{
    GstBuffer * buffer = gst_buffer_new_allocate(NULL, mp3_info->getSize() , NULL);
    gst_buffer_fill( buffer , 0, mp3_info->get() , mp3_info->getSize() );

    /* Bind buffer to appsrc */
    gst_app_src_push_buffer( GST_APP_SRC (m_source) , buffer );
	m_last_buffer = buffer;
}

void GPlayback::remove_buffer( void )
{
	gst_buffer_remove_all_memory ( m_last_buffer );
}

gboolean GPlayback::bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
    (void) bus;
    GMainLoop *loop = (GMainLoop *) data;

    switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_EOS:
            g_print ("End of stream\n");
            g_main_loop_quit (loop);

        break;
        default:
        break;
    }

    return TRUE;
}

gboolean GPlayback::cb_print_position (GPlayback * instance )
{
  gint64 pos;

  if (gst_element_query_position ( instance->getPipeline() , GST_FORMAT_TIME, &pos) )
  {
          if( pos > instance->getPosition() )
          {
             instance->setPosition( pos );

          } else if( pos == instance->getPosition() )
          {

              stringstream stream;
              stream << "Position: " << instance->getPosition();
              Logger::instance().info( stream.str() );

              if( instance->getPosition() != 0 )
              {
                  Logger::instance().info("Playback Finished ...");
                  instance->stop();
              }
          }
  }

  /* call me again */
  return TRUE;
}

GstElement * GPlayback::getPipeline(void)
{
    return m_pipeline;
}

bool GPlayback::isPlaying(void)
{
    return m_state_playing;
}

gint64 GPlayback::getPosition(void)
{
    return m_current_position;
}

void GPlayback::setPosition(gint64 pos)
{
    m_current_position = pos;
}

AlexaEvent::TransportInfo * GPlayback::binary_loader(const char *filename)
{
    AlexaEvent::TransportInfo * info = new AlexaEvent::TransportInfo();

    FILE * fp;
    size_t file_size = 0;
    char * buffer = nullptr;

    fp = fopen( filename , "rb");
    fseek( fp , 0 , SEEK_END );
    file_size = ftell( fp );
    buffer = (char*) malloc( sizeof(char) * file_size );
    memset( buffer, 0 , file_size );

    fseek( fp , 0 , SEEK_SET );
    fread( buffer , 1 , file_size , fp );
    fclose( fp );

    info->copy( buffer , file_size );
    return info;
}

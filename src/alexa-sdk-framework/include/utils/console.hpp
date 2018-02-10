#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "stdafx.hpp"

namespace AVS
{
    class Console
    {
        public:
            Console();
            virtual ~Console();

            void initialize(void);
            void setThreadStatus( bool status );
            bool getThreadStatus(void);
            virtual void onConsoleInputEvent( char * input ) = 0;

        protected:

            static void onConsoleThread( Console * console );

        private:

            bool m_thread_status;

    };
}

#endif // CONSOLE_HPP

#ifndef TRANSFERSTATE_HPP
#define TRANSFERSTATE_HPP

#include "stdafx.hpp"

namespace Server
{
    class TransferState
    {
        public:

            enum SIG
            {
                SIG_DISCONNECT
            };

            TransferState();
            ~TransferState();

            void setActivity( bool status );
            bool isActive(void);

            void setContentSize( size_t size );
            size_t getContentSize(void);
            size_t processingMagicHeader( char * data );

            char * getStringFromEnum( SIG signal );
            size_t getSizeFromEnum( SIG signal );

        protected:
        private:

            bool m_activity;
            size_t m_content_size;

    };
}

#endif // TRANSFERSTATE_HPP

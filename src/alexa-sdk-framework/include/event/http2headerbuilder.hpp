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
#ifndef HTTP2HEADERBUILDER_HPP
#define HTTP2HEADERBUILDER_HPP

#include "stdafx.hpp"
#include "event/transport_builder_interface.hpp"

namespace AlexaEvent
{
    enum class HTTP2HeaderFlag
    {
        FLAG_WITH_CONTENT_TYPE ,
        FLAG_WITHOUT_CONTENT_TYPE
    };

    class HTTP2HeaderBuilder : public TransportBuilderInterface
    {
        public:
            HTTP2HeaderBuilder( HTTP2HeaderFlag flag );
            ~HTTP2HeaderBuilder() = default;

            void setMethode( const char * );
            void setSheme( const char * );
            void setPath( const char * );
            void setAuthorization( const char * );
            void setContentType( const char * );

            TransportInfo * buildTransportInfo(void);
            TransportHeaderInfo * buildTransportHeaderInfo(void);

         private:

            HTTP2HeaderFlag m_flag;

            char * m_methode;
            char * m_sheme;
            char * m_path;
            char * m_authorization;
            char * m_content_type;
    };
}

#endif // HTTP2HEADERBUILDER_HPP

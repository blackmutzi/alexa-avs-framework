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
#ifndef JSONHEADERBUILDER_HPP
#define JSONHEADERBUILDER_HPP

#include "stdafx.hpp"
#include "event/transport_builder_interface.hpp"

namespace AlexaEvent
{
    enum class JsonHeaderFlag
    {
        FLAG_JSON_HEADER ,
        FLAG_AUDIO_HEADER
    };

    class JsonHeaderBuilder : public TransportBuilderInterface
    {
        public:
            JsonHeaderBuilder( JsonHeaderFlag flag );
            ~JsonHeaderBuilder() = default;

            void setBoundary( const char * );

            TransportInfo * buildTransportInfo(void);
            TransportHeaderInfo * buildTransportHeaderInfo(void);

        private:

            JsonHeaderFlag m_flag;
            char * m_boundary;
    };
}

#endif // JSONHEADERBUILDER_HPP

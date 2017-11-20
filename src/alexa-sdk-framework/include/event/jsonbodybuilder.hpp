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
#ifndef JSONBODYBUILDER_HPP
#define JSONBODYBUILDER_HPP

#include "include/stdafx.hpp"
#include "include/event/transport_builder_interface.hpp"

namespace AlexaEvent
{
    enum class JsonBodyFlag
    {
        FLAG_CONTENT_FINISHED ,
        FLAG_CONTENT_NOT_FINISHED
    };

    class JsonBodyBuilder : public TransportBuilderInterface
    {
        public:
            JsonBodyBuilder( JsonBodyFlag flag );
            ~JsonBodyBuilder() = default;

            void setBoundary( TransportInfo * boundary );
            void setBody( TransportInfo * json_body_info );

            TransportInfo * buildTransportInfo(void);
            TransportHeaderInfo * buildTransportHeaderInfo(void);


        private:

            JsonBodyFlag m_flag;
            TransportInfo * m_json_body_info;
            TransportInfo * m_boundary_info;
    };
}

#endif // JSONBODYBUILDER_HPP

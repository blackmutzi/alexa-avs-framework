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
#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "include/stdafx.hpp"
#include "include/event/transport_builder_interface.hpp"
#include "include/event/jsonbodybuilder.hpp"
#include "include/event/jsonheaderbuilder.hpp"

namespace AlexaEvent
{
    enum class JsonObjectFlag
    {
        FLAG_JSON_CONTENT_ONLY ,
        FLAG_JSON_CONTENT_WITH_AUDIO
    };

    class JsonObject : public TransportBuilderInterface
    {
        public:
            JsonObject( JsonObjectFlag flag );
            ~JsonObject() = default;

            TransportInfo * merge( TransportInfo * json_head , TransportInfo * json_body );
            void setJsonContent( TransportInfo * );
            void setAudioContent( TransportInfo * );

            TransportHeaderInfo * buildTransportHeaderInfo(void);
            TransportInfo * buildTransportInfo(void);

        private:

            JsonObjectFlag m_flag;
            TransportInfo * m_json_content_info;
            TransportInfo * m_audio_content_info;

    };
}

#endif // JSONOBJECT_H

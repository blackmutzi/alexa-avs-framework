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
#include "include/event/jsonobject.hpp"

using namespace AlexaEvent;

JsonObject::JsonObject(JsonObjectFlag flag)
    : TransportBuilderInterface() , m_flag( flag )
{}

TransportInfo * JsonObject::merge( TransportInfo * json_head , TransportInfo * json_body )
{
	/*
	 *  json_head is only a string part 
	 *  json_body is a string part or a binary (audio) part 
	 */
	
    TransportInfo * transport_info = new TransportInfo();				// create transport info instance 
	size_t offset  = 0;
	size_t size    = json_head->getSize() + json_body->getSize();   	// merge size 
	char * content = new char[ size ];									// allocate new content 
	memset( content, 0 , size );										// clean allocated space 
	memcpy( content, json_head->get() , json_head->getSize() );			// add json_head to content 
	offset = json_head->getSize();										// set offset 
	memcpy( content + offset , json_body->get() , json_body->getSize());

	transport_info->set( content );										// save content ptr 
	transport_info->setSize( size );									// save content ptr size 

	// free resources 
    delete json_head;
    delete json_body;

	// return 
    return transport_info;
}

void JsonObject::setJsonContent( TransportInfo * info )
{
    m_json_content_info = info;
}

void JsonObject::setAudioContent( TransportInfo * info )
{
    m_audio_content_info = info;
}

TransportInfo * JsonObject::buildTransportInfo(void)
{
    TransportInfo * transport_info = new TransportInfo();

    if( m_flag == JsonObjectFlag::FLAG_JSON_CONTENT_ONLY )
    {
        transport_info->copy( m_json_content_info->get() , m_json_content_info->getSize() );
        delete  m_json_content_info;
    }

    if( m_flag == JsonObjectFlag::FLAG_JSON_CONTENT_WITH_AUDIO)
    {
		TransportInfo * temp_info = nullptr;										// create a null ptr transport info instance 
		temp_info = merge( m_json_content_info , m_audio_content_info );			// create transportinfo | merge | free resource ( m_json_content_info , m_audio_content_info ) 
        transport_info->copy( temp_info->get() , temp_info->getSize() );			// copy data 
		delete temp_info;													    	// delete temp_info
    }

    return transport_info;
}

TransportHeaderInfo * JsonObject::buildTransportHeaderInfo(void)
{
    return nullptr;
}

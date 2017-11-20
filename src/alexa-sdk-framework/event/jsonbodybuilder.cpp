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
#include "include/event/jsonbodybuilder.hpp"

using namespace AlexaEvent;

JsonBodyBuilder::JsonBodyBuilder(JsonBodyFlag flag)
    : TransportBuilderInterface() , m_flag( flag )
{}

void JsonBodyBuilder::setBoundary( TransportInfo * boundary_info )
{
    m_boundary_info = boundary_info;
}

void JsonBodyBuilder::setBody( TransportInfo * json_body_info )
{
    m_json_body_info = json_body_info;
}

TransportInfo * JsonBodyBuilder::buildTransportInfo(void)
{
    TransportInfo * transport_info = new TransportInfo();	   // create new transport instance 
	size_t offset    = 0;									   // set offset to default=0
    size_t max_content_size = m_json_body_info->getSize() + 3; // create new size: json_body_size + 3 bytes (\n)
	char * content = new char[ max_content_size ];   		   // allocate new json_body content
	char * byte    = new char[1];
	*byte = '\n';
	memset( content , 0 , max_content_size);				   // clear allocated space 
	memcpy( content , byte , 1 );						       // write / add  1 byte (\n) to content 
	offset++;											       // increment offset 
	memcpy( content + offset , m_json_body_info->get() , m_json_body_info->getSize() ); // write json_body_info to content 
	offset+= m_json_body_info->getSize();			           // increment offset 
	memcpy( content + offset , byte , 1);				       // write / add 1 byte (\n)
	offset++;											       // increment offset
	memcpy( content + offset , byte , 1);				       // write / add 1 byte (\n) 
	delete[] byte;
	
	transport_info->set( content );							   // save content ptr 
	transport_info->setSize( max_content_size );			   // save content size 
	
	
    if( m_flag == JsonBodyFlag::FLAG_CONTENT_FINISHED )
    {
		size_t max_size = max_content_size + m_boundary_info->getSize() + 4; 	// define new content_finished size ( +4 bytes = "----" )  
		char * content_finished = new char[ max_size ]; 						// allocate new content_finished 
		memset( content_finished , 0 , max_size );      						// clear allocated space 
		memcpy( content_finished , content , max_content_size );  				// add json_body_content 
		offset = max_content_size;												// set offset  
		delete[] content;														// delete content 
		
		// build boundary info 
		stringstream info;
        info << "--" << m_boundary_info->get() << "--" << "\0";					// build it 
		memcpy( content_finished + offset , info.str().c_str() , m_boundary_info->getSize() + 4 ); // add boundary_info to content_finished 
		
		transport_info->set( content_finished );								// save content_finished ptr
		transport_info->setSize( max_size );									// save content_finished size 
    }

	// free resources 
    delete m_json_body_info;
    delete m_boundary_info;
	
	// return transport_info 
    return transport_info;
}

TransportHeaderInfo * JsonBodyBuilder::buildTransportHeaderInfo(void)
{
    return nullptr;
}

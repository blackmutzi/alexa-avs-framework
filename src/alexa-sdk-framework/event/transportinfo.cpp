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
#include "event/transportinfo.hpp"

using namespace AlexaEvent;

TransportInfo::TransportInfo()
    : m_info( nullptr ) , m_size_info( 0 )
{}

TransportInfo::TransportInfo( const char * info )
    : m_info( (char*) info ) , m_size_info( strlen( info ) )
{}

TransportInfo::TransportInfo( const char * binary_info , size_t size )
    : m_info( (char*) binary_info ) , m_size_info( size )
{}

TransportInfo::~TransportInfo()
{
    delete[] m_info;
    m_size_info = 0;
}

TransportInfo::TransportInfo(const TransportInfo &info)
{
    copy( info.get() , info.getSize() );
}

void TransportInfo::copy( const char * data , size_t size )
{
    m_info = new char[ size + 1 ];
    m_size_info = size;
    memset( m_info , 0 , size + 1);
    memcpy( m_info , data , size );
}

void TransportInfo::set( const char * info )
{
    m_info = (char*) info;
}

void TransportInfo::setSize( size_t size )
{
    m_size_info = size;
}

const char * TransportInfo::get(void) const
{
    return m_info;
}

size_t TransportInfo::getSize(void) const
{
    return m_size_info;
}

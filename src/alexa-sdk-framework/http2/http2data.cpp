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
#include "http2/http2data.hpp"

using namespace http2;

HTTP2Data::HTTP2Data()
    : m_data( nullptr ) , m_data_size( 0 )
{}

HTTP2Data::HTTP2Data(const HTTP2Data & instance )
    : m_data( (char*) instance.get() ) , m_data_size( instance.getSize() )
{}

HTTP2Data::HTTP2Data(const char *data, size_t size)
    : m_data( (char*) data ) , m_data_size( size )
{}

HTTP2Data::~HTTP2Data()
{
    delete[] m_data;
    m_data_size = 0;
}

void HTTP2Data::set( const char * data )
{
    m_data = (char*) data;
}

void HTTP2Data::setSize(size_t size)
{
    m_data_size = size;
}

const char * HTTP2Data::get( void ) const
{
    return m_data;
}

size_t HTTP2Data::getSize(void) const
{
    return m_data_size;
}

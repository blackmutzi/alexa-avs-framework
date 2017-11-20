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
#include "include/event/transportheaderinfo.hpp"

using namespace AlexaEvent;

TransportHeaderInfo::TransportHeaderInfo(nghttp2_nv *info)
    : m_info( info )
{}

void TransportHeaderInfo::set(nghttp2_nv *info)
{
    m_info = info;
}

void TransportHeaderInfo::setSize(size_t size)
{
    m_size_info = size;
}

nghttp2_nv * TransportHeaderInfo::get(void)
{
    return m_info;
}

size_t TransportHeaderInfo::getSize(void)
{
    return m_size_info;
}

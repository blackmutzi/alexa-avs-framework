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
#ifndef REQUESTLAYER_HPP
#define REQUESTLAYER_HPP

#include "stdafx.hpp"

namespace AlexaEvent
{
    //@Abstract | @Interfaces
    class TransportBuilderInterface;
    class TransportDataInterface;

    //@TransportBuilderInterface
    class HTTP2Header;
    class JsonHeader;
    class JsonBody;
    class JsonObject;

    //@maker
    class TransportInfoMaker;
    class AudioInfoMaker;

    //@container
    class TransportHeaderInfo;
    class TransportInfo;
    class AudioInfo;

    //@Util
    class JsonBodyFactory;
}

#endif // REQUESTLAYER_HPP

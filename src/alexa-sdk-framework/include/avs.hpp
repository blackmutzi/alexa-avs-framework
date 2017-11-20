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
#ifndef AVS_HPP
#define AVS_HPP

#include "include/stdafx.hpp"
#include "transportlayer.hpp"
#include "requestlayer.hpp"
#include "directivelayer.hpp"

namespace AVS
{
    class Application;
    class DirectiveEventMaker;
    class Pipeline;
    class Controller;
    class TransportDataMaker;
    class State;
    class ConfigReader;

    namespace http2
    {}

    namespace AlexaEvent
    {}

    namespace directive
    {}
}

#endif // AVS_HPP

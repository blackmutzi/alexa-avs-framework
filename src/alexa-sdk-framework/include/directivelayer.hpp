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
#ifndef DIRECTIVELAYER_HPP
#define DIRECTIVELAYER_HPP

#include "include/stdafx.hpp"

namespace directive
{
    //@Event Class
    class DirectiveEvent;

    //@Abstract | @Interface
    class DirectiveEventCreator;
    class DirectiveEventListenerInterface;
    class DirectiveCommand;

    //@base from DirectiveEventCreator
    class DirectiveCreator;

    //@base from DirectivenEventListenerInterface
    class DirectiveServer;

    //@converter: DirectiveEvent to DirectiveCommand
    class DirectiveCommandConverter;

    //@Builtin: AVS Directive Commands
    class SpeakerSetMuteDirective;
    class SpeechRecognizeStopCaptureDirective;
    class SpeechRecognizeExpectSpeechDirective;
    class SpeechSynthesizerSpeakDirective;
}

#endif // DIRECTIVELAYER_HPP

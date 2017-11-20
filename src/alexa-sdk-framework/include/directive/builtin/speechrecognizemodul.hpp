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
#ifndef SPEECHRECOGNIZEMODUL_HPP
#define SPEECHRECOGNIZEMODUL_HPP

#include "include/stdafx.hpp"
#include "include/utils/logger.hpp"
#include "include/directive/directivemodulinterface.hpp"
#include "include/directive/directivemaker.hpp"
#include "include/nlohmann_json.hpp"
#include "include/event/requestmanager.hpp"

using namespace AVS;
namespace directive
{
    class SpeechRecognizeModul : public DirectiveModulInterface
    {
        public:
            SpeechRecognizeModul( AlexaEvent::RequestManager * requestmanager );
            ~SpeechRecognizeModul() = default;

            void onStopCaptureDirective( const Directive * directive );
            void onExpectSpeechDirective( const Directive * directive );

            DirectiveCallbackCommand * getStopCaptureCommand(void);
            DirectiveCallbackCommand * getExpectSpeechCommand(void);

        protected:

            static void onStopCaptureCallback ( void * instance );
            static void onExpectSpeechCallback( void * instance  );

        private:

            DirectiveCallbackCommand * m_stopcapture;
            DirectiveCallbackCommand * m_expectspeech;
    };
}

#endif // SPEECHRECOGNIZEMODUL_HPP

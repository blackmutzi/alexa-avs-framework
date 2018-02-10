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
#ifndef SPEECHSYNTHESIZERMODUL_HPP
#define SPEECHSYNTHESIZERMODUL_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "directive/directivemodulinterface.hpp"
#include "directive/directivemaker.hpp"
#include "event/transportinfo.hpp"
#include "nlohmann_json.hpp"
#include "audio/playback.hpp"
#include "audio/gplayback.hpp"
#include "event/requestmanager.hpp"

namespace directive
{
    class SpeechSynthesizerModul : public DirectiveModulInterface
    {
        public:
            SpeechSynthesizerModul( AlexaEvent::RequestManager * requestmanager );
            ~SpeechSynthesizerModul() = default;

            void onSpeakDirective( const Directive * directive );

            DirectiveCallbackCommand * getSpeak(void);

		protected:

			static void PlaybackThread( AVS::GPlayback * instance );
            static void onSpeakDirectiveCallback( void * instance );
            void onPlayAlexa( TransportInfo * audio_info , std::string token );

        private:

            DirectiveCallbackCommand * m_speak;
			AVS::GPlayback * m_gplayback;
			
    };
}

#endif // SPEECHSYNTHESIZERMODUL_HPP

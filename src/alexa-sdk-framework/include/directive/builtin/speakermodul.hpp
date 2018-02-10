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
#ifndef SPEAKERMODUL_HPP
#define SPEAKERMODUL_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "directive/directivemodulinterface.hpp"
#include "directive/directivemaker.hpp"
#include "nlohmann_json.hpp"
#include "event/requestmanager.hpp"

using namespace AVS;
namespace directive
{
    using json = nlohmann::json;

    class SpeakerModul : public DirectiveModulInterface
    {
        public:
            SpeakerModul( AlexaEvent::RequestManager * requestmanager );
            ~SpeakerModul() = default;

            DirectiveCallbackCommand * getSetVolume(void);
            DirectiveCallbackCommand * getAdjustVolume(void);
            DirectiveCallbackCommand * getSetMute(void);

            void onSetVolumeDirective( const Directive * );
            void onAdjustVolumeDirective( const Directive * );
            void onSetMuteDirective( const Directive * );

        protected:

            static void onSetVolumeCallback( void * instance );
            static void onAdjustVolumeCallback( void * instance );
            static void onSetMuteCallback( void * instance );

        private:

            DirectiveCallbackCommand * m_setvolume;
            DirectiveCallbackCommand * m_adjustvolume;
            DirectiveCallbackCommand * m_setmute;

    };
}

#endif // SPEAKERMODUL_HPP

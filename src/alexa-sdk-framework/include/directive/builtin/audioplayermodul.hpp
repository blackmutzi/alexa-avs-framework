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
#ifndef AUDIOPLAYERMODUL_HPP
#define AUDIOPLAYERMODUL_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "directive/directivemaker.hpp"
#include "directive/directivemodulinterface.hpp"
#include "event/requestmanager.hpp"

namespace directive
{
    class AudioPlayerModul : public DirectiveModulInterface
    {
        public:
            AudioPlayerModul( AlexaEvent::RequestManager * requestmanager );
            ~AudioPlayerModul() = default;

            DirectiveCallbackCommand * getPlay(void);
            DirectiveCallbackCommand * getStop(void);
            DirectiveCallbackCommand * getClearQueue(void);

            void onPlayDirective( const Directive * directive );
            void onStopDirective( const Directive * directive );
            void onClearQueueDirective( const Directive * directive );

        protected:

            static void onPlayCallback( void * instance );
            static void onStopCallback( void * instance );
            static void onClearQueueCallback( void * instance );

        private:

            DirectiveCallbackCommand * m_play;
            DirectiveCallbackCommand * m_stop;
            DirectiveCallbackCommand * m_clearqueue;
    };
}

#endif // AUDIOPLAYERMODUL_HPP

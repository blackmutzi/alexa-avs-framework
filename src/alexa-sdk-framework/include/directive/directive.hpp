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
#ifndef DIRECTIVE_HPP
#define DIRECTIVE_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"

namespace directive
{
    /*!
     * \brief The DirectiveType class
     * avs indentification for directive classes
     * token as directive namespace name
     * value as directive name
     */
    class DirectiveType
    {
        public:
            DirectiveType() = default;
            DirectiveType( const char * token , const char * value );
            ~DirectiveType();

            void setToken( const char * token );
            void setValue( const char * value );

            const char * getToken(void) const;
            const char * getValue(void) const;

        private:

            const char * m_token;
            const char * m_value;
    };

    /*!
     * \brief The Directive class
     * contain response directive data from avs-amazon-server
     *
     * directivetype as identification ( directive namespace name , directive name )
     * jsonInfo  as json response content
     * audioInfo as audio response content (binary)
     *
     */
    class Directive
    {
        public:
            Directive();
            ~Directive();

            /*!
             * save directivetype instance
             * \brief setDirectiveType
             * \param type
             */
            void setDirectiveType( DirectiveType * type );

            /*!
             * save transportinfo instance as json content
             * \brief setJsonInfo
             * \param json_info
             */
            void setJsonInfo( AlexaEvent::TransportInfo * json_info );

            /*!
             * save transportinfo instance as audio content
             * \brief setAudioInfo
             * \param audio_info
             */
            void setAudioInfo( AlexaEvent::TransportInfo * audio_info );
            void setAudioInfoStatus( bool status );

            /*!
             * return true if audio transportinfo instance is set
             * \brief hasAudioInfo
             * \return
             */
            bool hasAudioInfo(void) const;

            /*!
             * return saved directivetype instance
             * \brief getDirectiveType
             * \return
             */
            DirectiveType * getDirectiveType(void) const;
            /*!
             * return saved transportinfo instance ( json )
             * \brief getJsonInfo
             * \return
             */
            AlexaEvent::TransportInfo * getJsonInfo(void) const;

            /*!
             * return saved transportinfo instance ( audio )
             * \brief getAudioInfo
             * \return
             */
            AlexaEvent::TransportInfo * getAudioInfo(void) const;

         protected:

            bool m_has_audio_info;
            DirectiveType * m_directive_type;
            AlexaEvent::TransportInfo * m_json_info;
            AlexaEvent::TransportInfo * m_audio_info;
    };
}

#endif // DIRECTIVE_HPP

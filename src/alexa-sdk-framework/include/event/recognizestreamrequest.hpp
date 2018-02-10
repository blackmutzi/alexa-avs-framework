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
#ifndef RECOGNIZESTREAMREQUEST_HPP
#define RECOGNIZESTREAMREQUEST_HPP

#include "stdafx.hpp"
#include "event/transportdatainterface.hpp"
#include "event/jsonobject.hpp"
#include "event/http2headerpost.hpp"

namespace AlexaEvent
{
    /*!
     * \brief The RecognizeStreamRequest class
     *  @see EventStreamRequest class
     *
     *  + set a recognize json-event
     *  + and set binary-audio-data
     */
    class RecognizeStreamRequest : public TransportDataInterface
    {
        public:
            RecognizeStreamRequest() = default;
            ~RecognizeStreamRequest() = default;

            /*!
             * set a access token
             * \brief setAccessToken
             * \param access_token
             */
            void setAccessToken( const char * access_token );

            /*!
             * set a boundary
             * \brief setBoundary
             * \param boundary
             */
            void setBoundary( const char * boundary );

            /*!
             * set a transportinfo as speech-recognize json-event
             * @see EventSpeechRecognizeModul
             * \brief setRecognizeJson
             * \param json_info
             */
            void setRecognizeJson( TransportInfo * json_info );

            /*!
             * set a transportinfo as recorded binary-audio-data
             * @see EventSpeechRecognizeModul
             * \brief setAudioInfo
             * \param audio_info
             */
            void setAudioInfo( TransportInfo * audio_info );

            /*!
             * final, build http2transportdata instance
             * \brief buildTransportData
             * \return
             */
            http2::SharedTransportData buildTransportData( void );

        private:

            char * m_access_token;
            char * m_boundary;
            TransportInfo * m_audio_info;
            TransportInfo * m_recognize_json;

    };
}

#endif // RECOGNIZESTREAMREQUEST_HPP

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
#ifndef TRANSPORTMAKER_H
#define TRANSPORTMAKER_H

#include "include/event/transport_builder_interface.hpp"
#include "include/event/http2headerpost.hpp"
#include "include/event/http2headerget.hpp"
#include "include/event/jsonheaderbuilder.hpp"
#include "include/event/jsonbodybuilder.hpp"
#include "include/event/jsonobject.hpp"

namespace AlexaEvent
{
    /*!
     * \brief The TransportMaker class
     * is a multipart http2 header and body maker
     */
    class TransportMaker
    {
        public:
            TransportMaker() = default;
            ~TransportMaker() = default;

            /*!
             * build the final transportinfo instance
             * \brief createTransportInfo
             * \param maker
             * \return TransportInfo instance
             */
            TransportInfo * createTransportInfo( TransportBuilderInterface * maker );

            /*!
             * build the final transportheaderinfo instance
             * \brief createTransportHeaderInfo
             * \param maker
             * \return TransportHeaderInfo instance
             */
            TransportHeaderInfo * createTransportHeaderInfo( TransportBuilderInterface * maker );

            /*!
             * build the final json header part
             * \brief createJsonHeaderInfo
             * \param boundary @see Controller
             * \return TransportInfo instance as json_header
             */
            TransportInfo * createJsonHeaderInfo( const char * boundary );

            /*!
             * build the final json audio header part
             * \brief createAudioHeaderInfo
             * \param boundary @see Controller
             * \return TransportInfo instance as json_audio_header
             */
            TransportInfo * createAudioHeaderInfo( const char * boundary );

            /*!
             * convert a boundary to a transportinfo instance
             * \brief createBoundaryInfo
             * \param boundary @see Controller
             * \return TransportInfo instance as boundary_info
             */
            TransportInfo * createBoundaryInfo( const char * boundary );

            /*!
             * build a json body part (multipart end)
             * \brief createJsonBodyContentFinished
             * \param json_content @see EventModulManager
             * \param boundary @see Controller
             * \return TransportInfo instance as json_body (flag: multipart end )
             */
            TransportInfo * createJsonBodyContentFinished( TransportInfo * json_content , const char * boundary );

            /*!
             * build a json body part ( multipart not end )
             * \brief createJsonBodyContentNotFinished
             * \param json_content @see EventModulManager
             * \param boundary @see Controller
             * \return TransportInfo instance as json_body ( flag: multipart not end )
             */
            TransportInfo * createJsonBodyContentNotFinished( TransportInfo * json_content , const char * boundary );

            /*!
             * build the final json object without binary-audio-data
             *
             * 1. Json Part
             * //////////////////////////////////
             * /// include json_header        ///
             * //////////////////////////////////
             *
             * ///////////////////////////////////////////
             * /// include json_body                   ///
             * ///    ||-> include json_content        ///
             * ///////////////////////////////////////////
             *
             * # Multipart End
             *
             * \brief createJsonObjectInfo
             * \param json_content @see EventModulManager
             * \param boundary @see Controller
             * \return TransportInfo instance as http2_multipart_json_object | @see HTTP2TransportData class
             */
            TransportInfo * createJsonObjectInfo( TransportInfo * json_content , const char * boundary );

            /*!
             * build the final json object with binary-audio-data
             *
             * 1. Json Part
             * //////////////////////////////////
             * /// include json_header        ///
             * //////////////////////////////////
             *
             * ////////////////////////////////////////////////////
             * /// include json_body (flag: multipart not end ) ///
               ///    ||-> include json_content                 ///
             * ////////////////////////////////////////////////////
             *
             * 2. Audio Part
             * //////////////////////////////////
             * /// include json_audio_header  ///
             * //////////////////////////////////
             *
             * /////////////////////////////////
             * /// include audio_content     ///
             * /////////////////////////////////
             *
             * # Multipart End
             *
             * \brief createJsonObjectInfo
             * \param json_content  @see EventModulManager
             * \param audio_content @see Recorder
             * \param boundary      @see Controller
             * \return TransportInfo instance as http2_multipart_json_object | @see HTTP2TransportData class
             */
            TransportInfo * createJsonObjectInfo( TransportInfo * json_content , TransportInfo * audio_content , const char *boundary );

            /*!
             * build the final Multipart HTTP2 Header ( method=POST )
             * \brief createHTTP2HeaderPostInfo
             * \param access_token @see Controller
             * \param endpoint @see alexa-avs-endpoints ( /v20160207/events )
             * \param boundary @see Controller
             * \return TransportHeaderInfo instance as http2_multipart_header | @see HTTP2TransportData class
             */
            TransportHeaderInfo * createHTTP2HeaderPostInfo( const char * access_token , const char * endpoint , const char * boundary );

            /*!
             * build final Multipart HTTP2 Header ( method=GET )
             * => is for alexa-avs-downchannel http2_header
             * \brief createHTTP2HeaderGetInfo
             * \param access_token @see Controller
             * \param endpoint @see alexa-avs-endpoints ( /v20160207/directives )
             * \return TransportHeaderInfo instance as http2_mulitpart_header @see HTTP2TransportData class
             */
            TransportHeaderInfo * createHTTP2HeaderGetInfo( const char * access_token , const char * endpoint );
    };
}

#endif // TRANSPORTMAKER_H

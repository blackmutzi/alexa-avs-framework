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
#ifndef HTTPINTERFACE_HPP
#define HTTPINTERFACE_HPP

#include "include/stdafx.hpp"
#include "include/auth/httpresponse.hpp"

namespace Auth
{
    /*!
     * \brief The HTTPInterface class
     *  make a connection to any http(s) url and send only post data
     *  @Library: Libcurl
     */
    class HTTPInterface
    {
        public:
             HTTPInterface( HTTPResponse * response_instance );
             ~HTTPInterface();

             /*!
              * set http(s) url
              * \brief setUrl
              * \param url
              */
             void setUrl( std::string url );
             /*!
              * set post data
              * \brief setPostData
              * \param data
              */
             void setPostData( std::string data );
             /*!
              * set http header data
              * \brief setHeaderData
              * \param data
              */
             void setHeaderData( std::string data );
             /*!
              * connect to server
              * \brief perform
              */
             void perform( void );

             /*!
              * return response data
              * \brief getResponse
              * \return HTTPResponse*
              */
             HTTPResponse * getResponse(void);

        protected:

             static size_t writeResponseData( void * contents , size_t size , size_t memb , void * user_response_instance );

             CURL * m_curl_instance;

             HTTPResponse * m_http_response;
    };
}

#endif // HTTPINTERFACE_HPP

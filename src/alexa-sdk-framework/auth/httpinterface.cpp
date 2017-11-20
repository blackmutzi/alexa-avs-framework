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
#include "include/auth/httpinterface.hpp"

using namespace Auth;

HTTPInterface::HTTPInterface( HTTPResponse * response_instance )
    : m_curl_instance( nullptr ) ,
      m_http_response( response_instance )
{
    curl_global_init(CURL_GLOBAL_ALL);

    if( m_curl_instance == nullptr )
            m_curl_instance = curl_easy_init();


    response_instance->set( (char*) malloc(1) );

    /* Response Setup here ..*/
    curl_easy_setopt( m_curl_instance, CURLOPT_WRITEFUNCTION, &HTTPInterface::writeResponseData );

    curl_easy_setopt( m_curl_instance  , CURLOPT_WRITEDATA, response_instance );
}

HTTPInterface::~HTTPInterface()
{
    delete m_http_response;
}

HTTPResponse * HTTPInterface::getResponse()
{
    return m_http_response;
}

void HTTPInterface::perform(void)
{
    CURLcode res;
    res = curl_easy_perform(m_curl_instance);
    curl_easy_cleanup( m_curl_instance );
    curl_global_cleanup();
}

void HTTPInterface::setUrl(string url)
{
    curl_easy_setopt( m_curl_instance , CURLOPT_URL, url.c_str() );
    curl_easy_setopt( m_curl_instance , CURLOPT_VERBOSE, 1L);
    curl_easy_setopt( m_curl_instance , CURLOPT_SSL_VERIFYPEER , false );
    curl_easy_setopt( m_curl_instance , CURLOPT_SSL_VERIFYHOST , 2 );
}

void HTTPInterface::setHeaderData(string header_data )
{
    struct curl_slist * m_header_content = NULL;

    m_header_content = curl_slist_append( m_header_content , header_data.c_str() );

    curl_easy_setopt( m_curl_instance , CURLOPT_HTTPHEADER , m_header_content );
}

void HTTPInterface::setPostData(string post_data)
{
    const char * origin_post_data = post_data.c_str();

    curl_easy_setopt(m_curl_instance , CURLOPT_POST, 1);
    curl_easy_setopt(m_curl_instance , CURLOPT_POSTFIELDSIZE, (long) strlen( origin_post_data ) );
    curl_easy_setopt(m_curl_instance , CURLOPT_POSTFIELDS, origin_post_data );
}

size_t HTTPInterface::writeResponseData(void *contents, size_t size, size_t nmemb, void *user_response_instance)
{
    size_t realsize = size * nmemb;
    HTTPResponse * origin_response = (HTTPResponse *) user_response_instance;

    char * memory = (char*) realloc( (char*) origin_response->get() , realsize + 1 );

    memset( memory , 0 , realsize + 1);
    memcpy( memory , contents , realsize );

    origin_response->set( memory );
    origin_response->setSize( realsize + 1 );

    return realsize;
}

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
#ifndef AUTHINFO_HPP
#define AUTHINFO_HPP

#include "stdafx.hpp"

namespace Auth
{
    /*!
     * \brief The AuthInfo class
     *  contains important data to connect Amazon API
     */
    class AuthInfo
    {
        public:
             AuthInfo() = default;
             ~AuthInfo() = default;

             /*!
              * \brief Amazon Login Link
              *
              *  important for login link is
              *  client_id , client_secret , product_name
              *  and redirect_uri
              *
              *  after Login get the code_grant
              *  with code_grant get refresh_token and with
              *  refresh_token get access_token.
              */
             void setClientId( std::string id );
             void setClientSecret( std::string secret);
             void setProductName( std::string name);
             void setRedirectUri( std::string uri);
             void setCodeGrant( std::string code);
             void setRefreshToken( std::string token );
             void setRefreshTokenValidStatus( bool status );

             std::string getClientId(void) const;
             std::string getClientSecret(void) const;
             std::string getProductName(void) const;
             std::string getRedirectUri(void) const;
             std::string getCodeGrant(void) const;
             std::string getRefreshToken(void) const;

             bool isRefreshTokenValid(void) const;

        private:

            std::string m_client_id;
            std::string m_client_secret;
            std::string m_code_grant;
            std::string m_product_name;
            std::string m_redirect_uri;
            std::string m_refresh_token;

            bool m_valid_refresh_token;
    };
}

#endif // AUTHINFO_HPP

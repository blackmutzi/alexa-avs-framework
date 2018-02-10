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
#include "auth/authinfo.hpp"

using namespace Auth;

void AuthInfo::setClientId(string id)
{
    m_client_id = id;
}

void AuthInfo::setClientSecret(string secret)
{
    m_client_secret = secret;
}

void AuthInfo::setProductName(string name)
{
    m_product_name = name;
}

void AuthInfo::setRedirectUri(string uri)
{
    m_redirect_uri = uri;
}

void AuthInfo::setCodeGrant(string code)
{
    m_code_grant = code;
}

void AuthInfo::setRefreshToken(string token)
{
    m_refresh_token = token;
}

void AuthInfo::setRefreshTokenValidStatus(bool status)
{
    m_valid_refresh_token = status;
}

std::string AuthInfo::getClientId(void) const
{
    return m_client_id;
}

std::string AuthInfo::getClientSecret(void) const
{
    return m_client_secret;
}

std::string AuthInfo::getProductName(void) const
{
    return m_product_name;
}

std::string AuthInfo::getRedirectUri(void) const
{
    return m_redirect_uri;
}

std::string AuthInfo::getCodeGrant(void) const
{
    return m_code_grant;
}

std::string AuthInfo::getRefreshToken(void) const
{
    return m_refresh_token;
}

bool AuthInfo::isRefreshTokenValid(void) const
{
    return m_valid_refresh_token;
}

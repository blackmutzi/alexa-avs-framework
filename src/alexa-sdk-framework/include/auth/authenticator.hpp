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
#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include "include/stdafx.hpp"
#include "include/utils/logger.hpp"
#include "include/auth/authinfo.hpp"
#include "include/auth/httppipeline.hpp"
#include "include/nlohmann_json.hpp"
#include "include/event/jsonfileloader.hpp"

using namespace AVS;

namespace Auth
{
    /*!
     * \brief The Authenticator class
     *
     * Connected to Amazon API
     * @API: https://api.amazon.com/auth/o2/token
     *
     */
    class Authenticator
    {
        public:

            using json = nlohmann::json;

            Authenticator();
            ~Authenticator() = default;

            /*!
             * read json_config_file and fill information
             * into the authinfo
             *
             * \brief createAuthInfo
             * \param auth_info
             * \param json_config_file
             */
            void createAuthInfo( AuthInfo * auth_info , std::string json_config_file );

            /*!
             * validate auth_info informations
             * \brief validateAuthInfo
             * \param auth_info
             * \return
             */
            bool validateAuthInfo( AuthInfo * auth_info );

            /*!
             * Build a Amazon Login Link
             * \brief createAmazonLoginLink
             * \param auth_info
             * \return
             */
            std::string createAmazonLoginLink( AuthInfo * auth_info );

            /*!
             * connect to amazon api and get a refresh_token by auth_info informations
             * mandatory: code grant
             *
             * \brief getRefreshToken
             * \param auth_info
             * \return
             */
            std::string getRefreshToken( AuthInfo * auth_info  ) throw( std::exception );

            /*!
             * connect to amazon api and get a access_token by auth_info informations
             * mandatory: refresh_token
             *
             * \brief getAccessToken
             * \param auth_info
             * \return
             */
            std::string getAccessToken( AuthInfo * auth_info  ) throw (std::exception);

            /*!
             * write config file new
             * \brief writeToFile
             * \param auth_info
             * \param json_config_file
             */
            void writeToFile( AuthInfo * auth_info , std::string json_config_file );

        protected:

            /*!
             * build post data for amazon api
             * \brief createRefreshTokenPostData
             * \param auth_info
             * \return
             */
            std::string createRefreshTokenPostData( AuthInfo * auth_info );

            /*!
             * build post data for amazon api
             * \brief createAccessTokenPostData
             * \param auth_info
             * \return
             */
            std::string createAccessTokenPostData( AuthInfo * auth_info );

            /*!
             * \brief validateCodeGrant
             * \param auth_info
             * \return
             */
            bool validateCodeGrant( AuthInfo * auth_info );

        private:

            void replace(string &str, string search, string replace);

            std::string m_api_amazon_url;
            std::string m_current_config;

    };
}

#endif // AUTHENTICATOR_HPP

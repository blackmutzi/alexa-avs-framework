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
#include "auth/authenticator.hpp"

using namespace Auth;

Authenticator::Authenticator()
    : m_api_amazon_url( std::string("https://api.amazon.com/auth/o2/token") ) ,
      m_current_config( std::string("") )
{}

void Authenticator::createAuthInfo( AuthInfo * auth_info , string json_config_file )
{
    m_current_config = json_config_file;

    json json_content;
    AlexaEvent::JsonFileLoader reader( json_config_file );

    reader.load();
    json_content = json::parse( reader.getJsonObject() );

    try{

        auth_info->setClientId( json_content["client_id"] );
        auth_info->setClientSecret( json_content["client_secret"] );
        auth_info->setProductName( json_content["product_id"] );
        auth_info->setRedirectUri( json_content["redirect_uri"] );

        auth_info->setCodeGrant( json_content["code_grant"] );
        auth_info->setRefreshToken( json_content["refresh_token"] );

    }catch( std::exception e )
    {
        Logger::instance().error("[CONFIG] corrupted config ");
    }

}

void Authenticator::writeToFile( AuthInfo * auth_info , string json_config_file )
{
    AlexaEvent::JsonFileLoader loader( json_config_file );
    json json_content;

    loader.load();
    json_content = json::parse( loader.getJsonObject() );

    json_content["client_id"]     = auth_info->getClientId();
    json_content["client_secret"] = auth_info->getClientSecret();
    json_content["product_id"]    = auth_info->getProductName();
    json_content["redirect_uri"]  = auth_info->getRedirectUri();
    json_content["code_grant"]    = auth_info->getCodeGrant();
    json_content["refresh_token"] = auth_info->getRefreshToken();

    ofstream stream( json_config_file );
    stream << json_content;
    stream.close();
}

bool Authenticator::validateCodeGrant( AuthInfo * auth_info )
{
    bool valid = true;

    if( auth_info->getCodeGrant().empty() )
    {
        Logger::instance().info("[CONFIG] Hello AVS User, go to this Amazon Login Page.");
        Logger::instance().info(" ---- ");
        Logger::instance().info( createAmazonLoginLink( auth_info ) );
        Logger::instance().info(" ---- ");
        Logger::instance().info("[CONFIG] And COPY the CODE GRANT into the CONFIG. Default /etc/alexa/config.json ");

        valid = false;
    }

    return valid;
}

bool Authenticator::validateAuthInfo( AuthInfo * auth_info )
{
    bool valid = false;

    if( !auth_info->getClientId().empty() && !auth_info->getClientSecret().empty()
                                          && !auth_info->getRedirectUri().empty() )
    {
        if( valid = validateCodeGrant( auth_info ) )
        {
            if( auth_info->getRefreshToken().empty() )
            {
                try{

                Logger::instance().warn("--- try to create a new refresh token ---" );
                auth_info->setRefreshToken( getRefreshToken( auth_info ) );
                writeToFile( auth_info , m_current_config );

                }catch( std::exception e)
                {
                    //Refresh Token Exception
                    valid = false;
                }
            }
       }
    }

    return valid;
}

std::string Authenticator::getRefreshToken( AuthInfo *auth_info ) throw( std::exception )
{
    HTTPResponse * response = nullptr;
    std::string error_description = "";
    std::string error = "";
    std::string refresh_token = "";
    std::string post_data = createRefreshTokenPostData( auth_info );
    json json_content;


    HTTPPipeline pipeline;
    pipeline.setUrl( m_api_amazon_url );
    pipeline.setHeaderData("Content-Type: application/x-www-form-urlencoded");
    pipeline.setPostData( post_data );
    pipeline.perform();

    response = pipeline.getResponse();
    json_content = json::parse( response->get() );

    try{

        refresh_token  = json_content["refresh_token"];

    }catch( std::exception e ) {

        // refresh_token string is null ( not found )
        error_description = json_content["error_description"];
        error             = json_content["error"];

        if( !error_description.empty() )
        {
            // HTTP/1.1 400 Bad Request - Exception
            string invalid = "invalid_grant";

            if( error == invalid )
            {
                auth_info->setCodeGrant("");
                writeToFile( auth_info , m_current_config );
                Logger::instance().exception("invalid grant code");

            } else {
                Logger::instance().exception( error );
            }
        }
    }

    return refresh_token;
}


std::string Authenticator::getAccessToken(AuthInfo *auth_info) throw( std::exception )
{
    HTTPResponse * response = nullptr;
    std::string error_description = "";
    std::string error             = "";
    std::string access_token      = "";
    std::string refresh_token     = "";
    std::string post_data         = createAccessTokenPostData( auth_info );
    json json_content;

    HTTPPipeline pipeline;
    pipeline.setUrl( m_api_amazon_url );
    pipeline.setHeaderData("Content-Type: application/x-www-form-urlencoded");
    pipeline.setPostData( post_data );
    pipeline.perform();

    response = pipeline.getResponse();
    json_content = json::parse( response->get() );

    try
    {
        access_token  = json_content["access_token"];
        refresh_token = json_content["refresh_token"];

        auth_info->setRefreshToken( refresh_token );
        writeToFile( auth_info , m_current_config );

    } catch ( std::exception e )
    {
        // access_token string is null ( not found )
        error_description = json_content["error_description"];
        error             = json_content["error"];

        if( !error_description.empty() )
        {
           // HTTP/1.1 400 Bad Request
           auth_info->setRefreshToken("");
           writeToFile( auth_info , m_current_config );
           Logger::instance().exception( error );
        }
    }

    return access_token;
}

std::string Authenticator::createAmazonLoginLink(AuthInfo *auth_info)
{
    // Generate Amazon Login Link
    // https://www.amazon.com/ap/oa?client_id=${CLIENT_ID}&scope=${SCOPE}&scope_data=${SCOPE_DATA}&response_type=code&redirect_uri=https://localhost:3000/authresponse
    stringstream login_link;
    std::string amazon_link;
    std::string scope = "alexa:all";
    std::string scope_data = "{\"${SCOPE}\": {\"productID\": \"${PRODUCT_ID}\",\"productInstanceAttributes\": {\"deviceSerialNumber\": \"${DEVICE_SERIAL_NUMBER}\"}}}";

    replace( scope_data , "${SCOPE}" , scope );
    replace( scope_data , "${PRODUCT_ID}" , auth_info->getProductName() );
    replace( scope_data , "${DEVICE_SERIAL_NUMBER}", "12345");

    login_link << "https://www.amazon.com/ap/oa?";
    login_link << "client_id=" << auth_info->getClientId() ;
    login_link << "&scope=" << scope;
    login_link << "&scope_data=" << scope_data;
    login_link << "&response_type=code";
    login_link << "&redirect_uri=" << auth_info->getRedirectUri();
    login_link << '\0';

    amazon_link = login_link.str();
    return amazon_link;
}

std::string Authenticator::createRefreshTokenPostData( AuthInfo * auth_info )
{
    std::string post_data;
    stringstream req_post_data;

    req_post_data << "grant_type=authorization_code";
    req_post_data << "&code=" << auth_info->getCodeGrant() ;
    req_post_data << "&client_id=" << auth_info->getClientId();
    req_post_data << "&client_secret=" << auth_info->getClientSecret();
    req_post_data << "&redirect_uri=" << auth_info->getRedirectUri();
    req_post_data << '\0';

    post_data = req_post_data.str();
    return post_data;
}

std::string Authenticator::createAccessTokenPostData(AuthInfo *auth_info)
{
    std::string post_data;
    stringstream req_post_data;

    req_post_data << "grant_type=refresh_token";
    req_post_data << "&refresh_token=" << auth_info->getRefreshToken();
    req_post_data << "&client_id=" << auth_info->getClientId();
    req_post_data << "&client_secret=" << auth_info->getClientSecret();
    req_post_data << '\0';

    post_data = req_post_data.str();
    return post_data;
}

void Authenticator::replace(string &str, string search, string replace)
{
    if( search.empty() )
           return;

    size_t start_pos = 0;

    while((start_pos = str.find( search , start_pos)) != std::string::npos) {
           str.replace(start_pos, search.length(),  replace );
           start_pos += replace.length();
    }
}

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
#include "directive/directive.hpp"

using namespace directive;

DirectiveType::DirectiveType( const char *token, const char *value)
    : m_token(nullptr) , m_value(nullptr)
{
    setToken( token );
    setValue( value );
}

DirectiveType::~DirectiveType()
{
	delete[] m_token;
	delete[] m_value;
}

void DirectiveType::setToken( const char *token)
{
    size_t size = strlen( token );
    char * new_token = new char[ size + 1];
    memset( new_token , 0 , size + 1);
    strncpy( new_token , token , size );
    m_token = new_token;
}

void DirectiveType::setValue( const char * value )
{
    size_t size = strlen( value );
    char * new_value = new char[ size + 1];
    memset( new_value, 0 , size + 1);
    strncpy( new_value , value , size );
    m_value = new_value;
}

const char * DirectiveType::getToken(void) const
{
    return m_token;
}

const char * DirectiveType::getValue(void) const
{
    return m_value;
}

Directive::Directive()
    : m_has_audio_info(false)
{}

Directive::~Directive()
{
    delete m_directive_type;
}

void Directive::setDirectiveType(DirectiveType *type)
{
    m_directive_type = type;
}

void Directive::setJsonInfo(AlexaEvent::TransportInfo *json_info)
{
    m_json_info = json_info;
}

void Directive::setAudioInfo(AlexaEvent::TransportInfo *audio_info)
{
    m_has_audio_info = true;
    m_audio_info = audio_info;
}

void Directive::setAudioInfoStatus( bool status )
{
    m_has_audio_info = status;
}

bool Directive::hasAudioInfo(void) const
{
    return m_has_audio_info;
}

DirectiveType * Directive::getDirectiveType(void) const
{
    return m_directive_type;
}

AlexaEvent::TransportInfo * Directive::getJsonInfo(void) const
{
    return m_json_info;
}

AlexaEvent::TransportInfo * Directive::getAudioInfo(void) const
{
    return m_audio_info;
}









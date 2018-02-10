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
#include "utils/logger.hpp"

using namespace AVS;

Logger * Logger::m_instance = nullptr;

Logger::Logger()
    : m_loglevel_info("INFO") ,
      m_loglevel_warn("WARNING") ,
      m_loglevel_error("ERROR") ,
      m_loglevel_debug("DEBUG") ,
      m_loglevel_bug("BUG") ,
      m_loglevel_exception("EXCEPTION") ,
      m_verbose_mode( false )
{}

Logger & Logger::instance()
{
    if( m_instance == nullptr )
            m_instance = new Logger();

    return *m_instance;
}

void Logger::verboseMode(bool mode)
{
    m_verbose_mode = mode;
}

void Logger::info(string message)
{
    createLogMessage( m_loglevel_info , message );
}

void Logger::warn(string message)
{
    if( m_verbose_mode )
            createLogMessage( m_loglevel_warn , message );
}

void Logger::error(string message)
{
    createLogMessage( m_loglevel_error , message );
    exit(0);
}

void Logger::exception(string message) throw( std::exception )
{
    createLogMessage( m_loglevel_exception , message );
    throw std::exception();
}

void Logger::debug(string debug_tag, string message)
{
    stringstream stream;
    stream << "[ " << debug_tag << " ] ";
    stream << message;

    if( m_verbose_mode )
          createLogMessage( m_loglevel_debug , stream.str() );
}

void Logger::bug(string bug_tag, string message)
{
    stringstream stream;
    stream << "[ " << bug_tag << " ] ";
    stream << message;

    if( m_verbose_mode )
            createLogMessage( m_loglevel_bug , stream.str() );
}

void Logger::createLogMessage(string log_level, string log_message)
{
    stringstream stream_message;
    stream_message << "[ " << log_level << " ] ";
    stream_message << log_message;

    std::cout << stream_message.str() << std::endl;
}







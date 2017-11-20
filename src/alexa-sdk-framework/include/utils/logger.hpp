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
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "include/stdafx.hpp"

namespace AVS
{
    class Logger
    {
        public:

            static Logger & instance(void);
            void verboseMode( bool mode );

            void info ( std::string message );
            void warn ( std::string message );
            void error( std::string message  );
            void exception( std::string message ) throw( std::exception );
            void debug( std::string debug_tag , std::string message );
            void bug( std::string bug_tag , std::string message );


        protected :

            void createLogMessage( std::string log_level , std::string log_message );

        private:
            Logger();
            Logger( const Logger & ){}
            Logger& operator = ( const Logger & ){ return *this; }
            ~Logger() = default;

            static Logger * m_instance;

            std::string m_loglevel_info;
            std::string m_loglevel_warn;
            std::string m_loglevel_error;
            std::string m_loglevel_debug;
            std::string m_loglevel_bug;
            std::string m_loglevel_exception;

            bool m_verbose_mode;
    };
}

#endif // LOGGER_HPP

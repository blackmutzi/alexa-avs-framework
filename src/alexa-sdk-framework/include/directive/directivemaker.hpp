#ifndef DIRECTIVEMAKER_HPP
#define DIRECTIVEMAKER_HPP

#include "include/stdafx.hpp"
#include "include/utils/logger.hpp"
#include "include/directive/directive.hpp"
#include "include/directive/directivecommand.hpp"

namespace directive
{

/*!
 * \brief The DirectiveMaker class
 * make directive instance and directivetype instance
 */
class DirectiveMaker
{
    public:
        DirectiveMaker() = default;
        ~DirectiveMaker() = default;

        /*!
         * create directivetype instance
         * \brief createDirectiveType
         * \param token as directive namespace name
         * \param value as directive name
         * \return
         */
        DirectiveType * createDirectiveType( const char * token , const char * value );

        /*!
         * create directive instance
         * \brief createDirective
         * \param type
         * \param json_info
         * \param audio_info
         * \return
         */
        Directive * createDirective( DirectiveType * type , AlexaEvent::TransportInfo * json_info , AlexaEvent::TransportInfo * audio_info = nullptr );


        /*!
         * \brief createDirectiveCallbackCommand
         * \param type
         * \param callback
         * \param instance
         * \return
         */
        DirectiveCallbackCommand * createDirectiveCallbackCommand( DirectiveType * type , DirectiveCallback callback , void * instance );

};


}

#endif // DIRECTIVEMAKER_HPP

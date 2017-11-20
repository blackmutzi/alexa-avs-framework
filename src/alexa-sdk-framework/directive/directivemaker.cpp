#include "include/directive/directivemaker.hpp"

using namespace directive;


DirectiveType * DirectiveMaker::createDirectiveType(const char *token, const char *value)
{
    return new DirectiveType( token , value );
}

Directive * DirectiveMaker::createDirective(DirectiveType *type, AlexaEvent::TransportInfo *json_info, AlexaEvent::TransportInfo *audio_info)
{
    Directive * directive = new Directive();

    directive->setDirectiveType( type );
    directive->setJsonInfo( json_info );

    if( audio_info != nullptr )
            directive->setAudioInfo( audio_info );

    return directive;
}

DirectiveCallbackCommand * DirectiveMaker::createDirectiveCallbackCommand(DirectiveType *type, DirectiveCallback callback, void *instance)
{
    DirectiveCallbackCommand * command = new DirectiveCallbackCommand();
    command->setDirectiveType( type );
    command->setCallback( callback );
    command->setInstance( instance );
    return command;
}



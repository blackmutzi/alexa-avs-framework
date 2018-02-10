#ifndef DIRECTIVEMODULINTERFACE_HPP
#define DIRECTIVEMODULINTERFACE_HPP

#include "stdafx.hpp"
#include "directive/directivecommand.hpp"
#include "event/requestmanager.hpp"

namespace directive
{

class DirectiveModulInterface
{
    public:
        DirectiveModulInterface( AlexaEvent::RequestManager * request_manager );
        virtual ~DirectiveModulInterface(){}

        DirectiveCallbackCommandList getDirectives( void );
        AlexaEvent::RequestManager * getRequestManager(void);

    protected:

        DirectiveCallbackCommandList m_directives;
        AlexaEvent::RequestManager * m_request_manager;
};

}
#endif // DIRECTIVEMODULINTERFACE_HPP

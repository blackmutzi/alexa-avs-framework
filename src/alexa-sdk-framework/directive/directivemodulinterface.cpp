#include "include/directive/directivemodulinterface.hpp"

using namespace directive;

DirectiveModulInterface::DirectiveModulInterface(RequestManager * request_manager )
    : m_request_manager( request_manager )
{}

DirectiveCallbackCommandList DirectiveModulInterface::getDirectives(void)
{
    return m_directives;
}

AlexaEvent::RequestManager * DirectiveModulInterface::getRequestManager(void)
{
    return m_request_manager;
}

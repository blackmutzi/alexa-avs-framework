#include "server/directiveproxy.hpp"

using namespace Server;

DirectiveProxy::DirectiveProxy(){}
DirectiveProxy::~DirectiveProxy(){}

void DirectiveProxy::setServer(ServerInterface *server)
{
    m_server = server;
}

void DirectiveProxy::onDirectiveEvent(Directive *directive)
{
    // Build Header Informations
    // Build Content Informations
    // Send to Server
}


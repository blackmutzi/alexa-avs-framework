#ifndef DIRECTIVEPROXY_HPP
#define DIRECTIVEPROXY_HPP

#include "include/stdafx.hpp"
#include "include/directive/directivelistenerinterface.hpp"
#include "include/server/serverinterface.hpp"

using namespace directive;

namespace Server
{
    class DirectiveProxy : public DirectiveListenerInterface
	{	
		public:
			DirectiveProxy();
			~DirectiveProxy();

            void setServer( ServerInterface * server );
            void onDirectiveEvent(Directive *directive) final;

        private:

            ServerInterface * m_server;
	};
}

#endif // DIRECTIVEPROXY_HPP

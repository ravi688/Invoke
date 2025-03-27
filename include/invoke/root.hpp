#pragma once

#include <invoke/api_defines.hpp> // for INVOKE_API
#include <common/defines.h> // for CAN_BE_UNUSED_VARIABLE

namespace invoke
{
	class INVOKE_API RootPrivilegesScope
	{
		public:
			// Tries to gain sudo privileges, otherwise throws a runtime exception
			RootPrivilegesScope();
			// Drops the sudo privileges
			~RootPrivilegesScope();
	};

	INVOKE_API bool HasRootPrivileges();
	INVOKE_API bool DropRootPrivileges();
	INVOKE_API bool GainRootPrivileges();
}

#define INVOKE_ROOT_PRIVILEGES_SCOPE CAN_BE_UNUSED_VARIABLE invoke::RootPrivilegesScope ___##__LINE__;

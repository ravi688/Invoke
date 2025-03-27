#pragma once

#include <invoke/api_defines.hpp> // for INVOKE_API
#include <common/defines.h> // for CAN_BE_UNUSED_VARIABLE

namespace invoke
{
	class INVOKE_API RootPrivilegesScope
	{
		public:
			// Tries to gain sudo privileges, otherwise throws a runtime exception
			// NOTE: It internally calls GainRootPrivileges()
			// NOTE: This throws a runtime error exception if it fails to get root privileges,
			// So only instantiate object of this type only if you're sure that the process has been ran with root privileges initially.
			RootPrivilegesScope();
			// Drops the sudo privileges
			// NOTE: It internally calls DropRootPrivileges()
			~RootPrivilegesScope();
	};

	// On Linux: It returns true if the process has root privileges currently, otherwise false.
	// On Windows (MinGW): it always returns true.  
	INVOKE_API bool HasRootPrivileges();
	// Description: Drops root privileges
	// Returns: On Linux, it returns true if the root privileges has been dropped successfully, otherwise false.
	// 			On Windows, it always returns true.
	INVOKE_API bool DropRootPrivileges();
	// Description: (Re)Gains root privileges
	// Returns: On Linux, it returns true if the root privileges has been (re)gained successfully, otherwise false.
	// 			On windows, it always returns true.
	INVOKE_API bool GainRootPrivileges();
}

// Use this macro to limit the root privileges to a limited scope
// Usage:
// {
//		INVOKE_ROOT_PRIVILEGES_SCOPE;
// 		Do you stuff here
// }
#define INVOKE_ROOT_PRIVILEGES_SCOPE CAN_BE_UNUSED_VARIABLE invoke::RootPrivilegesScope ___##__LINE__;

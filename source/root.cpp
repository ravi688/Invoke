#include <invoke/root.hpp>
#include <common/platform.h> // for PLATFORM_LINUX

#ifdef PLATFORM_LINUX
#include <unistd.h> //. for user id functions
#include <cstdlib> // for atoi()
#include <stdexcept> // for std::runtime_error()
#endif // PLATFORM_LINUX

namespace invoke
{
	RootPrivilegesScope::RootPrivilegesScope()
	{
#ifdef PLATFORM_LINUX
		bool result = GainRootPrivileges();
		if(!result)
			throw std::runtime_error("Couldn't get root privileges, make sure to launch the proccess using sudo");
#endif // PLATFORM_LINUX
	}

	RootPrivilegesScope::~RootPrivilegesScope()
	{
#ifdef PLATFORM_LINUX
		bool result = DropRootPrivileges();
		if(!result)
			throw std::runtime_error("Couldn't drop root privileges");
#endif // PLATFORM_LINUX
	}

	INVOKE_API bool HasRootPrivileges()
	{
#ifdef PLATFORM_LINUX
		return geteuid() == 0;
#else
		return true;
#endif // PLATFORM_LINUX
	}

	INVOKE_API bool GainRootPrivileges()
	{
#ifdef PLATFORM_LINUX
		// If already running under sudo, then return
		if(geteuid() == 0) return true;
		if(seteuid(0) != 0) return false;
		// Now the effective user id must be of root
		return geteuid() == 0;
#else
		return true;
#endif // PLATFORM_LINUX
	}

	INVOKE_API bool DropRootPrivileges()
	{
#ifdef PLATFORM_LINUX
		// Get the original user id (which user actually launched the process)
        	auto uidStr = getenv("SUDO_UID");
        	if(!uidStr)
                	return false;
        	uid_t originalUID = atoi(uidStr);

        	seteuid(originalUID);

        	return originalUID == geteuid();
#else
		return true;
#endif // PLATFORM_LINUX
	}
}

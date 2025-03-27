
#include <invoke/invoke.hpp>
#include <cassert>
#include <iostream>

#if defined(PLATFORM_LINUX)
#	include <unistd.h>
#endif // PLATFORM_LINUX

int main()
{
	auto returnCode = invoke::Exec({ "echo", "\"Hello World\""});
	assert(returnCode == 0);
	auto result = invoke::GetExecutablePaths("python");
	if(result)
	{
		std::cout << "Following are the paths to \'python\':\n";
		auto& paths = result.value();
		for(const auto& path : paths)
			std::cout << path << "\n";
	}
	else std::cerr << "No paths for python found\n";
	std::string str { "echo turn" };
	std::string echoStr = str.substr(0, 4);
	returnCode = invoke::Exec({ echoStr, "\"Hello Another World\"" });
	assert(returnCode == 0);

#ifdef PLATFORM_LINUX
	if(geteuid() == 0) {
		std::cout << "The process is running with sudo privileges\n";
	}
	else
	{
		std::cout << "The process is not runnign with sudo privileges\n";
	}
#endif // PLATFORM_LINUX
	return 0;
}


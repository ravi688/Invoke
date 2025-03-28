#include <invoke/invoke.hpp>
#include <cassert>
#include <iostream>
#include <common/defines.hpp>
#include <invoke/root.hpp>

static void TellIfRunningInSudo()
{
	if(invoke::HasRootPrivileges()) {
		std::cout << "The process is running with sudo privileges\n";
	}
	else
	{
		std::cout << "The process is not running with sudo privileges\n";
	}
}

int main(int argc, const char* argv[])
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

	returnCode = invoke::Exec({ "echo", "\"Hello World with root privileges\"" }, "", true);
	assert(returnCode == 0);

	bool isInitiallyRoot = invoke::HasRootPrivileges();

	TellIfRunningInSudo();

	{
		std::cout << "Dropping root privileges\n";
		bool result = invoke::DropRootPrivileges();
		assert(!isInitiallyRoot || result);
	}

	TellIfRunningInSudo();

	if(isInitiallyRoot)
	{
		std::cout << "Regaining root privileges\n";
		INVOKE_ROOT_PRIVILEGES_SCOPE;
		TellIfRunningInSudo();
		std::cout << "Dropping root privileges\n";
	}
	TellIfRunningInSudo();

	if(isInitiallyRoot)
	{
		std::cout << "Regaining root privileges\n";
		INVOKE_ROOT_PRIVILEGES_SCOPE;
		TellIfRunningInSudo();
		std::cout << "Dropping root privileges\n";
	}

	return 0;
}


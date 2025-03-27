# Invoke
Sub-process execution. A wrapper library around reproc used across my projects

## Process invocation example
```cpp
#include <invoke/invoke.hpp>
#include <cassert>
#include <iostream>

int main()
{
  // Command execute: echo "Hello World"
	auto returnCode = invoke::Exec({ "echo", "\"Hello World\""});
	assert(returnCode == 0);

  // Determine paths of a command
	auto result = invoke::GetExecutablePaths("python");
	if(result)
	{
		std::cout << "Following are the paths to \'python\':\n";
		auto& paths = result.value();
		for(const auto& path : paths)
			std::cout << path << "\n";
	}
	else std::cerr << "No paths for python found\n";
}
```

## Root privileges drop and re-gain example
```cpp
#include <invoke/root.hpp>
#include <cassert>
#include <iostream>

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

int main()
{
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
}
```

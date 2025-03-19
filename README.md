# Invoke
Sub-process execution. A wrapper library around reproc used across my projects

## Example
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

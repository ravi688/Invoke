
#include <invoke/invoke.hpp>
#include <cassert>
#include <iostream>

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
	return 0;
}


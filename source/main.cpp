
#include <invoke/invoke.hpp>
#include <cassert>

int main()
{
	auto returnCode = invoke::Exec({ "echo", "\"Hello World\""});
	assert(returnCode == 0);
	return 0;
}


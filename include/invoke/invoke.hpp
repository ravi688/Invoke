#include <invoke/defines.hpp>

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace invoke
{
	INVOKE_API std::optional<std::string> GetExecutablePath(std::string_view executable);
	INVOKE_API int Exec(const std::vector<std::string>& args, std::string_view workDir = "");
}

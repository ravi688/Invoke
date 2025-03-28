#pragma once

#include <invoke/defines.hpp>
#include <common/defines.h> // for CAN_BE_UNUSED_VARIABLE

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace invoke
{
	INVOKE_API std::optional<std::vector<std::string>> GetExecutablePaths(std::string_view executable);
	INVOKE_API int Exec(const std::vector<std::string>& args, std::string_view workDir = "", bool isGainRootPrivilges = false);
}

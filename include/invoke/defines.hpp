
#pragma once
#include <invoke/api_defines.hpp>
#if !defined(INVOKE_RELEASE) && !defined(INVOKE_DEBUG)
#   warning "None of INVOKE_RELEASE && INVOKE_DEBUG is defined; using INVOKE_DEBUG"
#   define INVOKE_DEBUG
#endif


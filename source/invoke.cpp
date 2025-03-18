#include <invoke/invoke.hpp>
#include <reproc/run.h>

// If on windows, use where instead of which
#ifdef _WIN32
static constexpr std::string_view gWhichCmd = "where";
// Otherwise use which (on linux and freebsd)
#else
static constexpr std::string_view gWhichCmd = "which";
#endif

namespace invoke
{
	// Returns absolute path of a shell command
	// It internally runs "which"
	INVOKE_API std::optional<std::string> GetExecutablePath(std::string_view executable)
	{
	    std::vector<const char*> args = { gWhichCmd.data(), executable.data(), nullptr};
	
	    reproc_t* process = reproc_new();
	    reproc_options options = {};
	
	    char buffer[4096];
	    std::string result;
	    bool isSuccess = true;
	
	    auto r = reproc_start(process, args.data(), options);
	    if (r >= 0)
	    {
	        // Read the output
	        while (true)
	        {
	            int bytes_read = reproc_read(process, REPROC_STREAM_OUT, reinterpret_cast<uint8_t*>(buffer), sizeof(buffer));
	            if (bytes_read < 0)
	                break;
	            result.append(buffer, bytes_read);
	        }
	        reproc_wait(process, REPROC_INFINITE);
	    } else isSuccess = false;
	    reproc_destroy(process);
	    // Remove trailing newline or carrage return characters if present
	    if (!result.empty())
	    	while(result.back() == '\n' || result.back() == '\r')
	        	result.pop_back();
	    if(isSuccess)
	    	return { result };
	    else return { };
	}

	INVOKE_API int Exec(const std::vector<std::string>& args, std::string_view workDir)
	{
		// Build c-style argument list
	  	std::vector<const char*> cArgs;
	  	cArgs.reserve(args.size());
	  	for(const auto& arg : args)
	  		cArgs.push_back(arg.data());
	  	cArgs.push_back(nullptr);
	
	  	// Setup options
	  	reproc_options opts { };
	  	if(workDir.size())
	  		opts.working_directory = workDir.data();
	  	// Execute the meson command with the built arguments
	  	int returnCode = reproc_run(cArgs.data(), opts);
	  	return returnCode;
	}
}

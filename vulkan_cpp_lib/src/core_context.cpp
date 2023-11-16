// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "core_context.h"
#include <logging.h>

namespace vtpl
{
    CoreContext::CoreContext(std::string session_folder, std::string lib_folder)
        : _session_folder(std::move(session_folder)), _lib_folder(std::move(lib_folder))
    {

        std::string name_of_app = "VulkanCpp";
        // Poco::Path _path(_session_folder);
        // std::string a(_session_folder);
        std::string a = _session_folder;
        // std::cout << "\n\nCoreContext-------- _session_folder: " << a << " _lib_folder: " << _lib_folder << std::endl;
        ::ray::RayLog::StartRayLog(name_of_app, ::ray::RayLogLevel::INFO, a, false);
        RAY_LOG_INF << printable_git_info(GIT_DETAILS);
    }
    CoreContext &CoreContext::instance(std::string session_folder, std::string lib_folder)
    {
        static CoreContext s_instance(std::move(session_folder), std::move(lib_folder));
        return s_instance;
    }
}
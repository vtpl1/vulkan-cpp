// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#pragma once
#ifndef core_context_h
#define core_context_h
#include <string>
namespace vtpl
{
class CoreContext
{
  private:
    CoreContext(std::string session_folder, std::string lib_folder);
    ~CoreContext() = default;

    std::string _session_folder;
    std::string _lib_folder;

  public:
    static CoreContext& instance(std::string session_folder = "session/", std::string lib_folder = "lib/");
    CoreContext(const CoreContext&) = delete;
    CoreContext& operator=(const CoreContext&) = delete;
};

} // namespace vtpl
#endif // core_context_h

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
# set(VCPKG_BUILD_TYPE release)
if(PORT MATCHES "ffmpeg")
set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()
if (WIN32)
else()
    # if(PORT MATCHES "ffmpeg")
    #     set(VCPKG_LIBRARY_LINKAGE dynamic)
    # endif()
    set(VCPKG_CMAKE_SYSTEM_NAME Linux)
endif()

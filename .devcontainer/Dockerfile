FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.21.5"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

ARG VULKAN_VERSION=1.3.268

RUN wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add - \
    && wget -qO "/etc/apt/sources.list.d/lunarg-vulkan-$VULKAN_VERSION-$(lsb_release -cs).list" "https://packages.lunarg.com/vulkan/$VULKAN_VERSION/lunarg-vulkan-$VULKAN_VERSION-$(lsb_release -cs).list" \
    && apt update && export DEBIAN_FRONTEND=noninteractive \
    && apt -y install vulkan-sdk

RUN curl -sSL https://bootstrap.pypa.io/get-pip.py -o get-pip.py && python3 get-pip.py && rm ./get-pip.py

RUN pip install clang-tidy clang-format

RUN apt update && apt install -y iputils-ping ccache
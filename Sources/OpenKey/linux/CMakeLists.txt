cmake_minimum_required(VERSION 3.16)

project(fcitx5-openkey VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# Fcitx5 development files (headers + cmake config) ship in the `fcitx5`
# package on Arch; no separate -dev package is required.
find_package(Fcitx5Core REQUIRED)

# Standard compiler flags shared by every Fcitx5 addon: sets C++20,
# -fvisibility=hidden, warnings, etc. (No dependency on extra-cmake-modules.)
include("${FCITX_INSTALL_CMAKECONFIG_DIR}/Fcitx5Utils/Fcitx5CompilerSettings.cmake")

add_subdirectory(src)

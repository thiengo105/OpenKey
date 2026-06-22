# The OpenKey engine is platform independent; we compile it straight into the
# addon and select the Linux key-code table with -DLINUX (see DataType.h).
set(OPENKEY_ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../engine")

set(OPENKEY_ENGINE_SOURCES
    "${OPENKEY_ENGINE_DIR}/Engine.cpp"
    "${OPENKEY_ENGINE_DIR}/Vietnamese.cpp"
    "${OPENKEY_ENGINE_DIR}/Macro.cpp"
    "${OPENKEY_ENGINE_DIR}/SmartSwitchKey.cpp"
    "${OPENKEY_ENGINE_DIR}/ConvertTool.cpp"
)

add_library(openkey MODULE
    openkeyengine.cpp
    ${OPENKEY_ENGINE_SOURCES}
)

# Fcitx5 loads the addon as "openkey.so" (matches Library=openkey in the conf).
set_target_properties(openkey PROPERTIES PREFIX "")

target_include_directories(openkey PRIVATE
    "${OPENKEY_ENGINE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(openkey PRIVATE LINUX)

target_link_libraries(openkey PRIVATE Fcitx5::Core Fcitx5::Config)

install(TARGETS openkey DESTINATION "${CMAKE_INSTALL_LIBDIR}/fcitx5")

# Addon descriptor (needs @PROJECT_VERSION@ substituted).
configure_file(openkey-addon.conf.in openkey-addon.conf @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/openkey-addon.conf"
    RENAME openkey.conf
    DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon")

# Input-method descriptor.
install(FILES openkey-im.conf
    RENAME openkey.conf
    DESTINATION "${CMAKE_INSTALL_DATADIR}/fcitx5/inputmethod")

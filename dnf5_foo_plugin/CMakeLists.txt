add_library(foo_cmd_plugin MODULE foo.cpp foo_cmd_plugin.cpp)

# disable the 'lib' prefix in order to create foo_cmd_plugin.so
set_target_properties(foo_cmd_plugin PROPERTIES PREFIX "")

pkg_check_modules(LIBDNF5 REQUIRED libdnf5)
target_link_libraries(foo_cmd_plugin PRIVATE ${LIBDNF5_LIBRARIES})
pkg_check_modules(LIBDNF5_CLI REQUIRED libdnf5-cli)
target_link_libraries(foo_cmd_plugin PRIVATE ${LIBDNF5_CLI_LIBRARIES})

install(TARGETS foo_cmd_plugin LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/dnf5/plugins/)

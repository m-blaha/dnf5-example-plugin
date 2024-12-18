add_library(baz MODULE baz.cpp)

# disable the 'lib' prefix in order to create baz.so
set_target_properties(baz PROPERTIES PREFIX "")
set_target_properties(baz PROPERTIES OUTPUT_NAME "baz")

pkg_check_modules(LIBDNF5 REQUIRED libdnf5)
target_link_libraries(baz PRIVATE ${LIBDNF5_LIBRARIES})

install(TARGETS baz LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/libdnf5/plugins/")
install(FILES "baz.conf" DESTINATION "${CMAKE_INSTALL_FULL_SYSCONFDIR}/dnf/libdnf5-plugins")

add_executable(GtkObjectManager main.cpp 
    "NavigationWindow.cpp"
    "NavigationWindow.hpp"
    "MainWindow.cpp"
    "MainWindow.hpp"
)
add_subdirectory(controllers)
add_subdirectory(models)
add_subdirectory(views)
add_subdirectory(widgets)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

target_include_directories(
    GtkObjectManager PUBLIC
    ${GTKMM_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_directories(GtkObjectManager PUBLIC ${GTKMM_LIBRARY_DIRS})
target_link_libraries(GtkObjectManager PUBLIC ${GTKMM_LIBRARIES})
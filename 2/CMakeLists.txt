cmake_minimum_required(VERSION 3.19)
project(RSSReader VERSION 0.0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

qt_add_executable(RSSReader
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(RSSReader
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS RSSReader
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET RSSReader
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

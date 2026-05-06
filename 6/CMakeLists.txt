cmake_minimum_required(VERSION 3.19)
project(RSSReader VERSION 0.0.1 LANGUAGES CXX)

configure_file(
    project.h.in # 输入文件
    project.h    # 输出文件
    @ONLY        # 仅替换 @VAR@ 形式的变量
)

set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Xml)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
    project.h
)

set(RESOURCES
    project.qrc
)

qt_add_executable(RSSReader
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(RSSReader PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(RSSReader
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Xml
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

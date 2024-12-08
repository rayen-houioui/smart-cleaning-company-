cmake_minimum_required(VERSION 3.16)

# Define your project
project(zeezeaez VERSION 0.1 LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic handling of Qt UI files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find Qt packages, including Bluetooth and other necessary modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets Core Gui Sql PrintSupport Charts Bluetooth SerialPort)

# Find the correct Qt version and components
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets Core Gui Sql PrintSupport Charts Bluetooth SerialPort)

# Define the source files for your project
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    connection.h
    connection.cpp
    employe.h
    employe.cpp
    arduino.h
    arduino.cpp
    resource.qrc
)

# Set up the executable, handling Qt6 specific differences
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(zeezeaez
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(zeezeaez SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(zeezeaez
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link necessary Qt libraries, including Qt Bluetooth and SerialPort
target_link_libraries(zeezeaez PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Bluetooth
    Qt${QT_VERSION_MAJOR}::SerialPort
)

# Set properties for MacOS or Windows executables
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.zeezeaez)
endif()

set_target_properties(zeezeaez PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install target configuration
include(GNUInstallDirs)
install(TARGETS zeezeaez
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize Qt 6 executable if necessary
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(zeezeaez)
endif()

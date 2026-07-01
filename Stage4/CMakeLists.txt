cmake_minimum_required(VERSION 3.16)

project(stage4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    stage4.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(stage4
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        TerritoryView.h
        Territory.h
        Territory.cpp
        TerritoryView.cpp
        Cellular.h
        Cellular.cpp
        Equipo.h
        Equipo.cpp
        CellularView.h CellularView.cpp
        MainWindow.h
        MainWindow.cpp
        Tablet.h Tablet.cpp
        TabletView.h TabletView.cpp
        EloTelTag.h EloTelTag.cpp
        EloTelTagView.h EloTelTagView.cpp
        ETNube.h ETNube.cpp
        VentanaFindMy.h VentanaFindMy.cpp
        SmartDeviceView.h SmartDeviceView.cpp
        EquipoPasivo.h EquipoPasivo.cpp
        gFindMy.h gFindMy.cpp
        recursos.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET stage4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(stage4 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(stage4
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(stage4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.stage4)
endif()
set_target_properties(stage4 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS stage4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(stage4)
endif()

cmake_minimum_required(VERSION 3.16)

project(Library-QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        # MODELS
        models/Book.cpp
        models/User.cpp
        models/Loan.cpp

        # REPOS
        repositories/VectorBookRepo.cpp
        repositories/VectorUserRepo.cpp
        repositories/VectorLoanRepo.cpp

        # SERVICES
        services/LibraryService.cpp

        # UTILS
        utils/inpuUtils/inputUtils.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Library-QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


        searchbookwindow.h searchbookwindow.cpp searchbookwindow.ui


        showdatawindow.h showdatawindow.cpp showdatawindow.ui
        searchdialog.h searchdialog.cpp searchdialog.ui

        usermanagedialog.h usermanagedialog.cpp usermanagedialog.ui
        enums/LibraryEnums.h
        loanmanagedialog.h loanmanagedialog.cpp loanmanagedialog.ui
        enums/QtEnums.h
        utils/inpuUtils/inputUtils.h
        services/LibraryService.h
        style/style.qss
        addbookdialog.h addbookdialog.cpp addbookdialog.ui





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Library-QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Library-QT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Library-QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(Library-QT PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/services
    ${CMAKE_CURRENT_SOURCE_DIR}/repositories
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/enums
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/inputUtils
)

target_link_libraries(Library-QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Library-QT)
endif()
set_target_properties(Library-QT PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Library-QT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Library-QT)
endif()

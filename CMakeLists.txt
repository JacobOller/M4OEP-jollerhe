cmake_minimum_required(VERSION 3.16)
project(M4OEP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(main
    Application/main.cpp
    Pipeline/DataPipeline.cpp
    Gui/AppPaths.cpp
    Gui/DataPipelineInitializer.cpp
    Gui/MainWindow.cpp
    Gui/SearchForm.ui
    Gui/HouseDetailForm.ui
    HouseObjects/House.cpp
    HouseObjects/HouseManager.cpp
    HouseObjects/HouseStatistics.cpp
    Sorting/HeapSort.cpp
)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(main PRIVATE Qt6::Widgets)

# The line below was written by Gemini and ensures that the program builds, as there was some
# vague error with the Qt libraries not being found that I couldn't fix.
if(WIN32)
    get_filename_component(_qt_bin "${Qt6_DIR}/../../../bin" ABSOLUTE)
    find_program(M4OEP_WINDEPLOYQT NAMES windeployqt HINTS "${_qt_bin}" NO_DEFAULT_PATH)
    if(M4OEP_WINDEPLOYQT)
        add_custom_command(TARGET main POST_BUILD
            COMMAND "${M4OEP_WINDEPLOYQT}" "$<TARGET_FILE:main>" $<IF:$<CONFIG:Debug>,--debug,--release>
            VERBATIM)
    endif()
endif()

add_executable(test
    Application/testing.cpp
    HouseObjects/House.cpp
    HouseObjects/HouseManager.cpp
    HouseObjects/HouseStatistics.cpp
    Sorting/HeapSort.cpp
    Menu/Menu.cpp
)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(console
    Application/console_main.cpp
    Application/App.cpp
    Pipeline/DataPipeline.cpp
    HouseObjects/House.cpp
    HouseObjects/HouseManager.cpp
    HouseObjects/HouseStatistics.cpp
    Sorting/HeapSort.cpp
    Menu/Menu.cpp
)
target_include_directories(console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

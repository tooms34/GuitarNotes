# Define project
cmake_minimum_required(VERSION 3.16.0)
set(Project_Name "GuitarNotes")
project(${Project_Name} C CXX)

set (CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)

 
#set(JUCE_DIR "/home/tooms/JUCE/cmake-build")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/tooms/JUCE/cmake-build")
#set(CMAKE_PREFIX_PATH "/home/tooms/JUCE/cmake-build")
#find_package(JUCE CONFIG REQUIRED)

add_subdirectory(JUCE EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

 
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.h)
 
# Application
juce_add_gui_app(${Project_Name}
     VERSION "1.0.0"
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "GuitarNotes")     # The name of the final executable, which can differ from the target name

 

target_sources(${Project_Name}
    PRIVATE
    ${SRC_FILES})


target_compile_definitions(${Project_Name}
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="GuitarNotes"
        JUCE_APPLICATION_VERSION_STRING="1.0.0")



        juce_generate_juce_header(${Project_Name})

        target_link_libraries(${Project_Name}
        PRIVATE
            # GuiAppData            # If we'd created a binary data target, we'd link to it here
            juce::juce_gui_extra
            juce::juce_audio_basics
            juce::juce_audio_utils
            juce::juce_audio_devices
            juce::juce_core
        PUBLIC
            juce::juce_recommended_config_flags
            juce::juce_recommended_lto_flags
            juce::juce_recommended_warning_flags)

cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(|PROJECTNAME|
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(|VST3SDKPATH|
    ${CMAKE_BINARY_DIR}/vst3sdk_build
)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(|PROJECTNAME|
    src/plugin.cpp
    src/plugin.h
    src/processor.cpp
    src/processor.h
    src/controller.cpp
    src/controller.h
)

target_link_libraries(|PROJECTNAME|
    PRIVATE
        sdk
)

if(SMTG_MAC)
    smtg_target_set_bundle(|PROJECTNAME|
        BUNDLE_IDENTIFIER "com.|COMPANYNAMELOWER|.|PROJECTNAMELOWER|"
        COMPANY_NAME "|COMPANYNAME|"
    )
endif()

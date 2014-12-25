cmake_minimum_required (VERSION 2.6)
project (Carbon)

set(CMAKE_SUPPRESS_REGENERATION TRUE)

#set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

include_directories( "${Carbon_SOURCE_DIR}/Source/Runtime/Common" )
include_directories( "${Carbon_SOURCE_DIR}/Source/Runtime/" )
include_directories( "${Carbon_SOURCE_DIR}/Source" )
include_directories( "${Carbon_SOURCE_DIR}/Source/UI/Base/GeneratedFiles")
include_directories( "$ENV{DXSDK_DIR}")
include_directories( "$ENV{QTDIR}/include")
include_directories( "$ENV{QTDIR}/include/QtCore")
include_directories( "$ENV{QTDIR}/include/QtGui")
include_directories( "$ENV{QTDIR}/include/QtWidgets")

link_directories( $ENV{QTDIR}/lib)
link_directories( ${Carbon_SOURCE_DIR}/Source/ThirdParty/Regal/Lib )

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCARBON_DEBUG_BUILD")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DCARBON_RELEASE_BUILD")

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

file(GLOB_RECURSE project_headers Source/*.h)
file(GLOB_RECURSE project_cpps Source/*.cpp)
file(GLOB_RECURSE project_cs Source/*.c)

set(all_files ${project_headers} ${project_cpps} ${project_cs})
source_group_by_dir(all_files)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../Binary")

add_executable(Carbon ${all_files})

target_link_libraries( Carbon debug Qt5Cored.lib debug Qt5Widgetsd.lib debug Qt5Guid.lib d3dcompiler.lib )
target_link_libraries( Carbon optimized Qt5Core.lib optimized Qt5Widgets.lib optimized Qt5Guid.lib d3dcompiler.lib)
target_link_libraries( Carbon d3d11.lib dxgi.lib regal32.lib)

if(WIN32)
   set_target_properties(Carbon PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
   set_target_properties(Carbon PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif(WIN32)

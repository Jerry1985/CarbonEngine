cmake_minimum_required (VERSION 2.6)
project (Carbon)

set(CMAKE_SUPPRESS_REGENERATION TRUE)

#set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

include_directories( "${Carbon_SOURCE_DIR}/Source/Runtime/Common" )
#include_directories( "C:/wxWidgets-3.0.1/include" )
#include_directories( "C:/wxWidgets-3.0.1/lib/vc_lib/mswud" )

link_directories( C:/wxWidgets-3.0.1/lib/vc_lib )

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

target_link_libraries( Carbon debug wxmsw30ud_core.lib debug wxbase30ud.lib debug wxtiffd.lib debug wxjpegd.lib debug wxpngd.lib debug wxzlibd.lib debug comctl32.lib debug uuid.lib debug rpcrt4.lib)
target_link_libraries( Carbon optimized wxmsw30u_core.lib optimized wxbase30u.lib optimized wxtiff.lib optimized wxjpeg.lib optimized wxpng.lib optimized wxzlib.lib optimized comctl32.lib optimized uuid.lib optimized rpcrt4.lib)

if(WIN32)
   #set_target_properties(Carbon PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
   #set_target_properties(Carbon PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif(WIN32)

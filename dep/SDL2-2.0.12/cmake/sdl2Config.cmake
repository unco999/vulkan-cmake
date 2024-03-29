cmake_minimum_required(VERSION 3.2)

set(SDL2_VERSION 2.0.12)

get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

set(SDL2_INCLUDE_DIRS "${_IMPORT_PREFIX}/include")
set(SDL2_LIBS SDL2.lib SDL2main.lib)

# Support both 32 bit and 64 bit builds.
if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBS_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/x64")
  
  file(
	  GLOB_RECURSE SDL2_DLLS
    "${CMAKE_CURRENT_LIST_DIR}/../lib/x64/*.dll"
  )
else()
  set(SDL2_LIBS_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/x86")

  file(
	  GLOB_RECURSE SDL2_DLLS
    "${CMAKE_CURRENT_LIST_DIR}/../lib/x86/*.dll"
  )
endif()
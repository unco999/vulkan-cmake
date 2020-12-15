cmake_minimum_required(VERSION 3.15)

project(Vulkan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
	set(SDL2_DIR "${PROJECT_SOURCE_DIR}/dep/SDL2-2.0.12/cmake")
endif()

set(GLM_DIR "${PROJECT_SOURCE_DIR}/dep/glm-0.9.9.8/cmake")

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)

if(NOT Vulkan_FOUND)
	message(FATAL_ERROR  "Vulkan could not be found.")
endif()

file(
	GLOB_RECURSE HEADER_FILES
	"include/*.h"
)

file(
	GLOB_RECURSE SOURCE_FILES
	"src/*.cpp"
)

add_executable(Vulkan ${SOURCE_FILES} ${HEADER_FILES})

source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/src" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/include" FILES ${HEADER_FILES})

target_include_directories(Vulkan PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
	${SDL2_INCLUDE_DIRS}
	${Vulkan_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}
)

target_link_directories(Vulkan PUBLIC ${SDL2_LIBS_DIR})
target_link_libraries(Vulkan PUBLIC ${SDL2_LIBS} ${Vulkan_LIBRARY})

if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(
			TARGET Vulkan POST_BUILD COMMAND
			${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:Vulkan>
		)
    endforeach()
endif()

add_custom_command(
	TARGET Vulkan POST_BUILD COMMAND
	${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
cmake_minimum_required(VERSION 3.15)
project(bfho VERSION 1.0 LANGUAGES CXX)

set(PROJECT_DESCRIPTION "Bullfrog Hi-Octane C++ library")

if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
endif()
if( NOT CMAKE_OPTIMIZATION_LEVEL )
	set( CMAKE_OPTIMIZATION_LEVEL 3 CACHE STRING "Choose the level of optimization." FORCE )
endif()

include(GNUInstallDirs)
include(FindPkgConfig)

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS ON)

if( CMAKE_BUILD_TYPE EQUAL Debug )
	add_compile_options(-g)
endif()

if( CMAKE_GENERATOR_PLATFORM STREQUAL "x64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "x86_64" OR CMAKE_GENERATOR_PLATFORM STREQUAL "AMD64" )
	add_compile_options(-mfpmath=sse)
endif()

add_compile_options(-march=native)
add_compile_options(-O${CMAKE_OPTIMIZATION_LEVEL})
add_compile_options(-fopenmp-simd)
add_compile_options(-ftree-vectorize)
add_compile_options(-Wno-gnu-alignof-expression)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-fpermissive)
add_compile_options(-ffunction-sections)
add_compile_options(-Wno-array-bounds)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-pedantic)
add_compile_options(-Wno-narrowing)
add_compile_options(-Wno-int-conversion)
add_link_options(-Wl,--gc-sections)
add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)


set(SOURCE_FILES
)

set(INCLUDE_DIR include)
set(INCLUDE_FILES
	"${INCLUDE_DIR}/${PROJECT_NAME}/entity.hpp"
	"${INCLUDE_DIR}/${PROJECT_NAME}/bfho.hpp"
)

set(EXAMPLE_SOURCE_FILES
	src/main.c
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
	PUBLIC_HEADER $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)



set(install_prefix "${CMAKE_INSTALL_PREFIX}")
set(install_libdir "${CMAKE_INSTALL_LIBDIR}")
set(install_includedir "${CMAKE_INSTALL_INCLUDEDIR}")
configure_file(lib${PROJECT_NAME}.pc.in ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.pc @ONLY)
set(ENV{PKG_CONFIG_PATH} "${PROJECT_BINARY_DIR}:$ENV{PKG_CONFIG_PATH}")

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION
	${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	)

install(FILES ${PROJECT_SOURCE_DIR}/${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} COMPONENT headers)

install(FILES lib${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)

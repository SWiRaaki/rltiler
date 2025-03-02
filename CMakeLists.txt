cmake_minimum_required( VERSION 3.10 )
project( rltiler )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release )
endif()
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wreturn-type -pedantic" )
set( CMAKE_CXX_FLAGS_DEBUG "-g2 -DDEBUG" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )

if( WIN32 )
	add_definitions( -DPLATFORM_WINDOWS )
	set( OS_LIBS "" )
elseif( UNIX )
	add_definitions( -DPLATFORM_LINUX )
	set( OS_LIBS "m" )
else()
	add_definitions( -DPLATFORM_GENERIC )
	set( OS_LIBS "" )
endif()

add_subdirectory(
	external/raylib
)

add_executable(
	rltiler
	main.c
)

set_property( TARGET rltiler PROPERTY C_STANDARD 99 )

target_link_libraries(
	rltiler
	raylib
	${OS_LIBS}
)

target_include_directories(
	rltiler
	PRIVATE inc
	PRIVATE external/raylib/src
)

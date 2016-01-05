cmake_minimum_required (VERSION 3.4)
project (crawler)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

include_directories(inc)

set(SOURCES
	src/cmain.cpp
	src/cworld.cpp
	src/ctimer.cpp
	src/ctiles.cpp
	src/ctile.cpp
	src/csimulator.cpp
	src/crenderer.cpp
	src/cobject.cpp
	src/cmath.cpp
	src/cmain.cpp
	src/cinput.cpp
	src/chero.cpp
	src/ccharacter.cpp
)	

add_executable(crawler ${SOURCES})


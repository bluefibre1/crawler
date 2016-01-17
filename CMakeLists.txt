cmake_minimum_required (VERSION 2.8)
project (crawler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    src/ccreature.cpp
    src/cbehavior.cpp
    src/cwindow.cpp
    src/citem.cpp
    src/cweapon.cpp
    src/cweapontemplate.cpp
    src/cweapontemplates.cpp
    src/cweaponfactory.cpp
    src/ccreaturetemplate.cpp
    src/ccreaturetemplates.cpp
    src/ccreaturefactory.cpp
    src/ccolor.cpp
    src/ccolors.cpp
    src/cfaction.cpp
    src/cfactions.cpp
    src/clogger.cpp
)	

add_executable(crawler ${SOURCES})

target_link_libraries(crawler -ltermcap)

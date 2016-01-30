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
    src/cbehavior.cpp
    src/cwindow.cpp
    src/cwindowmanager.cpp
    src/citem.cpp
    src/cweapon.cpp
    src/citemtemplate.cpp
    src/cweapontemplate.cpp
    src/citemtemplates.cpp
    src/citemfactory.cpp
    src/ccharactertemplate.cpp
    src/ccharactertemplates.cpp
    src/ccharacterfactory.cpp
    src/ccolor.cpp
    src/ccolors.cpp
    src/cfaction.cpp
    src/cfactions.cpp
    src/clogger.cpp
    src/croom.cpp
    src/croomtemplate.cpp
    src/cchest.cpp
    src/cchestfactory.cpp
    src/cdebugger.cpp
)	

add_executable(crawler ${SOURCES})

target_link_libraries(crawler -ltermcap)

cmake_minimum_required (VERSION 2.8)
project (crawler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

include_directories(inc)

set(SOURCES
	src/ccharacter.cpp
	src/chero.cpp
	src/cinput.cpp
	src/cmain.cpp
	src/cmain.cpp
	src/cmath.cpp
	src/cobject.cpp
	src/crenderer.cpp
	src/csimulator.cpp
	src/ctile.cpp
	src/ctiles.cpp
	src/ctimer.cpp
	src/cworld.cpp
    src/cbehavior.cpp
    src/ccharacterfactory.cpp
    src/ccharactertemplate.cpp
    src/ccharactertemplates.cpp
    src/cchest.cpp
    src/cchestfactory.cpp
    src/ccolor.cpp
    src/ccolors.cpp
    src/cdebugger.cpp
    src/cfaction.cpp
    src/cfactions.cpp
    src/citem.cpp
    src/citemfactory.cpp
    src/citemtemplate.cpp
    src/citemtemplates.cpp
    src/clogger.cpp
    src/croom.cpp
    src/croomfactory.cpp
    src/croomtemplate.cpp
    src/cweapon.cpp
    src/cweapontemplate.cpp
    src/cwindow.cpp
    src/cwindowmanager.cpp
)	

add_executable(crawler ${SOURCES})

target_link_libraries(crawler -ltermcap)

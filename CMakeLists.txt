cmake_minimum_required (VERSION 3.0)

set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake"
)

project ( ChatExample )

# set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

SET(PROJECT_NAME ChatExample)
FILE( GLOB PROJECT_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/src/*.cpp" )
SET(PROJECT_SOURCE_DIR gtk-build)
SET(PROJECT_BINARY_DIR gtk-build)

SET( wxWidgets_USE_LIBS ON )
SET( WXWIDGETS_USE_UNICODE ON )

# hack to use different versions :/
if(MSVC)
    SET(WXW_FILE_VERSION "30")
    SET(WXW_VERSION "3.0")
else()
    SET(WXW_FILE_VERSION "31")
    SET(WXW_VERSION "3.1")
endif()

set( wxWidgets_CONFIGURATION mswu )
set( wxWidgets_USE_STATIC ON )
set( WXWIDGETS_USE_DEBUG ON )
set( Boost_USE_STATIC_LIBS ON ) 
set( Boost_USE_MULTITHREADED ON )

SET(CMAKE_VERBOSE_MAKEFILE TRUE)

find_package( Boost COMPONENTS thread system date_time regex chrono )
add_subdirectory( dependencies/libP2PNetwork )

SET(PROJECT_LIBRARIES 
	debug ${Boost_SYSTEM_LIBRARY_DEBUG} optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
	debug ${Boost_DATE_TIME_LIBRARY_DEBUG} optimized ${Boost_DATE_TIME_LIBRARY_RELEASE}
	debug ${Boost_REGEX_LIBRARY_DEBUG} optimized ${Boost_REGEX_LIBRARY_RELEASE}
	debug ${Boost_THREAD_LIBRARY_DEBUG} optimized ${Boost_THREAD_LIBRARY_RELEASE}
	debug ${Boost_CHRONO_LIBRARY_DEBUG} optimized ${Boost_CHRONO_LIBRARY_RELEASE}
	debug ${Boost_SIGNALS_LIBRARY_DEBUG} optimized ${Boost_SIGNALS_LIBRARY_RELEASE}
	${WX_richtextd}
	libP2PNetwork
)

INCLUDE (FindwxW)
INCLUDE (UsewxW)

find_package( wxWidgets COMPONENTS core base richtext )
include(${wxWidgets_USE_FILE})

source_group( src FILES ${PROJECT_SOURCE_FILES} )

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/dependencies/libP2PNetwork/include"
	${Boost_INCLUDE_DIR}
)

link_directories( 
	"${CMAKE_SOURCE_DIR}/build/libs"
	${Boost_LIBRARY_DIR}
	${wxWidgets_LIB_DIR}
)

if(MSVC)
	ADD_DEFINITIONS( 
	    -D_CRT_SECURE_NO_DEPRECATE=1
	    -D_CRT_NON_CONFORMING_SWPRINTFS=1
	    -D_SCL_SECURE_NO_WARNINGS=1
	    -D_UNICODE
		-D_WIN32_WINNT=0x0501
	    -DNOPCH
	)

    ADD_DEFINITIONS( 
        -D__WXMSW__
    )
    set_target_properties( ChatExample PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
    set_target_properties( ChatExample PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:windows")
endif()

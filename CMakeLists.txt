cmake_minimum_required (VERSION 3.4)

project ( ChatExample )

add_subdirectory( Dependencies/libP2PNetwork )

set( Boost_USE_STATIC_LIBS ON ) 
set( Boost_USE_MULTITHREADED ON )
find_package( Boost COMPONENTS thread system date_time regex )
find_package(wxWidgets COMPONENTS core base )

FILE( GLOB ROOT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/src/*.cpp" )

source_group( src FILES ${ROOT_SRC_FILES} )

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${wxWidgets_ROOT_DIR}/include"
	"${wxWidgets_ROOT_DIR}/lib/vc_lib/mswud"
	"${CMAKE_SOURCE_DIR}/dependencies/libP2PNetwork/include"
	${Boost_INCLUDE_DIRS}
)

add_executable( 
	ChatExample
	${ROOT_SRC_FILES} 
)

link_directories( 
	"${CMAKE_SOURCE_DIR}/build/libs"
	${Boost_LIBRARY_DIRS}
)

target_link_libraries( 
	ChatExample
	debug ${WX_based} optimized ${WX_base} 
	debug ${WX_netd} optimized ${WX_net} 
	debug ${WX_xmld} optimized ${WX_xml} 
	debug ${WX_regexd} optimized ${WX_regex} 
	debug ${WX_expatd} optimized ${WX_expat} 
	debug ${WX_jpegd} optimized ${WX_jpeg} 
	debug ${WX_pngd} optimized ${WX_png} 
	debug ${WX_tiffd} optimized ${WX_tiff} 
	debug ${WX_zlibd} optimized ${WX_zlib} 
	debug ${WX_cored} optimized ${WX_core} 
	debug ${WX_advd} optimized ${WX_adv} 
	debug ${WX_htmld} optimized ${WX_html} 
	debug ${WX_gld} optimized ${WX_gl} 
	debug ${WX_qad} optimized ${WX_qa} 
	debug ${WX_xrcd} optimized ${WX_xrc} 
	debug ${WX_auid} optimized ${WX_aui} 
	debug ${WX_propgridd} optimized ${WX_propgrid} 
	debug ${WX_ribbond} optimized ${WX_ribbon} 
	debug ${WX_richtextd} optimized ${WX_richtext} 
	debug ${WX_mediad} optimized ${WX_media} 
	debug ${WX_stcd} optimized ${WX_stc} 
	debug ${WX_scintillad} optimized ${WX_scintilla} 
	debug ${WX_webviewd} optimized ${WX_webview} 
	debug ${Boost_SYSTEM_LIBRARY_DEBUG} optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
	debug ${Boost_DATE_TIME_LIBRARY_DEBUG} optimized ${Boost_DATE_TIME_LIBRARY_RELEASE}
	debug ${Boost_REGEX_LIBRARY_DEBUG} optimized ${Boost_REGEX_LIBRARY_RELEASE}
	libP2PNetwork
)

ADD_DEFINITIONS( 
    -D_CRT_SECURE_NO_DEPRECATE=1
    -D_CRT_NON_CONFORMING_SWPRINTFS=1
    -D_SCL_SECURE_NO_WARNINGS=1
    -D_UNICODE
    -DNOPCH
)

if(MSVC)
    ADD_DEFINITIONS( 
        -D__WXMSW__
    )
    set_target_properties( ChatExample PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
    set_target_properties( ChatExample PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:windows")
endif()

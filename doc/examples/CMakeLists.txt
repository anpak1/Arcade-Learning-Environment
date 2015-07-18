#set(CMAKE_C_COMPILER_INIT g++)
cmake_minimum_required(VERSION 2.8.8)
project(Example1 CXX)

# options are None, Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Release)

# check prerequisites
if(NOT Boost_FOUND)
	set(Boost_USE_MULTITHREADED ON)		# default is ON, use -mt variant
#	set(Boost_USE_STATIC_LIBS ON)		# default is OFF, use boost static library
#	set(Boost_USE_STATIC_RUNTIME ON)	# default is not set.

	find_package(Boost 1.50.0 COMPONENTS serialization thread system chrono)
	if(NOT Boost_FOUND)
		set(BOOST_ROOT "C:/boost/boost_1_57_0")						# if not set, it will let cmake to find it.
		set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib/x86)			# might need to set this too.
		set(Boost_NO_SYSTEM_PATHS ON)								# default is OFF, set to ON if BOOST_ROOT is set
		find_package(Boost 1.50.0 COMPONENTS serialization thread system chrono REQUIRED)
	endif()
endif()

MESSAGE( STATUS "Boost_LIBRARIES:         " ${Boost_LIBRARIES} )
MESSAGE( STATUS "Boost_INCLUDE_DIRS:         " ${Boost_INCLUDE_DIRS} )
set(CPPREMOTE_ROOT ${PROJECT_SOURCE_DIR}/../../../CppRemote)

MESSAGE( STATUS "PROJECT_SOURCE_DIR:         " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "CPPREMOTE_ROOT:         " ${CPPREMOTE_ROOT} )

find_path(Remote_INCLUDE_DIR remote/session.hpp
          HINTS
          ${CPPREMOTE_ROOT}/include
          ${CMAKE_INSTALL_PREFIX}/include
          ${CMAKE_INSTALL_PREFIX}/../../../../../include
          PATH_SUFFIXES include)

find_path(Remote_LIBRARY_DIR NAMES remote libremote.so
          HINTS
          ${CPPREMOTE_ROOT}/lib
          ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/../../../../../lib
          ${PROJECT_SOURCE_DIR}/../CppRemote)

find_library(Remote_LIBRARY NAMES remote libremote.so
          HINTS
          ${CPPREMOTE_ROOT}/lib
          ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/../../../../../lib
          ${PROJECT_SOURCE_DIR}/../CppRemote)

MESSAGE( STATUS "Remote_LIBRARY:         " ${Remote_INCLUDE_DIR}/lib )

IF(NOT(remote_INCLUDE_DIR))
  MESSAGE(ERROR "Could not find remote include location")
ENDIF()

IF(NOT(remote_LIBRARY_DIR))
  MESSAGE(ERROR "Could not find remote library")
ENDIF()

IF(NOT(remote_LIBRARY))
  MESSAGE(ERROR "Could not find remote library")
ENDIF()

set(ALE ${PROJECT_SOURCE_DIR}/../..)

if(NOT ALE_FOUND)

	if(MSVC)
		set(ALE_LIBRARY_PATH_RELEASE ${ALE})
	else()
		set(ALE_LIBRARY_PATH_RELEASE ${ALE})
	endif()
	MESSAGE( STATUS "ALE_LIBRARY_RELEASE:         " ${ALE_LIBRARY_RELEASE} )
	MESSAGE( STATUS "ALE_LIBRARY_PATH_RELEASE:         " ${ALE_LIBRARY_PATH_RELEASE} )
	find_library(ALE_LIBRARY_RELEASE ale ${ALE_LIBRARY_PATH_RELEASE})
	MESSAGE( STATUS "ALE_LIBRARY_RELEASE:         " ${ALE_LIBRARY_RELEASE} )
#	if(NOT Remote_LIBRARY_DEBUGNOTFOUND)
		if(NOT ALE_LIBRARY_RELEASENOTFOUND)
			set(ALE_FOUND)
#			set(Remote_LIBRARY debug ${Remote_LIBRARY_DEBUG} optimized ${Remote_LIBRARY_RELEASE})
			set(ALE_LIBRARY ${ALE_LIBRARY_RELEASE})
		endif()
#	endif()
endif()

# project configuration
set(Example_ROOT ${PROJECT_SOURCE_DIR})
set(Example_SRC_DIR ${Example_ROOT})
set(USE_SDL 0)


set(Example_INCLUDE_DIR ${Example_ROOT}/../../src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

#set(Example_SOURCE_FILES_client
#	${Example_SRC_DIR}/remote_player.cpp
#	${Example_SRC_DIR}/client.cpp
#)

MESSAGE( STATUS "Example_SRC_DIR:         " ${Example_SRC_DIR} )
set(Example_SOURCE_FILES_server
	${Example_INCLUDE_DIR}/ale_interface.hpp
	${Example_SRC_DIR}/ale_player.hpp
	${Example_SRC_DIR}/ale_player.cpp
	${Example_SRC_DIR}/remote_ALEInterface.cpp
	${Example_SRC_DIR}/remote_ALEInterface.hpp
	${Example_SRC_DIR}/sharedLibraryInterfaceExample_server.cpp
)

set(Example_SOURCE_FILES_client
	${Example_SRC_DIR}/remote_ALEInterface.cpp
	${Example_SRC_DIR}/remote_ALEInterface.hpp
	${Example_SRC_DIR}/sharedLibraryInterfaceExample_client.cpp
)

# compilers configuration
if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501 -D_SCL_SECURE_NO_WARNINGS)
	if(NOT MSVC)
		add_definitions(-DBOOST_THREAD_USE_LIB)
	endif()
endif()

# strip debug symbols
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
	set(CMAKE_EXE_LINKER_FLAGS_MinSizeRel "${CMAKE_EXE_LINKER_FLAGS_MinSizeRel} -s")
endif()

add_compile_options(-L${ALE} -lale -lz -lboost_system)
set(CMAKE_SHARED_LINKER_FLAGS "-lale -lz")

MESSAGE( STATUS "Example_INCLUDE_DIR:         " ${Example_INCLUDE_DIR} )
MESSAGE( STATUS "Remote_LIBRARY:         " ${Remote_LIBRARY} )
# build configurations
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Remote_INCLUDE_DIR})
include_directories(${Example_INCLUDE_DIR})
include_directories(${Example_INCLUDE_DIR}/controllers)
include_directories(${Example_INCLUDE_DIR}/os_dependent)
include_directories(${Example_INCLUDE_DIR}/environment)
include_directories(${Example_INCLUDE_DIR}/external)
include_directories(${Example_INCLUDE_DIR}/games)
include_directories(${Example_INCLUDE_DIR}/emucore)
include_directories(${Example_INCLUDE_DIR}/common)
include_directories(${Example_ROOT})
include_directories(${ALE})


add_executable(server ${Example_SOURCE_FILES_server})
add_executable(client ${Example_SOURCE_FILES_client})

# link target.  link order of link is significant.
#target_link_libraries(client ${Remote_LIBRARY})
target_link_libraries(server ${Remote_LIBRARY})
target_link_libraries(client ${Remote_LIBRARY})
target_link_libraries(server ${ALE_LIBRARY})
target_link_libraries(client ${ALE_LIBRARY})

target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server ${Boost_LIBRARIES})


if(WIN32)
	target_link_libraries(client ws2_32 mswsock)
	target_link_libraries(server ws2_32 mswsock)
endif()

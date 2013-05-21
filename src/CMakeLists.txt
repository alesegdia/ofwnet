# Name the sources
set(TARGETS client101
			clientqt
			server101
			serverOFW
			clientOFW)
			#server_tema)

set(client101_SRC client101.cpp)
set(server101_SRC server101.cpp)
set(server_tema_SRC server_player_creation.cpp)
set(clientOFW_SRC client_player_creation.cpp)
set(serverOFW_SRC server_player_creation.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(Qt4 REQUIRED)
find_package(ENet REQUIRED)
find_package(OpenMP REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Protobuf REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS system thread)

#find_package(Threads REQUIRED)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS netmsg.proto)

set(msgserializ_SRC serialize.cpp ${PROTO_SRCS} ${PROTO_HDRS})

include(${QT_USE_FILE})
set(HWQ_Qt4_UI
	gui/mainwindow.ui)
set(HWQ_Qt4_SRC
	client.hpp
	gui/mainwindow.h)
set(HWQ_Qt4_RES)
set(HWQ_LIB ${QT_LIBRARIES})

QT4_WRAP_CPP(HWQ_MOC_CPP ${HWQ_Qt4_SRC})
QT4_WRAP_UI(HWQ_UI_CPP ${HWQ_Qt4_UI})
QT4_ADD_RESOURCES(HWQ_RES_H ${HWQ_Qt4_RES})

include_directories(../build/src ../build/src/gui)

if(OPENAL_FOUND)
	include_directories(${OPENAL_INCLUDE_DIR})
endif()

set(clientqt_SRC clientqt.cpp
				 ${HWQ_MOC_CPP}
				 ${HWQ_UI_CPP}
				 ${HWQ_RES_H}
				 client.cpp
				 client.hpp
				 gui/mainwindow.cpp)

if(OPENMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Create the targets
foreach (target ${TARGETS})

	# Add target
	add_executable(${target} ${${target}_SRC})

	# Link proper libs
	target_link_libraries(${target} ${ENet_LIBRARIES})
	target_link_libraries(${target} ${HWQ_LIB})
	target_link_libraries(${target} ${PROTOBUF_LIBRARIES})

	if(Boost_FOUND)
		target_link_libraries(${target} ${Boost_LIBRARIES})
	endif()

	# target_link_libraries(${target} boost_system)
	# target_link_libraries(${target} boost_thread)

	if(OPENAL_FOUND)
		target_link_libraries(${target} ${OPENAL_LIBRARY})
	endif()

endforeach (target)

# Set output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

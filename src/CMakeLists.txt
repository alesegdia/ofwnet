# Name the sources
set(TARGETS client101
			clientqt
			server101)

set(client101_SRC client101.cpp)
set(server101_SRC server101.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(Qt4 REQUIRED)
find_package(ENet REQUIRED)
find_package(OpenMP REQUIRED)

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
	target_link_libraries(${target} boost_system)
	target_link_libraries(${target} boost_thread)
endforeach (target)

# Set output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

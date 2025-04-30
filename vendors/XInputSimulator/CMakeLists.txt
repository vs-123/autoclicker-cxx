cmake_minimum_required(VERSION 3.10)
project(XInputSimulator)

# Linux
if(UNIX AND NOT APPLE)
	find_library(X_11 X11)
	find_library(X_TST Xtst)
	set(EXTRA_LIBS ${X_11} ${X_TST})
	set(PLATFORM_SOURCE_FILES xinputsimulatorimpllinux.cpp xinputsimulatorimpllinux.h)
endif(UNIX AND NOT APPLE)

# Apple
if(APPLE)
	find_library(APP_SERVICES ApplicationServices)
	find_library(CARBON Carbon)
	find_library(CORE_FOUNDATION CoreFoundation)
	set(EXTRA_LIBS ${APP_SERVICES} ${CARBON} ${CORE_FOUNDATION})
	set(PLATFORM_SOURCE_FILES xinputsimulatorimplmacos.cpp xinputsimulatorimplmacos.h)
endif(APPLE)

# Windows
if(WIN32)
	# Uncomment and set the USER_32 library if needed
	# find_library(USER_32 User32.Lib)
	# set(EXTRA_LIBS ${USER_32})
	set(PLATFORM_SOURCE_FILES xinputsimulatorimplwin.cpp xinputsimulatorimplwin.h)
endif(WIN32)

# Specify the source files for the library
set(SOURCE_FILES
	notimplementedexception.cpp
	notimplementedexception.h
	xinputsimulator.cpp
	xinputsimulator.h
	xinputsimulatorimpl.cpp
	xinputsimulatorimpl.h
	${PLATFORM_SOURCE_FILES}
)

# Create the library
add_library(XInputSimulator STATIC ${SOURCE_FILES})

# Link the necessary libraries
target_link_libraries(XInputSimulator ${EXTRA_LIBS})

# Specify include directories for the library
target_include_directories(XInputSimulator PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

# Optionally, you can add installation rules
install(TARGETS XInputSimulator
	EXPORT XInputSimulatorTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(EXPORT XInputSimulatorTargets
	FILE XInputSimulatorTargets.cmake
	NAMESPACE XInputSimulator::
	DESTINATION lib/cmake/XInputSimulator
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
	DESTINATION include
	FILES_MATCHING PATTERN "*.h"
)

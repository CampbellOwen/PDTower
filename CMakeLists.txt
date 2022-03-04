cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if (NOT ${ENVSDK} STREQUAL "")
	# Convert path from Windows
	file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
	execute_process(
			COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
			COMMAND head -n 1
			COMMAND cut -c9-
			OUTPUT_VARIABLE SDK
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

if (NOT EXISTS ${SDK})
	message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
	return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Game Name Customization
set(PLAYDATE_GAME_NAME PDTower)
set(PLAYDATE_GAME_DEVICE PDTower_DEVICE)

project(${PLAYDATE_GAME_NAME} C ASM CXX)

set(SOURCES src/main.cpp src/Application.cpp src/Assets.cpp)
set(HEADERS src/include/main.h src/include/Application.h src/include/Assets.h)

if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE} ${SDK}/C_API/buildsupport/setup.c ${SOURCES} ${HEADERS})
	target_include_directories(${PLAYDATE_GAME_DEVICE} PRIVATE src/include)
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED ${SOURCES} ${HEADERS})
	target_include_directories(${PLAYDATE_GAME_NAME} PRIVATE src/include)
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)


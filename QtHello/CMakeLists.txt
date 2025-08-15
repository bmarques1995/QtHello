# CMakeList.txt: projeto de CMake para QtSample, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
cmake_minimum_required(VERSION 3.22)

set(TARGET_NAME QtSample)

if(WIN32)
	trace_dependency(NAME Qt6 COMPONENTS Core Widgets Gui Network INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtbase.py" LIMIT_SEARCH_PATHS)
	trace_dependency(NAME Qt6 COMPONENTS Svg INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/qtsvg.py" LIMIT_SEARCH_PATHS)
endif()

file(GLOB_RECURSE SAMPLE_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_executable(${TARGET_NAME} ${SAMPLE_HDRS} ${SAMPLE_SRCS})
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Core Qt6::Widgets Qt6::Svg Qt6::Gui Qt6::Network)
target_include_directories(${TARGET_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Editor>
	$<INSTALL_INTERFACE:./>
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/pch>
)

if(BUILD_AS_WINDOWED_APP)
	set_target_properties(${TARGET_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR BUILD_AS_WINDOWED_APP)
	target_compile_definitions(${TARGET_NAME} PUBLIC SAMPLE_WINDOWED)
endif()

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)

# TODO: Adicione testes e instale destinos, se necessário.

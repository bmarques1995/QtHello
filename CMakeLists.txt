# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.22)

option(BUILD_AS_WINDOWED_APP "Build the app as win32" OFF)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("QtHello")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_helpers")

include(dep_tracer)
include(target_destination)
include(source_downloader)

# Inclua subprojetos.
add_subdirectory ("QtHello")

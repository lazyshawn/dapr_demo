cmake_minimum_required(VERSION 3.15)
project(projectName)

set(CMAKE_CXX_STANDARD 17)
# Support degug
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

SET(CMAKE_BUILD_TYPE "Debug")

if(WIN32)
  # create symbol for exporting lib for dynmic library
  SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  # control where the static and shared libraries are built so that on windows
  # we don't need to tinker with the path to run the executable
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
  # Build static in windows
  option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
  # Set the runtime lib for MSCV (global)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
  option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
endif()

# include_directories(include)
# 3rd party lib
# link_directories(lib)

# 编译 protbuf
add_subdirectory(proto)

# add_executable(test_state
#   src/test_state.cpp
# )
# target_link_libraries(test_state
#   httplib
# )
#
# add_executable(test_subscribe
#   src/test_subscribe.cpp
# )
# target_link_libraries(test_subscribe
#   httplib
# )
#
# add_executable(test_publish
#   src/test_publish.cpp
# )
# target_link_libraries(test_publish
#   httplib
# )
#
# add_executable(grpc_svr
#   src/test_grpc_svr.cpp
# )
# target_link_libraries(grpc_svr PUBLIC
#   libmath
# )
#
# add_executable(grpc_cli
#   src/test_grpc_cli.cpp
# )
# target_link_libraries(grpc_cli PUBLIC
#   libmath
# )

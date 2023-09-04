# build grpc proto lib
# mathtest_lib
add_library(libmath SHARED
  src/mathtest.pb.cc
  src/mathtest.grpc.pb.cc
)
target_include_directories(libmath PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(libmath PUBLIC
  protoc grpc++
)

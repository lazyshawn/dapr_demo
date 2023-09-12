add_executable(dapr_state
  dapr_state.cpp
)

add_executable(dapr_subscribe
  dapr_subscribe.cpp
)

add_executable(dapr_publish
  dapr_publish.cpp
)

add_executable(grpc_svr
  grpc_svr.cpp
)
target_link_libraries(grpc_svr PUBLIC
  libmath
)

add_executable(grpc_cli
  grpc_cli.cpp
)
target_link_libraries(grpc_cli PUBLIC
  libmath
)

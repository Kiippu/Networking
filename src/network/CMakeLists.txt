add_library(Network STATIC BSDSocket.cpp)
target_include_directories(Network PUBLIC "./")

add_executable(Executable main.cc)
target_link_libraries(Executable PUBLIC Network)
target_link_libraries(Executable PUBLIC simp_server)

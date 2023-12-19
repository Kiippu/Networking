add_executable(Executable main.cc)
target_link_libraries(Executable PUBLIC Network)
target_link_libraries(Executable PUBLIC server)
target_link_libraries(Executable PUBLIC client)

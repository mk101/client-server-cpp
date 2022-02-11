include_directories(${Boost_INCLUDE_DIR})
add_executable(server main.cpp CardParser.cpp Server.cpp)

target_link_libraries(server PUBLIC ${Boost_LIBRARIE})
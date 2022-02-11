include_directories(${Boost_INCLUDE_DIR})
add_executable(client main.cpp)

target_link_libraries(client PUBLIC ${Boost_LIBRARIE})
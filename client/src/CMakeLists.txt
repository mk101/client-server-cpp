include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIRS})
add_executable(client main.cpp Client.cpp)

target_link_directories(client PUBLIC ${Boost_LIBRARY_DIRS})
#target_link_libraries(client PUBLIC ${Boost_LIBRARY_DIRS}/)
#target_link_libraries(client ${Boost_LIBRARIES})

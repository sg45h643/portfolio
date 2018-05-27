include_directories(../src)
# include_directories(../src/String)

add_executable(DijkstraTest DijkstraTest.cpp)
target_link_libraries(DijkstraTest TangoDijkstra)
add_test(DijkstraTest_test DijkstraTest)

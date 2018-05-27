add_subdirectory(Deque)
add_subdirectory(Queue)
add_subdirectory(String)

add_library(TangoDijkstra SHARED Dijkstra.cpp)
target_link_libraries(TangoDijkstra TangoString)

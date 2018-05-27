include_directories(../src)

add_executable(DequeIteratorTest DequeIteratorTest.cpp)
add_test(QDequeTest_ DequeIteratorTest)

add_executable(DequeTest DequeTest.cpp)
add_test(QDequeTest2_ DequeTest)

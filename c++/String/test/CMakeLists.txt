include_directories(../src)

add_executable(StringAppendTest StringAppendTest.cpp)
target_link_libraries(StringAppendTest string)
add_test(StringAppend_test StringAppendTest)

add_executable(StringOperatorTest StringOperatorTest.cpp)
target_link_libraries(StringOperatorTest string)
add_test(StringOperator_test StringOperatorTest)

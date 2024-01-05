include(../cmake/install-gtest.cmake)

# Добавляем бинарники тестов
add_executable(
    vector_test
    vector_test.cc
)

add_executable(
  list_test
  list_test.cc
)

# Линкуемся к фреймворку
target_link_libraries(
    vector_test
    PRIVATE
    GTest::GTest
    gmock
    MSDCore
)

target_link_libraries(
    list_test
    PRIVATE
    GTest::GTest
    gmock
    MSDCore 
)

include(GoogleTest)
add_test(msd_gtests vector_test)
add_test(msd_gtests list_test)
set(TESTLIST "${TESTLIST}" PARENT_SCOPE)

include(../cmake/install-gtest.cmake)

# Добавляем бинарники тестов
add_executable(
    vector_test
    vector_test.cc
)


# Линкуемся к фреймворку
target_link_libraries(
    vector_test
    PRIVATE
    GTest::GTest
    gmock
    MSDCore
)

include(GoogleTest)
add_test(vector_gtests vector_test)
set(TESTLIST "${TESTLIST}" PARENT_SCOPE)

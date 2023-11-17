# Подключаем модуль, скачивающий нужное
include(FetchContent)
# Определение того, что нужно скачать
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Скачиваем gtest
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

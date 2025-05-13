# Добавляем цель для создания статической библиотеки
add_library(s21_matrix_oop STATIC ../s21_matrix_oop.cpp)

# Добавляем цель для тестов
set(target test_matrix)
add_executable(${target} 
    test_matrix.cpp
)

# Линкуем тесты с библиотекой и GTest
target_link_libraries(${target}
    PRIVATE
    GTest::gtest_main
    s21_matrix_oop # Линкуем тесты с нашей библиотекой
)

include(GoogleTest)
gtest_discover_tests(${target})

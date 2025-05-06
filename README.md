# Comp-club-task

## Для запуска проекта нужно иметь

### Для запуска проекта нужно иметь
- `cmake` >= 3.20
- `g++` | `clang` | `mingw` с полной поддержкой C++20

## Сборка

Для сборки проекта используется CMake. Чтобы собрать проект необходимо:
`cmake -DCMAKE_CXX_COMPILER=<your_compiler> -B your_build_directory`

`cmake --build your_build_directory`

`your_build_directory/app/app input`

Для удобства в репозитории предоставлен тестовый `input.txt` с тестовыми входными данными из ТЗ
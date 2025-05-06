# Comp-club-task

## Для запуска проекта нужно иметь

- `cmake` >= 3.20
- `g++` | `clang` c полной поддержкой C++20

Примеры сборки и запуск тестов для windows и ubuntu приведены в CI.

## Сборка и запуск

Сборка проекта происходит с помощью CMake. Чтобы включить сборку тестов
необходим флаг `-DBUILD_TESTING=ON`. По умолчанию тесты не собираются.

`cmake -S . -B build -DBUILD_TESTING=ON`

`cmake --build build`

Чтобы запустить программу

`build/app/app.exe input.txt`

Чтобы протестировать

`ctest --test-dir build`

Для удобства в репозитории предоставлен тестовый `input.txt` с тестовыми входными данными из ТЗ

---

## Тестирование

Для тестирования использовался фреймворк Google Test. Фреймворк подтягивается с помощью CMake FetchContent.

Были рассмотрены следующие валидные сценарии:

* Сценарий из тестового задания ([input1.txt](tests/input_files/input1.txt))
* Отсутствие событий ([input2.txt](tests/input_files/input2.txt))
* Клиент сидит до закрытия ([input3.txt](tests/input_files/input3.txt))
* Клиент сидит неполный час ([input4.txt](tests/input_files/input4.txt))
* Очередь была заполнена и клиент просто ушел ([input8.txt](tests/input_files/input8.txt))

Были рассмотрены следующие некорректные сценарии:

* Мусор в файле ([input5.txt](tests/input_files/input5.txt))
* До пробела в одной строке корректная информация, а после - нет ([input6.txt](tests/input_files/input6.txt))
* Некорректное тело у входящего события ([input7.txt](tests/input_files/input7.txt))
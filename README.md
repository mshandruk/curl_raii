# Curl RAII Wrapper

Минималистичная обёртка для libcurl с использованием идиомы RAII и адаптеров.

## Особенности

- RAII-обёртка для `CURL*` (`CurlRAII`)
- Простая сессия для HTTP-запросов (`CurlEasySession`)
- Интерфейсный подход для легкой подмены HTTP-клиента (`CurlRAIIAdapter` / `HttpClient`)
- Легко тестируется с помощью моков

# Системные зависимости

Проект использует **libcurl**. Перед сборкой нужно установить библиотеку и заголовочные файлы.

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install libcurl4-openssl-dev
```

Для сборки потребуется CMake

```bash
sudo apt install cmake
```

На других системах используйте менеджер пакетов вашей ОС.

# Примеры использования

Полные примеры находятся в папке [examples](examples):

- `http_get.cpp` — простой HTTP GET запрос
- `download_file.cpp` — скачивание файла

# Работа с субмодулями (GoogleTest)

Для поддержки тестов(gtest) нужно выполнить клонирование

```bash
git clone --recurse-submodules  https://github.com/mshandruk/curl_raii.git
```

если репозиторий был сколнирован без субмодулей:

```bash
git submodule update --init --recursive
```

Сборка
------

#### Только библиотека

```bash
cmake -B build
cmake --build build
```

#### С тестами

```bash
cmake -B build -DCURL_RAII_BUILD_TESTS=ON
cmake --build build
ctest --output-on-failure
```

#### С примерами

```bash
cmake -B build -DCURL_RAII_BUILD_EXAMPLES=ON
cmake --build build

./build/examples/http_get_example
./build/examples/download_file_example
```

Лицензия
--------
MIT License. Подробнее в файле LICENSE.

Curl RAII Wrapper
------------------

Минималистичная обёртка для libcurl с использованием идиомы RAII и адаптеров.

## Особенности

- RAII-обёртка для `CURL*` (`CurlRAII`)
- Простая сессия для HTTP-запросов (`CurlEasySession`)
- Интерфейсный подход для легкой подмены HTTP-клиента (`CurlRAIIAdapter` / `HttpClient`)
- Легко тестируется с помощью моков

Примеры использования
---------------------

Полные примеры находятся в папке [examples](examples):

- `http_get.cpp` — простой HTTP GET запрос
- `download_file.cpp` — скачивание файла

Сборка
------

#### Только библиотека

````
cmake -B build
````

````
cmake --build build
````

#### С тестами

````
cmake -B build -DBUILD_TESTS=ON
````

````
cmake --build build
````

Запуск тестов

```
ctest --output-on-failure
```

#### С примерами

```
cmake -B build -DBUILD_EXAMPLES=ON
```

````
cmake --build build
````

Запуск

````
./build/examples/http_get_example
````

````
./build/examples/download_file_example
````

# KVS — in-memory key-value хранилище

Учебный проект: хранилище "ключ → значение" в памяти с сетевым доступом
(сеть появится на следующих этапах). Прообраз — Redis.

## Сборка

    cmake -B build -G Ninja
    cmake --build build

## Тесты

    ctest --test-dir build --output-on-failure

## Запуск

    ./build/kvs_cli

Команды CLI: `SET key value`, `GET key`, `DEL key`, `EXISTS key`,
`TYPE key`, `INCR key`, `EXIT`.

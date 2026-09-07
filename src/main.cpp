#include <print>
#include <iostream>
#include <sstream>
#include <string>
#include "store.hpp"

int main() {
    Store store;
    store.set("name", Value("Konstantin"));
    store.set("lang", Value("C++"));

    std::println("=== Демонстрация захвата в лямбдах ===");

    int count_ref = 0;
    store.for_each([&count_ref](const std::string& key, const Value& value) {
        ++count_ref;
        std::println("[по ссылке] #{} {} = {}", count_ref, key, value.str());
    });
    std::println("count_ref после обхода: {}", count_ref); // не 0

    int count_val = 0;
    store.for_each([count_val](const std::string& key, const Value& value) mutable {
        ++count_val;
        std::println("[по значению] #{} {} = {}", count_val, key, value.str());
    });
    std::println("count_val после обхода: {}", count_val); // остался 0!

    std::println("=== Простой CLI: SET / GET / DEL / EXIT ===");

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "EXIT") {
            break;
        } else if (cmd == "SET") {
            std::string key, val;
            iss >> key >> val;
            store.set(key, Value(val));
            std::println("OK");
        } else if (cmd == "GET") {
            std::string key;
            iss >> key;
            if (const Value* v = store.get(key)) {
                std::println("{}", v->str());
            } else {
                std::println("(nil)");
            }
        } else if (cmd == "DEL") {
            std::string key;
            iss >> key;
            std::println("{}", store.del(key) ? "1" : "0");
        } else if (!cmd.empty()) {
            std::println("Неизвестная команда: {}", cmd);
        }
    }
    return 0;
}

#include <print>
#include <iostream>
#include <string>
#include "store.hpp"
#include "command.hpp"

int main() {
    Store store;
    std::println("KVS — SET/GET/DEL/EXISTS/TYPE/INCR, EXIT для выхода");

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "EXIT") {
            break;
        }
        if (auto command = parse(line); command) {
            std::println("{}", execute(store, *command));
        } else if (!line.empty()) {
            std::println("Неизвестная команда или неверные аргументы");
        }
    }
    return 0;
}

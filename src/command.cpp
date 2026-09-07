#include "command.hpp"
#include "store.hpp"
#include "overloaded.hpp"
#include <cctype>

std::vector<std::string_view> tokenize(std::string_view input) {
    std::vector<std::string_view> tokens;
    std::size_t i = 0;
    const std::size_t n = input.size();

    auto skip_spaces = [&]() {
        while (i < n && std::isspace(static_cast<unsigned char>(input[i]))) {
            ++i;
        }
    };

    skip_spaces();
    while (i < n) {
        if (input[i] == '"') {
            std::size_t start = i + 1;
            std::size_t end = input.find('"', start);
            if (end == std::string_view::npos) {
                tokens.push_back(input.substr(start));
                i = n;
            } else {
                tokens.push_back(input.substr(start, end - start));
                i = end + 1;
            }
        } else {
            std::size_t start = i;
            while (i < n && !std::isspace(static_cast<unsigned char>(input[i]))) {
                ++i;
            }
            tokens.push_back(input.substr(start, i - start));
        }
        skip_spaces();
    }
    return tokens;
}

std::optional<Command> parse(std::string_view line) {
    auto tokens = tokenize(line);
    if (tokens.empty()) {
        return std::nullopt;
    }

    const std::string_view cmd = tokens[0];

    if (cmd == "SET" && tokens.size() >= 3) {
        return Command{SetCommand{
            std::string(tokens[1]),
            Value(std::string(tokens[2]))
        }};
    }
    if (cmd == "GET" && tokens.size() >= 2) {
        return Command{GetCommand{std::string(tokens[1])}};
    }
    if (cmd == "DEL" && tokens.size() >= 2) {
        return Command{DelCommand{std::string(tokens[1])}};
    }
    if (cmd == "EXISTS" && tokens.size() >= 2) {
        return Command{ExistsCommand{std::string(tokens[1])}};
    }
    if (cmd == "TYPE" && tokens.size() >= 2) {
        return Command{TypeCommand{std::string(tokens[1])}};
    }
    if (cmd == "INCR" && tokens.size() >= 2) {
        return Command{IncrCommand{std::string(tokens[1])}};
    }
    return std::nullopt;
}

std::string execute(Store& store, const Command& command) {
    return std::visit(overloaded{
        [&store](const SetCommand& c) -> std::string {
            store.set(c.key, c.value);
            return "OK";
        },
        [&store](const GetCommand& c) -> std::string {
            if (auto v = store.get(c.key); v) {
                return v->to_display_string();
            }
            return "(nil)";
        },
        [&store](const DelCommand& c) -> std::string {
            return store.del(c.key) ? "1" : "0";
        },
        [&store](const ExistsCommand& c) -> std::string {
            return store.get(c.key).has_value() ? "1" : "0";
        },
        [&store](const TypeCommand& c) -> std::string {
            if (auto v = store.get(c.key); v) {
                return std::string(v->type_name());
            }
            return "none";
        },
        [&store](const IncrCommand& c) -> std::string {
            auto v = store.get(c.key);
            if (!v) {
                store.set(c.key, Value(std::int64_t{1}));
                return "1";
            }
            if (!std::holds_alternative<std::int64_t>(v->storage())) {
                return "ERROR: value is not an integer";
            }
            std::int64_t next = std::get<std::int64_t>(v->storage()) + 1;
            store.set(c.key, Value(next));
            return std::to_string(next);
        }
    }, command);
}

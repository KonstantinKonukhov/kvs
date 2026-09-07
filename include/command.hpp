#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <variant>
#include "value.hpp"

struct SetCommand   { std::string key; Value value; };
struct GetCommand    { std::string key; };
struct DelCommand    { std::string key; };
struct ExistsCommand { std::string key; };
struct TypeCommand   { std::string key; };
struct IncrCommand   { std::string key; };

using Command = std::variant<
    SetCommand, GetCommand, DelCommand,
    ExistsCommand, TypeCommand, IncrCommand
>;


std::vector<std::string_view> tokenize(std::string_view input);

std::optional<Command> parse(std::string_view line);

class Store;

std::string execute(Store& store, const Command& command);

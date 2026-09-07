#pragma once
#include <string>
#include <string_view>
#include <cstdint>
#include <variant>
#include "overloaded.hpp"

class Value {
public:
    using Storage = std::variant<std::string, std::int64_t, double>;

    explicit Value(std::string data) : data_(std::move(data)) {}
    explicit Value(std::int64_t data) : data_(data) {}
    explicit Value(double data) : data_(data) {}

    const Storage& storage() const { return data_; }

    std::string_view type_name() const {
        return std::visit(overloaded{
            [](const std::string&) -> std::string_view { return "string"; },
            [](std::int64_t) -> std::string_view { return "int"; },
            [](double) -> std::string_view { return "double"; }
        }, data_);
    }

    std::string to_display_string() const {
        return std::visit(overloaded{
            [](const std::string& s) { return s; },
            [](std::int64_t i) { return std::to_string(i); },
            [](double d) { return std::to_string(d); }
        }, data_);
    }

private:
    Storage data_;
};

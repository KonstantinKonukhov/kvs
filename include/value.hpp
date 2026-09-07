#pragma once
#include <string>
#include <utility>

class Value {
public:
    explicit Value(std::string data) : data_(std::move(data)) {}

    const std::string& str() const { return data_; }

private:
    std::string data_;
};

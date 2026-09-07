#pragma once
#include <map>
#include <string>
#include "value.hpp"

class Store {
public:
    void set(const std::string& key, Value value);
    const Value* get(const std::string& key) const;
    bool del(const std::string& key);
    std::size_t size() const;

    template <typename Fn>
    void for_each(Fn fn) const {
        for (const auto& [key, value] : data_) {
            fn(key, value);
        }
    }

private:
    std::map<std::string, Value> data_;
};

#include "store.hpp"
#include <utility>

void Store::set(const std::string& key, Value value) {
    data_.insert_or_assign(key, std::move(value));
}

std::optional<Value> Store::get(const std::string& key) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        return std::nullopt;
    }
    return it->second;
}

bool Store::del(const std::string& key) {
    return data_.erase(key) > 0;
}

std::size_t Store::size() const {
    return data_.size();
}

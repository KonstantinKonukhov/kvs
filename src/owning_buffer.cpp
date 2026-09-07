#include "owning_buffer.hpp"
#include <algorithm>
#include <utility>

OwningBuffer::OwningBuffer(const char* data, std::size_t size)
    : data_(new char[size]), size_(size) {
    std::copy(data, data + size, data_);
}

OwningBuffer::~OwningBuffer() {
    delete[] data_;
}

OwningBuffer::OwningBuffer(const OwningBuffer& other)
    : data_(new char[other.size_]), size_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

OwningBuffer& OwningBuffer::operator=(const OwningBuffer& other) {
    OwningBuffer tmp(other);
    swap(tmp);
    return *this;
}

OwningBuffer::OwningBuffer(OwningBuffer&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

OwningBuffer& OwningBuffer::operator=(OwningBuffer&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

void OwningBuffer::swap(OwningBuffer& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}

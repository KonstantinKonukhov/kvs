#pragma once
#include <cstddef>


class OwningBuffer {
public:
    OwningBuffer(const char* data, std::size_t size);
    ~OwningBuffer();

    OwningBuffer(const OwningBuffer& other);

    OwningBuffer& operator=(const OwningBuffer& other);

    OwningBuffer(OwningBuffer&& other) noexcept;

    OwningBuffer& operator=(OwningBuffer&& other) noexcept;

    void swap(OwningBuffer& other) noexcept;

    std::size_t size() const { return size_; }
    const char* data() const { return data_; }

private:
    char* data_;
    std::size_t size_;
};

#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* m_buffer = nullptr;
    size_t m_size = 0u;
    size_t m_capacity = 0;

    void realloc() {
        constexpr size_t INITIAL_CAPACITY = 16u;
        const size_t new_capacity = std::max(INITIAL_CAPACITY, m_capacity * 2);

        auto* new_buffer = new T[new_capacity];
        if (m_capacity != 0u) {
            std::copy(m_buffer, m_buffer + m_size, new_buffer);
        }
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

public:
    Vector() = default;

    Vector(std::initializer_list<T> initList) {
        for (const auto& elem : initList) {
            push_back(elem);
        }
    }

    ~Vector() {
        delete[] m_buffer;
    }

    int size() const noexcept {
        return m_size;
    }

    int capacity() const noexcept {
        return m_capacity;
    }

    bool empty() const noexcept {
        return m_size == 0;
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            realloc();
        }
        m_buffer[m_size++] = value;
    }
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        m_buffer[m_size--];
    }

    void insert(int index, const T& value) {
        if (index >= 0 && index <= m_size) {
            if (m_size == m_capacity) {
                realloc();
            }
            for (int i = m_size - 1; i >= index; --i) {
                m_buffer[i + 1] = m_buffer[i];
            }
            m_buffer[index] = value;
            m_size++;
        }
    }

    void erase(int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < m_size - 1; ++i) {
            m_buffer[i] = m_buffer[i + 1];
        }
        m_size--;
    }

    T* begin() const {
        return m_buffer;
    }

    T* end() const {
        return m_buffer + m_size;
    }
};

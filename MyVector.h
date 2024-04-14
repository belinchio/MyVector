#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>

template <typename T>
class Vector {

public:

    using value_type        = T;
    using size_type         = size_t;
    using difference_type   = ptrdiff_t;
    using pointer           = value_type *;
    using const_pointer     = const value_type *;
    using reference         = value_type &;
    using const_reference   = const value_type &;

private:

    pointer m_buffer = nullptr;
    size_type m_size = 0u;
    size_type m_capacity = 0;

    void realloc() {
        constexpr size_type INITIAL_CAPACITY = 16u;
        const size_type new_capacity = std::max(INITIAL_CAPACITY, m_capacity * 2);

        auto* new_buffer = new value_type[new_capacity];
        if (m_capacity != 0u) {
            std::copy(m_buffer, m_buffer + m_size, new_buffer);
        }
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

public:

    //---------------Конструкторы-/-деструкторы---------------

    // Конструктор по умолчанию
    Vector() = default;

    //Конструктор копирования
    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        if (other.m_capacity != 0u) {
            m_buffer = new value_type[other.m_capacity];
            try {
                std::copy(other.m_buffer, other.m_buffer + other.m_size, m_buffer);
            } catch (...) {
                delete[]m_buffer;
                throw;
            }
        }
    }

    // Коструктор перемещения
    Vector(const Vector&& other) noexcept {
        swap(other);
    }

    // Конструктор, инициализирующий списком initList
    Vector(std::initializer_list<T> initList) {
        for (const auto& elem : initList) {
            push_back(elem);
        }
    }

    // Деструктор
    ~Vector() {
        clear();
        delete[] m_buffer;
    }

    //---------------Итераторы---------------
    /* 
     * begin/cbegin возвращает итератор на начало
     * end/cend возвращает итератор на конеч
     * rbegin/crbegin возвращает обратный итератор на начало
     * rend/crend вщзвращает обратный итератор на конец
     */

    pointer begin() const {
        return m_buffer;
    }

    const_pointer cbegin() const {
        return m_buffer;
    }

    pointer end() const {
        return m_buffer + m_size;
    }

    const_pointer cend() const {
        return m_buffer + m_size;
    }

    std::reverse_iterator<pointer> rbegin() const {
        return std::reverse_iterator<pointer>(m_buffer + m_size);
    }

    std::reverse_iterator<const_pointer> crbegin() const {
        return std::reverse_iterator<const_pointer>(m_buffer + m_size);
    }

    std::reverse_iterator<pointer> rend() const {
        std::reverse_iterator<pointer>m_buffer;
    }

    std::reverse_iterator<const_pointer> crend() const {
        return std::reverse_iterator<const_pointer>(m_buffer);
    }

    //---------------Доступ-к-элементам---------------

    reference at(const size_type index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_buffer[index];
    }

    const_reference operator[] (size_type index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    reference operator[] (size_type index) noexcept {
        return m_buffer[index];
    }

    Vector<value_type>& operator= (const Vector<value_type>& other) {
        Vector<value_type> copy(other);
        swap(copy);
    }

    constexpr const_reference front() const {
        return *begin();
    }

    constexpr const_reference back() const {
        return *std::prev(end());
    }

    constexpr reference data() noexcept {
        return m_buffer;
    }

    constexpr const_reference data() const noexcept {
        return m_buffer;
    }

    //---------------Ёмкость-контейнера---------------

    // Метод для проверки пуст ли вектор
    [[nodiscard]] bool empty() const noexcept {
        return m_size == 0;
    }

    // Метод для получения текущего размера вектора
    [[nodiscard]] size_type size() const noexcept {
        return m_size;
    }

    // Метод для получения максимально возможной вместимости вектора
    [[nodiscard]] size_type max_size() const noexcept {
        return std::numeric_limits<size_t>::max();
    }

    // Метод резервирования памяти
    void reserve(size_type new_capacity) {
        if (new_capacity <= m_capacity) {return;}
        
        T* new_buffer = new value_type[new_capacity];
        if (m_buffer != nullptr) {
            std::copy(m_buffer, m_buffer + m_size, new_buffer);
            delete[] m_buffer;
        }
        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

    // Метод для получения текущей вместимости вектора
    [[nodiscard]] size_type capacity() const noexcept {
        return m_capacity;
    }

    void shrinnk_to_fit() noexcept {
        if (m_buffer == nullptr || m_capacity == m_size) {return;}

        reference new_buffer = new value_type[m_size];
        std::copy(m_buffer, m_buffer + m_size, new_buffer);
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_capacity = m_size;
    }

    //---------------Модификаторы---------------

    // Метод очистки вектора
    void clear() {
        m_size = 0;
    }

    // Метод для вставки элемента по указанному индексу
    void insert(size_type index, const_reference value) {
        try {
            if (index > 0 && index <= m_size - 1) {
                if (m_size == m_capacity) {
                    realloc();
                }
                for (size_type i = m_size - 1; i >= index; --i) {
                    m_buffer[i + 1] = m_buffer[i];
                }
                m_buffer[index] = value;
                m_size++;
            }
        }  catch (...) {
            throw std::out_of_range("The index is out of acceptable range");

        }
    }

    //Метод для ставки элемента с заменой по указаному индексу
    template<typename Args>
    void emplace(const size_type index, Args&& args) const {
        if (index < 0 && index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        m_buffer[index] = T(std::forward<Args>(args));
    }

    // Метод для удаления элемента по указанному индуксу
    void erase(const size_type index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < m_size - 1; ++i) {
            m_buffer[i] = m_buffer[i + 1];
        }
        m_size--;
    }

    // Метод для добавления элемента в конец вектора
    void push_back(const_reference value) {
        if (m_size == m_capacity) {
            realloc();
        }
        m_buffer[m_size++] = value;
    }

    // Метод для удаления последнего элемента
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        m_buffer[m_size--];
    }
    
    //Метод для изменения размера вектора
    void resize(size_type new_size) {
        if (new_size < 0) {
            new_size = 0;
        }
        if (new_size != m_size) {
            if (new_size > m_capacity) {
                m_capacity = new_size;
                pointer new_buffer = new value_type[m_capacity];
                for (auto i = 0; i < m_size; ++i) {
                    new_buffer[i] = m_buffer[i];
                }
                delete[] m_buffer;
                m_buffer = new_buffer;
            }
            m_size = new_size;
        }
    }

    // Медод обнена содержимого двух векторов
    void swap(Vector<value_type>& other) noexcept {
        using std::swap;
        std::swap(m_buffer, other.m_buffer);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
};
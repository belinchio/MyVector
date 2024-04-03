#pragma once

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <cassert>

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

    // Конструктор по умолчанию
    Vector() = default;

    //Конструктор копирования
    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        if (other.m_capacity != 0u) {
            m_buffer = new T[other.m_capacity];
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
        delete[] m_buffer;
    }

    /* Итераторы
     *      begin/cbegin возвращает итератор на начало
     *      end/cend возвращает итератор на конеч
     *      rbegin/crbegin возвращает обратный итератор на начало
     *      rend/crend вщзвращает обратный итератор на конец
     */

    const T& operator [](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator [](size_t index) noexcept {
        return m_buffer[index];
    }

    T* begin() const {
        return m_buffer;
    }

    const T* cbegin() const {
        return m_buffer;
    }

    T* end() const {
        return m_buffer + m_size;
    }

    const T* cend() const {
        return m_buffer + m_size;
    }

    std::reverse_iterator<T*> rbegin() const {
        return std::reverse_iterator<T*>(m_buffer + m_size);
    }

    std::reverse_iterator<const T*> crbegin() const {
        return std::reverse_iterator<const T*>(m_buffer + m_size);
    }

    std::reverse_iterator<T*> rend() const {
        std::reverse_iterator<T*>m_buffer;
    }

    std::reverse_iterator<const T*> crend() const {
        return std::reverse_iterator<const T*>(m_buffer);
    }

    // Метод для получения текущего размера вектора
    [[nodiscard]] size_t size() const noexcept {
        return m_size;
    }

    // Метод для получения максимально возможной вместимости вектора
    [[nodiscard]] size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max();
    }

    // Метод для получения текущей вместимости вектора
    [[nodiscard]] size_t capacity() const noexcept {
        return m_capacity;
    }

    // Метод для проверки "пуст ли" вектор
    [[nodiscard]] bool empty() const noexcept {
        return m_size == 0;
    }

    // Метод для добавления элемента в конец вектора
    void push_back(const T& value) {
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

    // Метод для вставки элемента по указанному индексу
    void insert(size_t index, const T& value) {
        try {
            if (index > 0 && index <= m_size - 1) {
                if (m_size == m_capacity) {
                    realloc();
                }
                for (size_t i = m_size - 1; i >= index; --i) {
                    m_buffer[i + 1] = m_buffer[i];
                }
                m_buffer[index] = value;
                m_size++;
            }
        }  catch (...) {
            throw std::out_of_range("The index is out of acceptable range");

        }
    }

    // Метод для удаления элемента по указанному индуксу
    void erase(int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < m_size - 1; ++i) {
            m_buffer[i] = m_buffer[i + 1];
        }
        m_size--;
    }

    // Метод для доступа к элементу по указанному индексу
    T& at(const size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_buffer[index];
    }

    //Метод для ставки элемента с заменой по указаному индексу
    template<typename Args>
    void emplace(const int index, Args&& args) const {
        if (index < 0 && index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        m_buffer[index] = T(std::forward<Args>(args));
    }

    //Метод для изменения размера вектора
    void resize(size_t new_size) {
        if (new_size < 0) {
            new_size = 0;
        }
        if (new_size != m_size) {
            if (new_size > m_capacity) {
                m_capacity = new_size;
                T* new_buffer = new T[m_capacity];
                for (size_t i = 0; i < m_size; ++i) {
                    new_buffer[i] = m_buffer[i];
                }
                delete[] m_buffer;
                m_buffer = new_buffer;
            }
            m_size = new_size;
        }
    }

    // Медод обнена содержимого двух векторов
    void swap(Vector<T>& other) noexcept {
        using std::swap;
        std::swap(m_buffer, other.m_buffer);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    constexpr const T& front() const {
        return *begin();
    }

    constexpr const T& back() const {
        return *std::prev(end());
    }

    constexpr T* data() noexcept {
        return m_buffer;
    }

    constexpr const T* data() const noexcept {
        return m_buffer;
    }

//    constexpr T& at(size_t index) {
//        try {
//            if (index >= 0 && index < m_size) {
//                return m_buffer[index];
//            }
//        } catch (std::exception& e) {
//            std::cerr << e.what() << std::endl;
//        }
//    }
};

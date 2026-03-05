#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace softacademy {

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type  = std::size_t;

    Vector() noexcept : m_data(nullptr), m_size(0), m_cap(0) 
    {}

    explicit Vector(size_type count) : m_size(count), m_cap(count) {
        m_data = new T[m_cap]();
    }

    Vector(const Vector& other) : m_data(new T[other.m_cap]), m_size(other.m_size), m_cap(other.m_cap) {
        for (size_type i = 0; i < other.m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    Vector(Vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap) {
        other.m_data = nullptr; other.m_size = 0; other.m_cap = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size; m_cap = other.m_cap;
            m_data = new T[m_cap];
            for (size_type i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_data = other.m_data; m_size = other.m_size; m_cap = other.m_cap;
            other.m_data = nullptr; other.m_size = 0; other.m_cap = 0;
        }
        return *this;
    }

    ~Vector() { 
        delete[] m_data; 
    }

    size_type size() const noexcept { 
		return m_size; 
	}
    size_type capacity() const noexcept { 
		return m_cap; 
	}
    bool empty() const noexcept { 
		return m_size == 0; 
	}

    void reserve(size_type new_cap) {
        if (new_cap > m_cap) {
            reallocate(new_cap);
        }
    }

    T& operator[](size_type index) noexcept {
		 return m_data[index]; 
	}
    const T& operator[](size_type index) const noexcept { 
		return m_data[index]; 
	}

    T& at(size_type index) {
        if (index >= m_size) {
            throw std::out_of_range("Incorrect index:");
        }
        return m_data[index];
    }

    const T& at(size_type index) const {
        if (index >= m_size) {
            throw std::out_of_range("Incorrect index:");
        }
        return m_data[index];
    }

    T& front() { 
		return m_data[0]; 
	}
    const T& front() const { 
		return m_data[0]; 
	}
    T& back() { 
		return m_data[m_size - 1]; 
	}
    const T& back() const { 
		return m_data[m_size - 1]; 
	}

    T* data() noexcept { 
		return m_data; 
	}
    const T* data() const noexcept { 
		return m_data; 
	}

    void clear() noexcept { 
		m_size = 0; 
	}

    void push_back(const T& value) {
        grow_if_needed();
        m_data[m_size++] = value;
    }

    void push_back(T&& value) {
        grow_if_needed();
        m_data[m_size++] = std::move(value);
    }

    void pop_back() { 
        if (m_size > 0) {
            m_size--; 
        }
    }

    void resize(size_type new_size) {
        if (new_size > m_cap) {
            reserve(new_size);
        }
        m_size = new_size;
    }

    void resize(size_type new_size, const T& value) {
        if (new_size > m_cap) {
            reserve(new_size);
        }
        for (size_type i = m_size; i < new_size; i++) {
            m_data[i] = value;
        }
        m_size = new_size;
    }

    void swap(Vector& other) noexcept {
        T* tmp = new T[m_cap];
        for(int i = 0; i < (int)m_size; i++) {
            tmp[i] = m_data[i];
        }
        m_data = new T[other.m_cap];
        for(int i = 0; i < (int)other.m_size; i++) {
            m_data[i] = other.m_data[i];
        }
        other.m_data = new T[m_cap];
        for(int i = 0; i < (int)m_size; i++) {
            other.m_data[i] = tmp[i];
        }
        tmp = nullptr;
        m_size = other.m_size;
    }

private:
    T* m_data;
    size_type m_size;
    size_type m_cap;

    void grow_if_needed() {
        if (m_size < m_cap) {
            return;
        }

        if (m_cap == 0) {
            m_cap = 1;
        }

        reallocate(m_cap * 2);
    }

    
    void reallocate(size_type new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_type i = 0; i < m_size; i++) {
            new_data[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = new_data;
        m_cap = new_capacity;
    }
};

} // namespace softacademy

#endif

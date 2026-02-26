#include <iostream>

template <typename T> 
class Vector {
public:
	Vector(): m_data(nullptr), m_cap(0), m_size(0) {} 
	Vector(T* arr, int size) {
		m_size = size;
		m_cap = 1;

		while (m_cap <= size) {
			m_cap *= 2;
		}

		m_data = new T[m_cap];

		for (int i = 0; i < size; i++) {
			 m_data[i] = arr[i];
		}
	}

	Vector(const Vector& other): m_data(new T[other.m_cap]), m_size(other.m_size), m_cap(other.m_cap) {
		for (int i = 0; i < other.m_size; i++) { 
			m_data[i] = other.m_data[i];
		}
	}

	Vector(Vector&& other) : m_data(other.m_data) {
		other.m_data = nullptr;
		m_cap = 0;
		m_size = 0;
	}
	~Vector() {
		delete[] m_data;
	}
	
	Vector& operator=(const Vector& other) {	
		m_data = new T[other.m_cap];

		for (int i = 0; i < other.m_size; i++) { 
			m_data[i] = other.m_data[i];
		}
		m_cap = other.m_cap;
		m_size = other.m_size;
		return *this;
	}

	Vector&& operator=(Vector&& other) {
		m_data = new T[other.m_cap];
		for (int i = 0; i < other.m_size; i++) {
			m_data[i] = other.m_data[i];
		}
		m_cap = other.m_cap;
		m_size = other.m_size;
		other.m_data = nullptr;
		m_cap = 0;
		m_size = 0;
		return *this;
	}
public:
	T operator[](int index) {
		return m_data[index];
	}
public: 
	void push_back(const T value) {
		if (m_cap > m_size) {	
			m_data[m_size] = value;
			m_size++;
			return;
		}
		T* tmp = new T[m_cap];
		for (int i = 0; i < m_size; i++) {
			tmp[i] = m_data[i];
		}

        while (m_cap <= m_size) {
            m_cap *= 2;
        }

        m_data = nullptr;
        m_data = new T[m_cap];
        for(int i = 0; i < m_size; i++) {
            m_data[i] = tmp[i];
        }
		m_data[m_size] = value;
		m_size++;
		tmp = nullptr;

		return;	
	}

	void pop_back() {
		m_size--;
	}

	void insert(const T value, int index) {
		if(index < 0 || index > m_size) {
			throw std::invalid_argument("Incorrect index:");
		} 

		T* tmp = new T[m_cap];
        for (int i = 0; i < m_size; i++) {
            tmp[i] = m_data[i];
        }

        while (m_cap <= m_size) {
            m_cap *= 2;
        }

        m_data = nullptr;
        m_data = new T[m_cap];
        for(int i = 0; i < m_size; i++) {
            m_data[i] = tmp[i];
        }
        m_size++;
        tmp = nullptr;

		for(int i = m_size; i > index; i--) {
			m_data[i] = m_data[i--];
		}

		m_data[index] = value;
	}
	
	void erase(int index) {
		if(index < 0 || index > m_size) {
			throw std::invalid_argument("Incorrect index:");
		}
		
		for(int i = index; i < m_size; i++) {
			m_data[i] = m_data[i + 1];
		}
		m_size--;
	}
	
	void swap(Vector& other) {
		T* tmp = new T[m_cap];
		for(int i = 0; i < m_size; i++) {
			tmp[i] = m_data[i];
		}
		
		m_data = new T[other.m_cap];
		for(int i = 0; i < other.m_size; i++) {
			m_data[i] = other.m_data[i];
		}

		other.m_data = new T[m_cap];
		for(int i = 0; i < m_size; i++) {
			other.m_data[i] = tmp[i];
		}

		tmp = nullptr;
		m_size = other.m_size;
	}

	T at(int index) {
		if(index < 0 || index > m_size) {
			throw std::invalid_argument("Incorrect index:");
		}
		return m_data[index];
	}

	T getFront() {
		return m_data[0];
	}
	
	T getBack() {
		return m_data[m_size];
	}

	int getCapacity() {
		return m_cap;
	}

	int getSize() {
		return m_size;
	}

	bool isEmpty() {
		if(m_size == 0) {
			return true;
		}
		return false;
	}

	void clear() {
		m_size = 0;
		m_cap = 1;
	}

private:
	T* m_data;
	int m_cap;
	int m_size;
};

int main() {
	
	return 0;
}

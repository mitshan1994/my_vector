#include <initializer_list>
#include <cstdlib>  // for size_t
#include <iostream>
#include <cstring>  // for memcpy

template <typename T>
class Vector {
public:
    using iterator = T*;
    // create an empty vector
    Vector();
    // create a vector object with size size
    Vector(int size);
    Vector(const Vector<T> &rhs);
    // rvalue reference to take the resource
    Vector(Vector<T> &&rhs);
    Vector(std::initializer_list<T> il);
    ~Vector();

    Vector<T>& operator=(const Vector<T> &rhs);
    Vector<T>& operator=(Vector<T> &&rhs);

    iterator begin();
    iterator end();
    std::size_t size() const;
    std::size_t capacity() const;
    bool is_empty() const;
    T at(std::size_t idx);
    T& operator[](std::size_t n)
        { return buffer[n]; }
    const T& operator[](std::size_t n) const
        { return buffer[n]; }
    void set_at(std::size_t idx, T new_value);
    void push_back(const T &t);
    void push_back(T &&t);
    void pop_back();
    void print() const;
    
private:
    // if size == capacity, return true
    bool is_full();
    // expand the capacity to satisfy the needs
    bool expand();
    
    size_t _size;  // underscore because the same name with member functions
    size_t _capacity;
    T *buffer;
};

template <typename T>
Vector<T>::Vector() : Vector(10)
{
    std::cout << "Vector() constructor used\n";
//    Vector(10);  // default size 10
}

template <typename T>
Vector<T>::Vector(int size)
{
    _size = size;
    _capacity = size * 2 + 1;
    buffer = new T[_capacity];
    std::cout << "Vector(int) constructor used\n";
}

template <typename T>
Vector<T>::Vector(const Vector<T> &rhs)
{
    _size = rhs._size;
    _capacity = _size * 2 + 1;
    buffer = new T[_capacity];
    memcpy(buffer, rhs.buffer, sizeof(T) * _size);
    std::cout << "reference constructor used\n";
}
 
template <typename T>
Vector<T>::Vector(Vector<T> &&rhs)
{
    buffer = rhs.buffer;
    _size = rhs._size;
    _capacity = rhs._capacity;
    rhs._size = rhs._capacity = 0;
    rhs.buffer = nullptr;
    std::cout << "rvalue constructor used\n";
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> il)
{
    _size = il.size();
    _capacity = _size * 2 + 1;
    buffer = new T[_capacity];
    for (auto it = il.begin(); it != il.end(); ++it)
        buffer[it - il.begin()] = *it;
    std::cout << "initializer_list constructor used.\n";
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] buffer;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &rhs)
{
    if (_capacity < rhs._size) {
        delete[] buffer;
        buffer = new T[rhs._capacity];
        _capacity = rhs._capacity;
    }
    memcpy(buffer, rhs.buffer, sizeof(T) * rhs._size);
    _size = rhs._size;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&rhs)
{
    if (&rhs == this)
        return *this;
    delete[] buffer;
    buffer = rhs.buffer;
    _size = rhs._size;
    _capacity = rhs._capacity;
    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return buffer;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return buffer + _size;
}

template <typename T>
std::size_t Vector<T>::size() const
{
    return _size;
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
    return _capacity;
}

template <typename T>
bool Vector<T>::is_empty() const
{
    return 0 == _size;
}

template <typename T>
T Vector<T>::at(std::size_t idx)
{
    return buffer[idx];
}

template <typename T>
void Vector<T>::set_at(std::size_t idx, T new_value)
{
    buffer[idx] = new_value;
}

template <typename T>
void Vector<T>::push_back(const T &t)
{
    if(is_full())
        expand();
    buffer[_size++] = t;
}

template <typename T>
void Vector<T>::push_back(T &&t)
{
    if (is_full())
        expand();
    buffer[_size++] = std::move(t); // if T has move assignment
}

template <typename T>
bool Vector<T>::is_full()
{
    return _size == _capacity;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (_size == 0) {
        std::cout << "No element to pop\n";
        return;
    }
    --_size();
}

template <typename T>
bool Vector<T>::expand()
{
    T *new_buffer = new T[_capacity * 2 + 1];
    memcpy(new_buffer, buffer, sizeof(T) * _size);
    _capacity = _capacity * 2 + 1;
    delete[] buffer;
    buffer = new_buffer;
}

template <typename T>
void Vector<T>::print() const
{
    for (int i = 0; i != _size; ++i)
        std::cout << buffer[i] << "  ";
    std::cout << std::endl;
}

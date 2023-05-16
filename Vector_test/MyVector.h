#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <limits>

template <class T>
class MyVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    using iterator = T*;
    using const_iterator = const T*;

    // Constructors
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}
    MyVector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {}

    // Destructor
    ~MyVector() {
        delete[] data_;
    }

    // Copy assignment operator
    MyVector<T>& operator=(const MyVector<T>& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    // Assign values to the container
    void assign(size_t count, const T& value) {
        clear();
        resize(count, value);
    }

    // Assign a range of values to the container
    template <typename InputIterator>
    void assign_range(InputIterator first, InputIterator last) {
        clear();
        insert(end(), first, last);
    }

    // Returns the associated allocator
    // (assuming default allocator here)
    std::allocator<T> get_allocator() const {
        return std::allocator<T>();
    }

    // Element access
    T& at(size_t pos) {
        if (pos >= size_)
            throw std::out_of_range("Index out of range");
        return data_[pos];
    }

    const T& at(size_t pos) const {
        if (pos >= size_)
            throw std::out_of_range("Index out of range");
        return data_[pos];
    }

    T& operator[](size_t pos) {
        return data_[pos];
    }

    const T& operator[](size_t pos) const {
        return data_[pos];
    }

    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    // Iterators
    iterator begin() {
        return data_;
    }

    const_iterator begin() const {
        return data_;
    }

    const_iterator cbegin() const {
        return data_;
    }

    iterator end() {
        return data_ + size_;
    }

    const_iterator end() const {
        return data_ + size_;
    }

    const_iterator cend() const {
        return data_ + size_;
    }

    // Reverse iterators
    std::reverse_iterator<iterator> rbegin() {
        return std::reverse_iterator<iterator>(end());
    }

    std::reverse_iterator<const_iterator> rbegin() const {
        return std::reverse_iterator<const_iterator>(end());
    }

    std::reverse_iterator<const_iterator> crbegin() const {
        return std::reverse_iterator<const_iterator>(cend());
    }

    std::reverse_iterator<iterator> rend() {
        return std::reverse_iterator<iterator>(begin());
    }

    std::reverse_iterator<const_iterator> rend() const {
        return std::reverse_iterator<const_iterator>(begin());
    }

    // Capacity
    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t max_size() const {
        return std::numeric_limits<size_t>::max();
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

    size_t capacity() const {
        return capacity_;
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            T* new_data = new T[size_];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    // Modifiers
    void clear() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    iterator insert(iterator pos, const T& value) {
        size_t index = pos - begin();
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::copy_backward(begin() + index, end(), end() + 1);
        *(begin() + index) = value;
        ++size_;
        return begin() + index;
    }

    template <typename InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last) {
        size_t count = std::distance(first, last);
        size_t index = pos - begin();
        if (size_ + count > capacity_) {
            size_t new_capacity = std::max(size_ + count, capacity_ == 0 ? 1 : capacity_ * 2);
            reserve(new_capacity);
        }
        std::copy_backward(begin() + index, end(), end() + count);
        std::copy(first, last, begin() + index);
        size_ += count;
        return begin() + index;
    }

    template <typename... Args>
    iterator emplace(iterator pos, Args&&... args) {
        size_t index = pos - begin();
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        std::copy_backward(begin() + index, end(), end() + 1);
        *(begin() + index) = T(std::forward<Args>(args)...);
        ++size_;
        return begin() + index;
    }

    iterator erase(iterator pos) {
        std::copy(pos + 1, end(), pos);
        --size_;
        return pos;
    }

    iterator erase(iterator first, iterator last) {
        size_t count = last - first;
        std::copy(last, end(), first);
        size_ -= count;
        return first;
    }

    void push_back(const T& value) {
        insert(end(), value);
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        emplace(end(), std::forward<Args>(args)...);
    }

    template <typename InputIterator>
    void append_range(InputIterator first, InputIterator last) {
        insert(end(), first, last);
    }

    void pop_back() {
        --size_;
    }

    void resize(size_t count) {
        resize(count, T());
    }

    void resize(size_t count, const T& value) {
        if (count < size_) {
            size_ = count;
        }
        else if (count > size_) {
            if (count > capacity_) {
                reserve(count);
            }
            std::fill(data_ + size_, data_ + count, value);
            size_ = count;
        }
    }

    void swap(MyVector<T>& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

#endif
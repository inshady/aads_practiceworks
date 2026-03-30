#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
#include <stdexcept>


namespace topit {

  template< class T > struct Vector {
    Vector();
    Vector(size_t s, const T &val);
    ~Vector();

    Vector(const Vector< T > &rhs);
    Vector< T >& operator=(const Vector< T >&);
    Vector(Vector< T >&&) noexcept;
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T > &rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T &val);

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t s);
  };

  template< class T > bool operator==(const Vector< T > &lhs, const Vector< T > &rhs);
  template< class T > bool operator!=(const Vector< T > &lhs, const Vector< T > &rhs);
}

template< class T > topit::Vector< T >& topit::Vector< T >::operator=(Vector< T > &&rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T > topit::Vector< T >::Vector(Vector< T > &&rhs) noexcept:
 data_(rhs.data_),
 size_(rhs.size_),
 capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T > topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T > void topit::Vector< T >::swap(Vector< T > &rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T > topit::Vector< T >::Vector(const Vector< T > &rhs):
 Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); i++) {
    data_[i] = rhs.data_[i];
  }
}

template< class T > T& topit::Vector< T >::operator[](size_t id) noexcept
{
  return this->at(id);
}

template< class T > const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return this->at(id);
}

template< class T > void topit::Vector< T >::pushBack(const T &val)
{
  if (size_ < capacity_) {
    data_[size_ + 1] = val;
    size_++;
  } else {
    T* newData = new T[size_ + 1];
    for (size_t i = 0; i < size_; i++) {
      newData[i] = data_[i];
    }
    newData[size_ + 1] = val;
    delete[] data_;
    data_ = newData;
    size_++;
    capacity_++;
  }
}

template< class T > bool topit::operator==(const Vector< T > &lhs, const Vector< T > &rhs)
{
  if (lhs.getCapacity() == rhs.getCapacity() && lhs.getSize() == rhs.getSize()) {
    size_t count = 0;
    for (size_t i = 0; i < lhs.getSize(); i++) {
      if (lhs[i] == rhs[i]) {
        count++;
      }
    }
    if (count == lhs.getSize()) {
      return true;
    }
  }
  return false;
}

template< class T > bool topit::operator!=(const Vector< T > &lhs, const Vector< T > &rhs)
{
  return !(lhs == rhs);
}

template< class T > T& topit::Vector< T >::at(size_t id) {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template< class T > const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template< class T > bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T > size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T > size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}


template< class T > topit::Vector< T >::Vector():
 data_(nullptr),
 size_(0),
 capacity_(0)
{}

template< class T > topit::Vector< T >::Vector(size_t s):
 data_(s ? new T[s] : nullptr),
 size_(s),
 capacity_(s)
{}

template< class T > topit::Vector< T >::Vector(size_t s, const T &val):
 Vector(s)
{
  for (size_t i = 0; i < s; i++) {
    data_[i] = val;
  }
}

template< class T > topit::Vector< T >::~Vector()
{
  delete[] data_;
}


#endif

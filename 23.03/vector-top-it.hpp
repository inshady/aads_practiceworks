#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
#include <stdexcept>


namespace topit {

  template< class T > struct Vector {
    Vector();
    Vector(size_t s, const T &val);
    ~Vector();

    Vector(const Vector< T >&) = delete;
    Vector< T >& operator=(const Vector< T >&) = delete;

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
  if (lhs.capacity_ == rhs.capacity_ && lhs.size_ == rhs.size_) {
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
      if (lhs.data_[i] == rhs.data_[i]) {
        count++;
      }
    }
    if (count == lhs.size_) {
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
  return const_cast< T& >(static_cast< const Vector< T >* >(this)->at(id));
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

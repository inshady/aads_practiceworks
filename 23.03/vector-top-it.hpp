#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>
#include <stdexcept>


namespace topit {

  template< class T > struct VIter;
  template< class T > struct Vector {
    friend class VIter< T >;

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

    VIter< T > begin() noexcept;
    VIter< T > end() noexcept;

    void pushBack(const T &val);
    void pushFront(const T& val);

    void insert(size_t pos, const T& val);
    void insert(size_t pos, const Vector< T > &rhs, size_t b, size_t e);
    void erase(size_t pos);

    void insert(VIter< T > pos, const T& val);
    void insert(VIter< T > pos, const Vector< T > &rhs, VIter< T > b, VIter< T > e);
    void insert(VIter< T > pos, const Vector< T > &rhs);
    void erase(VIter< T > pos);
    void erase(VIter< T > b, VIter< T > e);
    void erase(VIter< T > pos, size_t count);

    T& operator[](size_t id);
    const T& operator[](size_t id) const;
    T& at(size_t id);
    const T& at(size_t id) const;

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t s);
  };

  template< class T > struct VIter {
    friend class Vector< T >;

    VIter& operator++();
    VIter operator+(int shift);
    VIter& operator--();
    VIter operator-(int shift);

    T& operator*() noexcept;
    T* operator->() noexcept;

    size_t getPos() const noexcept {
      return pos_;
    }

    bool operator==(const VIter& rhs) const noexcept;
    bool operator!=(const VIter& rhs) const noexcept;
   private:
    explicit VIter(size_t pos, Vector< T > *vec);
    size_t pos_;
    Vector< T > *vec_;
  };

  template< class T > VIter< T >::VIter(size_t pos, Vector< T > *vec):
  pos_(pos),
  vec_(vec)
  {}

  template< class T > bool operator==(const Vector< T > &lhs, const Vector< T > &rhs);
  template< class T > bool operator!=(const Vector< T > &lhs, const Vector< T > &rhs);
}

template< class T > void topit::Vector< T >::erase(VIter< T > b, VIter< T > e)
{
  erase(b, e.pos_ - b.pos_);
}

template< class T > void topit::Vector< T >::erase(VIter< T > pos, size_t count)
{
  if (pos.pos_ + count > getSize()) {
    throw std::out_of_range("bad count");
  }

  for(size_t i = 0; i < count; i++) {
    erase(pos.pos_);
  }
}

template< class T > void topit::Vector< T >::erase(VIter< T > pos)
{
  erase(pos.pos_);
}

template< class T > void topit::Vector< T >::insert(VIter< T > pos, const T& val)
{
  insert(pos.pos_, val);
}

template< class T > void topit::Vector< T >::insert(VIter< T > pos, const Vector< T > &rhs, VIter< T > b, VIter< T > e)
{
  insert(pos.pos_, rhs, b.pos_, e.pos_);
}

template< class T > void topit::Vector< T >::insert(VIter< T > pos, const Vector< T > &rhs)
{
  insert(pos.pos_, rhs, 0, rhs.getSize());
}

template< class T > topit::VIter< T > topit::Vector< T >::end() noexcept
{
  return VIter< T >(getSize(), this);
}

template< class T > topit::VIter< T > topit::Vector< T >::begin() noexcept
{
  return VIter< T >(0, this);
}

template< class T > bool topit::VIter< T >::operator!=(const VIter& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T > bool topit::VIter< T >::operator==(const VIter& rhs) const noexcept
{
  return pos_ == rhs.pos_ && vec_ == rhs.vec_;
}

template< class T > T& topit::VIter< T >::operator*() noexcept
{
  return vec_->data_[pos_];
}

template< class T > T* topit::VIter< T >::operator->() noexcept
{
  return &(vec_->data_[pos_]);
}

template< class T > topit::VIter< T > topit::VIter< T >::operator-(int shift)
{
  pos_ -= shift;
  return *this;
}

template< class T > topit::VIter< T >& topit::VIter< T >::operator--()
{
  pos_--;
  return *this;
}

template< class T > topit::VIter< T > topit::VIter< T >::operator+(int shift)
{
  pos_ += shift;
  return *this;
}

template< class T > topit::VIter< T >& topit::VIter< T >::operator++()
{
  pos_++;
  return *this;
}

template< class T > void topit::Vector< T >::erase(size_t pos)
{
  if (pos >= getSize()) {
    throw std::out_of_range("bad pos");
  }
  Vector< T > result(getSize() - 1);
  for (size_t i = 0; i < pos; i++) {
    result[i] = (*this)[i];
  }
  for (size_t i = pos + 1; i < getSize(); i++) {
    result[i - 1] = (*this)[i];
  }
  swap(result);
}

template< class T > void topit::Vector< T >::insert(size_t pos, const Vector< T > &rhs, size_t b, size_t e)
{
  if (pos > getSize() || b > rhs.getSize() || e > rhs.getSize() || b > e) {
    throw std::out_of_range("bad pos");
  }
  Vector< T > result(getSize() + e - b);
  for (size_t i = 0; i < pos; i++) {
    result[i] = (*this)[i];
  }
  for (size_t i = pos; i < pos + e - b; i++) {
    result[i] = rhs[i - pos + b];
  }
  for (size_t i = pos + e - b; i < getSize() + e - b; i++) {
    result[i] = (*this)[i - e + b];
  }
  swap(result);
}

template< class T > void topit::Vector< T >::insert(size_t pos, const T& val)
{
  if (pos > getSize()) {
    throw std::out_of_range("bad pos");
  }
  Vector< T > result(getSize() + 1);
  for (size_t i = 0; i < pos; i++) {
    result[i] = (*this)[i];
  }
  result[pos] = val;
  for (size_t i = pos; i < getSize(); i++) {
    result[i + 1] = (*this)[i];
  }
  swap(result);
}

template< class T > void topit::Vector< T >::pushFront(const T& val)
{
  Vector< T > result(getSize() + 1);
  result[0] = val;
  for (size_t i = 0; i < getSize(); i++) {
    result[i + 1] = (*this)[i];
  }

  swap(result);
}

template< class T > topit::Vector< T >& topit::Vector< T >::operator=(Vector< T > &&rhs) noexcept
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
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
  if (this == std::addressof(rhs)) {
    return *this;
  }
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

template< class T > T& topit::Vector< T >::operator[](size_t id)
{
  return this->at(id);
}

template< class T > const T& topit::Vector< T >::operator[](size_t id) const
{
  return this->at(id);
}

template< class T > void topit::Vector< T >::pushBack(const T &val)
{
  Vector< T > result(getSize() + 1);
  for (size_t i = 0; i < getSize(); i++) {
    result[i] = (*this)[i];
  }
  result[getSize()] = val;
  swap(result);
}

template< class T > bool topit::operator==(const Vector< T > &lhs, const Vector< T > &rhs)
{
  if (lhs.getSize() == rhs.getSize()) {
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

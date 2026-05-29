#ifndef Vector_H
#define Vector_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

/**
 * @file Vector.h
 * @brief Šiame faile yra įgyvendinta paprasta vektoriaus klasė, kuri imituoja
 * std::vector funkcionalumą. Ši klasė naudoja dinaminę atmintį ir turi
 * pagrindinius metodus, tokius kaip push_back, pop_back, clear, size, capacity,
 * operator[], ir kt.
 *
 * Vector klasė yra naudinga mokymosi tikslais, siekiant suprasti, kaip veikia
 * dinaminė atmintis ir kaip galima įgyvendinti konteinerius C++ kalba. Ji taip
 * pat gali būti naudojama vietoj std::vector tam tikrose situacijose, kur
 * reikia paprastesnio ar labiau pritaikyto sprendimo.
 *
 * Ši klasė yra testuojama naudojant Google Test framework'ą, siekiant
 * užtikrinti, kad visi metodai veiktų teisingai įvairiais scenarijais.
 *
 */

template <typename T> class Vector {
private:
  T *data;
  size_t Asize;
  size_t Acapacity;
  std::allocator<T> alloc;

public:
  using type = T;
  using value_type = T;
  using size_type = std::size_t;
  using Allocator = std::allocator<T>;

  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Vector() : data(nullptr), Asize(0), Acapacity(0) {}

  explicit Vector(size_type count) : Asize(count), Acapacity(count) {
    data = alloc.allocate(count);
    for (size_type i = 0; i < count; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + i);
    }
  }

  Vector(size_type count, const T &value) : Asize(count), Acapacity(count) {
    data = alloc.allocate(count);
    for (size_type i = 0; i < count; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + i, value);
    }
  }
  template <class InputIt, typename = typename std::enable_if<
                               !std::is_integral<InputIt>::value>::type>
  Vector(InputIt first, InputIt last) {
    Asize = std::distance(first, last);
    Acapacity = Asize;

    data = alloc.allocate(Acapacity);

    size_type i = 0;

    try {
      for (; first != last; ++first, ++i) {
        std::allocator_traits<Allocator>::construct(alloc, data + i, *first);
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        std::allocator_traits<Allocator>::destroy(alloc, data + j);
      }

      alloc.deallocate(data, Acapacity);
      throw;
    }
  }

  Vector(const Vector &other, const Allocator &alloc)
      : Asize(other.Asize), Acapacity(other.Acapacity), alloc(alloc) {
    data = this->alloc.allocate(Acapacity);

    for (size_type i = 0; i < Asize; ++i)
      std::allocator_traits<Allocator>::construct(this->alloc, data + i,
                                                  other.data[i]);
  }

  Vector(Vector &&other) noexcept
      : data(other.data), Asize(other.Asize), Acapacity(other.Acapacity),
        alloc(std::move(other.alloc)) {
    other.data = nullptr;
    other.Asize = 0;
    other.Acapacity = 0;
  }

  Vector(Vector &&other, const Allocator &alloc) {
    data = other.data;
    Asize = other.Asize;
    Acapacity = other.Acapacity;
    this->alloc = alloc;
    other.data = nullptr;
    other.Asize = 0;
    other.Acapacity = 0;
  }

  Vector(const Vector &other) : Asize(other.Asize), Acapacity(other.Acapacity) {
    data = alloc.allocate(Acapacity);

    for (size_type i = 0; i < Asize; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + i,
                                                  other.data[i]);
    }
  }

  Vector(std::initializer_list<T> init, const Allocator &alloc = Allocator())
      : Asize(init.size()), Acapacity(init.size()), alloc(alloc) {
    data = this->alloc.allocate(Acapacity);

    size_type i = 0;
    for (const auto &v : init)
      std::allocator_traits<Allocator>::construct(this->alloc, data + i++, v);
  }

  ~Vector() {
    clear();
    if (data)
      alloc.deallocate(data, Acapacity);
  }

  Vector &operator=(const Vector &other) {
    if (this == &other)
      return *this;

    T *newData = alloc.allocate(other.Acapacity);
    size_type i = 0;

    try {
      for (; i < other.Asize; ++i) {
        std::allocator_traits<Allocator>::construct(alloc, newData + i,
                                                    other.data[i]);
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j)
        std::allocator_traits<Allocator>::destroy(alloc, newData + j);

      alloc.deallocate(newData, other.Acapacity);
      throw;
    }
    clear();
    if (data)
      alloc.deallocate(data, Acapacity);

    data = newData;
    Asize = other.Asize;
    Acapacity = other.Acapacity;

    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      clear();
      if (data)
        alloc.deallocate(data, Acapacity);

      data = other.data;
      Asize = other.Asize;
      Acapacity = other.Acapacity;
      alloc = std::move(other.alloc);

      other.data = nullptr;
      other.Asize = 0;
      other.Acapacity = 0;
    }
    return *this;
  }

  Vector &operator=(std::initializer_list<T> ilist) {

    clear();
    if (data)
      alloc.deallocate(data, Acapacity);

    Asize = ilist.size();
    Acapacity = ilist.size();
    data = alloc.allocate(Acapacity);

    size_t i = 0;
    for (const auto &item : ilist) {
      std::allocator_traits<Allocator>::construct(alloc, data + i++, item);
    }
    return *this;
  }

  void assign(size_type count, const T &value) {
    clear();
    if (count > Acapacity) {
      if (data)
        alloc.deallocate(data, Acapacity);
      data = alloc.allocate(count);
      Acapacity = count;
    }

    for (size_type i = 0; i < count; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + i, value);
    }
    Asize = count;
  }

  template <class InputIt, typename = typename std::enable_if<
                               !std::is_integral<InputIt>::value>::type>
  void assign(InputIt first, InputIt last) {
    size_type count = std::distance(first, last);

    T *newData = alloc.allocate(count);

    for (size_type i = 0; i < count; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, newData + i, *first);
      ++first;
    }

    clear();
    if (data)
      alloc.deallocate(data, Acapacity);

    data = newData;
    Asize = count;
    Acapacity = count;
  }

  void assign(std::initializer_list<T> ilist) {
    size_type count = ilist.size();
    T *newData = alloc.allocate(count);

    size_type i = 0;
    for (const auto &item : ilist) {
      std::allocator_traits<Allocator>::construct(alloc, newData + i++, item);
    }

    clear();
    if (data)
      alloc.deallocate(data, Acapacity);

    data = newData;
    Asize = count;
    Acapacity = count;
  }

  template <class R> void assign_range(R &&rg) {
    assign(std::begin(rg), std::end(rg));
  }

  void push_back(const T &value) {
    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    std::allocator_traits<Allocator>::construct(alloc, data + Asize, value);
    ++Asize;
  }

  void push_back(T &&value) {
    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    std::allocator_traits<Allocator>::construct(alloc, data + Asize,
                                                std::move(value));
    ++Asize;
  }

  reference operator[](size_type pos) { return data[pos]; }

  const_reference operator[](size_type pos) const { return data[pos]; }

  size_type size() const noexcept { return Asize; }

  size_type capacity() const noexcept { return Acapacity; }

  void reserve(size_type new_cap) {
    if (new_cap <= Acapacity)
      return;

    T *newData = alloc.allocate(new_cap);

    size_type i = 0;

    try {
      for (; i < Asize; ++i) {
        std::allocator_traits<Allocator>::construct(
            alloc, newData + i, std::move_if_noexcept(data[i]));
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        std::allocator_traits<Allocator>::destroy(alloc, newData + j);
      }

      alloc.deallocate(newData, new_cap);
      throw;
    }

    for (size_type i = 0; i < Asize; ++i) {
      std::allocator_traits<Allocator>::destroy(alloc, data + i);
    }

    if (data) {
      alloc.deallocate(data, Acapacity);
    }

    data = newData;
    Acapacity = new_cap;
  }

  void pop_back() {
    if (Asize > 0) {
      --Asize;
      std::allocator_traits<Allocator>::destroy(alloc, data + Asize);
    }
  }
  void clear() {
    for (size_type i = 0; i < Asize; ++i)
      std::allocator_traits<Allocator>::destroy(alloc, data + i);

    Asize = 0;
  }

  iterator begin() { return data; }
  const_iterator begin() const { return data; }
  const_iterator cbegin() const noexcept { return data; }
  iterator end() { return data + Asize; }
  const_iterator end() const { return data + Asize; }
  const_iterator cend() const noexcept { return data + Asize; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }
  reference front() {
    if (Asize == 0)
      throw std::out_of_range("Vector is empty");
    return data[0];
  }
  const_reference front() const {
    if (Asize == 0)
      throw std::out_of_range("Vector is empty");
    return data[0];
  }
  reference back() {
    if (Asize == 0)
      throw std::out_of_range("Vector is empty");
    return data[Asize - 1];
  }
  const_reference back() const {
    if (Asize == 0)
      throw std::out_of_range("Vector is empty");
    return data[Asize - 1];
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    size_type index = pos - data;
    if (index > Asize)
      throw std::out_of_range("Range error");

    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    for (size_type i = Asize; i > index; --i) {
      std::allocator_traits<Allocator>::construct(alloc, data + i,
                                                  std::move(data[i - 1]));
      std::allocator_traits<Allocator>::destroy(alloc, data + i - 1);
    }

    std::allocator_traits<Allocator>::construct(alloc, data + index,
                                                std::forward<Args>(args)...);
    ++Asize;
    return data + index;
  }

  template <class... Args> reference emplace_back(Args &&...args) {
    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    std::allocator_traits<Allocator>::construct(alloc, data + Asize,
                                                std::forward<Args>(args)...);

    return data[Asize++];
  }

  iterator insert(const_iterator pos, const T &value) {
    size_type index = pos - data;

    if (index > Asize)
      throw std::out_of_range("Insert position out of range");

    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    for (size_type i = Asize; i > index; --i) {
      std::allocator_traits<Allocator>::construct(
          alloc, data + i, std::move_if_noexcept(data[i - 1]));

      std::allocator_traits<Allocator>::destroy(alloc, data + i - 1);
    }

    std::allocator_traits<Allocator>::construct(alloc, data + index, value);

    ++Asize;
    return data + index;
  }
  iterator insert(const_iterator pos, T &&value) {
    size_type index = pos - data;

    if (index > Asize)
      throw std::out_of_range("Insert position out of range");

    if (Asize >= Acapacity)
      reserve(Acapacity == 0 ? 1 : Acapacity * 2);

    for (size_type i = Asize; i > index; --i) {
      std::allocator_traits<Allocator>::construct(
          alloc, data + i, std::move_if_noexcept(data[i - 1]));
      std::allocator_traits<Allocator>::destroy(alloc, data + i - 1);
    }

    std::allocator_traits<Allocator>::construct(alloc, data + index,
                                                std::move(value));

    ++Asize;
    return data + index;
  }

  iterator insert(const_iterator pos, size_type count, const T &value) {
    size_type index = pos - data;

    if (index > Asize)
      throw std::out_of_range("Insert position out of range");

    if (Asize + count > Acapacity)
      reserve((std::max)(Acapacity * 2, Asize + count));

    for (size_type i = Asize + count; i > index + count; --i) {
      std::allocator_traits<Allocator>::construct(
          alloc, data + i - 1, std::move(data[i - count - 1]));
      std::allocator_traits<Allocator>::destroy(alloc, data + i - count - 1);
    }

    for (size_type i = 0; i < count; ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + index + i,
                                                  value);
    }

    Asize += count;
    return data + index;
  }
  template <class InputIt, typename = typename std::enable_if<
                               !std::is_integral<InputIt>::value>::type>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    size_type index = pos - data;
    size_type count = std::distance(first, last);

    if (index > Asize)
      throw std::out_of_range("Insert position out of range");

    if (Asize + count > Acapacity)
      reserve((std::max)(Acapacity * 2, Asize + count));

    for (size_type i = Asize + count; i > index + count; --i) {
      std::allocator_traits<Allocator>::construct(
          alloc, data + i - 1, std::move(data[i - count - 1]));
      std::allocator_traits<Allocator>::destroy(alloc, data + i - count - 1);
    }

    size_type i = 0;
    for (; first != last; ++first, ++i) {
      std::allocator_traits<Allocator>::construct(alloc, data + index + i,
                                                  *first);
    }

    Asize += count;
    return data + index;
  }
  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  }

  iterator erase(iterator pos) { return erase(const_iterator(pos)); }
  iterator erase(const_iterator pos) {
    size_type index = pos - data;

    if (index >= Asize)
      throw std::out_of_range("Erase position out of range");

    for (size_type i = index; i < Asize - 1; ++i) {
      data[i] = std::move(data[i + 1]);
    }

    --Asize;

    std::allocator_traits<Allocator>::destroy(alloc, data + Asize);

    return data + index;
  }
  iterator erase(const_iterator first, const_iterator last) {
    size_type start = first - data;
    size_type end = last - data;

    if (start > Asize || end > Asize || start > end)
      throw std::out_of_range("Erase range out of range");

    size_type count = end - start;

    for (size_type i = start; i < Asize - count; ++i) {
      data[i] = std::move(data[i + count]);
    }

    for (size_type i = Asize - count; i < Asize; ++i) {
      std::allocator_traits<Allocator>::destroy(alloc, data + i);
    }

    Asize -= count;

    return data + start;
  }
  void shrink_to_fit() {
    if (Asize == 0) {
      clear();

      if (data)
        alloc.deallocate(data, Acapacity);

      data = nullptr;
      Acapacity = 0;
      return;
    }

    if (Asize < Acapacity) {
      T *newData = alloc.allocate(Asize);

      for (size_type i = 0; i < Asize; i++) {
        std::allocator_traits<Allocator>::construct(alloc, newData + i,
                                                    std::move(data[i]));

        std::allocator_traits<Allocator>::destroy(alloc, data + i);
      }

      alloc.deallocate(data, Acapacity);

      data = newData;
      Acapacity = Asize;
    }
  }
  void resize(size_type count) {
    if (count < Asize) {
      for (size_type i = count; i < Asize; ++i)
        std::allocator_traits<Allocator>::destroy(alloc, data + i);
    } else if (count > Asize) {
      if (count > Acapacity) {
        reserve(count);
      }
      for (size_type i = Asize; i < count; ++i)
        std::allocator_traits<Allocator>::construct(alloc, data + i);
    }
    Asize = count;
  }
  void resize(size_type count, const T &value) {
    if (count < Asize) {
      for (size_type i = count; i < Asize; ++i)
        std::allocator_traits<Allocator>::destroy(alloc, data + i);
    } else if (count > Asize) {
      if (count > Acapacity) {
        reserve(count);
      }
      for (size_type i = Asize; i < count; ++i)
        std::allocator_traits<Allocator>::construct(alloc, data + i, value);
    }
    Asize = count;
  }

  bool empty() const noexcept { return Asize == 0; }

  T *data_ptr() { return data; }

  const T *data_ptr() const { return data; }

  reference at(size_type pos) {
    if (pos >= Asize)
      throw std::out_of_range("Vector index out of range");
    return data[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= Asize)
      throw std::out_of_range("Vector index out of range");
    return data[pos];
  }

  void swap(Vector &other) noexcept(
      std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
      std::allocator_traits<Allocator>::is_always_equal::value) {
    if (this != &other) {
      std::swap(data, other.data);
      std::swap(Asize, other.Asize);
      std::swap(Acapacity, other.Acapacity);

      if constexpr (std::allocator_traits<
                        Allocator>::propagate_on_container_swap::value) {
        std::swap(alloc, other.alloc);
      }
    }
  }

  size_type max_size() const noexcept {
    return std::allocator_traits<Allocator>::max_size(alloc);
  }

  friend bool operator==(const Vector &lhs, const Vector &rhs) {
    if (lhs.size() != rhs.size())
      return false;

    for (size_type i = 0; i < lhs.size(); i++) {
      if (lhs[i] != rhs[i])
        return false;
    }
    return true;
  }
  friend bool operator!=(const Vector &lhs, const Vector &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const Vector &lhs, const Vector &rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
  }

  friend bool operator<=(const Vector &lhs, const Vector &rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>(const Vector &lhs, const Vector &rhs) {
    return rhs < lhs;
  }

  friend bool operator>=(const Vector &lhs, const Vector &rhs) {
    return !(lhs < rhs);
  }

  template <typename R> iterator insert_range(const_iterator pos, R &&rg) {
    return insert(pos, std::begin(rg), std::end(rg));
  }

  template <typename R> void append_range(R &&rg) {
    insert_range(cend(), std::forward<R>(rg));
  }

  friend void swap(Vector<T> &a, Vector<T> &b) noexcept { a.swap(b); }

  Allocator get_allocator() const { return alloc; }
};

#endif
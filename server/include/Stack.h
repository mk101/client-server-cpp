#pragma once
#include <cstdint>
#include <stdexcept>

namespace Utils {

template<class T>
class Stack {
 protected:
  T *mass;
  size_t size = 10;
  size_t num;
  int32_t topInd = -1;
  [[nodiscard]] virtual int32_t getNextInd(int32_t index) const {
    return ++index;
  }

 public:
  explicit Stack(size_t size = 10) : size(size), num(0) {
    mass = new T[size];
  }
  Stack(const Stack<T> &s) {
    size = s.size;
    num = s.num;
    topInd = s.topInd;
    mass = new T[size];
    for (size_t i = 0; i < size; i++) {
      mass[i] = s.mass[i];
    }
  }
  ~Stack() {
    delete[] mass;
  }

  Stack<T> &operator=(const Stack<T> &s) {
    if (&s == this) {
      return *this;
    }

    size = s.size;
    num = s.num;
    topInd = s.topInd;
    mass = new T[size];
    for (size_t i = 0; i < size; i++) {
      mass[i] = s.mass[i];
    }

    return *this;
  }

  [[nodiscard]] bool isEmpty() const {
    return num == 0;
  }
  [[nodiscard]] bool isFull() const {
    return num == size;
  }

  void push(const T &t) {
    if (isFull()) {
      throw std::runtime_error("Structure is full");
    }

    topInd = getNextInd(topInd);
    mass[topInd] = t;
    num++;
  }

  virtual T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty");
    }

    num--;
    return mass[topInd--];
  }
};

}

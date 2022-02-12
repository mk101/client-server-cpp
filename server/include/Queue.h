#pragma once
#include "Stack.h"

namespace Utils {

template<class T>
class Queue : public Stack<T> {
 protected:
  int32_t lowInd = 0;
  [[nodiscard]] int32_t getNextInd(int32_t index) const override {
    return ++index % this->size;
  }

 public:
  explicit Queue(size_t size = 10) : Stack<T>(size) {}
  Queue(const Queue<T> &q) {
    this->size = q.size;
    this->num = q.num;
    this->topInd = q.topInd;
    this->lowInd = q.lowInd;
    this->mass = new T[this->size];
    for (size_t i = 0; i < this->size; i++) {
      this->mass[i] = q.mass[i];
    }
  }

  Queue<T> &operator=(const Queue<T> &q) {
    if (&q == this) {
      return *this;
    }
    this->size = q.size;
    this->num = q.num;
    this->topInd = q.topInd;
    this->lowInd = q.lowInd;
    this->mass = new T[this->size];
    for (size_t i = 0; i < this->size; i++) {
      this->mass[i] = q.mass[i];
    }

    return *this;
  }

  T pop() override {
    if (this->isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }

    T &tmp = this->mass[lowInd];
    this->num--;
    lowInd = getNextInd(lowInd);
    return tmp;
  }
};

}

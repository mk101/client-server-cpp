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

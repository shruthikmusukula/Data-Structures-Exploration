#pragma once

#include <iostream>
#include <cstdlib>

// Default capacity of the queue
#define SIZE 3

using std::ostream;

// Templated Queue Class
template <typename T>
class queue {
  T *arr;
  int front;
  int rear;
  size_t capacity;
  size_t count;

public:
  queue(size_t size = SIZE);   // constructor
  ~queue();                   // destructor

  void push(T value);
  T pop();
  T peek();

  size_t size();
  bool isEmpty();
  bool isFull();

  template <typename U>
  friend ostream& operator<<(ostream& os, const queue<U>& queue);
};


#include "queue.hpp"

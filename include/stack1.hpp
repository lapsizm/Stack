// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_STACK1_HPP_
#define INCLUDE_STACK1_HPP_

#include <exception>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
struct Node {
  std::unique_ptr<Node> prev = nullptr;
  T data_;
  Node(std::unique_ptr<Node>&& el, T&& value)
      : prev(std::move(el)), data_(std::move(value)) {}
  Node(std::unique_ptr<Node>&& el, const T& value)
      : prev(std::move(el)), data_(value) {}
};


template <typename T>
class Stack1 {
  std::unique_ptr<Node<T>> head_ = nullptr;
  size_t size_ = 0;

 public:
  Stack1() = default;
  ~Stack1() = default;

  explicit Stack1(const Stack1&) = delete;
  Stack1& operator=(const Stack1&) = delete;


  explicit Stack1(Stack1&& moved_stack) noexcept;
  Stack1& operator=(Stack1<T>&& moved_stack) noexcept;

  size_t size() const;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
};

template <typename T>
Stack1<T>::Stack1(Stack1<T>&& moved_stack) noexcept
    : head_(std::move(moved_stack.head_)), size_(std::move(moved_stack.size_)) {
  moved_stack.head_ = nullptr;
  moved_stack.size_ = 0;
}

template <typename T>
Stack1<T>& Stack1<T>::operator=(Stack1<T>&& moved_stack) noexcept {
  head_ = std::move(moved_stack.head_);
  size_ = std::move(moved_stack.size_);
  moved_stack.head_ = nullptr;
  moved_stack.size_ = 0;
  return *this;
}

template <typename T>
size_t Stack1<T>::size() const {
  return size_;
}

template <typename T>
void Stack1<T>::push(T&& value) {
  Node<T> node(std::move(head_), std::move(value));
  head_ = std::make_unique<Node<T>>(std::move(node));
  ++size_;
}

template <typename T>
void Stack1<T>::push(const T& value) {
  Node<T> node(std::move(head_), value);
  head_ = std::make_unique<Node<T>>(std::move(node));
  ++size_;
}

template <typename T>
void Stack1<T>::pop() {
  if (head_ == nullptr) throw std::runtime_error("Stack is empty");
  head_ = std::move(head_->prev);
  --size_;
}

template <typename T>
const T& Stack1<T>::head() const {
  if (head_ == nullptr) throw std::runtime_error("Stack is empty");
  return head_->data_;
}

#endif  // INCLUDE_STACK1_HPP_

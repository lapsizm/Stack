// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_STACK2_HPP_
#define INCLUDE_STACK2_HPP_

#include <exception>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
struct Node2 {
  std::unique_ptr<Node2> prev_ = nullptr;
  T data_;
  Node2(std::unique_ptr<Node2>&& node, T&& val)
      : prev_(std::move(node)), data_(std::move(val)) {}
};

template <
    typename T,
    class = typename std::enable_if<std::is_move_constructible<T>::value>::type,
    class = typename std::enable_if<std::is_move_assignable<T>::value>::type>

class Stack2 {
  std::unique_ptr<Node2<T>> head_ = nullptr;
  size_t size_ = 0;

 public:
  Stack2() = default;
  ~Stack2() = default;

  explicit Stack2(const Stack2&) = delete;
  Stack2& operator=(const Stack2&) = delete;

  explicit Stack2(Stack2&& moved_stack) noexcept
      : head_(std::move(moved_stack.head_)),
        size_(std::move(moved_stack.size_)) {
    moved_stack.head_ = nullptr;
    moved_stack.size_ = 0;
  }

  Stack2& operator=(Stack2&& moved_stack) noexcept {
    head_ = std::move(moved_stack.head_);
    size_ = std::move(moved_stack.size_);
    moved_stack.head_ = nullptr;
    moved_stack.size_ = 0;
    return *this;
  }

  size_t size() const { return size_; }

  template <typename... Args>
  void push_emplace(Args&&... value) {
    T&& new_obj = T(std::forward<Args>(value)...); //создаем новый экземпляр
    push(std::move(new_obj));
  }

  void push(T&& value) {
    std::unique_ptr<Node2<T>> node = std::make_unique<Node2<T>>(std::move(head_), std::move(value));
    head_ = std::move(node);
    ++size_;
  }

  const T& head() const {
    if (head_ == nullptr) throw std::runtime_error("Stack is empty");
    return head_->data_;

  }
  T pop() {
    if (head_ == nullptr) throw std::runtime_error("Stack is empty");
    auto value = std::move(head_->data_);
    head_ = std::move(head_->prev_);
    --size_;
    return value;
  }
};

#endif  // INCLUDE_STACK2_HPP_

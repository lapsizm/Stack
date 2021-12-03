// Copyright 2021 Your Name <your_email>

#include <gtest/gtest.h>

#include <stack1.hpp>
#include <stack2.hpp>
#include <string>

TEST(Stack1, Stack1TESTS) {
  Stack1<int> stack;
  stack.push(2);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 2);
  stack.push(17);
  stack.push(39);
  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.head(), 39);

  stack.push(std::move(55));
  EXPECT_EQ(stack.size(), 4);
  EXPECT_EQ(stack.head(), 55);

  Stack1<int> stack2(std::move(stack));
  EXPECT_EQ(stack2.size(), 4);
  EXPECT_EQ(stack2.head(), 55);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_THROW(stack.head(), std::runtime_error);

  EXPECT_EQ(stack2.pop(), 55);
  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.head(), 39);


  stack2.pop();
  stack2.pop();
  EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST(Stack2, Stack2TEST) {
  Stack2<std::string> stack;
  stack.push("Hello world");
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), "Hello world");

  stack.push(std::move("Rvalue"));
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), "Rvalue");

  Stack2<std::string> stack2(std::move(stack));
  EXPECT_EQ(stack2.size(), 2);
  EXPECT_EQ(stack2.head(), "Rvalue");
  EXPECT_EQ(stack.size(), 0);
  EXPECT_THROW(stack.head(), std::runtime_error);

  EXPECT_EQ(stack2.pop(), "Rvalue");
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack2.head(), "Hello world");

  stack2.pop();
  EXPECT_THROW(stack.pop(), std::runtime_error);

  Stack2<std::string> new_stack;
  new_stack.push_emplace(std::move("Privet mir"));
  new_stack.push_emplace(std::move("Im head"));

  EXPECT_EQ(new_stack.size(), 2);
  EXPECT_EQ(new_stack.head(), "Im head");
}

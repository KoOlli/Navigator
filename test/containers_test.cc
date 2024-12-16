#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../containers/s21_list.h"
#include "../containers/s21_queue.h"
#include "../containers/s21_stack.h"

template <typename ValueType>
bool Comparelists(s21::list<ValueType> my_list,
                  std::list<ValueType> orig_list) {
  bool result = true;
  if (my_list.size() == orig_list.size()) {
    auto it = my_list.begin();
    auto orig = orig_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*it != *orig) {
        result = false;
        break;
      }
      ++it;
      ++orig;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(list, default_constructor_test) {
  s21::list<int> my_list;
  std::list<int> orig_list;
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.empty(), orig_list.empty());
  ASSERT_TRUE(my_list.empty());
}

TEST(list, parameterized_constructor_test) {
  s21::list<int> my_list(8);
  std::list<int> orig_list(8);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.empty(), orig_list.empty());
}

TEST(list, initializer_list_constructor_test) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, copy_constructor_test_1) {
  s21::list<char> my_list;
  std::list<char> orig_list;
  s21::list<char> my_copy(my_list);
  std::list<char> orig_copy(orig_list);
  ASSERT_EQ(my_list.size(), my_copy.size());
  ASSERT_EQ(my_copy.empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.size(), orig_copy.size());
  ASSERT_TRUE(my_copy.empty());
}

TEST(list, copy_constructor_test_2) {
  s21::list<char> my_list{'x', 'y', 'z'};
  std::list<char> orig_list{'x', 'y', 'z'};
  s21::list<char> my_copy = my_list;
  std::list<char> orig_copy = orig_list;
  ASSERT_EQ(my_list.size(), my_copy.size());
  ASSERT_EQ(my_copy.size(), orig_copy.size());
  ASSERT_TRUE(Comparelists(my_copy, orig_copy));
}

TEST(list, move_constructor_test_1) {
  s21::list<int> my_list{11, 88, 74, 90};
  std::list<int> orig_list{11, 88, 74, 90};
  s21::list<int> my_move(std::move(my_list));
  std::list<int> orig_move(std::move(orig_list));
  ASSERT_EQ(my_move.size(), orig_move.size());
  ASSERT_TRUE(Comparelists(my_move, orig_move));
}

TEST(list, move_constructor_test_2) {
  s21::list<double> my_list;
  std::list<double> orig_list;
  s21::list<double> my_move(std::move(my_list));
  std::list<double> orig_move(std::move(orig_list));
  ASSERT_EQ(my_move.size(), orig_move.size());
  ASSERT_EQ(my_move.empty(), orig_move.empty());
}

TEST(list, push_back_test_1) {
  s21::list<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  my_list.push_back(7.67);
  orig_list.push_back(7.67);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.back(), orig_list.back());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, push_back_test_2) {
  s21::list<std::string> my_list{"Blacksad", "Weekly"};
  std::list<std::string> orig_list{"Blacksad", "Weekly"};
  my_list.push_back("Smirnov");
  my_list.push_back("Fiston");
  orig_list.push_back("Smirnov");
  orig_list.push_back("Fiston");
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.back(), orig_list.back());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, push_front_test_1) {
  s21::list<int> my_list{1345, 56789, 6788, 9090};
  std::list<int> orig_list{1345, 56789, 6788, 9090};
  my_list.push_front(1000);
  orig_list.push_front(1000);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.front(), orig_list.front());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, push_front_test_2) {
  s21::list<char> my_list;
  std::list<char> orig_list;
  my_list.push_front('a');
  orig_list.push_front('a');
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.front(), orig_list.front());
}

TEST(list, pop_back_test_1) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.pop_back();
  orig_list.pop_back();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.back(), orig_list.back());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, pop_back_test_2) {
  s21::list<float> my_list{0.6};
  std::list<float> orig_list{0.6};
  my_list.pop_back();
  orig_list.pop_back();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.empty(), orig_list.empty());
  ASSERT_TRUE(my_list.empty());
}

TEST(list, pop_front_test_1) {
  s21::list<int> my_list{56, -33, 1, 34, 12, 91};
  std::list<int> orig_list{56, -33, 1, 34, 12, 91};
  my_list.pop_front();
  orig_list.pop_front();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.front(), orig_list.front());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, pop_front_test_2) {
  s21::list<std::string> my_list{"list", "stack", "map"};
  std::list<std::string> orig_list{"list", "stack", "map"};
  my_list.pop_front();
  orig_list.pop_front();
  my_list.pop_front();
  orig_list.pop_front();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.front(), orig_list.front());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, clear_test) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.clear();
  orig_list.clear();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_EQ(my_list.empty(), orig_list.empty());
  ASSERT_TRUE(my_list.empty());
}

TEST(list, iterator_insert_test_1) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.insert(++my_list.begin(), -9);
  orig_list.insert(++orig_list.begin(), -9);
  auto orig = orig_list.begin();
  for (auto it = my_list.begin(); it != my_list.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, iterator_insert_test_2) {
  s21::list<double> my_list{1.8, 77.7, 6.67, 0.88};
  std::list<double> orig_list{1.8, 77.7, 6.67, 0.88};
  my_list.insert(my_list.begin(), -3.33);
  orig_list.insert(orig_list.begin(), -3.33);
  my_list.insert(my_list.end(), 21.5);
  orig_list.insert(orig_list.end(), 21.5);
  ASSERT_EQ(my_list.size(), orig_list.size());
  auto orig = orig_list.begin();
  for (auto it = my_list.begin(); it != my_list.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, iterator_insert_test_3) {
  s21::list<int> my_list;
  std::list<int> orig_list;
  my_list.insert(my_list.begin(), 111);
  orig_list.insert(orig_list.begin(), 111);
  ASSERT_EQ(my_list.size(), orig_list.size());
  auto orig = orig_list.begin();
  for (auto it = my_list.begin(); it != my_list.end(); ++it, ++orig) {
    ASSERT_EQ(*it, *orig);
  }
}

TEST(list, erase_test_1) {
  s21::list<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  auto it1 = my_list.begin();
  my_list.erase(++it1);
  auto it2 = orig_list.begin();
  orig_list.erase(++it2);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, erase_test_2) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  my_list.erase(my_list.begin());
  orig_list.erase(orig_list.begin());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, swap_test_1) {
  s21::list<double> my_list;
  std::list<double> orig_list;
  s21::list<double> my_swap{0.3};
  std::list<double> orig_swap{0.3};
  ASSERT_EQ(my_list.empty(), orig_list.empty());
  ASSERT_EQ(my_list.size(), orig_list.size());
  my_swap.swap(my_list);
  orig_swap.swap(orig_list);
  ASSERT_EQ(my_swap.size(), orig_swap.size());
  ASSERT_EQ(my_swap.empty(), orig_swap.empty());
  ASSERT_TRUE(my_swap.empty());
}

TEST(list, swap_test_2) {
  s21::list<int> my_list{67, -7, 21};
  std::list<int> orig_list{67, -7, 21};
  s21::list<int> my_swap{1, 2, 3, 4, 5};
  std::list<int> orig_swap{1, 2, 3, 4, 5};
  my_swap.swap(my_list);
  orig_swap.swap(orig_list);
  ASSERT_EQ(my_swap.size(), orig_swap.size());
  ASSERT_TRUE(Comparelists(my_swap, orig_swap));
}

TEST(list, sort_test) {
  s21::list<int> my_list{1, 77, -3, 45, 67, 88};
  std::list<int> orig_list{1, 77, -3, 45, 67, 88};
  orig_list.sort();
  my_list.sort();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, reverse_test) {
  s21::list<double> my_list{0.44, -3.88, 1.98, 2.56, -0.1};
  std::list<double> orig_list{0.44, -3.88, 1.98, 2.56, -0.1};
  orig_list.reverse();
  my_list.reverse();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, unique_test_1) {
  s21::list<int> my_list{1, 1, -3, 1, 67, 67, 67, 3, 1, 1};
  std::list<int> orig_list{1, 1, -3, 1, 67, 67, 67, 3, 1, 1};
  orig_list.unique();
  my_list.unique();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, unique_test_2) {
  s21::list<char> my_list{'a', 'b', 'd', 'd', 'i', 'a', 'a', 'c'};
  std::list<char> orig_list{'a', 'b', 'd', 'd', 'i', 'a', 'a', 'c'};
  orig_list.unique();
  my_list.unique();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, splice_test_1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> orig_list{1, 2, 3, 4, 5};
  s21::list<int> my_add{6, 7, 8};
  std::list<int> orig_add{6, 7, 8};
  orig_list.splice(orig_list.end(), orig_add);
  my_list.splice(my_list.end(), my_add);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, splice_test_2) {
  s21::list<char> my_list{'l', 'i', 's', 't'};
  std::list<char> orig_list{'l', 'i', 's', 't'};
  s21::list<char> my_add{'c', '+', '+'};
  std::list<char> orig_add{'c', '+', '+'};
  orig_list.splice(orig_list.begin(), orig_add);
  my_list.splice(my_list.begin(), my_add);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, splice_test_3) {
  s21::list<int> my_list;
  std::list<int> orig_list;
  s21::list<int> my_add{1, 2, 3};
  std::list<int> orig_add{1, 2, 3};
  orig_list.splice(orig_list.begin(), orig_add);
  my_list.splice(my_list.begin(), my_add);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, splice_test_4) {
  s21::list<double> my_list{0.01, -0.2, 1.98};
  std::list<double> orig_list{0.01, -0.2, 1.98};
  s21::list<double> my_add{3.33, 2.22};
  std::list<double> orig_add{3.33, 2.22};
  orig_list.splice(++orig_list.begin(), orig_add);
  my_list.splice(++my_list.begin(), my_add);
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, merge_test_1) {
  s21::list<double> my_list{0.01, -0.2, 1.98};
  std::list<double> orig_list{0.01, -0.2, 1.98};
  s21::list<double> my_add{3.33, 2.22};
  std::list<double> orig_add{3.33, 2.22};
  orig_list.merge(orig_add);
  my_list.merge(my_add);
  orig_list.sort();
  my_list.sort();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, merge_test_2) {
  s21::list<int> my_list;
  std::list<int> orig_list;
  s21::list<int> my_add{21, 135, 0, -15};
  std::list<int> orig_add{21, 135, 0, -15};
  orig_list.merge(orig_add);
  my_list.merge(my_add);
  orig_list.sort();
  my_list.sort();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, merge_test_3) {
  s21::list<int> my_list{5, 89, -33, 784, 0, 45};
  std::list<int> orig_list{5, 89, -33, 784, 0, 45};
  s21::list<int> my_add{5, 89, -33, 784, 0, 45};
  std::list<int> orig_add{5, 89, -33, 784, 0, 45};
  orig_list.merge(orig_add);
  my_list.merge(my_add);
  orig_list.sort();
  my_list.sort();
  ASSERT_EQ(my_list.size(), orig_list.size());
  ASSERT_TRUE(Comparelists(my_list, orig_list));
}

TEST(list, iterator_operator_test_1) {
  s21::list<double> my_list{0.99, 8.56, -3.45, 1.34};
  std::list<double> orig_list{0.99, 8.56, -3.45, 1.34};
  s21::list<double>::iterator it_my = ++my_list.begin();
  std::list<double>::iterator it_orig = ++orig_list.begin();
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(list, iterator_operator_test_2) {
  s21::list<int> my_list{1, 9, 34, 8};
  std::list<int> orig_list{1, 9, 34, 8};
  s21::list<int>::iterator it_my = ++my_list.begin();
  std::list<int>::iterator it_orig = ++orig_list.begin();
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(queue, default_constructor_test) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  ASSERT_EQ(my_queue.empty(), orig_queue.empty());
  ASSERT_EQ(my_queue.size(), orig_queue.size());
}

TEST(queue, initializer_list_constructor_test) {
  s21::queue<int> my_queue{21, 456, -89, 67};
  std::queue<int> orig_queue;
  orig_queue.push(21);
  orig_queue.push(456);
  orig_queue.push(-89);
  orig_queue.push(67);
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  while (!my_queue.empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.front(), orig_queue.front());
    my_queue.pop();
    orig_queue.pop();
  }
  ASSERT_EQ(my_queue.empty(), orig_queue.empty());
}

TEST(queue, copy_constructor_test_1) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  s21::queue<int> my_copy(my_queue);
  std::queue<int> orig_copy(orig_queue);
  ASSERT_EQ(my_copy.empty(), orig_copy.empty());
  ASSERT_EQ(my_copy.size(), orig_copy.size());
}

TEST(queue, copy_constructor_test_2) {
  s21::queue<double> my_queue;
  std::queue<double> orig_queue;
  my_queue.push(0.88);
  my_queue.push(3.33);
  my_queue.push(-11.45);
  orig_queue.push(0.88);
  orig_queue.push(3.33);
  orig_queue.push(-11.45);
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  s21::queue<double> my_copy(my_queue);
  std::queue<double> orig_copy(orig_queue);
  ASSERT_EQ(my_copy.size(), orig_copy.size());
  while (!my_copy.empty() && !orig_copy.empty()) {
    ASSERT_EQ(my_copy.front(), orig_copy.front());
    my_copy.pop();
    orig_copy.pop();
  }
  ASSERT_EQ(my_copy.empty(), orig_copy.empty());
}

TEST(queue, move_constructor_test) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  for (int i = 0; i < 8; ++i) {
    my_queue.push(i);
    orig_queue.push(i);
  }
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  s21::queue<int> my_move(std::move(my_queue));
  std::queue<int> orig_move(std::move(orig_queue));
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  ASSERT_EQ(my_move.size(), orig_move.size());
  while (!my_move.empty() && !orig_move.empty()) {
    ASSERT_EQ(my_move.front(), orig_move.front());
    my_move.pop();
    orig_move.pop();
  }
}

TEST(queue, swap_test_1) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  s21::queue<int> my_swap;
  std::queue<int> orig_swap;
  ASSERT_EQ(my_queue.empty(), orig_queue.empty());
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  my_swap.swap(my_queue);
  orig_swap.swap(orig_queue);
  ASSERT_EQ(my_swap.empty(), orig_swap.empty());
  ASSERT_EQ(my_swap.size(), orig_swap.size());
}

TEST(queue, swap_test_2) {
  s21::queue<char> my_queue;
  std::queue<char, std::list<char>> orig_queue;
  my_queue.push('a');
  my_queue.push('b');
  my_queue.push('c');
  my_queue.push('d');
  orig_queue.push('a');
  orig_queue.push('b');
  orig_queue.push('c');
  orig_queue.push('d');
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  s21::queue<char> my_swap{'x', 'y', 'z'};
  std::list<char> tmp{'x', 'y', 'z'};
  std::queue<char, std::list<char>> orig_swap(tmp);
  my_swap.swap(my_queue);
  orig_swap.swap(orig_queue);
  ASSERT_EQ(my_swap.size(), orig_swap.size());
  while (!my_swap.empty() && !orig_swap.empty()) {
    ASSERT_EQ(my_swap.front(), orig_swap.front());
    my_swap.pop();
    orig_swap.pop();
  }
  ASSERT_EQ(my_swap.empty(), orig_swap.empty());
}

TEST(queue, front_test) {
  s21::queue<int> my_queue{0, 1, 4, 77, 5, 33};
  std::list<int> tmp{0, 1, 4, 77, 5, 33};
  std::queue<int, std::list<int>> orig_queue(tmp);
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  while (!my_queue.empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.front(), orig_queue.front());
    my_queue.pop();
    orig_queue.pop();
  }
  ASSERT_EQ(my_queue.empty(), orig_queue.empty());
}

TEST(queue, push_test) {
  s21::queue<double> my_queue{0.78, 3.33, -5.35, 8.845, -0.99, 1.11};
  std::list<double> tmp{0.78, 3.33, -5.35, 8.845, -0.99, 1.11};
  std::queue<double, std::list<double>> orig_queue(tmp);
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  my_queue.push(0.33);
  orig_queue.push(0.33);
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  ASSERT_EQ(my_queue.back(), orig_queue.back());

  while (!my_queue.empty() && !orig_queue.empty()) {
    ASSERT_EQ(my_queue.front(), orig_queue.front());
    my_queue.pop();
    orig_queue.pop();
  }
}

TEST(queue, move_operator_test) {
  s21::queue<char> my_queue;
  std::queue<char> orig_queue;
  my_queue.push('a');
  my_queue.push('b');
  my_queue.push('c');
  my_queue.push('d');
  orig_queue.push('a');
  orig_queue.push('b');
  orig_queue.push('c');
  orig_queue.push('d');
  s21::queue<char> my_move;
  std::queue<char> orig_move;
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  ASSERT_EQ(my_move.size(), orig_move.size());
  my_move = std::move(my_queue);
  orig_move = std::move(orig_queue);
  ASSERT_EQ(my_move.size(), orig_move.size());
  ASSERT_EQ(my_queue.size(), orig_queue.size());
  while (!my_move.empty() && !orig_move.empty()) {
    ASSERT_EQ(my_move.front(), orig_move.front());
    my_move.pop();
    orig_move.pop();
  }
}

TEST(stack, default_constructor_test) {
  s21::stack<int> my_stack;
  std::stack<int> orig_stack;
  ASSERT_EQ(my_stack.size(), orig_stack.size());
  ASSERT_EQ(my_stack.empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.empty());
}

TEST(stack, initializer_list_constructor_test) {
  s21::stack<int> my_stack{3, 1};
  std::vector<int> tmp{3, 1};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  ASSERT_EQ(my_stack.size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.top(), orig_stack.top());
    my_stack.pop();
    orig_stack.pop();
  }
}

TEST(stack, copy_constructor_test_1) {
  s21::stack<double> my_stack;
  std::stack<double> orig_stack;
  s21::stack<double> my_copy(my_stack);
  std::stack<double> orig_copy(orig_stack);
  ASSERT_EQ(my_copy.size(), orig_copy.size());
  ASSERT_EQ(my_copy.empty(), orig_copy.empty());
  ASSERT_TRUE(my_copy.empty());
}

TEST(stack, copy_constructor_test_2) {
  s21::stack<int> my_stack{1, 3, 5};
  std::vector<int> tmp{1, 3, 5};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  s21::stack<int> my_copy(my_stack);
  std::stack<int, std::vector<int>> orig_copy(orig_stack);
  ASSERT_EQ(my_copy.size(), orig_copy.size());
  while (!orig_copy.empty()) {
    ASSERT_EQ(my_copy.top(), orig_copy.top());
    my_copy.pop();
    orig_copy.pop();
  }
}

TEST(stack, move_constructor_test_1) {
  s21::stack<int> my_stack;
  std::stack<int> orig_stack;
  s21::stack<int> my_move(std::move(my_stack));
  std::stack<int> orig_move(std::move(orig_stack));
  ASSERT_EQ(my_move.size(), orig_move.size());
  ASSERT_EQ(my_move.empty(), orig_move.empty());
  ASSERT_TRUE(my_move.empty());
}

TEST(stack, move_constructor_test_2) {
  s21::stack<char> my_stack{'a', 'b', 'c', 'd'};
  std::vector<char> tmp{'a', 'b', 'c', 'd'};
  std::stack<char, std::vector<char>> orig_stack(tmp);
  s21::stack<char> my_move(std::move(my_stack));
  std::stack<char, std::vector<char>> orig_move(std::move(orig_stack));
  ASSERT_EQ(my_move.size(), orig_move.size());
  ASSERT_EQ(my_move.empty(), orig_move.empty());
  ASSERT_FALSE(my_move.empty());
  while (!orig_move.empty()) {
    ASSERT_EQ(my_move.top(), orig_move.top());
    my_move.pop();
    orig_move.pop();
  }
}

TEST(stack, move_operator_test) {
  s21::stack<double> my_stack{0.456, 1.567, -4.678, 0.789};
  std::vector<double> tmp{0.456, 1.567, -4.678, 0.789};
  std::stack<double, std::vector<double>> orig_stack(tmp);
  s21::stack<double> my_move{3.001, 5.456};
  std::vector<double> tmp_move{3.001, 5.456};
  std::stack<double, std::vector<double>> orig_move(tmp_move);
  my_move = std::move(my_stack);
  orig_move = std::move(orig_stack);
  ASSERT_EQ(my_move.size(), orig_move.size());
  while (!orig_move.empty()) {
    ASSERT_EQ(my_move.top(), orig_move.top());
    my_move.pop();
    orig_move.pop();
  }
}

TEST(stack, push_test_1) {
  s21::stack<int> my_stack{3, 4, 9};
  std::vector<int> tmp{3, 4, 9};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  my_stack.push(9);
  my_stack.push(15);
  my_stack.push(34);
  orig_stack.push(9);
  orig_stack.push(15);
  orig_stack.push(34);
  ASSERT_EQ(my_stack.size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.top(), orig_stack.top());
    my_stack.pop();
    orig_stack.pop();
  }
}

TEST(stack, push_test_2) {
  s21::stack<std::string> my_stack;
  my_stack.push("karleenk");
  my_stack.push("waltlate");
  my_stack.push("mullsher");
  std::stack<std::string> orig_stack;
  orig_stack.push("karleenk");
  orig_stack.push("waltlate");
  orig_stack.push("mullsher");
  ASSERT_EQ(my_stack.size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.top(), orig_stack.top());
    my_stack.pop();
    orig_stack.pop();
  }
}

TEST(stack, empty_test) {
  s21::stack<char> my_stack{'a', 'b', 'c', 'd'};
  std::vector<char> tmp{'a', 'b', 'c', 'd'};
  std::stack<char, std::vector<char>> orig_stack(tmp);
  my_stack.push('e');
  orig_stack.push('e');
  ASSERT_EQ(my_stack.size(), orig_stack.size());
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.top(), orig_stack.top());
    my_stack.pop();
    orig_stack.pop();
  }
  ASSERT_EQ(my_stack.empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.empty());
}

TEST(stack, swap_test_1) {
  s21::stack<double> my_stack{3.0001, 4.767090, -0.56753, -5.6786};
  s21::stack<double> my_swap;
  my_stack.swap(my_swap);
  std::vector<double> tmp{3.0001, 4.767090, -0.56753, -5.6786};
  std::stack<double, std::vector<double>> orig_stack(tmp);
  std::stack<double, std::vector<double>> orig_swap;
  orig_stack.swap(orig_swap);
  ASSERT_EQ(my_stack.empty(), orig_stack.empty());
  ASSERT_TRUE(my_stack.empty());
  while (!orig_swap.empty()) {
    ASSERT_EQ(my_swap.top(), orig_swap.top());
    my_swap.pop();
    orig_swap.pop();
  }
}

TEST(stack, swap_test_2) {
  s21::stack<int> my_stack{4, 67, -34, 2, 91, 3, 8};
  s21::stack<int> my_swap{3, 0, 1, 7, 9};
  my_stack.swap(my_swap);
  std::vector<int> tmp{4, 67, -34, 2, 91, 3, 8};
  std::stack<int, std::vector<int>> orig_stack(tmp);
  std::vector<int> tmp_swap{3, 0, 1, 7, 9};
  std::stack<int, std::vector<int>> orig_swap(tmp_swap);
  orig_stack.swap(orig_swap);
  while (!orig_swap.empty()) {
    ASSERT_EQ(my_swap.top(), orig_swap.top());
    my_swap.pop();
    orig_swap.pop();
  }
  while (!orig_stack.empty()) {
    ASSERT_EQ(my_stack.top(), orig_stack.top());
    my_stack.pop();
    orig_stack.pop();
  }
}

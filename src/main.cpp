#include <iostream>
#include <map>
#include <vector>
#include <forward_list>

#include "fix_allocator.h"
#include "list.h"

int factor(int n) {
    return n == 0 ? 1 : n * factor(n - 1);
}

int main() {

    std::map<int, int> m_i;
    for (int i = 0; i < 10; ++i) {
        m_i.emplace(i, factor(i));
    }

    std::map<int, int, std::less<>, FixAllocator<std::pair<const int, int>, 10> > m_i_my_alloc;
    for (int i = 0; i < 10; ++i) {
        m_i_my_alloc.emplace(i, factor(i));
    }
    for (const auto &item : m_i) {
        std::cout << item.first << " " << item.second << std::endl;
    }

//    std::forward_list<int> fl;
//    for (int i = 0; i < 10; ++i) {
//        fl.emplace_front(i);
//    }
//    for (const auto &item_fl:fl) {
//        std::cout << item_fl << std::endl;
//    }

//    List<int> list;
//    for (int i = 0; i < 10; ++i) {
//        list.push_front(i);
//    }
//    for (auto node = list.get_head(); node; node = node->next) {
//        std::cout << node->value << std::endl;
//    }

    List<int, FixAllocator<int, 10>> list_my_alloc;
    for (int i = 0; i < 10; ++i) {
        list_my_alloc.push_front(i);
    }
    for (auto node = list_my_alloc.get_head(); node; node = node->next) {
        std::cout << node->value << std::endl;
    }

    return 0;
}
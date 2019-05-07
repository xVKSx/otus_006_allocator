#include <iostream>
#include <map>
#include <vector>

#include "fix_allocator.h"

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

    return 0;
}
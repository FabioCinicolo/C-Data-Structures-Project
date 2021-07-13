typedef unsigned long ulong;
#include <iostream>
#include "vector/vector.hpp"
#include "binarytree/binarytree.hpp"
#include "binarytree/lnk/binarytreelnk.hpp"
int main() {
    ulong i = 0;
    lasd::Vector<int>vec(3);
    vec[0]=2;
    lasd::BinaryTreeLnk<int>b(vec);
    return 0;
}
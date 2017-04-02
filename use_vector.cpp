 #include <iostream>
#include "vector.h"

int main()
{
    Vector<int> v{1, 2, 3, 4, 5};
//    v.print();
//    Vector<int> v2(Vector<int>{1, 3, 2});
//    Vector<int> v2(std::move((Vector<int>())));
//    Vector<int> v2 = (Vector<int>());
//    std::cout << "size: " << v2.size() << std::endl;
//    v2.print();
//    std::cout << "end of program\n";

    Vector<int> v2(v);
    v2.print();
    std::cout << "size: " << v2.size() << "\t"
              << "capacity: " << v2.capacity() << std::endl;
    std::cout << "size of v: " << v.size() << "\t"
              << "capacity: :" << v.capacity() << "\n";

    auto it1 = v2.begin();
    auto it2 = v2.end();
    ++it1;
    std::cout << "v2.end() - v2.begin() = " << it2 - it1 << std::endl;

//    v2.expand();
//    std::cout << "v2 capacity: " << v2.capacity() << std::endl;
//    v2.print();

    Vector<int> v3;
    v3 = v2;
    std::cout << "v3: ";
    v3.print();
    std::cout << "v3[2] = " << v3[2] << std::endl;
    v3[2] = 10;
    std::cout << "After v3[2] = 10, v3: \n";
    v3.print();

    const Vector<int> v4;
    v4.print();
    
    return 0;
}

#include <static_vector.hpp>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {
    nstl::static_vector< int, 10 > v{1, 2, 3, 4, 5};
    for(auto i : v) {
        std::cout << i << std::endl;
    }

    nstl::static_vector< int, 10 > other = v;
    for(auto i = 0U; i < other.size(); i++) {
        std::cout << other[i] << std::endl;
    }
    return 0;
}

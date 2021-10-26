#include <initializer_list>
#include <static_vector.hpp>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS
#include "catch.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

namespace {
    SCENARIO("Test static vector", "[vector]") {
        GIVEN("A static_vector of size N with a list of numbers") {
            constexpr auto N = 10U;
            const std::initializer_list< int > init_list = {1, 1, 1, 3, 4, 5, 5, 6, 6, 10};
            WHEN("Initializing with initialization list") {
                nstl::static_vector< int, 10 > v{init_list};
                THEN("vector contains values from the list") {
                    REQUIRE(std::equal(std::cbegin(v), std::cend(v), std::cbegin(init_list)));
                }
            }
            WHEN("Initializing with iterators") {
                nstl::static_vector< int, 10 > v{std::cbegin(init_list),
                                                 std::cend(init_list)};
                THEN("vector contains values from the iterators") {
                    REQUIRE(std::equal(std::cbegin(v), std::cend(v), std::cbegin(init_list)));
                }
            }
            WHEN("Values are inserted through push_back") {
                nstl::static_vector< int, 10 > v{};
                std::copy(std::cbegin(init_list), std::cend(init_list), std::back_inserter(v));
                THEN("vector contains values from original container") {
                    REQUIRE(std::equal(std::cbegin(v), std::cend(v), std::cbegin(init_list)));
                }
            }
            WHEN("Call capacity") {
                nstl::static_vector< int, 10 > v{};
                THEN("Capacity is equal with the static size of the vector") {
                    REQUIRE(10 == v.capacity());
                }
            }
        }
    }
} // namespace

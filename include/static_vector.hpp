#pragma once

#include <initializer_list>
#include <memory_resource>
#include <vector>

namespace nstl {
    namespace detail {
        template< std::size_t Sz >
        class memory_resource : public std::pmr::memory_resource {
          public:
            memory_resource(void* memory) : m_memory{memory} {
            }

          private:
            void* do_allocate(std::size_t bytes, std::size_t alignment) override {
                if(bytes > (Sz * alignment)) {
                    std::abort(); // do not allow allocations more than in static memory
                }

                return m_memory;
            }

            void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
            }

            bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
                return this == &other;
            }

            void* m_memory;
        };

        template< typename T, std::size_t Sz >
        struct memory_storage {
            std::aligned_storage_t< sizeof(T), alignof(T) > m_memory[Sz];
            memory_resource< Sz > resource{&m_memory[0]};
            using allocator = std::pmr::polymorphic_allocator< T >;
            allocator m_allocator{&resource};
        };
    } // namespace detail

    template< typename T, std::size_t Sz >
    class static_vector
     : private detail::memory_storage< T, Sz >,
       private std::vector< T, std::pmr::polymorphic_allocator< T > > {
        using base = std::vector< T, std::pmr::polymorphic_allocator< T > >;
        using storage = detail::memory_storage< T, Sz >;

      public:
        static_vector() : base{storage::m_allocator} {
            base::reserve(Sz);
        }

        template< std::size_t OtherSz >
        static_vector(const static_vector< T, OtherSz >& other)
         : base{storage::m_allocator} {
            static_assert(OtherSz <= Sz,
                          "Others vector size can't be bigger that the current "
                          "one.");
            base::reserve(Sz);
            insert(end(), std::cbegin(other), std::cend(other));
        }

        static_vector(const std::initializer_list< T >& init_list)
         : base{storage::m_allocator} {
            base::reserve(Sz);
            insert(end(), std::cbegin(init_list), std::cend(init_list));
        }

        template< typename Iterator >
        static_vector(Iterator first, Iterator last)
         : base{storage::m_allocator} {
            base::reserve(Sz);
            insert(end(), first, last);
        }

        static_vector& operator=(const static_vector< T, Sz >& other) {
            base::clear();
            insert(end(), std::cbegin(other), std::cend(other));
            return *this;
        }

        constexpr std::size_t capacity() const {
            return Sz;
        }

        using base::begin;
        using base::cbegin;
        using base::cend;
        using base::const_iterator;
        using base::end;
        using base::erase;
        using base::insert;
        using base::iterator;
        using base::push_back;
        using base::size;
        using base::value_type;
        using base::operator[];
    };
} // namespace nstl

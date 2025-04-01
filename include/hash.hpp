#if !defined(HASH)
#define HASH

#include <string>
#include <cstdint>

#include <modulo.hpp>
#include <trees.hpp>

namespace nm {
    template <std::int64_t M, std::int64_t P>
    class Hash : public Arithmetic<std::int64_t> {
        private:
            std::size_t n;
            vector<std::int64_t> hash;
            vector<std::int64_t> power;

        public:
            Hash(std::string &s);
            std::int64_t Interval(std::size_t left, std::size_t right);
            ~Hash() {};
    };

} // string hash

namespace nm {
    /*
     * M is expected to be a modular data type (int32_m, int32_n, int32_p)
     * P is any prime that is less than but near to prime used to initialize
     *  modular data type
     */
    template <typename M, M P>
    class ModHash{
        private:
            std::size_t n;
            std::vector<M> hash;
            std::vector<M> power;

        public:
            ModHash(std::string &s);
            std::int64_t Interval(std::size_t left, std::size_t right);
            ~ModHash() {};
    };

} // better string hash

namespace nm {
    template <typename T>
    class CoordinateCompression {
        private:
            Splay<T, T, Node<T> > coordinates;
            std::vector<T> elements;
        public:
            CoordinateCompression(std::vector<T> data);
            std::int32_t coordinate(T x);
            T element(std::size_t i);
            ~CoordinateCompression() {};
    };
} // coordinate compression

#endif // HASH

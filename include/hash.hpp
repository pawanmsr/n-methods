#if !defined(HASH)
#define HASH

#include <modulo.hpp>
#include <trees.hpp>

#include <string>
#include <cstdint>

namespace nm {
    template <std::int64_t M, std::int64_t P>
    class Hash : public Arithmetic<std::int64_t> {
        private:
            std::size_t n;
            std::vector<std::int64_t> hash;
            std::vector<std::int64_t> power;

        public:
            Hash(std::string &s);
            std::int64_t Interval(std::size_t left, std::size_t right);
            ~Hash() {};
    };

} // string hash

namespace nm {
    const int32_m P_ASCII = 257; // UTF-8

    /*
     * M is expected to be a modular data type
     *  (such as int32_m, int32_n, int32_p).
     * P is any prime that is greater than but
     *  near the values encountered during hashing.
     * P must be lower than the Modulus.
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
            Splay<Node<T, T>, T, T> coordinates;
            std::vector<T> elements;
        public:
            CoordinateCompression(std::vector<T> data);
            std::int32_t coordinate(T x);
            T element(std::size_t i);
            ~CoordinateCompression() {};
    };
} // coordinate compression

#endif // HASH

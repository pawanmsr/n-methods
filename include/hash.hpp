#if !defined(HASH)
#define HASH

#include <string>
#include <cstdint>

#include <modulo.hpp>

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

} // namespace nm

#endif // HASH

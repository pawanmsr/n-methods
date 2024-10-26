#if !defined(CRYPTO)
#define CRYPTO

#include <vector>
#include <string>
#include <cstddef>
#include <functional>
namespace nm
{
    class DES {
    private:
        // key optionals
        std::string key;
        std::vector<unsigned char> uc_key;
        std::vector<std::byte> byte_key;

        std::function<std::byte(std::byte, std::byte)> feistel;
    public:
        DES();
        void encrypt();
        void decrypt();
        ~DES();
    };
    
} // namespace nm


#endif // CRYPTO

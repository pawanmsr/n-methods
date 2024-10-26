#if !defined(CRYPTO)
#define CRYPTO

namespace nm
{
    class DES {
    private:
    public:
        DES();
        void encrypt();
        void decrypt();
        ~DES();
    };
    
} // namespace nm


#endif // CRYPTO

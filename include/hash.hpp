#if !defined(HASH)
#define HASH

namespace nm
{
    class Linear
    {
    private:
        std::size_t m;
    public:
        Linear(std::size_t mod);
        ~Linear();
    };
    
} // namespace nm


#endif // HASH

#if !defined(HASH)
#define HASH

namespace nm
{
    template<typename T>
    class Linear
    {
    private:
        std::size_t m;
    public:
        Linear(std::size_t mod);
        T hash(T x);
        ~Linear();
    };
    
} // namespace nm


#endif // HASH

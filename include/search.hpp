#if !defined(SEARCH)
#define SEARCH

#include <utility.hpp>

#include <vector>
#include <string>
#include <functional>

namespace nm
{
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = default_compare<T>);

    class KMP {
    private:
        std::vector<int32_t> positions;
        std::vector<int32_t> partial;
        std::vector<int32_t> prefix;
        std::string w;
        std::string s; // input
        std::size_t n; // input length
        std::size_t i; // processed
    
    protected:
        void prefix_function();
        void partial_function();
        
    public:
        KMP(std::string word);
        void append(std::string s);
        void stream(char c);
        ~KMP();
    };
    
} // namespace nm


#endif // SEARCH

#if !defined(SEARCH)
#define SEARCH

#include <utility.hpp>

#include <vector>
#include <string>
#include <functional>

namespace nm {
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
        std::int32_t i; // processed
    
    protected:
        void prefix_function();
        void failure_function();
        
    public:
        KMP(std::string word);
        
        void clear();
        void flush();
        
        void stream(char c);
        void stream(std::string s);
        std::vector<int32_t> search();
        
        ~KMP();
    };
    
} // namespace nm


#endif // SEARCH

#if !defined(SEARCH)
#define SEARCH

#include <utility.hpp>

#include <vector>
#include <string>
#include <functional>

namespace nm {
    // 64 MegaBytes
    const size_t SIZE_LIMIT_MEM = 64 * 1024 * 1024;

    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = default_compare<T>);

    class KMP {
    private:
        std::vector<std::int32_t> positions;
        std::vector<std::int32_t> partial;
        std::vector<std::int32_t> prefix;

        bool case_sensitive;
        std::size_t critical_memory;
        
        std::string w;
        std::string s; // input
        
        std::size_t n; // input length
        std::int32_t i; // processed
    
    protected:
        std::size_t memory(bool all = false);
        void prefix_function();
        void failure_function();
        bool compare(char x, char y);
        
    public:
        KMP(std::string word,
            bool case_sensitive = true,
                std::size_t memory = SIZE_LIMIT_MEM);
        
        void clear();
        void flush();
        
        void stream(char c);
        void stream(std::string s);
        std::vector<int32_t> search();
        
        ~KMP();
    };
    
} // namespace nm

#endif // SEARCH

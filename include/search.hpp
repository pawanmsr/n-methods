#if !defined(SEARCH)
#define SEARCH

#include <utility.hpp>

#include <vector>
#include <string>
#include <functional>

namespace nm {
    const std::size_t ASCII = 256; // 0-indexed - printable above 31
    const std::size_t UTF_EIGHT = 1000;
    const std::size_t SIZE_LIMIT_MEM = 64 * 1024 * 1024; // 64 MegaBytes

    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = default_compare<T>);

    /*
     * String Search
     * Base class for string search algorithms.
     */
    class SS {
    protected:
        bool case_sensitive;
        std::size_t critical_memory;
        bool compare(char x, char y);

        std::string w;
        std::string s; // input

        std::size_t n; // input length
        std::int32_t i; // processed
    public:
        SS(std::string word,
            bool case_sensitive = true,
                std::size_t memory = SIZE_LIMIT_MEM);
        
        void clear();
        void flush();
        
        void stream(char c);
        void stream(std::string s);

        ~SS();
    };
    
    /*
     * Knuth, Morris, Pratt
     * String search algorithm.
     */
    class KMP : public SS {
        private:
            std::vector<std::int32_t> positions;
            std::vector<std::int32_t> partial;
            std::vector<std::int32_t> prefix;
    
        protected:
            std::size_t memory(bool all = false);
            void prefix_function();
            void failure_function();
        
        public:
            KMP(std::string word,
                bool case_sensitive = true,
                    std::size_t memory = SIZE_LIMIT_MEM);
            
            void clear();
            std::vector<std::int32_t> search();
        
            ~KMP();
    };

    /*
     * Boyar (Robert S.) and Moore (J. Strother) Algorithm
     * https://www.cs.utexas.edu/~moore/best-ideas/string-searching/index.html
     */
    class BMA : public SS {
        private:
            std::vector<std::uint32_t> delta_one;
            std::vector<std::uint32_t> delta_two;
            std::vector<std::uint32_t> positions;
            std::vector<std::uint32_t> delta_zero;

        protected:
            void delta_function();
            std::size_t memory(bool all = false);

        public:
            BMA(std::string word,
                bool case_sensitive = true,
                    std::size_t memory = SIZE_LIMIT_MEM);
            
            void clear();
            std::vector<std::uint32_t> search();
            
            ~BMA();
    };
} // namespace nm

#endif // SEARCH

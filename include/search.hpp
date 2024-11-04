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
        std::vector<int> positions;
        std::vector<int> partial;
        std::vector<int> prefix;
    public:
        KMP(string word);
        ~KMP();
    };
    
} // namespace nm


#endif // SEARCH

#if !defined(SORTING)
#define SORTING

#include <functional>
#include<vector>

namespace nm
{
    template<typename T>
    void quick_sort(int lo, int hi, std::vector<T>& v, std::function<bool(T, T)>& compare);
    
} // namespace nm


#endif // SORTING

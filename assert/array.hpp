#include <iostream>
#include <cmath>

constexpr double default_tolerance = 1e-4;

struct is_subtractable_impl {
    template <class T>
    static auto check(T&& x)->decltype(x-x, std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};

template <class T>
struct is_subtractable : decltype(is_subtractable_impl::check<T>(std::declval<T>())){};

template <class ElemType, std::enable_if_t<is_subtractable<ElemType>::value, std::nullptr_t> = nullptr>
bool assertNear(const ElemType& expected, const ElemType& actual, const double tolerance = default_tolerance){
    if(std::abs(expected - actual) > tolerance)
        return false;
    return true;
};

template <class ElemType, size_t arraySize>
bool assertNear(const ElemType (&expected)[arraySize], const ElemType (&actual)[arraySize], const double tolerance = default_tolerance){
    for(size_t i=0; i<arraySize; ++i)
        if(!assertNear(expected[i], actual[i], tolerance))
            return false;
    return true;
};

template <class ElemType>
bool assertNear(size_t arraySize, const ElemType *expected, const ElemType *actual, const double tolerance = default_tolerance){
    for(size_t i=0; i<arraySize; ++i)
        if(!assertNear(expected[i], actual[i], tolerance))
            return false;
    return true;
};


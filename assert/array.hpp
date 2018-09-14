#include <iostream>
#include <cmath>

namespace assert{

constexpr double default_tolerance = 1e-4;

namespace {

    struct is_subtractable_impl {
        template <class T>
        static auto check(T&& x)->decltype(x-x, std::true_type{});
        template <class T>
        static auto check(...)->std::false_type;
    };

    template <class T>
    struct is_subtractable : decltype(is_subtractable_impl::check<T>(std::declval<T>())){};

}

template <class ElemType, std::enable_if_t<is_subtractable<ElemType>::value, std::nullptr_t> = nullptr>
inline bool assertNear(const ElemType& expected, const ElemType& actual, const double tolerance = default_tolerance){
    if(std::abs(expected - actual) > tolerance){
        std::cerr << "\033[91m[Error]\033[0m Assertion failed (tolerance = " << tolerance << ")" << std::endl;
        std::cerr << "(expected) " << expected << " <> " << actual << " (actual)" << std::endl;
        return false;
    }
    return true;
};

template <class ElemType, size_t arraySize>
inline bool assertNear(const ElemType (&expected)[arraySize], const ElemType (&actual)[arraySize], const double tolerance = default_tolerance){
    for(size_t i=0; i<arraySize; ++i){
        if(!assertNear(expected[i], actual[i], tolerance)){
            std::cerr << "\t |> at index " << i << " / " << arraySize << std::endl;
            return false;
        }
    }
    return true;
};

template <class ElemType>
inline bool assertNear(size_t arraySize, const ElemType *expected, const ElemType *actual, const double tolerance = default_tolerance){
    for(size_t i=0; i<arraySize; ++i){
        if(!assertNear(expected[i], actual[i], tolerance)){
            std::cerr << "\t |> at index " << i << " / " << arraySize << std::endl;
            return false;
        }
    }
    return true;
};

}   // ~ namespace


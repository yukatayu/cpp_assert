#include <iostream>
#include <cmath>

constexpr double default_tolerance = 1e-4;

template <class ElemType>
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


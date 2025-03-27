// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_SMALL_STRING_FORMATTER_TOSTRING_HPP
#define OPENCV_SMALL_STRING_FORMATTER_TOSTRING_HPP

#include <string>
#include <type_traits>
#include "opencv2/core/utils/small_string_formatter_dummy.hpp"

namespace cv {
namespace utils {
namespace detail {

template <typename T>
struct exist_tostring_in_std
{
    template <typename U>
    static auto test(int) -> decltype(std::to_string(std::declval<U>()), std::true_type{});
    template <typename U>
    static auto test(...) -> std::false_type;
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};


template <typename T>
struct exist_tostring_in_cv
{
    template <typename U>
    static auto test(int) -> decltype(cv::to_string(std::declval<U>()), std::true_type{});
    template <typename U>
    static auto test(...) -> std::false_type;
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template <typename T>
struct exist_tostring_in_global
{
    template <typename U>
    static auto test(int) -> decltype(::to_string(std::declval<U>()), std::true_type{});
    template <typename U>
    static auto test(...) -> std::false_type;
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template <typename T>
struct exist_tostring_in_unqualified
{
    template <typename U>
    static auto test(int) -> decltype(to_string(std::declval<U>()), std::true_type{});
    template <typename U>
    static auto test(...) -> std::false_type;
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template <
    typename T,
    bool = ::cv::utils::detail::exist_tostring_in_std<T>::value,
    bool = ::cv::utils::detail::exist_tostring_in_cv<T>::value,
    bool = ::cv::utils::detail::exist_tostring_in_global<T>::value,
    bool = ::cv::utils::detail::exist_tostring_in_unqualified<T>::value
> struct ToStringResolver
    : std::false_type
{
};

template <typename T, bool b1, bool b2, bool b3>
struct ToStringResolver<T, true, b1, b2, b3>
    : std::true_type
{
    inline static std::string to_string_resolved(const T& value)
    {
        // calls std
        return std::to_string(value);
    }
};

template <typename T, bool b1, bool b2>
struct ToStringResolver<T, false, true, b1, b2>
    : std::true_type
{
    inline static std::string to_string_resolved(const T& value)
    {
        // calls cv
        return cv::to_string(value);
    }
};

template <typename T, bool b1>
struct ToStringResolver<T, false, false, true, b1>
    : std::true_type
{
    inline static std::string to_string_resolved(const T& value)
    {
        // calls global
        return ::to_string(value);
    }
};

template <typename T>
struct ToStringResolver<T, false, false, false, true>
    : std::true_type
{
    inline static std::string to_string_resolved(const T& value)
    {
        // calls unqualified (possibly Koenig ADL)
        return to_string(value);
    }
};

}}} // namespace

#endif // OPENCV_SMALL_STRING_FORMATTER_TOSTRING_HPP

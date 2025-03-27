// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_SMALL_STRING_FORMATTER_OPS_HPP
#define OPENCV_SMALL_STRING_FORMATTER_OPS_HPP

#include <string>
#include <type_traits>
#include "opencv2/core/utils/small_string_formatter_base.hpp"
#include "opencv2/core/utils/small_string_formatter_tostring.hpp"

namespace cv {
namespace utils {
namespace detail {

    template <
    typename T,
    bool = std::is_same<typename std::remove_cv<T>::type, char>::value,
    bool = std::is_trivially_assignable<const char*&, T>::value,
    bool = std::is_constructible<std::string, T>::value,
    bool = std::is_pointer<T>::value,
    bool = std::is_base_of<std::true_type, cv::utils::detail::ToStringResolver<T>>::value
> struct WriteToCvFmt
    : std::false_type
{
};

template <typename T, bool b1, bool b2, bool b3, bool b4>
struct WriteToCvFmt<T, true, b1, b2, b3, b4>
    : std::true_type
{
    inline static cv::utils::logging::SmallStringFormatter& write_to_cvfmt(cv::utils::logging::SmallStringFormatter& cvfmt, char value)
    {
        cvfmt._s += value;
        return cvfmt;
    }
};

template <typename T, bool b1, bool b2, bool b3>
struct WriteToCvFmt<T, false, true, b1, b2, b3>
    : std::true_type
{
    inline static cv::utils::logging::SmallStringFormatter& write_to_cvfmt(cv::utils::logging::SmallStringFormatter& cvfmt, const char* value)
    {
        cvfmt._s += value;
        return cvfmt;
    }
};

template <typename T, bool b1, bool b2>
struct WriteToCvFmt<T, false, false, true, b1, b2>
    : std::true_type
{
    inline static cv::utils::logging::SmallStringFormatter& write_to_cvfmt(cv::utils::logging::SmallStringFormatter& cvfmt, const std::string& value)
    {
        cvfmt._s += value;
        return cvfmt;
    }
};

template <typename T, bool b1>
struct WriteToCvFmt<T, false, false, false, true, b1>
    : std::true_type
{
    inline static cv::utils::logging::SmallStringFormatter& write_to_cvfmt(cv::utils::logging::SmallStringFormatter& cvfmt, T value)
    {
        static_assert(std::is_pointer<T>::value, "T must be a pointer type");
        char buf[24] = {};
        std::snprintf(buf, sizeof(buf), "%p", value);
        buf[sizeof(buf) - 1u] = 0;
        cvfmt._s += buf;
        return cvfmt;
    }
};

template <typename T>
struct WriteToCvFmt<T, false, false, false, false, true>
    : std::true_type
{
    inline static cv::utils::logging::SmallStringFormatter& write_to_cvfmt(cv::utils::logging::SmallStringFormatter& cvfmt, const T& value)
    {
        cvfmt._s += cv::utils::detail::ToStringResolver<T>::to_string_resolved(value);
        return cvfmt;
    }
};

}}} // namespace

template <typename T>
inline auto operator<<(cv::utils::logging::SmallStringFormatter& cvfmt, T value)
    -> typename std::enable_if<
        ::cv::utils::detail::WriteToCvFmt<T>::value,
        cv::utils::logging::SmallStringFormatter&
    >::type
{
    return ::cv::utils::detail::WriteToCvFmt<T>::write_to_cvfmt(cvfmt, value);
}

template <typename T>
inline auto operator+=(cv::utils::logging::SmallStringFormatter& cvfmt, T value)
    -> typename std::enable_if<
        ::cv::utils::detail::WriteToCvFmt<T>::value,
        cv::utils::logging::SmallStringFormatter&
    >::type
{
    return cvfmt << value;
}

inline cv::utils::logging::SmallStringFormatter& operator<<(
    cv::utils::logging::SmallStringFormatter& cvfmt, 
    const cv::utils::logging::SmallStringFormatter& value)
{
    cvfmt._s += value._s;
    return cvfmt;
}

inline cv::utils::logging::SmallStringFormatter& operator+=(
    cv::utils::logging::SmallStringFormatter& cvfmt, 
    const cv::utils::logging::SmallStringFormatter& value)
{
    cvfmt._s += value._s;
    return cvfmt;
}

inline cv::utils::logging::SmallStringFormatter& operator+=(
    cv::utils::logging::SmallStringFormatter& cvfmt, 
    const std::string& value)
{
    cvfmt._s += value;
    return cvfmt;
}

#endif // OPENCV_SMALL_STRING_FORMATTER_OPS_HPP

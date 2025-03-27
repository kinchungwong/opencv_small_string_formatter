// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_SMALL_STRING_FORMATTER_STREAM_HPP
#define OPENCV_SMALL_STRING_FORMATTER_STREAM_HPP

#include <string>
#include <type_traits>
#include <ostream>
#include "opencv2/core/utils/small_string_formatter_base.hpp"
#include "opencv2/core/utils/small_string_formatter_tostring.hpp"
#include "opencv2/core/utils/small_string_formatter_ops.hpp"

inline ::std::ostream& operator<<(::std::ostream& os, const cv::utils::logging::SmallStringFormatter& cvfmt)
{
    os << cvfmt._s;
    return os;
}

inline cv::utils::logging::SmallStringFormatter& operator<<(
    cv::utils::logging::SmallStringFormatter& cvfmt,
    std::ostream& (*pf)(std::ostream&))
{
    if (pf == static_cast<std::ostream& (*)(std::ostream&)>(std::endl))
    {
        cvfmt._s += '\n';
    }
    return cvfmt;
}

#endif // OPENCV_SMALL_STRING_FORMATTER_STREAM_HPP

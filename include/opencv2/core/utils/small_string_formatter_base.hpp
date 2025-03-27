// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_SMALL_STRING_FORMATTER_BASE_HPP
#define OPENCV_SMALL_STRING_FORMATTER_BASE_HPP

#include <string>

namespace cv {
namespace utils {
namespace logging {

class SmallStringFormatter
{
public:
    std::string _s;
    explicit SmallStringFormatter(size_t sz_reserve = 0u)
        : _s()
    {
        if (sz_reserve)
        {
            _s.reserve(sz_reserve);
        }
    }
    ~SmallStringFormatter() = default;
    const std::string& str() const
    {
        return _s;
    }
    std::string& str()
    {
        return _s;
    }
    const char* c_str() const
    {
        return _s.c_str();
    }
    const char* data() const
    {
        return _s.data();
    }
    size_t size() const
    {
        return _s.size();
    }
    explicit operator const std::string&() const
    {
        return _s;
    }
    explicit operator std::string() const
    {
        return _s;
    }
    explicit operator bool() const noexcept
    {
        return !_s.empty();
    }
};

}}} // namespace

#endif // OPENCV_SMALL_STRING_FORMATTER_BASE_HPP

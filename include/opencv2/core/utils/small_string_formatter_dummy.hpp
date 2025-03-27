// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_SMALL_STRING_FORMATTER_DUMMY_HPP
#define OPENCV_SMALL_STRING_FORMATTER_DUMMY_HPP

#include <string>

namespace
{
    struct _incomplete_type;
}

namespace
{
    std::string to_string(const _incomplete_type&);
}

namespace cv
{
    std::string to_string(const _incomplete_type&);
};

std::string to_string(const _incomplete_type&);

#endif // OPENCV_SMALL_STRING_FORMATTER_DUMMY_HPP

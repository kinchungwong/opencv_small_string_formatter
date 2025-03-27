#include <iostream>
#include "opencv2/core/utils/small_string_formatter.hpp"

namespace my_namespace
{
    struct MyType
    {
    };

    std::string to_string(const MyType&)
    {
        return "MyType";
    }
}

__attribute__((noinline))
int main()
{
    using SSF = cv::utils::logging::SmallStringFormatter;
    SSF vfmt(256u);
    const auto my_type = my_namespace::MyType();
    vfmt << 123 << " " 
        << 123.0f << " " 
        << ((char)123) << " " 
        << ((unsigned char)(123)) << "... " 
        << std::string("Hello") 
        << '@' << &vfmt << " " 
        << my_type << "@" << &my_type;
    vfmt << "\n";
    vfmt << std::endl << "between the two std::endl" << std::endl;
    vfmt << "\nshall I repeat myself one more time?\n" << vfmt;
    std::cout << vfmt;
    return 0;
}

# opencv_small_string_formatter
A small string formatter intended for use within OpenCV logger

### Design goal

OpenCV internally uses std::ostringstream for its logging purpose. However,
as a cross-platform library, OpenCV needs to workaround issues that may
arise from some platforms not having robust std::ostringstream support,
or where extra care must be taken at specific times such as during 
application startup and shutdown, and dynamic library loading and unloading.

Because of issues with the original STL stream library, it is desirable
to have a minimal library that supports a very limited subset of string
formatting needs that are used within OpenCV internal logging.

### Requirement

- Use of std::ostringstream (or their headers) is optional

### Assumption

- Use of std::string is acceptable
  - Reason: we have not observed the kind of issues that plagued STL stream,
    such as facet and locale requiring dynamic initialization and
    thread-safety.

### Header layout

- ```base.hpp```
  - The minimal class which contains an std::string
  - Out-converters
  - No in-converters
- ```tostring.hpp```
  - Traits library to detect presence of a ```to_string()``` method for
    a given type, which may reside in:
    - in ```std``` namespace (preferred)
    - in ```cv``` namespace
    - in global namespace
    - in unspecified namespace, typically implying ADL lookup
- ```ops.hpp```
  - Defines all write operations for the string formatter class
    - Delegates ```to_string()``` cases to the ```tostring.hpp```
    - Handles special cases, which do not involve the ```to_string()``` method
- ```stream.hpp```
  - Allows sending the formatted string to std::ostream
  - Optional; the string formatter class can be used without including this header.

### Specialized rendering of types

These are handled in the ```ops.hpp```, with a precedence order based on type traits
that is not subject to the implicit conversion or decay rules of the C++ language.

The precedence order is intended to be flexible, and allows to be updated in order
to work around issues that arise from any implicit rules.

### License

Code obtained from this repository or a fork is governed by Creative Commons Zero v1.0 Universal.

It is the author(s) intention that the code will be contributed to the OpenCV library;
once accepted, the portion of code that resides in OpenCV will be governed by the
license(s) that are applicable to the OpenCV project.

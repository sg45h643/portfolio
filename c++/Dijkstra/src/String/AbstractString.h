#ifndef ABSTRACT_STRING_H
#define ABSTRACT_STRING_H

#include <cstddef>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <ostream>
#include <istream>

namespace tango
{
    class AbstractString;
}

namespace tango
{
    class AbstractString
    {
        public:
            virtual ~AbstractString() {}

            virtual AbstractString& operator=(const AbstractString& str);

            virtual AbstractString& operator+=(const AbstractString& str);

            friend std::ostream& operator<<(std::ostream& ostr, const AbstractString& str) { ostr << str.str(); return ostr; }
            friend inline std::istream& operator>>(std::istream& istr, AbstractString& str);

            virtual void append(const char* str, size_t slen) = 0;
            virtual void append(const char* str);
            virtual void append(const std::string& str);
            virtual void append(const AbstractString& str);

            virtual void write(const char* str, size_t slen);
            virtual void write(const char* str);
            virtual void write(const std::string& str);
            virtual void write(const AbstractString& str);

            virtual std::string str() const = 0;

            virtual size_t size() const = 0;
            virtual bool empty() const = 0;

            virtual void clear() = 0;
    };
}

#endif // ABSTRACT_STRING_H

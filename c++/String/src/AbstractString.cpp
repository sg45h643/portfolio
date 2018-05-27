#include "AbstractString.h"

namespace tango
{
 AbstractString& AbstractString::operator=(const AbstractString& str)
    {
        std::string tmp = str.str();
        write(tmp);

        return *this;
    }

    AbstractString& AbstractString::operator+=(const AbstractString& str)
    {
        append(str);

        return *this;
    }

    std::istream& operator>>(std::istream& istr, AbstractString& str)
    {
        uint32_t length = istr.gcount();
        char buffer[1024];
        int32_t avail = 1024;

        while(length)
        {
            avail = length < sizeof(buffer) ? length : sizeof(buffer);

            istr.read(buffer, avail);
            str.append(buffer, avail);

            length -= avail;
        }

        return istr;
    }

    void AbstractString::append(const char* str)
    {
        uint32_t length = strlen(str);

        append(str, length);
    }

    void AbstractString::append(const std::string& str)
    {
        append(str.data(), str.size());
    }

    void AbstractString::append(const AbstractString& str)
    {
        append(str.str());
    }

    void AbstractString::write(const char* str, size_t slen)
    {
        clear();
        append(str, slen);
    }

    void AbstractString::write(const char* str)
    {
        clear();
        append(str);
    }

    void AbstractString::write(const std::string& str)
    {
        clear();
        append(str);
    }

    void AbstractString::write(const AbstractString& str)
    {
        clear();
        append(str);
    }
}

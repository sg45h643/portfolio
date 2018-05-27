#include "String.h"

namespace tango
{
    String::String():
        _str(NULL),
        offset(0),
        length(0)
    {}

    String::String(const char* str):
        _str(NULL),
        offset(0),
        length(0)
    {
        append(str);
    }

    String::String(const String& str):
        _str(NULL),
        offset(0),
        length(0)
    {
        append(str);
    }

    String::String(const std::string& str):
        _str(NULL),
        offset(0),
        length(0)
    {
        append(str);
    }

    String::String(const char* str, size_t slen):
        _str(NULL),
        offset(0),
        length(0)
    {
        append(str, slen);
    }

    String::~String()
    {
        delete[] _str;
    }

    String& String::operator=(const char* str)
    {
        write(str);

        return *this;
    }

    String& String::operator=(const String& str)
    {
        write(str);

        return *this;
    }

    String& String::operator=(const std::string& str)
    {
        write(str);

        return *this;
    }

    bool operator==(const String& str1, const String& str2)
    {
        if(str1.size() != str2.size())
            return false;

        for(uint32_t i = 0; i < str1.size(); i++)
            if(str1[i] != str2[i])
                return false;

        return true;
    }

    bool operator!=(const String& str1, const String& str2)
    {
        return !operator==(str1, str2);
    }

    char& String::operator[](uint32_t key)
    {
        assert(key < offset);

        return _str[key];
    }

    const char& String::operator[](uint32_t key) const
    {
        assert(key < offset);

        return _str[key];
    }

    void String::append(const char* str, size_t slen)
    {
        assert(str);
        assert(0 < slen);

        if(length < slen + offset)
            resize(slen + offset);

        for(uint32_t i = 0; i < slen; i++, offset++)
            _str[offset] = str[i];
    }

    std::string String::str() const
    {
        return std::string(_str, offset);
    }

    size_t String::size() const
    {
        return offset;
    }

    bool String::empty() const
    {
        return offset == 0;
    }

    String String::substr(size_t st, ssize_t off)
    {
        uint32_t end = st;

        if(st < offset)
        {
            if(offset < st + off)
                end = offset;
            else
                end = off;
        }

        return String(&_str[st], end);
    }

    void String::clear()
    {
        offset = 0;
    }

    void String::resize(uint32_t memory)
    {
        if(length)
        {
            length = (length + memory / BASE_LENGTH + 1) * BASE_LENGTH;
            char* new_str = new char[length];

            for(uint32_t i = 0; i < offset; i++)
                new_str[i] = _str[i];

            delete[] _str;
            _str = new_str;
        }
        else
        {
            length = (memory / BASE_LENGTH + 1) * BASE_LENGTH;
            _str = new char[length];
            offset = 0;
        }
    }
}

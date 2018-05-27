#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <assert.h>

namespace tango
{
    class String;
}

#include "AbstractString.h"

#define BASE_LENGTH (100 + 1)

namespace tango
{
    class String:
        public AbstractString
    {
        public:
            String();
            String(const char* str);
            String(const String& str);
            String(const std::string& str);
            String(const char* str, size_t slen);
            virtual ~String();

            String& operator=(const char* str);
            String& operator=(const String& str);
            String& operator=(const std::string& str);

            friend String operator+(const String& str1, const String& str2) { String str(str1); str += str2; return str;}

            friend bool operator==(const String& str1, const String& str2);
            friend bool operator!=(const String& str1, const String& str2);

            char& operator[](uint32_t key);
            const char& operator[](uint32_t key) const;

            void append(const char* str, size_t slen);
            using AbstractString::append;

            std::string str() const;

            size_t size() const;
            bool empty() const;

            String substr(size_t st, ssize_t off = -1);

            void clear();

        private:
            void resize(uint32_t memory);

        private:
            char* _str;
            uint32_t offset;
            uint32_t length;
    };
}

#endif // STRING_H

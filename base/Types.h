#pragma once

#include <stdint.h>
#include <string.h>
#include <string>

#ifndef NDEBUG
#include <assert.h>
#endif

namespace cppl
{
    using std::string;

    inline void memZero(void *p, size_t n)
    {
        memset(p, 0, n);
    }

    template <typename To, typename From>
    inline To implicit_cast(From const &f)
    {
        return f;
    }

    template <typename To, typename From> // use like this: down_cast<T*>(foo);
    inline To down_cast(From *f)          // so we only accept pointers
    {
        if (false)
        {
            implicit_cast<From *, To>(0);
        }

#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
        assert(f == NULL || dynamic_cast<To>(f) != NULL); // RTTI: debug mode only!
#endif
        return static_cast<To>(f);
    }

}
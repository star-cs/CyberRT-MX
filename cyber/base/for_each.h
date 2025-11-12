#ifndef __BASE_FOR_EACH_H__
#define __BASE_FOR_EACH_H__

#include <type_traits>
#include <iostream>
#include "macros.h"

namespace cyber
{
namespace base
{

    DEFINE_TYPE_TRAIT(HasLess, operator<) // NOLINT

    template <class Value, class End>
    typename std::enable_if<HasLess<Value>::value && HasLess<End>::value, bool>::type
    LessThan(const Value &val, const End &end)
    {
        return val < end;
    }

    template <class Value, class End>
    typename std::enable_if<!HasLess<Value>::value || !HasLess<End>::value, bool>::type
    LessThan(const Value &val, const End &end)
    {
        return val != end;
    }

#define FOR_EACH(i, begin, end)                                                                    \
    for (auto i = (true ? (begin) : (end)); cyber::base::LessThan(i, (end)); ++i)

} // namespace base
} // namespace cyber

#endif
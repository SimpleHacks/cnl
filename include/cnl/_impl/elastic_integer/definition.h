
//          Copyright John McFarlane 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_ELASTIC_INTEGER_DEFINITION_H)
#define CNL_IMPL_ELASTIC_INTEGER_DEFINITION_H

#include "../../integer.h"
#include "../elastic_tag.h"
#include "../num_traits/set_digits.h"
#include "../wrapper.h"
#include "declaration.h"
#include "rep_of.h"
#include "tag_of.h"

#include <algorithm>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        template<int Digits, integer Narrowest>
        using elastic_rep_t =
                typename set_digits<Narrowest, std::max(digits<Narrowest>, Digits)>::type;

        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::is_elastic_integer

        template<class ElasticInteger>
        struct is_elastic_integer : std::false_type {
        };

        template<int Digits, integer Narrowest>
        struct is_elastic_integer<elastic_integer<Digits, Narrowest>> : std::true_type {
        };

        template<integer Rep, int Digits, integer Narrowest>
        struct is_elastic_integer<wrapper<Rep, elastic_tag<Digits, Narrowest>>>;

        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::elastic_integer_base_t

        template<int Digits, integer Narrowest>
        using elastic_integer_base_t = _impl::wrapper<
                _impl::rep_of_t<elastic_integer<Digits, Narrowest>>,
                _impl::tag_of_t<elastic_integer<Digits, Narrowest>>>;
    }

    template<int Digits, integer Narrowest>
    class elastic_integer : public _impl::elastic_integer_base_t<Digits, Narrowest> {
    public:
        using _base = _impl::elastic_integer_base_t<Digits, Narrowest>;
        static_assert(
                !_impl::is_elastic_integer<_impl::rep_of_t<_base>>::value,
                "elastic_integer of elastic_integer is not a supported");

        /// default constructor
        elastic_integer() = default;

        /// constructor not taking cnl::fraction
        template<typename Number>
        // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr elastic_integer(Number const& n)
            : _base(n)
        {
        }
    };

    namespace _impl {
        template<bool Signed>
        struct machine_digits {
            static constexpr int value =
                    digits<typename std::conditional<Signed, signed, unsigned>::type>;
        };

        template<integer S>
        using narrowest = set_digits_t<S, machine_digits<numbers::signedness_v<S>>::value>;
    }

    template<class S>
    elastic_integer(S const& s) -> elastic_integer<digits<S>, _impl::narrowest<S>>;

    template<CNL_IMPL_CONSTANT_VALUE_TYPE Value>
    elastic_integer(constant<Value>) -> elastic_integer<digits<constant<Value>>>;
}

#endif  // CNL_IMPL_ELASTIC_INTEGER_DEFINITION_H

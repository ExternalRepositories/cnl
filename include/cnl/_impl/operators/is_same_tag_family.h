
//          Copyright John McFarlane 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_OPERATORS_IS_SAME_TAG_FAMILY_H)
#define CNL_IMPL_OPERATORS_IS_SAME_TAG_FAMILY_H

#include "../num_traits/tag.h"

#include <type_traits>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        template<tag Tag1, tag Tag2, class Enabled = void>
        struct is_same_tag_family : std::is_same<Tag1, Tag2> {
        };
    }
}

#endif  // CNL_IMPL_OPERATORS_IS_SAME_TAG_FAMILY_H

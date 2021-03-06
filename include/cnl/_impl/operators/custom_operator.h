
//          Copyright John McFarlane 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief primary templates providing basis for arithmetic operator customization points

#if !defined(CNL_IMPL_OPERATORS_GENERIC_OPERATORS_H)
#define CNL_IMPL_OPERATORS_GENERIC_OPERATORS_H

#include "../config.h"
#include "../num_traits/tag.h"
#include "operators.h"

#include <type_traits>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        struct native_tag;

        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::wants_generic_ops

        // true iff T wants generic operator overloads
        template<class T>
        inline constexpr auto wants_generic_ops = false;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::operand

    /// \brief used as Operands parameter of \ref cnl::custom_operator
    /// \tparam Rep type of operand handled by custom_operator specialization
    /// \tparam Tag behavior of `Rep` handled by custom_operator specialization
    template<typename Rep, tag Tag = _impl::native_tag>
    class operand;

    namespace _impl {
        template<typename T>
        inline constexpr bool is_operand_specialization = false;

        template<typename Rep, typename Tag>
        inline constexpr bool is_operand_specialization<operand<Rep, Tag>> = true;

        template<typename T>
        concept operand_specialization = is_operand_specialization<T>;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // generic operators

    /// \brief customization point for operator overloads
    /// \note avoids the need to overload every last operator
    template<_impl::op Operator, _impl::operand_specialization... Operands>
    struct custom_operator;

    template<class ArchetypeTag, typename Initializer>
    struct deduction;

    template<_impl::compound_assign_op Operator, class LhsOperand, tag LhsTag, class RhsOperand, tag RhsTag>
    struct custom_operator<
            Operator,
            operand<LhsOperand, LhsTag>,
            operand<RhsOperand, RhsTag>> {
        constexpr LhsOperand& operator()(LhsOperand& lhs, RhsOperand const& rhs) const
        {
            using compound_assign_operator = cnl::custom_operator<
                    typename Operator::binary, operand<LhsOperand, LhsTag>, operand<RhsOperand, RhsTag>>;
            using compound_assign_operator_result = decltype(compound_assign_operator{}(lhs, rhs));
            using convert_operator = cnl::custom_operator<
                    _impl::convert_op,
                    operand<compound_assign_operator_result, RhsTag>,
                    operand<LhsOperand, LhsTag>>;
            return lhs = convert_operator{}(compound_assign_operator{}(lhs, rhs));
        }
    };
}

#endif  // CNL_IMPL_OPERATORS_GENERIC_OPERATORS_H

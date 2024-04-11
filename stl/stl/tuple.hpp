// tuple standard header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
#ifndef _TUPLE_
#define _TUPLE_
#include <yvals_core.h>
#if _STL_COMPILER_PREPROCESSOR
#ifdef __cpp_lib_concepts
#include <compare>
#endif // __cpp_lib_concepts
#include <type_traits>
#include <xutility>

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

_STD_BEGIN
#if _HAS_CONDITIONAL_EXPLICIT
template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_conditional_explicit_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_conditional_explicit_v0<true, tuple<_Dests...>, _Srcs...> =
!conjunction_v<is_convertible<_Srcs, _Dests>...>;

template <class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_conditional_explicit_v =
_Tuple_conditional_explicit_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>;
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
// Constrain tuple's implicit constructors
template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_implicit_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_implicit_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_constructible<_Dests, _Srcs>..., is_convertible<_Srcs, _Dests>...>;

template <class _Dest, class... _Srcs>
struct _Tuple_implicit_val
    : bool_constant<_Tuple_implicit_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>> {
};

// Constrain tuple's explicit constructors
template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_explicit_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_explicit_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_constructible<_Dests, _Srcs>..., negation<conjunction<is_convertible<_Srcs, _Dests>...>>>;

template <class _Dest, class... _Srcs>
struct _Tuple_explicit_val
    : bool_constant<_Tuple_explicit_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>> {
};
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_constructible_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_constructible_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_constructible<_Dests, _Srcs>...>;

template <class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_constructible_v =
_Tuple_constructible_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>;

template <class _Dest, class... _Srcs>
struct _Tuple_constructible_val : bool_constant<_Tuple_constructible_v<_Dest, _Srcs...>> { };

template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_constructible_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_constructible_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_nothrow_constructible<_Dests, _Srcs>...>;

template <class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_constructible_v =
_Tuple_nothrow_constructible_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>;

template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_assignable_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_assignable_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_assignable<_Dests&, _Srcs>...>; // note _Dests& instead of _Dests

template <class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_assignable_v =
_Tuple_assignable_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>;

template <class _Dest, class... _Srcs>
struct _Tuple_assignable_val : bool_constant<_Tuple_assignable_v<_Dest, _Srcs...>> { };

template <bool _Same, class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_assignable_v0 = false;

template <class... _Dests, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_assignable_v0<true, tuple<_Dests...>, _Srcs...> =
conjunction_v<is_nothrow_assignable<_Dests&, _Srcs>...>; // note _Dests& instead of _Dests

template <class _Dest, class... _Srcs>
_INLINE_VAR constexpr bool _Tuple_nothrow_assignable_v =
_Tuple_nothrow_assignable_v0<tuple_size_v<_Dest> == sizeof...( _Srcs ), _Dest, _Srcs...>;

// Constrain tuple's copy converting constructor (LWG-2549)
template <class _Myself, class... _Other>
struct _Tuple_convert_copy_val : true_type { };

template <class _This, class _Uty>
struct _Tuple_convert_copy_val<tuple<_This>, _Uty>
    : bool_constant<!disjunction_v<is_same<_This, _Uty>, is_constructible<_This, const tuple<_Uty>&>,
    is_convertible<const tuple<_Uty>&, _This>>> {};

// Constrain tuple's move converting constructor (LWG-2549)
template <class _Myself, class... _Other>
struct _Tuple_convert_move_val : true_type { };

template <class _This, class _Uty>
struct _Tuple_convert_move_val<tuple<_This>, _Uty>
    : bool_constant<!disjunction_v<is_same<_This, _Uty>, is_constructible<_This, tuple<_Uty>>,
    is_convertible<tuple<_Uty>, _This>>> {};

// Constrain tuple's perfect forwarding constructor (LWG-3121)
template <class _Myself, class _This2, class... _Rest2>
struct _Tuple_perfect_val : true_type { };

template <class _Myself, class _This2>
struct _Tuple_perfect_val<_Myself, _This2>
    : bool_constant<!is_same_v<_Myself, remove_const_t<remove_reference_t<_This2>>>> {
};

struct _Ignore { // struct that ignores assignments
    template <class _Ty>
    constexpr const _Ignore& operator=( const _Ty& ) const noexcept /* strengthened */ {
        // do nothing
        return *this;
    }
};

_INLINE_VAR constexpr _Ignore ignore {};

// Note: To improve throughput, this file uses extra _STD qualification for names that appear in the
// arguments of enable_if_t. Specifically, we qualify names which appear anywhere in the STL as members of
// some class - including injected-class-names! - that we know are not members of the class being defined.
// This avoids pointless class-member lookup for those names in this context.

template <class _Ty>
struct _Tuple_val { // stores each value in a tuple
    constexpr _Tuple_val() : _Val() { }

    template <class _Other>
    constexpr _Tuple_val( _Other&& _Arg ) : _Val( _STD forward<_Other>( _Arg ) ) { }

    template <class _Alloc, class... _Other, enable_if_t<!uses_allocator_v<_Ty, _Alloc>, int> = 0>
    constexpr _Tuple_val( const _Alloc&, allocator_arg_t, _Other&&... _Arg ) : _Val( _STD forward<_Other>( _Arg )... ) { }

    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_STD uses_allocator<_Ty, _Alloc>,
        _STD is_constructible<_Ty, _STD allocator_arg_t, const _Alloc&, _Other...>>,
        int> = 0>
        constexpr _Tuple_val( const _Alloc& _Al, allocator_arg_t, _Other&&... _Arg )
        : _Val( allocator_arg, _Al, _STD forward<_Other>( _Arg )... ) {
    }

    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_STD uses_allocator<_Ty, _Alloc>,
        _STD negation<_STD is_constructible<_Ty, _STD allocator_arg_t, const _Alloc&, _Other...>>>,
        int> = 0>
    constexpr _Tuple_val( const _Alloc& _Al, allocator_arg_t, _Other&&... _Arg )
        : _Val( _STD forward<_Other>( _Arg )..., _Al ) {
    }

    _Ty _Val;
};

struct _Exact_args_t {
    explicit _Exact_args_t() = default;
}; // tag type to disambiguate construction (from one arg per element)

struct _Unpack_tuple_t {
    explicit _Unpack_tuple_t() = default;
}; // tag type to disambiguate construction (from unpacking a tuple/pair)

struct _Alloc_exact_args_t {
    explicit _Alloc_exact_args_t() = default;
}; // tag type to disambiguate construction (from an allocator and one arg per element)

struct _Alloc_unpack_tuple_t {
    explicit _Alloc_unpack_tuple_t() = default;
}; // tag type to disambiguate construction (from an allocator and unpacking a tuple/pair)

template <class... _Types>
class tuple;

template <>
class tuple<> { // empty tuple
public:
    constexpr tuple() noexcept = default; /* strengthened */

    constexpr tuple( const tuple& ) noexcept /* strengthened */ { } // TRANSITION, ABI: should be defaulted

    template <class _Alloc>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& ) noexcept /* strengthened */ { }

    template <class _Alloc>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc&, const tuple& ) noexcept /* strengthened */ { }

    template <class _Tag, enable_if_t<is_same_v<_Tag, _STD _Exact_args_t>, int> = 0>
    constexpr tuple( _Tag ) noexcept /* strengthened */ { }

    template <class _Tag, class _Alloc, enable_if_t<is_same_v<_Tag, _STD _Alloc_exact_args_t>, int> = 0>
    constexpr tuple( _Tag, const _Alloc& ) noexcept /* strengthened */ { }

    constexpr tuple& operator=( const tuple& ) = default;

    _CONSTEXPR20 void swap( tuple& ) noexcept { }

    constexpr bool _Equals( const tuple& ) const noexcept {
        return true;
    }

#ifdef __cpp_lib_concepts
    _NODISCARD constexpr strong_ordering _Three_way_compare( const tuple& ) const noexcept {
        return strong_ordering::equal;
    }
#else // ^^^ defined(__cpp_lib_concepts) / !defined(__cpp_lib_concepts) vvv
    _NODISCARD constexpr bool _Less( const tuple& ) const noexcept {
        return false;
    }
#endif // ^^^ !defined(__cpp_lib_concepts) ^^^
};

template <class _This, class... _Rest>
class tuple<_This, _Rest...> : private tuple<_Rest...> { // recursive tuple definition
public:
    using _This_type = _This;
    using _Mybase = tuple<_Rest...>;

    template <class _Tag, class _This2, class... _Rest2, enable_if_t<is_same_v<_Tag, _STD _Exact_args_t>, int> = 0>
    constexpr tuple( _Tag, _This2&& _This_arg, _Rest2&&... _Rest_arg )
        : _Mybase( _Exact_args_t {}, _STD forward<_Rest2>( _Rest_arg )... ), _Myfirst( _STD forward<_This2>( _This_arg ) ) {
    }

    template <class _Tag, class _Tpl, size_t... _Indices, enable_if_t<is_same_v<_Tag, _STD _Unpack_tuple_t>, int> = 0>
    constexpr tuple( _Tag, _Tpl&& _Right, index_sequence<_Indices...> );

    template <class _Tag, class _Tpl, enable_if_t<is_same_v<_Tag, _STD _Unpack_tuple_t>, int> = 0>
    constexpr tuple( _Tag, _Tpl&& _Right )
        : tuple( _Unpack_tuple_t {}, _STD forward<_Tpl>( _Right ),
            make_index_sequence<tuple_size_v<remove_reference_t<_Tpl>>>{} ) {
    }

    template <class _Tag, class _Alloc, class _This2, class... _Rest2,
        enable_if_t<is_same_v<_Tag, _STD _Alloc_exact_args_t>, int> = 0>
    constexpr tuple( _Tag, const _Alloc& _Al, _This2&& _This_arg, _Rest2&&... _Rest_arg )
        : _Mybase( _Alloc_exact_args_t {}, _Al, _STD forward<_Rest2>( _Rest_arg )... ),
        _Myfirst( _Al, allocator_arg, _STD forward<_This2>( _This_arg ) ) {
    }

    template <class _Tag, class _Alloc, class _Tpl, size_t... _Indices,
        enable_if_t<is_same_v<_Tag, _STD _Alloc_unpack_tuple_t>, int> = 0>
    constexpr tuple( _Tag, const _Alloc& _Al, _Tpl&& _Right, index_sequence<_Indices...> );

    template <class _Tag, class _Alloc, class _Tpl, enable_if_t<is_same_v<_Tag, _STD _Alloc_unpack_tuple_t>, int> = 0>
    constexpr tuple( _Tag, const _Alloc& _Al, _Tpl&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD forward<_Tpl>( _Right ),
            make_index_sequence<tuple_size_v<remove_reference_t<_Tpl>>>{} ) {
    }

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _This2 = _This,
        enable_if_t<conjunction_v<_STD is_default_constructible<_This2>, _STD is_default_constructible<_Rest>...>,
        int> = 0>
    constexpr explicit(
        !conjunction_v<_Is_implicitly_default_constructible<_This2>, _Is_implicitly_default_constructible<_Rest>...> )
        tuple() noexcept( conjunction_v<is_nothrow_default_constructible<_This2>,
            is_nothrow_default_constructible<_Rest>...> ) // strengthened
        : _Mybase(), _Myfirst() {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _This2 = _This,
        enable_if_t<conjunction_v<is_default_constructible<_This2>, is_default_constructible<_Rest>...,
        _Is_implicitly_default_constructible<_This2>, _Is_implicitly_default_constructible<_Rest>...>,
        int> = 0>
    constexpr tuple() noexcept( conjunction_v<is_nothrow_default_constructible<_This2>,
        is_nothrow_default_constructible<_Rest>...> ) // strengthened
        : _Mybase(), _Myfirst() {
    }

    template <class _This2 = _This,
        enable_if_t<conjunction_v<is_default_constructible<_This2>, is_default_constructible<_Rest>...,
        negation<conjunction<_Is_implicitly_default_constructible<_This2>,
        _Is_implicitly_default_constructible<_Rest>...>>>,
        int> = 0>
        constexpr explicit tuple() noexcept( conjunction_v<is_nothrow_default_constructible<_This2>,
            is_nothrow_default_constructible<_Rest>...> ) // strengthened
        : _Mybase(), _Myfirst() {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _This2 = _This, enable_if_t<_Tuple_constructible_v<tuple, const _This2&, const _Rest&...>, int> = 0>
    constexpr explicit( _Tuple_conditional_explicit_v<tuple, const _This2&, const _Rest&...> ) tuple(
        const _This& _This_arg, const _Rest&... _Rest_arg ) noexcept( conjunction_v<is_nothrow_copy_constructible<_This2>,
            is_nothrow_copy_constructible<_Rest>...> ) // strengthened
        : tuple( _Exact_args_t {}, _This_arg, _Rest_arg... ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _This2 = _This,
        enable_if_t<_Tuple_implicit_val<tuple, const _This2&, const _Rest&...>::value, int> = 0>
    constexpr tuple( const _This& _This_arg, const _Rest&... _Rest_arg ) noexcept(
        conjunction_v<is_nothrow_copy_constructible<_This2>,
        is_nothrow_copy_constructible<_Rest>...> ) // strengthened
        : tuple( _Exact_args_t {}, _This_arg, _Rest_arg... ) {
    }

    template <class _This2 = _This,
        enable_if_t<_Tuple_explicit_val<tuple, const _This2&, const _Rest&...>::value, int> = 0>
    constexpr explicit tuple( const _This& _This_arg, const _Rest&... _Rest_arg ) noexcept(
        conjunction_v<is_nothrow_copy_constructible<_This2>,
        is_nothrow_copy_constructible<_Rest>...> ) // strengthened
        : tuple( _Exact_args_t {}, _This_arg, _Rest_arg... ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _This2, class... _Rest2,
        enable_if_t<conjunction_v<_STD _Tuple_perfect_val<tuple, _This2, _Rest2...>,
        _STD _Tuple_constructible_val<tuple, _This2, _Rest2...>>,
        int> = 0>
        constexpr explicit( _Tuple_conditional_explicit_v<tuple, _This2, _Rest2...> ) tuple( _This2&& _This_arg,
            _Rest2&&... _Rest_arg ) noexcept( _Tuple_nothrow_constructible_v<tuple, _This2, _Rest2...> ) // strengthened
        : tuple( _Exact_args_t {}, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _This2, class... _Rest2,
        enable_if_t<
        conjunction_v<_Tuple_perfect_val<tuple, _This2, _Rest2...>, _Tuple_implicit_val<tuple, _This2, _Rest2...>>,
        int> = 0>
    constexpr tuple( _This2&& _This_arg, _Rest2&&... _Rest_arg ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _This2, _Rest2...> ) // strengthened
        : tuple( _Exact_args_t {}, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }

    template <class _This2, class... _Rest2,
        enable_if_t<
        conjunction_v<_Tuple_perfect_val<tuple, _This2, _Rest2...>, _Tuple_explicit_val<tuple, _This2, _Rest2...>>,
        int> = 0>
    constexpr explicit tuple( _This2&& _This_arg, _Rest2&&... _Rest_arg ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _This2, _Rest2...> ) // strengthened
        : tuple( _Exact_args_t {}, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

    tuple( const tuple& ) = default;
    tuple( tuple&& ) = default;

#if _HAS_CONDITIONAL_EXPLICIT
    template <class... _Other, enable_if_t<conjunction_v<_STD _Tuple_constructible_val<tuple, const _Other&...>,
        _STD _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
    constexpr explicit( _Tuple_conditional_explicit_v<tuple, const _Other&...> )
        tuple( const tuple<_Other...>& _Right ) noexcept(
            _Tuple_nothrow_constructible_v<tuple, const _Other&...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class... _Other, enable_if_t<conjunction_v<_Tuple_implicit_val<tuple, const _Other&...>,
        _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
    constexpr tuple( const tuple<_Other...>& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, const _Other&...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }

    template <class... _Other, enable_if_t<conjunction_v<_Tuple_explicit_val<tuple, const _Other&...>,
        _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
    constexpr explicit tuple( const tuple<_Other...>& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, const _Other&...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class... _Other, enable_if_t<conjunction_v<_STD _Tuple_constructible_val<tuple, _Other...>,
        _STD _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
    constexpr explicit( _Tuple_conditional_explicit_v<tuple, _Other...> )
        tuple( tuple<_Other...>&& _Right ) noexcept( _Tuple_nothrow_constructible_v<tuple, _Other...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class... _Other,
        enable_if_t<conjunction_v<_Tuple_implicit_val<tuple, _Other...>, _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
    constexpr tuple( tuple<_Other...>&& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _Other...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }

    template <class... _Other,
        enable_if_t<conjunction_v<_Tuple_explicit_val<tuple, _Other...>, _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
    constexpr explicit tuple( tuple<_Other...>&& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _Other...> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _First, class _Second,
        enable_if_t<_Tuple_constructible_v<tuple, const _First&, const _Second&>, int> = 0>
    constexpr explicit( _Tuple_conditional_explicit_v<tuple, const _First&, const _Second&> )
        tuple( const pair<_First, _Second>& _Right ) noexcept(
            _Tuple_nothrow_constructible_v<tuple, const _First&, const _Second&> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _First, class _Second,
        enable_if_t<_Tuple_implicit_val<tuple, const _First&, const _Second&>::value, int> = 0>
    constexpr tuple( const pair<_First, _Second>& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, const _First&, const _Second&> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }

    template <class _First, class _Second,
        enable_if_t<_Tuple_explicit_val<tuple, const _First&, const _Second&>::value, int> = 0>
    constexpr explicit tuple( const pair<_First, _Second>& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, const _First&, const _Second&> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _Right ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _First, class _Second, enable_if_t<_Tuple_constructible_v<tuple, _First, _Second>, int> = 0>
    constexpr explicit( _Tuple_conditional_explicit_v<tuple, _First, _Second> ) tuple(
        pair<_First, _Second>&& _Right ) noexcept( _Tuple_nothrow_constructible_v<tuple, _First, _Second> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _First, class _Second, enable_if_t<_Tuple_implicit_val<tuple, _First, _Second>::value, int> = 0>
    constexpr tuple( pair<_First, _Second>&& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _First, _Second> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }

    template <class _First, class _Second, enable_if_t<_Tuple_explicit_val<tuple, _First, _Second>::value, int> = 0>
    constexpr explicit tuple( pair<_First, _Second>&& _Right ) noexcept(
        _Tuple_nothrow_constructible_v<tuple, _First, _Second> ) // strengthened
        : tuple( _Unpack_tuple_t {}, _STD move( _Right ) ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class _This2 = _This,
        enable_if_t<conjunction_v<_STD is_default_constructible<_This2>, _STD is_default_constructible<_Rest>...>,
        int> = 0>
    _CONSTEXPR20 explicit(
        !conjunction_v<_Is_implicitly_default_constructible<_This2>, _Is_implicitly_default_constructible<_Rest>...> )
        tuple( allocator_arg_t, const _Alloc& _Al )
        : _Mybase( allocator_arg, _Al ), _Myfirst( _Al, allocator_arg ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class _This2 = _This,
        enable_if_t<conjunction_v<is_default_constructible<_This2>, is_default_constructible<_Rest>...,
        _Is_implicitly_default_constructible<_This2>, _Is_implicitly_default_constructible<_Rest>...>,
        int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al )
        : _Mybase( allocator_arg, _Al ), _Myfirst( _Al, allocator_arg ) {
    }

    template <class _Alloc, class _This2 = _This,
        enable_if_t<conjunction_v<is_default_constructible<_This2>, is_default_constructible<_Rest>...,
        negation<conjunction<_Is_implicitly_default_constructible<_This2>,
        _Is_implicitly_default_constructible<_Rest>...>>>,
        int> = 0>
        _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al )
        : _Mybase( allocator_arg, _Al ), _Myfirst( _Al, allocator_arg ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class _This2 = _This,
        enable_if_t<_Tuple_constructible_v<tuple, const _This2&, const _Rest&...>, int> = 0>
    _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, const _This2&, const _Rest&...> )
        tuple( allocator_arg_t, const _Alloc& _Al, const _This& _This_arg, const _Rest&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _This_arg, _Rest_arg... ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class _This2 = _This,
        enable_if_t<_Tuple_implicit_val<tuple, const _This2&, const _Rest&...>::value, int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, const _This& _This_arg, const _Rest&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _This_arg, _Rest_arg... ) {
    }

    template <class _Alloc, class _This2 = _This,
        enable_if_t<_Tuple_explicit_val<tuple, const _This2&, const _Rest&...>::value, int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, const _This& _This_arg, const _Rest&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _This_arg, _Rest_arg... ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class _This2, class... _Rest2,
        enable_if_t<conjunction_v<_STD _Tuple_perfect_val<tuple, _This2, _Rest2...>,
        _STD _Tuple_constructible_val<tuple, _This2, _Rest2...>>,
        int> = 0>
        _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, _This2, _Rest2...> )
        tuple( allocator_arg_t, const _Alloc& _Al, _This2&& _This_arg, _Rest2&&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class _This2, class... _Rest2,
        enable_if_t<
        conjunction_v<_Tuple_perfect_val<tuple, _This2, _Rest2...>, _Tuple_implicit_val<tuple, _This2, _Rest2...>>,
        int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, _This2&& _This_arg, _Rest2&&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }

    template <class _Alloc, class _This2, class... _Rest2,
        enable_if_t<
        conjunction_v<_Tuple_perfect_val<tuple, _This2, _Rest2...>, _Tuple_explicit_val<tuple, _This2, _Rest2...>>,
        int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, _This2&& _This_arg, _Rest2&&... _Rest_arg )
        : tuple( _Alloc_exact_args_t {}, _Al, _STD forward<_This2>( _This_arg ), _STD forward<_Rest2>( _Rest_arg )... ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

    template <class _Alloc, class _This2 = _This,
        enable_if_t<_Tuple_constructible_v<tuple, const _This2&, const _Rest&...>, int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, const tuple& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }

    template <class _Alloc, class _This2 = _This, enable_if_t<_Tuple_constructible_v<tuple, _This2, _Rest...>, int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, tuple&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_STD _Tuple_constructible_val<tuple, const _Other&...>,
        _STD _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
        _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, const _Other&...> )
        tuple( allocator_arg_t, const _Alloc& _Al, const tuple<_Other...>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class... _Other,
        enable_if_t<
        conjunction_v<_Tuple_implicit_val<tuple, const _Other&...>, _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, const tuple<_Other...>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }

    template <class _Alloc, class... _Other,
        enable_if_t<
        conjunction_v<_Tuple_explicit_val<tuple, const _Other&...>, _Tuple_convert_copy_val<tuple, _Other...>>,
        int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, const tuple<_Other...>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_STD _Tuple_constructible_val<tuple, _Other...>,
        _STD _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
        _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, _Other...> )
        tuple( allocator_arg_t, const _Alloc& _Al, tuple<_Other...>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_Tuple_implicit_val<tuple, _Other...>, _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, tuple<_Other...>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }

    template <class _Alloc, class... _Other,
        enable_if_t<conjunction_v<_Tuple_explicit_val<tuple, _Other...>, _Tuple_convert_move_val<tuple, _Other...>>,
        int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, tuple<_Other...>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_constructible_v<tuple, const _First&, const _Second&>, int> = 0>
    _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, const _First&, const _Second&> )
        tuple( allocator_arg_t, const _Alloc& _Al, const pair<_First, _Second>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_implicit_val<tuple, const _First&, const _Second&>::value, int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, const pair<_First, _Second>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }

    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_explicit_val<tuple, const _First&, const _Second&>::value, int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, const pair<_First, _Second>& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _Right ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

#if _HAS_CONDITIONAL_EXPLICIT
    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_constructible_v<tuple, _First, _Second>, int> = 0>
    _CONSTEXPR20 explicit( _Tuple_conditional_explicit_v<tuple, _First, _Second> )
        tuple( allocator_arg_t, const _Alloc& _Al, pair<_First, _Second>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }
#else // ^^^ _HAS_CONDITIONAL_EXPLICIT ^^^ / vvv !_HAS_CONDITIONAL_EXPLICIT vvv
    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_implicit_val<tuple, _First, _Second>::value, int> = 0>
    _CONSTEXPR20 tuple( allocator_arg_t, const _Alloc& _Al, pair<_First, _Second>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }

    template <class _Alloc, class _First, class _Second,
        enable_if_t<_Tuple_explicit_val<tuple, _First, _Second>::value, int> = 0>
    _CONSTEXPR20 explicit tuple( allocator_arg_t, const _Alloc& _Al, pair<_First, _Second>&& _Right )
        : tuple( _Alloc_unpack_tuple_t {}, _Al, _STD move( _Right ) ) {
    }
#endif // ^^^ !_HAS_CONDITIONAL_EXPLICIT ^^^

    tuple& operator=( const volatile tuple& ) = delete;

    template <class _Myself = tuple, class _This2 = _This,
        enable_if_t<conjunction_v<_STD _Is_copy_assignable_no_precondition_check<_This2>,
        _STD _Is_copy_assignable_no_precondition_check<_Rest>...>,
        int> = 0>
    _CONSTEXPR20 tuple& operator=( _Identity_t<const _Myself&> _Right ) noexcept(
        conjunction_v<is_nothrow_copy_assignable<_This2>, is_nothrow_copy_assignable<_Rest>...> ) /* strengthened */ {
        _Myfirst._Val = _Right._Myfirst._Val;
        _Get_rest() = _Right._Get_rest();
        return *this;
    }

    template <class _Myself = tuple, class _This2 = _This,
        enable_if_t<conjunction_v<_STD _Is_move_assignable_no_precondition_check<_This2>,
        _STD _Is_move_assignable_no_precondition_check<_Rest>...>,
        int> = 0>
    _CONSTEXPR20 tuple& operator=( _Identity_t<_Myself&&> _Right ) noexcept(
        conjunction_v<is_nothrow_move_assignable<_This2>, is_nothrow_move_assignable<_Rest>...> ) {
        _Myfirst._Val = _STD forward<_This>( _Right._Myfirst._Val );
        _Get_rest() = _STD forward<_Mybase>( _Right._Get_rest() );
        return *this;
    }

    template <class... _Other, enable_if_t<conjunction_v<_STD negation<_STD is_same<tuple, _STD tuple<_Other...>>>,
        _STD _Tuple_assignable_val<tuple, const _Other&...>>,
        int> = 0>
    _CONSTEXPR20 tuple& operator=( const tuple<_Other...>& _Right ) noexcept(
        _Tuple_nothrow_assignable_v<tuple, const _Other&...> ) /* strengthened */ {
        _Myfirst._Val = _Right._Myfirst._Val;
        _Get_rest() = _Right._Get_rest();
        return *this;
    }

    template <class... _Other, enable_if_t<conjunction_v<_STD negation<_STD is_same<tuple, _STD tuple<_Other...>>>,
        _STD _Tuple_assignable_val<tuple, _Other...>>,
        int> = 0>
    _CONSTEXPR20 tuple& operator=( tuple<_Other...>&& _Right ) noexcept(
        _Tuple_nothrow_assignable_v<tuple, _Other...> ) /* strengthened */ {
        _Myfirst._Val = _STD forward<typename tuple<_Other...>::_This_type>( _Right._Myfirst._Val );
        _Get_rest() = _STD forward<typename tuple<_Other...>::_Mybase>( _Right._Get_rest() );
        return *this;
    }

    template <class _First, class _Second,
        enable_if_t<_Tuple_assignable_v<tuple, const _First&, const _Second&>, int> = 0>
    _CONSTEXPR20 tuple& operator=( const pair<_First, _Second>& _Right ) noexcept(
        _Tuple_nothrow_assignable_v<tuple, const _First&, const _Second&> ) /* strengthened */ {
        _Myfirst._Val = _Right.first;
        _Get_rest()._Myfirst._Val = _Right.second;
        return *this;
    }

    template <class _First, class _Second, enable_if_t<_Tuple_assignable_v<tuple, _First, _Second>, int> = 0>
    _CONSTEXPR20 tuple& operator=( pair<_First, _Second>&& _Right ) noexcept(
        _Tuple_nothrow_assignable_v<tuple, _First, _Second> ) /* strengthened */ {
        _Myfirst._Val = _STD forward<_First>( _Right.first );
        _Get_rest()._Myfirst._Val = _STD forward<_Second>( _Right.second );
        return *this;
    }

    _CONSTEXPR20 void swap( tuple& _Right ) noexcept(
        conjunction_v<_Is_nothrow_swappable<_This>, _Is_nothrow_swappable<_Rest>...> ) {
        _Swap_adl( _Myfirst._Val, _Right._Myfirst._Val );
        _Mybase::swap( _Right._Get_rest() );
    }

    constexpr _Mybase& _Get_rest() noexcept { // get reference to rest of elements
        return *this;
    }

    constexpr const _Mybase& _Get_rest() const noexcept { // get const reference to rest of elements
        return *this;
    }

    template <class... _Other>
    constexpr bool _Equals( const tuple<_Other...>& _Right ) const {
        return _Myfirst._Val == _Right._Myfirst._Val && _Mybase::_Equals( _Right._Get_rest() );
    }

#ifdef __cpp_lib_concepts
    template <class _First, class... _Other>
    _NODISCARD constexpr common_comparison_category_t<_Synth_three_way_result<_This, _First>,
        _Synth_three_way_result<_Rest, _Other>...>
        _Three_way_compare( const tuple<_First, _Other...>& _Right ) const {
        if ( auto _Result = _Synth_three_way {}( _Myfirst._Val, _Right._Myfirst._Val ); _Result != 0 ) {
            return _Result;
        }
        return _Mybase::_Three_way_compare( _Right._Get_rest() );
    }
#else // ^^^ defined(__cpp_lib_concepts) / !defined(__cpp_lib_concepts) vvv
    template <class... _Other>
    _NODISCARD constexpr bool _Less( const tuple<_Other...>& _Right ) const {
        return _Myfirst._Val < _Right._Myfirst._Val
            || ( !( _Right._Myfirst._Val < _Myfirst._Val ) && _Mybase::_Less( _Right._Get_rest() ) );
    }
#endif // ^^^ !defined(__cpp_lib_concepts) ^^^

    template <size_t _Index, class... _Types>
    friend constexpr tuple_element_t<_Index, tuple<_Types...>>& get( tuple<_Types...>& _Tuple ) noexcept;

    template <size_t _Index, class... _Types>
    friend constexpr const tuple_element_t<_Index, tuple<_Types...>>& get( const tuple<_Types...>& _Tuple ) noexcept;

    template <size_t _Index, class... _Types>
    friend constexpr tuple_element_t<_Index, tuple<_Types...>>&& get( tuple<_Types...>&& _Tuple ) noexcept;

    template <size_t _Index, class... _Types>
    friend constexpr const tuple_element_t<_Index, tuple<_Types...>>&& get( const tuple<_Types...>&& _Tuple ) noexcept;

    template <size_t _Index, class... _Types>
    friend constexpr auto&& _Tuple_get( tuple<_Types...>&& _Tuple ) noexcept;

    template <class _Ty, class... _Types>
    friend constexpr _Ty& get( tuple<_Types...>& _Tuple ) noexcept;

    template <class _Ty, class... _Types>
    friend constexpr const _Ty& get( const tuple<_Types...>& _Tuple ) noexcept;

    template <class _Ty, class... _Types>
    friend constexpr _Ty&& get( tuple<_Types...>&& _Tuple ) noexcept;

    template <class _Ty, class... _Types>
    friend constexpr const _Ty&& get( const tuple<_Types...>&& _Tuple ) noexcept;

    _Tuple_val<_This> _Myfirst; // the stored element
};

#if _HAS_CXX17
template <class... _Types>
tuple( _Types... )->tuple<_Types...>;

template <class _Ty1, class _Ty2>
tuple( pair<_Ty1, _Ty2> )->tuple<_Ty1, _Ty2>;

template <class _Alloc, class... _Types>
tuple( allocator_arg_t, _Alloc, _Types... )->tuple<_Types...>;

template <class _Alloc, class _Ty1, class _Ty2>
tuple( allocator_arg_t, _Alloc, pair<_Ty1, _Ty2> )->tuple<_Ty1, _Ty2>;

template <class _Alloc, class... _Types>
tuple( allocator_arg_t, _Alloc, tuple<_Types...> )->tuple<_Types...>;
#endif // _HAS_CXX17

template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator==( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    static_assert( sizeof...( _Types1 ) == sizeof...( _Types2 ), "cannot compare tuples of different sizes" );
    return _Left._Equals( _Right );
}

#ifdef __cpp_lib_concepts
template <class... _Types1, class... _Types2>
_NODISCARD constexpr common_comparison_category_t<_Synth_three_way_result<_Types1, _Types2>...> operator<=>(
    const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    static_assert( sizeof...( _Types1 ) == sizeof...( _Types2 ), "cannot compare tuples of different sizes" );
    return _Left._Three_way_compare( _Right );
}
#else // ^^^ defined(__cpp_lib_concepts) / !defined(__cpp_lib_concepts) vvv
#if !_HAS_CXX20
template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator!=( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    return !( _Left == _Right );
}
#endif // !_HAS_CXX20

template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator<( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    static_assert( sizeof...( _Types1 ) == sizeof...( _Types2 ), "cannot compare tuples of different sizes" );
    return _Left._Less( _Right );
}

template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator>=( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    return !( _Left < _Right );
}

template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator>( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    return _Right < _Left;
}

template <class... _Types1, class... _Types2>
_NODISCARD constexpr bool operator<=( const tuple<_Types1...>& _Left, const tuple<_Types2...>& _Right ) {
    return !( _Right < _Left );
}
#endif // ^^^ !defined(__cpp_lib_concepts) ^^^

template <class... _Types, enable_if_t<conjunction_v<_STD _Is_swappable<_Types>...>, int> = 0>
_CONSTEXPR20 void swap( tuple<_Types...>& _Left, tuple<_Types...>& _Right ) noexcept( noexcept( _Left.swap( _Right ) ) ) {
    return _Left.swap( _Right );
}

template <class _Ty, class _Tuple>
struct _Tuple_element { }; // backstop _Tuple_element definition

template <class _This, class... _Rest>
struct _Tuple_element<_This, tuple<_This, _Rest...>> { // select first element
    static_assert( !_Is_any_of_v<_This, _Rest...>, "duplicate type T in get<T>(tuple)" );
    using _Ttype = tuple<_This, _Rest...>;
};

template <class _Ty, class _This, class... _Rest>
struct _Tuple_element<_Ty, tuple<_This, _Rest...>> { // recursive _Tuple_element definition
    using _Ttype = typename _Tuple_element<_Ty, tuple<_Rest...>>::_Ttype;
};

template <size_t _Index, class... _Types>
_NODISCARD constexpr tuple_element_t<_Index, tuple<_Types...>>& get( tuple<_Types...>& _Tuple ) noexcept {
    using _Ttype = typename tuple_element<_Index, tuple<_Types...>>::_Ttype;
    return static_cast< _Ttype& >( _Tuple )._Myfirst._Val;
}

template <size_t _Index, class... _Types>
_NODISCARD constexpr const tuple_element_t<_Index, tuple<_Types...>>& get( const tuple<_Types...>& _Tuple ) noexcept {
    using _Ttype = typename tuple_element<_Index, tuple<_Types...>>::_Ttype;
    return static_cast< const _Ttype& >( _Tuple )._Myfirst._Val;
}

template <size_t _Index, class... _Types>
_NODISCARD constexpr tuple_element_t<_Index, tuple<_Types...>>&& get( tuple<_Types...>&& _Tuple ) noexcept {
    using _Ty = tuple_element_t<_Index, tuple<_Types...>>;
    using _Ttype = typename tuple_element<_Index, tuple<_Types...>>::_Ttype;
    return static_cast< _Ty&& >( static_cast< _Ttype& >( _Tuple )._Myfirst._Val );
}

template <size_t _Index, class... _Types>
_NODISCARD constexpr const tuple_element_t<_Index, tuple<_Types...>>&& get( const tuple<_Types...>&& _Tuple ) noexcept {
    using _Ty = tuple_element_t<_Index, tuple<_Types...>>;
    using _Ttype = typename tuple_element<_Index, tuple<_Types...>>::_Ttype;
    return static_cast< const _Ty&& >( static_cast< const _Ttype& >( _Tuple )._Myfirst._Val );
}

template <size_t _Index, class... _Types>
_NODISCARD constexpr auto&& _Tuple_get( tuple<_Types...>&& _Tuple ) noexcept {
    // used by pair's piecewise constructor
    using _Ty = tuple_element_t<_Index, tuple<_Types...>>;
    using _Ttype = typename tuple_element<_Index, tuple<_Types...>>::_Ttype;
    return static_cast< _Ty&& >( static_cast< _Ttype& >( _Tuple )._Myfirst._Val );
}

template <class _Ty, class... _Types>
_NODISCARD constexpr _Ty& get( tuple<_Types...>& _Tuple ) noexcept {
    using _Ttype = typename _Tuple_element<_Ty, tuple<_Types...>>::_Ttype;
    return static_cast< _Ttype& >( _Tuple )._Myfirst._Val;
}

template <class _Ty, class... _Types>
_NODISCARD constexpr const _Ty& get( const tuple<_Types...>& _Tuple ) noexcept {
    using _Ttype = typename _Tuple_element<_Ty, tuple<_Types...>>::_Ttype;
    return static_cast< const _Ttype& >( _Tuple )._Myfirst._Val;
}

template <class _Ty, class... _Types>
_NODISCARD constexpr _Ty&& get( tuple<_Types...>&& _Tuple ) noexcept {
    using _Ttype = typename _Tuple_element<_Ty, tuple<_Types...>>::_Ttype;
    return static_cast< _Ty&& >( static_cast< _Ttype& >( _Tuple )._Myfirst._Val );
}

template <class _Ty, class... _Types>
_NODISCARD constexpr const _Ty&& get( const tuple<_Types...>&& _Tuple ) noexcept {
    using _Ttype = typename _Tuple_element<_Ty, tuple<_Types...>>::_Ttype;
    return static_cast< const _Ty&& >( static_cast< const _Ttype& >( _Tuple )._Myfirst._Val );
}

template <class _This, class... _Rest>
template <class _Tag, class _Tpl, size_t... _Indices, enable_if_t<is_same_v<_Tag, _STD _Unpack_tuple_t>, int>>
constexpr tuple<_This, _Rest...>::tuple( _Tag, _Tpl&& _Right, index_sequence<_Indices...> )
    : tuple( _Exact_args_t {}, _STD get<_Indices>( _STD forward<_Tpl>( _Right ) )... ) {
}

template <class _This, class... _Rest>
template <class _Tag, class _Alloc, class _Tpl, size_t... _Indices,
    enable_if_t<is_same_v<_Tag, _STD _Alloc_unpack_tuple_t>, int>>
    constexpr tuple<_This, _Rest...>::tuple( _Tag, const _Alloc& _Al, _Tpl&& _Right, index_sequence<_Indices...> )
    : tuple( _Alloc_exact_args_t {}, _Al, _STD get<_Indices>( _STD forward<_Tpl>( _Right ) )... ) {
}

template <class... _Types>
_NODISCARD constexpr tuple<_Unrefwrap_t<_Types>...> make_tuple( _Types&&... _Args ) { // make tuple from elements
    using _Ttype = tuple<_Unrefwrap_t<_Types>...>;
    return _Ttype( _STD forward<_Types>( _Args )... );
}

template <class... _Types>
_NODISCARD constexpr tuple<_Types&...> tie( _Types&... _Args ) noexcept { // make tuple from elements
    using _Ttype = tuple<_Types&...>;
    return _Ttype( _Args... );
}

template <class... _Types>
_NODISCARD constexpr tuple<_Types&&...> forward_as_tuple( _Types&&... _Args ) noexcept { // forward arguments in a tuple
    return tuple<_Types&&...>( _STD forward<_Types>( _Args )... );
}

template <class _Seq_type1, class _Seq_type2>
struct _Cat_sequences;

template <size_t... _Indexes1, size_t... _Indexes2>
struct _Cat_sequences<index_sequence<_Indexes1...>,
    index_sequence<_Indexes2...>> { // concatenates two index_sequence types
    using type = index_sequence<_Indexes1..., _Indexes2...>;
};

template <class _Ty, size_t _Size>
class array;

template <size_t _Idx, class _Ty, size_t _Size>
_NODISCARD constexpr _Ty& get( array<_Ty, _Size>& _Arr ) noexcept;

template <size_t _Idx, class _Ty, size_t _Size>
_NODISCARD constexpr const _Ty& get( const array<_Ty, _Size>& _Arr ) noexcept;

template <size_t _Idx, class _Ty, size_t _Size>
_NODISCARD constexpr _Ty&& get( array<_Ty, _Size>&& _Arr ) noexcept;

template <size_t _Idx, class _Ty, size_t _Size>
_NODISCARD constexpr const _Ty&& get( const array<_Ty, _Size>&& _Arr ) noexcept;

template <class _Ty, class... _For_array>
struct _View_as_tuple { // tuple_cat() supports only tuples, pairs, and arrays
    static_assert( _Always_false<_Ty>, "Unsupported tuple_cat arguments." );
};

template <class... _Types>
struct _View_as_tuple<tuple<_Types...>> { // view a tuple as a tuple
    using type = tuple<_Types...>;
};

template <class _Ty1, class _Ty2>
struct _View_as_tuple<pair<_Ty1, _Ty2>> { // view a pair as a tuple
    using type = tuple<_Ty1, _Ty2>;
};

template <class _Ty, class... _Types>
struct _View_as_tuple<array<_Ty, 0>, _Types...> { // view an array as a tuple; ends recursion at 0
    using type = tuple<_Types...>;
};

template <class _Ty, size_t _Size, class... _Types>
struct _View_as_tuple<array<_Ty, _Size>, _Types...>
    : _View_as_tuple<array<_Ty, _Size - 1>, _Ty, _Types...> { // view an array as a tuple; counts down to 0
};

template <size_t _Nx, class _Ty>
struct _Repeat_for : integral_constant<size_t, _Nx> { }; // repeats _Nx for each _Ty in a parameter pack

template <class _Ret, class _Kx_arg, class _Ix_arg, size_t _Ix_next, class... _Tuples>
struct _Tuple_cat2 { // determine tuple_cat's return type and _Kx/_Ix indices
    static_assert( sizeof...( _Tuples ) == 0, "Unsupported tuple_cat arguments." );
    using type = _Ret;
    using _Kx_arg_seq = _Kx_arg;
    using _Ix_arg_seq = _Ix_arg;
};

template <class... _Types1, class _Kx_arg, size_t... _Ix, size_t _Ix_next, class... _Types2, class... _Rest>
struct _Tuple_cat2<tuple<_Types1...>, _Kx_arg, index_sequence<_Ix...>, _Ix_next, tuple<_Types2...>, _Rest...>
    : _Tuple_cat2<tuple<_Types1..., _Types2...>, typename _Cat_sequences<_Kx_arg, index_sequence_for<_Types2...>>::type,
    index_sequence<_Ix..., _Repeat_for<_Ix_next, _Types2>::value...>, _Ix_next + 1,
    _Rest...> { // determine tuple_cat's return type and _Kx/_Ix indices
};

template <class... _Tuples>
struct _Tuple_cat1 : _Tuple_cat2<tuple<>, index_sequence<>, index_sequence<>, 0,
    typename _View_as_tuple<decay_t<_Tuples>>::type...> { // prepare to determine tuple_cat's
                                                          // return type and _Kx/_Ix indices
};

template <class _Ret, size_t... _Kx, size_t... _Ix, class _Ty>
constexpr _Ret _Tuple_cat( index_sequence<_Kx...>, index_sequence<_Ix...>, _Ty&& _Arg ) { // concatenate tuples
    return _Ret( _STD get<_Kx>( _STD get<_Ix>( _STD forward<_Ty>( _Arg ) ) )... );
}

template <class... _Tuples>
_NODISCARD constexpr typename _Tuple_cat1<_Tuples...>::type tuple_cat( _Tuples&&... _Tpls ) { // concatenate tuples
    using _Cat1 = _Tuple_cat1<_Tuples...>;
    return _Tuple_cat<typename _Cat1::type>( typename _Cat1::_Kx_arg_seq {}, typename _Cat1::_Ix_arg_seq {},
        _STD forward_as_tuple( _STD forward<_Tuples>( _Tpls )... ) );
}

#if _HAS_CXX17
template <class _Callable, class _Tuple, size_t... _Indices>
constexpr decltype( auto ) _Apply_impl(
    _Callable&& _Obj, _Tuple&& _Tpl, index_sequence<_Indices...> ) { // invoke _Obj with the elements of _Tpl
    return _STD invoke( _STD forward<_Callable>( _Obj ), _STD get<_Indices>( _STD forward<_Tuple>( _Tpl ) )... );
}

template <class _Callable, class _Tuple>
constexpr decltype( auto ) apply( _Callable&& _Obj, _Tuple&& _Tpl ) { // invoke _Obj with the elements of _Tpl
    return _Apply_impl( _STD forward<_Callable>( _Obj ), _STD forward<_Tuple>( _Tpl ),
        make_index_sequence<tuple_size_v<remove_reference_t<_Tuple>>>{} );
}

template <class _Ty, class _Tuple, size_t... _Indices>
constexpr _Ty _Make_from_tuple_impl( _Tuple&& _Tpl, index_sequence<_Indices...> ) {
    // construct _Ty from the elements of _Tpl
    static_assert( is_constructible_v<_Ty, decltype( _STD get<_Indices>( _STD forward<_Tuple>( _Tpl ) ) )...>,
        "the target type must be constructible from the fields of the argument tuple (N4892 [tuple.apply]/2)." );
    return _Ty( _STD get<_Indices>( _STD forward<_Tuple>( _Tpl ) )... );
}

template <class _Ty, class _Tuple>
_NODISCARD constexpr _Ty make_from_tuple( _Tuple&& _Tpl ) { // construct _Ty from the elements of _Tpl
    return _Make_from_tuple_impl<_Ty>(
        _STD forward<_Tuple>( _Tpl ), make_index_sequence<tuple_size_v<remove_reference_t<_Tuple>>>{} );
}
#endif // _HAS_CXX17

template <class... _Types, class _Alloc>
struct uses_allocator<tuple<_Types...>, _Alloc> : true_type { }; // true_type if container allocator enabled

#if _HAS_TR1_NAMESPACE
namespace _DEPRECATE_TR1_NAMESPACE tr1 {
    using _STD get;
    using _STD ignore;
    using _STD make_tuple;
    using _STD ref;
    using _STD tie;
    using _STD tuple;
} // namespace tr1
#endif // _HAS_TR1_NAMESPACE

_STD_END

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _TUPLE_

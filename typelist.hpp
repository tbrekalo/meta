#ifndef META_TYPELIST_HPP_
#define META_TYPELIST_HPP_

#include <type_traits>

namespace tl::meta {

template <class... Ts>
struct Typelist {};

struct Nil {};

template <class T>
struct Head;

template <class T, class... Ts>
struct Head<Typelist<T, Ts...>> {
  using Type = T;
};

template <>
struct Head<Typelist<>> {
  using Type = Nil;
};

template <class T>
using HeadT = typename Head<T>::Type;

template <class T>
struct Tail;

template <class T, class... Ts>
struct Tail<Typelist<T, Ts...>> {
  using Type = Typelist<Ts...>;
};

template <>
struct Tail<Typelist<>> {
  using Type = Nil;
};

template <class T>
using TailT = typename Tail<T>::Type;

template <class... TypeLists>
struct Join;

template <class... Ts>
struct Join<Typelist<Ts...>> {
  using Type = Typelist<Ts...>;
};

template <class... Lhs, class... Rhs>
struct Join<Typelist<Lhs...>, Typelist<Rhs...>> {
  using Type = Typelist<Lhs..., Rhs...>;
};

template <class... Lhs, class... Rhs, class... Lists>
struct Join<Typelist<Lhs...>, Typelist<Rhs...>, Lists...> {
  using Type = typename Join<Typelist<Lhs..., Rhs...>, Lists...>::Type;
};

template <class... Ts>
using JoinT = typename Join<Ts...>::Type;

template <class... Ts>
struct Flatten;

template <class T>
struct Flatten<T> {
  using Type = Typelist<T>;
};

template <class... Ts>
struct Flatten<Typelist<Ts...>> {
  using Type = typename Join<typename Flatten<Ts>::Type...>::Type;
};

template <template <class Arg> class Fn, class T>
struct Map;

template <template <class Arg> class Fn, class... Ts>
struct Map<Fn, Typelist<Ts...>> {
  using Type = Typelist<typename Fn<Ts>::Type...>;
};

using TL1 = Typelist<char>;
using TL2 = Typelist<int, short>;
using TL3 = Typelist<void>;
using TL4 = Typelist<char, int, short, void>;

using TL123 = Typelist<Typelist<TL1, TL2>, TL3>;
static_assert(std::is_same_v<Flatten<TL123>::Type, TL4>);

// TODO: composition, filter, fold, cartesian product?

}  // namespace tl::meta

#endif /* META_TYPELIST_HPP_ */

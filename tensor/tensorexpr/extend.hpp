#ifndef __TENSOREXPR_LR_HPP__
#define __TENSOREXPR_LR_HPP__

#include <tensor.h>

namespace tensor {

enum Side : bool {
  Right,
  Left,
};

template <intmax_t I, Side S, typename E, template <typename...> class N, typename... P>
class ExtendExpression;

#define L I
template <intmax_t I, Side S, typename E, template <typename...> class N, typename... P>
auto extl(TensorExpression<E,N,P...> const& t) -> ExtendExpression<L,S,E,N,P...> const {
  return ExtendExpression<L,S,E,N,P...>(t);
};
#undef L

#define R I
// TODO currently behaves like extl
// Idea: allow negative extends to indicate a right,
// act as a rotated until at -1,
// then switch to a left.
template <intmax_t I, Side S, typename E, template <typename...> class N, typename... P>
auto extr(TensorExpression<E,N,P...> const& t) -> ExtendExpression<R,S,E,N,P...> const {
  return ExtendExpression<R,S,E,N,P...>(t);
};
#undef R

template <intmax_t I, Side S, typename E, template <typename...> class N, typename... P>
class ExtendExpression : public TensorExpression<ExtendExpression<I,S,E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const & e;

  public:
    ExtendExpression(TensorExpression<E,N,P...> const& e) : e(e) {};

    inline size_type size() const { return e.size(); }
    inline size_type size(size_type i) const { return e.size(i); }
    inline size_type stride(size_type i) const { return e.stride(i); }
    static constexpr intmax_t order() { return E::order(); }

    template <typename... Etc>
    inline value_type at(size_type i, Etc... etc) const {
      return ExtendExpression<I-1,S,E,N,P...>(e).at(etc...);
    }
    template <typename... Etc>
    inline value_type operator()(size_type i, Etc... etc) const {
      return ExtendExpression<I-1,S,E,N,P...>(e).operator()(etc...);
    }
};

template <typename E, Side S, template <typename...> class N, typename... P>
class ExtendExpression<0,S,E,N,P...> : public TensorExpression<ExtendExpression<0,S,E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const & e;

  public:
    ExtendExpression(TensorExpression<E,N,P...> const& e) : e(e) {};

    inline size_type size() const { return e.size(); }
    inline size_type size(size_type i) const { return e.size(i); }
    inline size_type stride(size_type i) const { return e.stride(i); }
    static constexpr intmax_t order() { return E::order(); }

    template <typename... I>
    inline value_type at(I... i) const {
      return e.at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return e.operator()(i...);
    }
};

}//namespace tensor

#endif//__TENSOREXPR_LR_HPP__

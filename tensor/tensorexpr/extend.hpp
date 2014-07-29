#ifndef __TENSOREXPR_LR_HPP__
#define __TENSOREXPR_LR_HPP__

#include <tensor.h>

namespace tensor {

enum Side : bool {
  R,
  L,
};

template <intmax_t I, Side S, typename E, template <typename...> class N, typename... P>
class ExtendExpression;

template <typename E, template <typename...> class N, typename... P>
auto lexpr(TensorExpression<E,N,P...> const& t) -> ExtendExpression<E::order(),E,N,P...> const {
  return ExtendExpression<E::order(),E,N,P...>(t);
};

// TODO currently behaves like extl
// act as a rotated until at 1,
// then switch to a left.
template <typename E, template <typename...> class N, typename... P>
auto rexpr(TensorExpression<E,N,P...> const& t) -> ExtendExpression<0,E,N,P...> const {
  return ExtendExpression<0,E,N,P...>(t);
};

#define SIDE S == Side::R && I-1 ? Side::R : Side::L
#define NEXT S == Side::R && I == 1 ? I-1 : sizeof...(Etc)-E::order()
//#define RETL(op) ExtendExpression<NEXT,SIDE,E,N,P...>(e).op(etc...,i)
//#define RETR(op) ExtendExpression<NEXT,SIDE,E,N,P...>(e).op(etc...)
//#define ARGS S == Side::R ? etc...,i : etc...
template <intmax_t I, typename E, template <typename...> class N, typename... P>
class ExtendExpression : public TensorExpression<ExtendExpression<I,S,E,N,P...>,N,P...> {
  /**
   * ExtendExpression
   * Acts in all respects line a normal TensorExpression, but adds dimenions to
   * the left or to the right.

TODO : Need to handle I = 1 case.
TODO : Can do left / right w/o I specification for extr and extl.
       Just specify I using base expression's order.
  **/
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
      return S == Side::R ? ExtendExpression<NEXT,SIDE,E,N,P...>(e).at(etc...,i)
                              : ExtendExpression<NEXT,SIDE,E,N,P...>(e).at(etc...);
    }
    template <typename... Etc>
    inline value_type operator()(size_type i, Etc... etc) const {
      return S == Side::R ? ExtendExpression<NEXT,SIDE,E,N,P...>(e).operator()(etc...,i)
                              : ExtendExpression<NEXT,SIDE,E,N,P...>(e).operator()(etc...);
    }
};
#undef ARGS
#undef NEXT
#undef SIDE

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

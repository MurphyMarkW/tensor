#ifndef __TENSOREXPR_ROTATE_HPP__
#define __TENSOREXPR_ROTATE_HPP__

#include <tensor.h>

namespace tensor {

template <intmax_t R, typename E, template <typename...> class N, typename... P>
class RotExpr : public TensorExpression<RotExpr<R,E,N,P...>,N,P...>,
                public RotExpr<R-1,E,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

  public:
    using RotExpr<R-1,E,N,P...>::RotExpr;

    inline size_type size() const { return static_cast<RotExpr<R-1,E,N,P...> const&>(*this).size(); }
    inline size_type size(size_type i) const { return static_cast<RotExpr<R-1,E,N,P...> const&>(*this).size(i); }
    inline size_type stride(size_type i) const { return static_cast<RotExpr<R-1,E,N,P...> const&>(*this).stride(i); }
    static constexpr intmax_t order() { return E::order(); }

    template <typename... I>
    inline value_type at(size_type r, I... i) const {
      return static_cast<RotExpr<R-1,E,N,P...> const&>(*this).at(i...,r);
    }
    template <typename... I>
    inline value_type operator()(size_type r, I... i) const {
      return static_cast<RotExpr<R-1,E,N,P...> const&>(*this).operator()(i...,r);
    }
};

template <typename E, template <typename...> class N, typename... P>
class RotExpr<0,E,N,P...> : public TensorExpression<RotExpr<0,E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const& e;

  public:
    RotExpr(TensorExpression<E,N,P...> const& e) : e(e) {};

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

#define L I % E::order()
template <intmax_t I, typename E, template <typename...> class N, typename... P>
RotExpr<L,E,N,P...> const rotl(TensorExpression<E,N,P...> const& t) {
  return RotExpr<L,E,N,P...>(t);
};
#undef L

#define R I % E::order() ? E::order() - (I % E::order()) : 0
template <intmax_t I, typename E, template <typename...> class N, typename... P>
RotExpr<R,E,N,P...> const rotr(TensorExpression<E,N,P...> const& t) {
  return RotExpr<R,E,N,P...>(t);
};
#undef R

}//namespace tensor

#endif//__TENSOREXPR_ROTATE_HPP__

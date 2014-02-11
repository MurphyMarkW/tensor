#ifndef __TENSOREXPR_LR_HPP__
#define __TENSOREXPR_LR_HPP__

#include <tensor.h>

namespace tensor {

template <typename E, template <typename...> class N, typename... P>
class RExpr : public TensorExpression<RExpr<E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const& e;

  public:
    RExpr(TensorExpression<E,N,P...> const& e) : e(e) {};

    inline size_type size() const { return e.size(); }
    inline size_type size(size_type i) const { return e.size(i); }
    inline size_type stride(size_type i) const { return e.stride(i); }
    static constexpr intmax_t order() { return E::order(); }

    template <typename... I>
    inline value_type at(size_type l, I... i) const {
      return (sizeof...(I)+1 > E::order()) ? at(i...) : e.at(l,i...);
    }
    template <typename... I>
    inline value_type operator()(size_type l, I... i) const {
      return (sizeof...(I)+1 > E::order()) ? operator()(i...) : e.operator()(l,i...);
    }
    inline value_type operator()(size_type i) const {
      return e.operator()(i);
    }
};

template <typename E, template <typename...> class N, typename... P>
RExpr<E,N,P...> const rex(TensorExpression<E,N,P...> const& t) {
  return RExpr<E,N,P...>(t);
};

}//namespace tensor

#endif//__TENSOREXPR_LR_HPP__

#ifndef __TENSOREXPR_LR_HPP__
#define __TENSOREXPR_LR_HPP__

#include <tensor.h>

namespace tensor {

template <intmax_t I, typename E, template <typename...> class N, typename... P>
ExtendExpression;

#define L I
template <intmax_t I, typename E, template <typename...> class N, typename... P>
ExtendExpression<L,E,N,P...> const extl(TensorExpression<E,N,P...> const& t) {
  return ExtendExpression<L>(t);
};
#undef L

#define R I 
template <intmax_t I, typename E, template <typename...> class N, typename... P>
ExtendExpression<

template <intmax_t I, typename E, template <typename...> class N, typename... P>
class ExtendExpression : public TensorExpression<ExtendExpression<E,N,P...>,N,P...> {
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
      return ExtendExpression<R-1>(e).at(etc...);
    }
    template <typename... Etc>
    inline value_type operator()(size_type i, Etc... etc) const {
      return ExtendExpression<R-1>(e).operator()(etc...);
    }
};

template <typename E, template <typename...> class N, typename... P>
class LExpr : public TensorExpression<LExpr<E,N,P...>,N,P...>,
              public RotExpr<E::order(),RExpr<E,N,P...>,N,P...>,
              public RExpr<E,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const & e;

  public:
    RExpr(TensorExpression<E,N,P...> const& e) : e(e) {};

    inline size_type size() const { return e.size(); }
    inline size_type size(size_type i) const { return e.size(i); }
    inline size_type stride(size_type i) const { return e.stride(i); }
    static constexpr intmax_t order() { return E::order(); }

    template <typename... Etc>
    inline value_type at(size_type i, Etc... etc) const {
      return at(etc...);
    }
    template <typename... I>
    typename enable_if<(sizeof...(I) == E::order()),value_type>::type
    inline at(I... i) const {
      return e.at(i...);
    }
    inline value_type at(size_type i) const {
      return e.at(i);
    }

    template <typename... Etc>
    inline value_type operator()(size_type i, Etc... etc) const {
      return operator()(etc...);
    }
    template <typename... I>
    typename enable_if<(sizeof...(I) == E::order()),value_type>::type
    inline operator()(I... i) const {
      return e.operator()(i...);
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

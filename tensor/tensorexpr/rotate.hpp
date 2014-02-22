#ifndef __TENSOREXPR_ROTATE_HPP__
#define __TENSOREXPR_ROTATE_HPP__

#include <tensor.h>

namespace tensor {

template <intmax_t I, typename E, template <typename...> class N, typename... P>
class RotateExpression;

#define L I % E::order()
template <intmax_t I, typename E, template <typename...> class N, typename... P>
auto rotl(TensorExpression<E,N,P...> const& t) -> RotateExpression<L,E,N,P...> const {
  return RotateExpression<L,E,N,P...>(t);
};
#undef L

#define R E::order() - (I % E::order())
template <intmax_t I, typename E, template <typename...> class N, typename... P>
auto rotr(TensorExpression<E,N,P...> const& t) -> RotateExpression<R,E,N,P...> const {
  return RotateExpression<R,E,N,P...>(t);
};
#undef R

template <intmax_t I, typename E, template <typename...> class N, typename... P>
class RotateExpression : public TensorExpression<RotateExpression<I,E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const& e;

  public:
    RotateExpression(TensorExpression<E,N,P...> const& e) : e(e) {};

    inline size_type size() const { return e.size(); }
    inline size_type size(size_type i) const {
      return RotateExpression<I-1,E,N,P...>(e).size(i ? i-1 : E::order()-1);
    }
    inline size_type stride(size_type i) const {
      return RotateExpression<I-1,E,N,P...>(e).stride(i ? i-1 : E::order()-1);
    }
    inline constexpr intmax_t order() { return E::order(); }

    template <typename... Etc>
    inline value_type at(size_type i, Etc... etc) const {
      return RotateExpression<I-1,E,N,P...>(e).at(etc...,i);
    }
    template <typename... Etc>
    inline value_type operator()(size_type i, Etc... etc) const {
      return RotateExpression<I-1,E,N,P...>(e).operator()(etc...,i);
    }
};

template <typename E, template <typename...> class N, typename... P>
class RotateExpression<0,E,N,P...> : public TensorExpression<RotateExpression<0,E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    TensorExpression<E,N,P...> const& e;

  public:
    RotateExpression(TensorExpression<E,N,P...> const& e) : e(e) {};

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

#endif//__TENSOREXPR_ROTATE_HPP__

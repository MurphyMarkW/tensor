#ifndef __TENSOREXPR_STRIP_HPP__
#define __TENSOREXPR_STRIP_HPP__

#include <tensor.h>

namespace tensor {

template <typename E, template <typename...> class N, typename... P>
class LExpression {
  // TODO
};

template <typename E, template <typename...> class N, typename... P>
class RExpression : public TensorExpression<RExpression<E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

  public:
    // TODO add other tensor expression methods

    template <typename... I>
    inline value_type at(size_type l, I... i) const {
      return (sizeof...(I)+1 > E::order()) ? at(i...) : static_cast<E const&>(*this).at(i...);
    }
    template <typename... I>
    inline value_type operator()(size_type l, I... i) const {
      return (sizeof...(I)+1 > E::order()) ? operator()(i...) : static_cast<E const&>(*this).operator()(i...);
    }
};

template <typename E, template <typename...> class N, typename... P>
class Right : public TensorExpression<RExpression<Right<E,N,P...>,N,P...>,N,P...>,
              public RExpression<Right<E,N,P...>,N,P...> {
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

    E const& e;

  public:
    Right(TensorExpression<E,N,P...> const& e) : e(e) {};

    // TODO add other tensor expression methods

    template <typename... I>
    inline value_type at(I... i) const {
      return e.at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return e.operator()(i...);
    }
};

template <typename E, template <typename...> class N, typename... P>
Right<E,N,P...> const rex(TensorExpression<E,N,P...> const& t) {
  return Right<E,N,P...>(t);
};

}//namespace tensor

#endif//__TENSOREXPR_STRIP_HPP__

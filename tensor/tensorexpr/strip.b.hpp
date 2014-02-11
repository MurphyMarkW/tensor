#ifndef __TENSOREXPR_STRIP_HPP__
#define __TENSOREXPR_STRIP_HPP__

#include <tensor.h>
#include "rotate.hpp"

namespace tensor {

// Yes, I know people dislike this...
// Deal with it. Tired of the stds...
using std::enable_if;
using std::is_base_of;

template <typename E, typename T, intmax_t O, intmax_t S>
class Strip : public Strip<E,T,O,S-1>,
              public Rotate<Strip<E,T,O,S-1>,T,O,(S>0)?1:0> {
  // TODO
};

template <typename E, typename T, intmax_t O>
class Strip<E,T,O,0> {
  // TODO
};

template <typename E, typename T, intmax_t O, intmax_t S>
class StripExpression : public TensorExpression<StripExpression<E,T,O,S>,T,O>,
                        public Rotate<Strip<E,T,O,S-1>,T,O,(S>0)?1:0>,
                        public Strip<E,T,O,S-1> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    StripExpression(TensorExpression<E,T,O> const& t) :
      Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S>::Rotate(t),
      Strip<E,T,O,S-1>::Strip(t) {};
    //using Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S>::Rotate;

    template <typename I, typename... Etc>
    inline value_type at(I i, Etc... etc) const {
      return static_cast<Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S> const&>(*this).at(etc...,i);
    }
    template <typename I, typename... Etc>
    inline value_type operator()(I i, Etc... etc) const {
      return static_cast<Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S> const&>(*this)(etc...,i);
    }
};//StripExpression

template <typename E, typename T, intmax_t O, intmax_t S>
class Strip : public Strip<E,T,O,S-1> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    using Strip<E,T,O,S-1>::Strip;

    template <typename... I>
    inline value_type at(I... i) const {
      return static_cast<Strip<E,T,O,S-1> const&>(*this).at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return static_cast<Strip<E,T,O,S-1> const&>(*this)(i...);
    }
};//Strip

template <typename E, typename T, intmax_t O>
class Strip<E,T,O,0> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

    E const& t;

  public:
    Strip(TensorExpression<E,T,O> const& t) : t(t) {};

    template <typename... I>
    inline value_type at(I... i) const {
      return t.at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return t(i...);
    }
};//Strip

template <typename E, typename T, intmax_t O, intmax_t S>
class StripExpression : public TensorExpression<StripExpression<E,T,O,S>,T,O>,
                        public Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    using Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S>::Rotate;

    template <typename I, typename... Etc>
    inline value_type at(I i, Etc... etc) const {
      return static_cast<Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S> const&>(*this).at(etc...,i);
    }
    template <typename I, typename... Etc>
    inline value_type operator()(I i, Etc... etc) const {
      return static_cast<Rotate<Strip<E,T,O,(S>0)?S:0>,T,O,S> const&>(*this)(etc...,i);
    }
};//StripExpression

template <intmax_t S, typename E, typename T, intmax_t O>
inline StripExpression<E,T,O,S> const strip(TensorExpression<E,T,O> const& t) {
  return StripExpression<E,T,O,S>(t);
};//StripExpression

}//namespace tensor

#endif//__TENSOREXPR_STRIP_HPP__

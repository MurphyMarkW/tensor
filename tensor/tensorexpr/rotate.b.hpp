#ifndef __TENSOREXPR_ROTATE_HPP__
#define __TENSOREXPR_ROTATE_HPP__

#include <tensor.h>

namespace tensor {

// Yes, I know people dislike this...
// Deal with it. Tired of the stds...
using std::enable_if;
using std::is_base_of;

template <typename E, typename T, intmax_t O, intmax_t R>
class RotateExpression : public RotateExpression<E,T,O,(R%O)?R%O+1:0> {
  // TODO
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    // TODO other expression stuff?

    // Type casting for nested expressions.
    operator E & () { return static_cast<E &>(*this); }
    operator E const& () const { return static_cast<E const&>(*this); }

    template <typename I, typename... Etc>
    inline value_type at(I i, Etc... etc) const {
      return static_cast<RotateExpression<E,T,O,(R%O)?R%O+1:0> const&>(*this).at(etc...,i);
    }
    template <typename I, typename... Etc>
    inline value_type operator()(I i, Etc... etc) const {
      return static_cast<RotateExpression<E,T,O,(R%O)?R%O+1:0> const&>(*this)(etc...,i);
    }
};

template <typename E, typename T, intmax_t O>
class RotateExpression<E,T,O,O> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    // TODO other expression stuff?

    // Type casting for nested expressions.
    operator E & () { return static_cast<E &>(*this); }
    operator E const& () const { return static_cast<E const&>(*this); }

    template <typename... I>
    inline value_type at(I... i) const {
      return static_cast<E const&>(*this).at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return static_cast<E const&>(*this)(i...);
    }
};

template <typename E, typename T, intmax_t O>
class RotateExpression<E,T,O,0> {
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

  public:
    // TODO other expression stuff?

    // Type casting for nested expressions.
    operator E & () { return static_cast<E &>(*this); }
    operator E const& () const { return static_cast<E const&>(*this); }

    template <typename... I>
    inline value_type at(I... i) const {
      return static_cast<E const&>(*this).at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return static_cast<E const&>(*this)(i...);
    }
};

template <typename E, typename T, intmax_t O, intmax_t R>
class Rotate : public TensorExpression<RotateExpression<Rotate<E,T,O,R>,T,O,R>,T,O>,
               public RotateExpression<Rotate<E,T,O,R>,T,O,R> {
  // TODO Rotate is now the full class, RotateExpression an expression template.
  public:
    typedef typename E::size_type   size_type;
    typedef typename E::value_type  value_type;

    E const& t;

  public:
    Rotate(TensorExpression<E,T,O> const& t) : t(t) {};

    template <typename... I>
    inline value_type at(I... i) const {
      return t.at(i...);
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      return t(i...);
    }
};


template <intmax_t R, typename E, typename T, intmax_t O>
inline Rotate<E,T,O,R> const rotate(TensorExpression<E,T,O> const& t) {
  return Rotate<E,T,O,R>(t);
};//RotateExpression

}//namespace tensor

#endif//__TENSOREXPR_ROTATE_HPP__

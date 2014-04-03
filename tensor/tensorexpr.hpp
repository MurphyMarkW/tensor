#ifndef __TENSOREXPR_HPP__
#define __TENSOREXPR_HPP__

#include <tensor.h>

namespace tensor {

template <typename E, template <typename...> class N, typename... P>
class TensorExpression : public TensorBase {
  /**
   * Tensor expressions provide order-dependent size and accessor functionality.
   * Orderperations involving Tensor expressions result in new Tensor expressions.
   * This allows for compile time optimization of compound operations, and thus
   * massive speed up by removing the need for creation of intermediate data.
  **/

  // Typedefs.
  public:
    typedef typename N<P...>::size_type       size_type;
    typedef typename N<P...>::reference       reference;
    typedef typename N<P...>::value_type      value_type;
    typedef typename N<P...>::const_reference const_reference;

  public:
    inline size_type size() const { return static_cast<E const&>(*this).size(); }
    inline size_type size(size_type i) const { return static_cast<E const&>(*this).size(i); }
    inline size_type stride(size_type i) const { return static_cast<E const&>(*this).stride(i); }
    static constexpr intmax_t order() { return E::order(); }

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

};//TensorExpression

}//namespace tensor

#include "tensorexpr/arithmetic.hpp"
#include "tensorexpr/rotate.hpp"
#include "tensorexpr/extend.hpp"
//#include "tensorexpr/lr.hpp"

#endif//__TENSOREXPR_HPP__

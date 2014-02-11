#ifndef __TENSOREXPR_CONTRACT_HPP__
#define __TENSOREXPR_CONTRACT_HPP__

#include <tensor.h>

namespace tensor {

// Yes, I know people dislike this...
// Deal with it. Tired of the stds...
using std::enable_if;
using std::is_base_of;

template <typename E, typename T, std::size_t O>
class TensorContract : public TensorExpression<TensorContract<E,T,O>,T,O> {
  public:
    typedef typename TensorExpression<TensorContract<E,T,O>,T,O>::size_type size_type;
    typedef typename TensorExpression<TensorContract<E,T,O>,T,O>::value_type value_type;

    TensorExpression<E,T,O> const& t;
    size_type               const& a;
    size_type               const& b;

  public:
    TensorContract(TensorExpression<E,T,O> const& t,
                   size_type const& a, size_type const& b) : t(t),a(a),b(b) {
      // Check the incoming parameters.
      if(t.size(a) != t.size(b)) throw TensorException("size mismatch on contraction");
      // Calculate the contraction constants.
      // TODO
    };

    inline size_type dims() const { return O-2; }
    inline size_type size() const { return t.size()-t.size(a); }
    inline size_type size(size_type i) const { return t.size(i); }
    inline size_type stride(size_type i) const { return t.stride(i); }

    template <typename... I>
    inline value_type at(I... i) const {
      // TODO Split indices and multiply values from each tensor.
      return 0; // TODO Return actual value.
    }
    template <typename... I>
    inline value_type operator()(I... i) const {
      // TODO Split indices and multiply values from each tensor.
      return 0; // TODO Return actual value.
    }
};

}//namespace tensor

#endif//__TENSOREXPR_CONTRACT_HPP__

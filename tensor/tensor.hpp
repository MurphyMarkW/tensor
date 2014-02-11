#ifndef __TENSOR_HPP__
#define __TENSOR_HPP__

#include <tensor.h>
#include <stdlib.h>
#include <vector>
#include <array>
//#include <algorithm>
//#include <type_traits>
#include <stdexcept>

namespace tensor {

template <typename T, intmax_t O>
class Tensor : public TensorMixin<O,std::vector,T> {
  /**
   *  Tensor - Full implementation of std::vector based tensor.
   *  Parameters:
   *    T - Element type
   *    O - Tensor order
  **/

  // Inherit constructors from TensorMixin
  public:
    using TensorMixin<O,std::vector,T>::TensorMixin;
};

}//namespace tensor

#endif//__TENSOR_HPP__

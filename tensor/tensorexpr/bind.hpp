#ifndef __TENSOREXPR_BIND_HPP__
#define __TENSOREXPR_BIND_HPP__

#include <tensor.h>
#include "rotate.hpp"
#include "strip.hpp"

#include <algorithm>

namespace tensor {

// Yes, I know people dislike this...
// Deal with it. Tired of the stds...
using std::enable_if;
using std::is_base_of;
using std::size_t;

template <typename E1, typename E2,
          typename T1, typename T2,
          size_t   O1, size_t   O2,
          size_t   RN, size_t   SN>
class BindExpression : public BindExpression<E1,E2,T1,T2,O1,O2,RN,SN> { // TODO Paras
  // TODO - Call left and right branch.
  //      - Left branch handles rotation and stripping for left expr.
  //      - Right branch handles stripping for right expr.
  //      - Specialization such that only init returns product.
};

template <typename E1, typename E2,
          typename T1, typename T2,
          size_t   O1, size_t   O2>
class BindExpression<0,0> : public BindExpression<E1,E2,T1,T2,O1,O2,0,0> { // TODO Paras
  // TODO - Base case for RN == SN == 0
};

template <typename E1, typename E2,
          typename T1, typename T2,
          size_t   O1, size_t   O2>
class BindExpression<0,O1> : public BindExpression<E1,E2,T1,T2,O1,O2,0,O1> { // TODO Paras
  // TODO - Base case for RN == 0, SN == O1
};

template <typename E1, typename E2,
          typename T1, typename T2,
          size_t   O1, size_t   O2>
class BindExpression<0,O2> : public BindExpression<E1,E2,T1,T2,O1,O2,0,O2> { // TODO Paras
  // TODO - Base case for RN == 0, SN == O2
};

template <typename E1, typename E2,
          typename T1, typename T2,
          size_t   O1, size_t   O2>
class BindExpression<O1,0> : public BindExpression<E1,E2,T1,T2,O1,O2,O1,0> { // TODO Paras
  // TODO - Base case for RN == O1, SN == 0
};

}//namespace tensor

#endif//__TENSOREXPR_BIND_HPP__

#ifndef __TENSOR_H__
#define __TENSOR_H__

#include <cstdlib>
#include <iostream>

namespace tensor {

// Library-wide definitions.
typedef typename std::intmax_t intmax_t;

using std::enable_if;
using std::is_base_of;
using std::is_convertible;

/**
 * TensorBase - Fully implemented, empty base class.
 *              Used to prevent certain types of aliasing.
**/
class TensorBase {};

/**
 * TensorException - Library specific exception.
**/
class TensorException : public std::exception {};

/**
 * Tensor - Full implementation of std::vector based tensor.
 * Parameters:
 *    T - Element type
 *    O - Tensor order
**/
template <typename T, intmax_t O>
class Tensor;

/**
 * TensorMixin - Mixin that exposes tensor syntax.
 * Parameters:
 *    O - Tensor order
 *    N - Namespace template from which to pull typedefs
 *    P - Namespace parameters to fully instantiate namespace
**/
template <intmax_t O, template <typename...> class N, typename... P>
class TensorMixin;

/**
 * TensorExpression - Base class for expression templating with tensor syntax.
 * Parameters:
 *    E - Base expression
 *    N - Namespace template from which to pull typedefs
 *    P - Namespace parameters to fully instantiate namespace
**/
template <typename E, template <typename...> class N, typename... P>
class TensorExpression;

}//namespace tensor

#include <tensor/tensor.hpp>
#include <tensor/tensormixin.hpp>
#include <tensor/tensorexpr.hpp>

#endif//__TENSOR_H__

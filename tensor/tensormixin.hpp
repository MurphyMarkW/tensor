#ifndef __TENSORMIXIN_HPP__
#define __TENSORMIXIN_HPP__

#include <tensor.h>
#include <stdlib.h>
#include <vector>
#include <array>
//#include <algorithm>
//#include <type_traits>
#include <stdexcept>

namespace tensor {

template <intmax_t O, template <typename...> class N, typename... P>
class TensorMixin : public TensorExpression<TensorMixin<O,N,P...>,N,P...> {
  /**
   *  TensorMixin - Mixin that exposes tensor syntax.
   *  Parameters:
   *    O - Tensor order
   *    N - Namespace template from which to pull typedefs
   *    P - Namespace parameters to fully instantiate namespace
   *
   *  Requirements:
   *    Classes which derive from TensorMixin need only provide a
   *    template container exposing the following:
   *
   *    Typedefs:
   *      typename size_type  - type for indexing
   *      typename value_type - type of contained elements
   *      typename reference  - type for referencing elements
   *      typename const_reference  - const type of reference
   *
   *    Operators:
   *      size_type size() - container size
   *      auto resize(size_type) - container resizing
   *      (const_)reference at(size_type) - bounds checked accessor
   *      (const_)reference operator()(size_type) - non-bounds checked
  **/

  // Typenames required for tensor syntax.
  public:
    typedef typename N<P...>::size_type        size_type;
    typedef typename N<P...>::reference        reference;
    typedef typename N<P...>::value_type       value_type;
    typedef typename N<P...>::const_reference  const_reference;

  // Constructors.
  public:
    TensorMixin();
    template <typename... Etc>
    TensorMixin(size_type i, Etc... etc);
    template <typename E, template <typename...> class n, typename... p>
    TensorMixin(TensorExpression<E,n,p...> const&);
    template <typename E, template <typename...> class n, typename... p>
    TensorMixin(TensorExpression<E,n,p...>      &);
  protected:
    template <typename... I>
    void _TensorMixin(size_type,I...);
    void _TensorMixin(size_type);

  // Internal state.
  protected:
    N<P...> _data;
    std::array<size_type,O> _size;
    std::array<size_type,O> _stride;

  // State accessors. 
  public:
    inline size_type size() const;
    inline size_type size(size_type) const;
    inline size_type stride(size_type) const;
    static constexpr intmax_t order() { return O; }

  // (Const) Reference accessor with(out) range check.
  #define OpAccess(op)                                                                  \
  public:                                                                               \
    template <typename... I,                                                            \
              typename enable_if<(O>1)&&(sizeof...(I)==O-2),int>::type = 0>             \
    reference op (size_type,size_type,I...);                                            \
    reference op (size_type);                                                           \
    template <typename... I,                                                            \
              typename enable_if<(O>1)&&(sizeof...(I)==O-2),int>::type = 0>             \
    const_reference op (size_type,size_type,I...) const;                                \
    const_reference op (size_type) const;                                               \
  protected:                                                                            \
    template <typename... I,                                                            \
              typename enable_if<(O>1)&&(sizeof...(I)<O-2),int>::type = 0>              \
    reference op (size_type,size_type,I...);                                            \
    template <typename... I,                                                            \
              typename enable_if<(O>1)&&(sizeof...(I)<O-2),int>::type = 0>              \
    const_reference op (size_type,size_type,I...) const;                                \

  OpAccess(at)
  OpAccess(operator())
  #undef OpAccess

  // Assignment operator.
  #define OpAssign(op)                                                                  \
  public:                                                                               \
    TensorMixin & operator op (value_type);                                             \
    TensorMixin & operator op (reference);                                              \
    TensorMixin & operator op (const_reference);                                        \
    template <typename E, template <typename...> class n, typename... p>                \
    TensorMixin & operator op (TensorExpression<E,n,p...> const&);                      \
    template <typename E, template <typename...> class n, typename... p>                \
    TensorMixin & operator op (TensorExpression<E,n,p...>      &);                      \

  OpAssign(=)
  OpAssign(+=)
  OpAssign(-=)
  OpAssign(*=)
  OpAssign(/=)
  #undef OpAssign
};

}//namespace tensor

#include <tensor/tensormixin.hxx>

#endif//__TENSORMIXIN_HPP__

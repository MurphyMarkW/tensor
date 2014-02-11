#ifndef __TENSOREXPR_ARITHMETIC_HPP__
#define __TENSOREXPR_ARITHMETIC_HPP__

#include <tensor.h>

namespace tensor {

#define DefineTensorOp(id,op)                                                           \
template <typename E1, typename E2, template <typename...> class N, typename... P>      \
class id : public TensorExpression< id <E1,E2,N,P...>,N,P...> {                         \
  public:                                                                               \
    typedef typename N<P...>::size_type       size_type;                                \
    typedef typename N<P...>::reference       reference;                                \
    typedef typename N<P...>::value_type      value_type;                               \
    typedef typename N<P...>::const_reference const_reference;                          \
                                                                                        \
    E1 const& e1;                                                                       \
    E2 const& e2;                                                                       \
                                                                                        \
  public:                                                                               \
    id (E1 const& e1, E2 const& e2) : e1(e1), e2(e2) {};                                \
                                                                                        \
    inline size_type size() const { return e1.size(); }                                 \
    inline size_type size(size_type i) const { return e1.size(i); }                     \
    inline size_type stride(size_type i) const { return e1.stride(i); }                 \
    static constexpr intmax_t order() { return E1::order(); }                           \
                                                                                        \
    template <typename... I>                                                            \
    inline value_type at(I... i) const {                                                \
      return e1.at(i...) op e2;                                                         \
    }                                                                                   \
    template <typename... I>                                                            \
    inline value_type operator()(I... i) const {                                        \
      return e1.operator()(i...) op e2;                                                 \
    }                                                                                   \
};                                                                                      \
                                                                                        \
template <typename E1, typename E2,                                                     \
          template <typename...> class N, typename T, typename... P>                    \
inline typename enable_if<!is_base_of<TensorBase,E2>::value,id<E1,E2,N,T,P...> >::type  \
operator op (TensorExpression<E1,N,T,P...> const& e1,                                   \
             E2                            const& e2) {                                 \
  return id <E1,E2,N,T,P...>(e1,e2);                                                    \
};                                                                                      \

DefineTensorOp(TensorValueAddition,+)
DefineTensorOp(TensorValueSubtraction,-)
DefineTensorOp(TensorValueMultiplication,*)
DefineTensorOp(TensorValueDivision,/)
#undef DefineTensorOp

#define DefineTensorOp(id,op)                                                           \
template <typename E1, typename E2, template <typename...> class N, typename... P>      \
class id : public TensorExpression< id <E1,E2,N,P...>,N,P...> {                         \
  public:                                                                               \
    typedef typename N<P...>::size_type       size_type;                                \
    typedef typename N<P...>::reference       reference;                                \
    typedef typename N<P...>::value_type      value_type;                               \
    typedef typename N<P...>::const_reference const_reference;                          \
                                                                                        \
    E1 const& e1;                                                                       \
    E2 const& e2;                                                                       \
                                                                                        \
  public:                                                                               \
    id (E1 const& e1, E2 const& e2) : e1(e1), e2(e2) {};                                \
                                                                                        \
    inline size_type size() const { return e2.size(); }                                 \
    inline size_type size(size_type i) const { return e2.size(i); }                     \
    inline size_type stride(size_type i) const { return e2.stride(i); }                 \
    static constexpr intmax_t order() { return E2::order(); }                           \
                                                                                        \
    template <typename... I>                                                            \
    inline value_type at(I... i) const {                                                \
      return e1 op e2.at(i...);                                                         \
    }                                                                                   \
    template <typename... I>                                                            \
    inline value_type operator()(I... i) const {                                        \
      return e1 op e2.operator()(i...);                                                 \
    }                                                                                   \
};                                                                                      \
                                                                                        \
template <typename E1, typename E2,                                                     \
          template <typename...> class N, typename T, typename... P>                    \
inline typename enable_if<!is_base_of<TensorBase,E1>::value,id<E1,E2,N,E1,P...> >::type \
operator op (E1                            const& e1,                                   \
             TensorExpression<E2,N,T,P...> const& e2) {                                 \
  return id <E1,E2,N,E1,P...>(e1,e2);                                                   \
};                                                                                      \

DefineTensorOp(ValueTensorAddition,+)
DefineTensorOp(ValueTensorSubtraction,-)
DefineTensorOp(ValueTensorMultiplication,*)
DefineTensorOp(ValueTensorDivision,/)
#undef DefineTensorOp

#define DefineTensorExpr(id,op)                                                         \
template <typename E1, typename E2, template <typename...> class N, typename... P>      \
class id : public TensorExpression< id <E1,E2,N,P...>,N,P...> {                         \
  public:                                                                               \
    typedef typename N<P...>::size_type       size_type;                                \
    typedef typename N<P...>::reference       reference;                                \
    typedef typename N<P...>::value_type      value_type;                               \
    typedef typename N<P...>::const_reference const_reference;                          \
                                                                                        \
    E1 const& e1;                                                                       \
    E2 const& e2;                                                                       \
                                                                                        \
  public:                                                                               \
    id (TensorExpression<E1,N,P...> const& e1,                                          \
        E2                          const& e2) : e1(e1), e2(e2) {};                     \
                                                                                        \
    inline size_type size() const { return e1.size(); }                                 \
    inline size_type size(size_type i) const { return e1.size(i); }                     \
    inline size_type stride(size_type i) const { return e1.stride(i); }                 \
    static constexpr intmax_t order() { return E1::order(); }                           \
                                                                                        \
    template <typename... I>                                                            \
    inline value_type at(I... i) const {                                                \
      return e1.at(i...) op e2.at(i...);                                                \
    }                                                                                   \
    template <typename... I>                                                            \
    inline value_type operator()(I... i) const {                                        \
      return e1.operator()(i...) op e2.operator()(i...);                                \
    }                                                                                   \
};                                                                                      \
                                                                                        \
template <typename E1, typename E2, template <typename...> class N, typename... P>      \
inline typename enable_if<is_base_of<TensorBase,E2>::value,id<E1,E2,N,P...> >::type     \
operator op (TensorExpression<E1,N,P...> const& e1,                                     \
             E2                          const& e2) {                                   \
  return id <E1,E2,N,P...>(e1,e2);                                                      \
};                                                                                      \

DefineTensorExpr(TensorAddition,+)
DefineTensorExpr(TensorSubtraction,-)
DefineTensorExpr(TensorMultiplication,*)
DefineTensorExpr(TensorDivision,/)
#undef DefineTensorExpr

}//namespace tensor

#endif//__TENSOREXPR_ARITHMETIC_HPP__

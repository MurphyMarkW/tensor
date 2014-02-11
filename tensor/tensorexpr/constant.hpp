#ifndef __TENSOREXPR_CONSTANT_HPP__
#define __TENSOREXPR_CONSTANT_HPP__

#include <tensor.h>

namespace tensor {

template <typename T>
struct ConstantNamespace {
  typedef std::size_t size_type;
  typedef T           value_type;
  typedef T      &    reference;
  typedef T const&    const_reference;
};

template <typename T, intmax_t O, typename N = ConstantNamespace<T> >
class Constant : public TensorExpression<Constant<T,O,N>,O,N> {
  public:                                                                               \
    typedef typename N::size_type       size_type;                                      \
    typedef typename N::reference       reference;                                      \
    typedef typename N::value_type      value_type;                                     \
    typedef typename N::const_reference const_reference;                                \

    const_reference c;

  public:
    Constant(const_reference c) : c(c) {};

    inline size_type dims() const { return O; }                                         \
    inline size_type size() const { return 1; }                                  \
    inline size_type size(size_type i) const { return 1; }                      \
    inline size_type stride(size_type i) const { return 0; }                  \
                                                                                        \
    template <typename... I>                                                            \
    inline value_type at(I... i) const {                                                \
      return e.at(i...) op static_cast<const_reference>(v);                             \
    }                                                                                   \
    template <typename... I>                                                            \
    inline value_type operator()(I... i) const {                                        \
      return e.operator()(i...) op static_cast<const_reference>(v);                     \
    }                                                                                   \
};                                                                                      \
                                                                                        \
template <typename E, intmax_t O, typename N, typename V>                               \
inline id <E,O,N,V> const operator op (TensorExpression<E,O,N> const& e,                \
                                       V                       const& v) {              \
  return id <E,O,N,V>(e,v);                                                             \
};                                                                                      \

DefineTensorExpr(TensorValueAddition,+)
DefineTensorExpr(TensorValueSubtraction,-)
DefineTensorExpr(TensorValueMultiplication,*)
DefineTensorExpr(TensorValueDivision,/)
#undef DefineTensorExpr

#define DefineTensorExpr(id,op)                                                         \
template <typename E, intmax_t O, typename N, typename V>                               \
class id : public TensorExpression< id <E,O,N,V>,O,N> {                                 \
  public:                                                                               \
    typedef typename N::size_type       size_type;                                      \
    typedef typename N::reference       reference;                                      \
    typedef typename N::value_type      value_type;                                     \
    typedef typename N::const_reference const_reference;                                \
                                                                                        \
    E const& e;                                                                         \
    V const& v;                                                                         \
                                                                                        \
  public:                                                                               \
    id (V const& v, E const& e) : e(e), v(v) {};                                        \
                                                                                        \
    inline size_type dims() const { return O; }                                         \
    inline size_type size() const { return e.size(); }                                  \
    inline size_type size(size_type i) const { return e.size(i); }                      \
    inline size_type stride(size_type i) const { return e.stride(i); }                  \
                                                                                        \
    template <typename... I>                                                            \
    inline V at(I... i) const {                                                \
      std::cout << "YOLO" << std::endl; \
      return v op static_cast<V const&>(e.at(i...));                                    \
    }                                                                                   \
    template <typename... I>                                                            \
    inline V operator()(I... i) const {                                        \
      std::cout << "YOLO" << std::endl; \
      std::cout << v op static_cast<V const&>(e.operator()(i...)) << std::endl; \
      return v op static_cast<V const&>(e.operator()(i...));                            \
    }                                                                                   \
};                                                                                      \
                                                                                        \
template <typename E, intmax_t O, typename N, typename V>                               \
inline id <E,O,N,V> const operator op (V                       const& v,                \
                                       TensorExpression<E,O,N> const& e) {              \
  return id <E,O,N,V>(v,e);                                                             \
};                                                                                      \

DefineTensorExpr(ValueTensorAddition,+)
DefineTensorExpr(ValueTensorSubtraction,-)
DefineTensorExpr(ValueTensorMultiplication,*)
DefineTensorExpr(ValueTensorDivision,/)
#undef DefineTensorExpr
/*
#define DefineTensorExpr(id,op)                                                         \
template <typename E1, typename E2, typename T1, typename T2, intmax_t O>               \
class id : public TensorExpression< id <E1,E2,T1,T2,O>,T1,O> {                          \
  public:                                                                               \
    typedef typename E1::size_type size_type;                                           \
    typedef typename E1::value_type value_type;                                         \
                                                                                        \
    E1 const& a;                                                                        \
    E2 const& b;                                                                        \
                                                                                        \
  public:                                                                               \
    id (TensorExpression<E1,T1,O> const& a,                                             \
        TensorExpression<E2,T2,O> const& b) : a(a), b(b) {};                            \
                                                                                        \
    inline size_type dims() const { return a.dims(); }                                  \
    inline size_type size() const { return a.size(); }                                  \
    inline size_type size(size_type i) const { return a.size(i); }                      \
    inline size_type stride(size_type i) const { return a.stride(i); }                  \
                                                                                        \
    template <typename... I>                                                            \
    inline value_type at(I... i) const {                                                \
      return a.at(i...) op static_cast<value_type>(b.at(i...));                         \
    }                                                                                   \
    template <typename... I>                                                            \
    inline value_type operator()(I... i) const {                                        \
      return a(i...) op static_cast<value_type>(b(i...));                               \
    }                                                                                   \
                                                                                        \
};                                                                                      \
                                                                                        \
template <typename E1, typename E2, typename T1, typename T2, intmax_t O,               \
          typename = typename enable_if<is_convertible<T2,T1>::value>::type>            \
inline id <E1,E2,T1,T2,O> operator op (TensorExpression<E1,T1,O>  const& a,             \
                                       TensorExpression<E2,T2,O>  const& b) {           \
  return id <E1,E2,T1,T2,O>(a,b);                                                       \
};                                                                                      \

DefineTensorExpr(TensorAddition,+)
DefineTensorExpr(TensorSubtraction,-)
DefineTensorExpr(TensorMultiplication,*)
DefineTensorExpr(TensorDivision,/)
#undef DefineTensorExpr
*/
}//namespace tensor

#endif//__TENSOREXPR_CONSTANT_HPP__

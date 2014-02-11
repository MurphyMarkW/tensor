#ifndef __TENSORMIXIN_HXX__
#define __TENSORMIXIN_HXX__

#include <tensor.h>

namespace tensor {

template <intmax_t O, template <typename...> class N, typename... P>
TensorMixin<O,N,P...>::TensorMixin() {
  static_assert(O,"tensor syntax requires order to be greater than or equal to 1");
  _size.fill(0);    // Set tensor sizes.
  _stride.fill(1);  // Set tensor strides.
  _data.resize(0);  // Call base storage resize.
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename E, template <typename...> class n, typename... p>
TensorMixin<O,N,P...>::TensorMixin(TensorExpression<E,n,p...> const& te) {
  for(size_type i = 0; i < O; ++i) {
    _size[i]   = te.size(i);   // Copy tensor sizes.
    _stride[i] = te.stride(i); // Copy tensor strides.
  }
  _data.resize(_size[0] * _stride[0]);
  for(size_type i = 0; i < size(); ++i) {
    operator()(i) = te.operator()(i); // Copy element by element.
  }
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename E, template <typename...> class n, typename... p>
TensorMixin<O,N,P...>::TensorMixin(TensorExpression<E,n,p...>      & te) {
  for(size_type i = 0; i < O; ++i) {
    _size[i]   = te.size(i);   // Copy tensor sizes.
    _stride[i] = te.stride(i); // Copy tensor strides.
  }
  _data.resize(_size[0] * _stride[0]);
  for(size_type i = 0; i < size(); ++i) {
    operator()(i) = te.operator()(i); // Copy element by element.
  }
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... I, typename _enabler>
TensorMixin<O,N,P...>::TensorMixin(I... i) {
  static_assert(O>0,"tensor order must be greater than 0");
  _TensorMixin(i...);
  _data.resize(size(0)*stride(0));
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... I>
void TensorMixin<O,N,P...>::_TensorMixin(size_type i, I... etc) {
  _size[O-sizeof...(I)-1] = i;
  _TensorMixin(etc...);
  _stride[O-sizeof...(I)-1] = size(O-sizeof...(I)) * stride(O-sizeof...(I));
};

template <intmax_t O, template <typename...> class N, typename... P>
void TensorMixin<O,N,P...>::_TensorMixin(size_type i) {
  _size[O-1] = i;
  _stride[O-1] = 1;
};

template <intmax_t O, template <typename...> class N, typename... P>
inline auto TensorMixin<O,N,P...>::size() const -> size_type {
  return _data.size();
};

template <intmax_t O, template <typename...> class N, typename... P>
inline auto TensorMixin<O,N,P...>::size(size_type i) const -> size_type {
  #ifndef DISABLE_NSOR_EXCEPTIONS
  if(i>=O) throw std::out_of_range("out of range exception");
  #endif//DISABLE_NSOR_EXCEPTIONS
  return _size[i];
};

template <intmax_t O, template <typename...> class N, typename... P>
inline auto TensorMixin<O,N,P...>::stride(size_type i) const -> size_type {
  #ifndef DISABLE_NSOR_EXCEPTIONS
  if(i>=O) throw std::out_of_range("out of range exception");
  #endif//DISABLE_NSOR_EXCEPTIONS
  return _stride[i];
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)==O-2),int>::type>
auto TensorMixin<O,N,P...>::at(size_type i, size_type j, Etc... etc) -> reference {
  // Check that the indices are within range.
  if(i >= size(O-sizeof...(Etc)-2))
    throw std::out_of_range("out of range exception");
  if(j >= size(O-sizeof...(Etc)-1))
    throw std::out_of_range("out of range exception");
  // Recursively deconstruct parameters.
  return at(i*stride(O-sizeof...(Etc)-2)+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)<O-2),int>::type>
auto TensorMixin<O,N,P...>::at(size_type i, size_type j, Etc... etc) -> reference {
  // Check that the index is within range.
  if(j >= size(O-sizeof...(Etc)-1))
    throw std::out_of_range("out of range exception");
  // Recursively deconstruct parameters.
  return at(i+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
auto TensorMixin<O,N,P...>::at(size_type i) -> reference {
  // Pass off handling to the data container.
  return _data.at(i);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)==O-2),int>::type>
auto TensorMixin<O,N,P...>::at(size_type i, size_type j, Etc... etc) const -> const_reference {
  // Check that the indices are within range.
  if(i >= size(O-sizeof...(Etc)-2))
    throw std::out_of_range("out of range exception");
  if(j >= size(O-sizeof...(Etc)-1))
    throw std::out_of_range("out of range exception");
  // Recursively deconstruct parameters.
  return at(i*stride(O-sizeof...(Etc)-2)+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)<O-2),int>::type>
auto TensorMixin<O,N,P...>::at(size_type i, size_type j, Etc... etc) const -> const_reference {
  // Check that the index is within range.
  if(j >= size(O-sizeof...(Etc)-1))
    throw std::out_of_range("out of range exception");
  // Recursively deconstruct parameters.
  return at(i+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
auto TensorMixin<O,N,P...>::at(size_type i) const -> const_reference {
  // Pass off handling to the data container.
  return _data.at(i);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)==O-2),int>::type>
auto TensorMixin<O,N,P...>::operator()(size_type i, size_type j, Etc... etc) -> reference {
  // Recursively deconstruct parameters.
  return operator()(i*stride(O-sizeof...(Etc)-2)+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)<O-2),int>::type>
auto TensorMixin<O,N,P...>::operator()(size_type i, size_type j, Etc... etc) -> reference {
  // Recursively deconstruct parameters.
  return operator()(i+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
auto TensorMixin<O,N,P...>::operator()(size_type i) -> reference {
  // Pass off handling to the data container.
  return _data.operator[](i);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)==O-2),int>::type>
auto TensorMixin<O,N,P...>::operator()(size_type i, size_type j, Etc... etc) const -> const_reference {
  // Recursively deconstruct parameters.
  return operator()(i*stride(O-sizeof...(Etc)-2)+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename... Etc,
          typename enable_if<(O>1)&&(sizeof...(Etc)<O-2),int>::type>
auto TensorMixin<O,N,P...>::operator()(size_type i, size_type j, Etc... etc) const -> const_reference {
  // Recursively deconstruct parameters.
  return operator()(i+j*stride(O-sizeof...(Etc)-1),etc...);
};

template <intmax_t O, template <typename...> class N, typename... P>
auto TensorMixin<O,N,P...>::operator()(size_type i) const -> const_reference {
  // Pass off handling to the data container.
  return _data.operator[](i);
};

#define OpAssign(op)                                                                    \
template <intmax_t O, template <typename...> class N, typename... P>                    \
TensorMixin<O,N,P...> & TensorMixin<O,N,P...>::operator op (value_type v) {             \
  for(size_type i = 0; i < size(); ++i) {                                               \
    operator()(i) op v;                                                                 \
  }                                                                                     \
  return *this;                                                                         \
};                                                                                      \
                                                                                        \
template <intmax_t O, template <typename...> class N, typename... P>                    \
TensorMixin<O,N,P...> & TensorMixin<O,N,P...>::operator op (reference r) {              \
  for(size_type i = 0; i < size(); ++i) {                                               \
    operator()(i) op r;                                                                 \
  }                                                                                     \
  return *this;                                                                         \
};                                                                                      \
                                                                                        \
template <intmax_t O, template <typename...> class N, typename... P>                    \
TensorMixin<O,N,P...> & TensorMixin<O,N,P...>::operator op (const_reference c) {        \
  for(size_type i = 0; i < size(); ++i) {                                               \
    operator()(i) op c;                                                                 \
  }                                                                                     \
  return *this;                                                                         \
};                                                                                      \

OpAssign(=)
OpAssign(+=)
OpAssign(-=)
OpAssign(*=)
OpAssign(/=)
#undef OpAssign


#define OpAssign(op)                                                                    \
template <intmax_t O, template <typename...> class N, typename... P>                    \
template <typename E, template <typename...> class n, typename... p>                    \
TensorMixin<O,N,P...> &                                                                 \
TensorMixin<O,N,P...>::operator op (TensorExpression<E,n,p...> const& te) {             \
  if(size() != te.size()) throw TensorException();                                      \
  for(size_type i = 0; i < size(); ++i) {                                               \
    operator()(i) op te(i);                                                             \
  }                                                                                     \
  return *this;                                                                         \
};                                                                                      \
                                                                                        \
template <intmax_t O, template <typename...> class N, typename... P>                    \
template <typename E, template <typename...> class n, typename... p>                    \
TensorMixin<O,N,P...> &                                                                 \
TensorMixin<O,N,P...>::operator op (TensorExpression<E,n,p...>      & te) {             \
  if(size() != te.size()) throw TensorException();                                      \
  for(size_type i = 0; i < size(); ++i) {                                               \
    operator()(i) op te(i);                                                             \
  }                                                                                     \
  return *this;                                                                         \
};                                                                                      \

OpAssign(+=)
OpAssign(-=)
OpAssign(*=)
OpAssign(/=)
#undef OpAssign

template <intmax_t O, template <typename...> class N, typename... P>
template <typename E, template <typename...> class n, typename... p>
TensorMixin<O,N,P...> & TensorMixin<O,N,P...>::operator=(TensorExpression<E,n,p...> const& te) {
  // Copy over bookkeeping.
  for(size_type i = 0; i < O; ++i) {
    _size[i]   = te.size(i);
    _stride[i] = te.stride(i);
  }

  // Resize and copy over elements sequentially.
  _data.resize(_size[0] * _stride[0]);
  for(size_type i = 0; i < te.size(); ++i) {
    operator()(i) = te(i);
  }

  // Done.
  return *this;
};

template <intmax_t O, template <typename...> class N, typename... P>
template <typename E, template <typename...> class n, typename... p>
TensorMixin<O,N,P...> & TensorMixin<O,N,P...>::operator=(TensorExpression<E,n,p...>      & te) {
  // Copy over bookkeeping.
  for(size_type i = 0; i < O; ++i) {
    _size[i]   = te.size(i);
    _stride[i] = te.stride(i);
  }

  // Resize and copy over elements sequentially.
  _data.resize(_size[0] * _stride[0]);
  for(size_type i = 0; i < te.size(); ++i) {
    operator()(i) = te(i);
  }

  // Done.
  return *this;
};

}//namespace tensor

#endif//__TENSORMIXIN_HXX__

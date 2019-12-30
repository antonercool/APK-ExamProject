#pragma once
#include "boost/bind.hpp"

namespace Attacher
{

template <typename T> struct has_function_operator
{
  typedef char operator_implemented;
  typedef long operator_not_implemented;

  // Hits this template function if type has implemented operator()
  template <typename U>
  static operator_implemented check_for_operator(decltype(&U::operator()));

  // Trash can for all types without operator()
  template <typename U> static operator_not_implemented check_for_operator(...);

  // gives value either 1 or 0 decided from wether the check_for_operator
  // returns a char or a long
  // enum { value = sizeof(check_for_operator<T>(0)) == sizeof(char) };

  // The reason for passing 0/nullptr in the parameter is because it can be
  // passed to a member function pointer
  static const bool value = sizeof(check_for_operator<T>(0)) == sizeof(char);
};

template <typename T, typename A> auto attach(T &t, A &a)
{
  if constexpr (has_function_operator<T>::value)
  {
    // This has function operator
    a.attach(t); 
  }
  else
  {
    // This does not have function operator
    a.attach(boost::bind(&T::callback, &t, _1));
  }
}
} // namespace Attacher
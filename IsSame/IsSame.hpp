#pragma once
template <typename type1, typename type2> 
struct IsSame
{
  static const bool value = false;
};

template <typename type1> 
struct IsSame<type1, type1>
{
  static const bool value = true;
};
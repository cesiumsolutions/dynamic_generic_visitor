#ifndef TypeIndex_hpp
#define TypeIndex_hpp

#include <typeindex>

template<typename T>
std::type_index
typeIndexOf()
{
  return std::type_index( typeid( T ) );
}

template<typename T>
std::type_index
typeIndexOf( T const & )
{
  return std::type_index( typeid( T ) );
}

#endif // TypeIndex_hpp
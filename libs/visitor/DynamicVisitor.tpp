#ifndef DynamicVisitor_tpp
#define DynamicVisitor_tpp

#include <visitor/TypeIndex.hpp>

template<typename ReturnType, typename... ParameterTypes>
template<typename VisiteeType>
bool
DynamicVisitor<ReturnType( ParameterTypes... )>::hasHandler() const
{
  return handlers.find( typeIndexOf<VisiteeType>() ) != handlers.end();
} // DynamicVisitor<ReturnType(ParameterTypes...)>::hasHandler<VisiteeType>

template<typename ReturnType, typename... ParameterTypes>
template<typename VisiteeType>
void
DynamicVisitor<ReturnType( ParameterTypes... )>::addHandler(
    Handler<VisiteeType> const & handler )
{
  handlers[typeIndexOf<VisiteeType>()] =
      [handler]( boost::any const & visitee,
                 ParameterTypes &&... params ) -> ReturnType {
    return handler( boost::any_cast<VisiteeType const &>( visitee ),
                    std::forward<ParameterTypes>( params )... );
  };
} // DynamicVisitor<ReturnType(ParameterTypes...)>::addHandler<VisiteeType>

template<typename ReturnType, typename... ParameterTypes>
template<typename VisiteeType>
typename DynamicVisitor<ReturnType( ParameterTypes... )>::ResultType
DynamicVisitor<ReturnType( ParameterTypes... )>::visit(
    VisiteeType const & visitee,
    ParameterTypes &&... params )
{
  auto hit = handlers.find( typeIndexOf<VisiteeType>() );
  if ( hit == handlers.end() ) {
    return {};
  }

  return hit->second( visitee, std::forward<ParameterTypes>( params )... );
} // DynamicVisitor<ReturnType (ParameterTypes...)>::visit<VisiteeType>

#endif // DynamicVisitor_tpp
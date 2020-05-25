#ifndef StaticVisitor_hpp
#define StaticVisitor_hpp

template<typename ReturnType, typename... VisiteeTypes>
struct StaticVisitor;

template<typename _ReturnType,
         typename FirstVisiteeType,
         typename... RestVisiteeTypes>
struct StaticVisitor<_ReturnType, FirstVisiteeType, RestVisiteeTypes...>
    : public StaticVisitor<_ReturnType, RestVisiteeTypes...>
{
  using ReturnType = _ReturnType;

  using StaticVisitor<ReturnType, RestVisiteeTypes...>::visit;

  virtual ReturnType visit( FirstVisiteeType const & visitee ) = 0;
}; // class StaticVisitor<ReturnType, FirstVisiteeType, RestVisiteeTypes...>

template<typename _ReturnType, typename VisiteeType>
struct StaticVisitor<_ReturnType, VisiteeType>
{
  using ReturnType = _ReturnType;

  virtual ReturnType visit( VisiteeType const & visitee ) = 0;
}; // class StaticVisitor<ReturnType, VisiteeType>

#endif // StaticVisitor_hpp

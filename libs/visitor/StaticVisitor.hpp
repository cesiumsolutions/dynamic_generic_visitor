#ifndef StaticVisitor_hpp
#define StaticVisitor_hpp

template<typename... VisiteeTypes>
struct StaticVisitor;

template<typename FirstVisiteeType, typename... RestVisiteeTypes>
struct StaticVisitor<FirstVisiteeType, RestVisiteeTypes...>
    : public StaticVisitor<RestVisiteeTypes...>
{
  using StaticVisitor<RestVisiteeTypes...>::visit;

  virtual void visit( FirstVisiteeType const & visitee ) = 0;
}; // class StaticVisitor<FirstVisiteeType, RestVisiteeTypes...>

template<typename VisiteeType>
struct StaticVisitor<VisiteeType>
{
  virtual void visit( VisiteeType const & visitee ) = 0;
}; // class StaticVisitor<VisiteeType>

#endif // StaticVisitor_hpp

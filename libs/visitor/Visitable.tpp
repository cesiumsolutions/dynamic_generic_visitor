#ifndef Visitable_tpp
#define Visitable_tpp

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType, typename VisitorType, typename ReturnType>
Visitable<VisiteeType, VisitorType, ReturnType>::Visitable(
    VisiteeType const & visitee )
    : VisitableBase<VisitorType, ReturnType>()
    , mVisitee( std::cref( visitee ) )
{
} // Visitable<VisiteeType, VisitorType, ReturnType>::Visitable

template<typename VisiteeType, typename VisitorType, typename ReturnType>
std::type_info const &
Visitable<VisiteeType, VisitorType, ReturnType>::typeInfo() const
{
  return typeid( VisiteeType );
} // Visitable<VisiteeType, VisitorType, ReturnType>::typeInfo

template<typename VisiteeType, typename VisitorType, typename ReturnType>
ReturnType
Visitable<VisiteeType, VisitorType, ReturnType>::accept(
    VisitorType & visitor ) const
{
  return visitor.visit( mVisitee.get() );
} // Visitable<VisiteeType, VisitorType, ReturnType>::accept

// ----------------------------------------------------------------------------
// Smart pointer initialization free functions
// ----------------------------------------------------------------------------

template<typename VisitorType, typename ReturnType, typename VisiteeType>
VisitableUPtr<VisitorType, ReturnType>
makeUniqueVisitable( VisiteeType const & visitee )
{
  return VisitableUPtr<VisitorType, ReturnType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeUniqueVisitable

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType, typename VisitorType::ReturnType>
makeUniqueVisitable( VisiteeType const & visitee )
{
  using ReturnType = VisitorType::ReturnType;

  return VisitableUPtr<VisitorType, ReturnType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeUniqueVisitable


template<typename VisitorType, typename ReturnType, typename VisiteeType>
VisitableSPtr<VisitorType, ReturnType>
makeSharedVisitable( VisiteeType const & visitee )
{
  return VisitableSPtr<VisitorType, ReturnType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeSharedVisitable

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType, typename VisitorType::ReturnType>
makeSharedVisitable( VisiteeType const & visitee )
{
  using ReturnType = VisitorType::ReturnType;

  return VisitableSPtr<VisitorType, ReturnType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeSharedVisitable

#endif // Visitable_tpp

#ifndef Visitable_tpp
#define Visitable_tpp

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType, typename VisitorType>
Visitable<VisiteeType, VisitorType>::Visitable( VisiteeType const & visitee )
    : VisitableBase<VisitorType>()
    , mVisitee( std::cref( visitee ) )
{
} // Visitable<VisiteeType, VisitorType>::Visitable

template<typename VisiteeType, typename VisitorType>
std::type_info const &
Visitable<VisiteeType, VisitorType>::typeInfo() const
{
  return typeid( VisiteeType );
} // Visitable<VisiteeType, VisitorType>::typeInfo

template<typename VisiteeType, typename VisitorType>
void
Visitable<VisiteeType, VisitorType>::accept( VisitorType & visitor ) const
{
  return visitor.visit( mVisitee.get() );
} // Visitable<VisiteeType, VisitorType>::accept

// ----------------------------------------------------------------------------
// Smart pointer initialization free functions
// ----------------------------------------------------------------------------

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType>
makeUniqueVisitable( VisiteeType const & visitee )
{
  return VisitableUPtr<VisitorType>(
      new Visitable<VisiteeType, VisitorType>( visitee ) );
} // makeUniqueVisitable

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType>
makeSharedVisitable( VisiteeType const & visitee )
{
  return VisitableSPtr<VisitorType>(
      new Visitable<VisiteeType, VisitorType>( visitee ) );
} // makeSharedVisitable

#endif // Visitable_tpp

#ifndef Visitable_tpp
#define Visitable_tpp

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType,
         typename VisitorType,
         typename ReturnType,
         typename... ParameterTypes>
Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes... )>::Visitable(
    VisiteeType const & visitee )
    : VisitableBase<VisitorType, ReturnType( ParameterTypes... )>()
    , mVisitee( visitee )
{
} // Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes...
  // )>::Visitable

template<typename VisiteeType,
         typename VisitorType,
         typename ReturnType,
         typename... ParameterTypes>
std::type_info const &
Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes... )>::typeInfo()
    const
{
  return typeid( VisiteeType );
} // Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes...
  // )>::typeInfo

template<typename VisiteeType,
         typename VisitorType,
         typename ReturnType,
         typename... ParameterTypes>
ReturnType
Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes... )>::accept(
    VisitorType & visitor,
    ParameterTypes... parameters ) const
{
  return visitor.visit( mVisitee,
                        std::forward<ParameterTypes>( parameters )... );
} // Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes...
  // )>::accept

// ----------------------------------------------------------------------------
// Smart pointer initialization free functions
// ----------------------------------------------------------------------------

template<typename VisitorType, typename SignatureType, typename VisiteeType>
VisitableUPtr<VisitorType, SignatureType>
makeUniqueVisitable( VisiteeType const & visitee )
{
  return VisitableUPtr<VisitorType, SignatureType>(
      new Visitable<VisiteeType, VisitorType, SignatureType>( visitee ) );
} // makeUniqueVisitable

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType, typename VisitorType::SignatureType>
makeUniqueVisitable( VisiteeType const & visitee )
{
  using SignatureType = typename VisitorType::SignatureType;

  return VisitableUPtr<VisitorType, SignatureType>(
      new Visitable<VisiteeType, VisitorType, SignatureType>( visitee ) );
} // makeUniqueVisitable


template<typename VisitorType, typename SignatureType, typename VisiteeType>
VisitableSPtr<VisitorType, SignatureType>
makeSharedVisitable( VisiteeType const & visitee )
{
  return VisitableSPtr<VisitorType, SignatureType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeSharedVisitable

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType, typename VisitorType::SignatureType>
makeSharedVisitable( VisiteeType const & visitee )
{
  using SignatureType = typename VisitorType::SignatureType;

  return VisitableSPtr<VisitorType, SignatureType>(
      new Visitable<VisiteeType, VisitorType, ReturnType>( visitee ) );
} // makeSharedVisitable

#endif // Visitable_tpp

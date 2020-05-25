#ifndef StaticVisitor_hpp
#define StaticVisitor_hpp

namespace detail {

template<typename VisiteeType, typename SignatureType>
struct InvokeVisit;

template<typename VisiteeType, typename ReturnType, typename... ParameterTypes>
struct InvokeVisit<VisiteeType, ReturnType( ParameterTypes... )>
{
  virtual ReturnType visit( VisiteeType const & visitee,
                            ParameterTypes... parameters ) = 0;
}; // struct InvokeVisit

} // namespace detail

template<typename SignatureType, typename... VisiteeTypes>
struct StaticVisitor;

template<typename _SignatureType,
         typename FirstVisiteeType,
         typename... RestVisiteeTypes>
struct StaticVisitor<_SignatureType, FirstVisiteeType, RestVisiteeTypes...>
    : public StaticVisitor<_SignatureType, RestVisiteeTypes...>
    , public detail::InvokeVisit<FirstVisiteeType, _SignatureType>
{
  using SignatureType = _SignatureType;

  using StaticVisitor<SignatureType, RestVisiteeTypes...>::visit;
  using detail::InvokeVisit<FirstVisiteeType, SignatureType>::visit;
}; // class StaticVisitor<SignatureType, FirstVisiteeType, RestVisiteeTypes...>

template<typename _SignatureType, typename VisiteeType>
struct StaticVisitor<_SignatureType, VisiteeType>
    : public detail::InvokeVisit<VisiteeType, _SignatureType>
{
  using SignatureType = _SignatureType;

  using detail::InvokeVisit<VisiteeType, SignatureType>::visit;
}; // class StaticVisitor<SignatureType, VisiteeType>

#endif // StaticVisitor_hpp

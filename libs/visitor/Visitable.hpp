#ifndef Visitable_hpp
#define Visitable_hpp

#include <functional>
#include <typeinfo>

// ----------------------------------------------------------------------------
// VisitableBase
// ----------------------------------------------------------------------------

template<typename VisitorType, typename SignatureType>
class VisitableBase;

template<typename VisitorType, typename ReturnType, typename... ParameterTypes>
class VisitableBase<VisitorType, ReturnType( ParameterTypes... )>
{
public:
  virtual ~VisitableBase() = default;

  virtual std::type_info const & typeInfo() const = 0;
  virtual ReturnType             accept( VisitorType & visitor,
                                         ParameterTypes... parameters ) const = 0;

}; // class VisitableBase<VisitorType, ReturnType (ParameterTypes...)>

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType,
         typename VisitorType,
         typename SignatureType = typename VisitorType::SignatureType>
class Visitable;

template<typename VisiteeType,
         typename VisitorType,
         typename ReturnType,
         typename... ParameterTypes>
class Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes... )>
    : public VisitableBase<VisitorType, ReturnType( ParameterTypes... )>
{
public:
  Visitable( VisiteeType const & visitee );

  std::type_info const & typeInfo() const override;
  ReturnType             accept( VisitorType & visitor,
                                 ParameterTypes... parameters ) const override;

private:
  std::reference_wrapper<VisiteeType const> mVisitee;
}; // class Visitable<VisiteeType, VisitorType, ReturnType( ParameterTypes... )>


template<typename VisitorType,
         typename SignatureType = typename VisitorType::SignatureType>
using VisitableUPtr =
    std::unique_ptr<VisitableBase<VisitorType, SignatureType>>;

template<typename VisitorType, typename SignatureType, typename VisiteeType>
VisitableUPtr<VisitorType, SignatureType>
makeUniqueVisitable( VisiteeType const & visitee );

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType, typename VisitorType::SignatureType>
makeUniqueVisitable( VisiteeType const & visitee );


template<typename VisitorType,
         typename SignatureType = typename VisitorType::SignatureType>
using VisitableSPtr =
    std::shared_ptr<VisitableBase<VisitorType, SignatureType>>;

template<typename VisitorType, typename SignatureType, typename VisiteeType>
VisitableSPtr<VisitorType, SignatureType>
makeSharedVisitable( VisiteeType const & visitee );

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType, typename VisitorType::SignatureType>
makeSharedVisitable( VisiteeType const & visitee );

#include <visitor/Visitable.tpp>

#endif // Visitable_hpp

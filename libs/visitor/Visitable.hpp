#ifndef Visitable_hpp
#define Visitable_hpp

#include <functional>
#include <typeinfo>

// ----------------------------------------------------------------------------
// VisitableBase
// ----------------------------------------------------------------------------

template<typename VisitorType, typename ReturnType>
class VisitableBase
{
public:
  virtual ~VisitableBase() = default;

  virtual std::type_info const & typeInfo() const                      = 0;
  virtual ReturnType             accept( VisitorType & visitor ) const = 0;

}; // class VisitableBase<VisitorType, ReturnType>

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType, typename VisitorType, typename ReturnType>
class Visitable : public VisitableBase<VisitorType, ReturnType>
{
public:
  Visitable( VisiteeType const & visitee );

  std::type_info const & typeInfo() const override;
  ReturnType             accept( VisitorType & visitor ) const override;

private:
  std::reference_wrapper<VisiteeType const> mVisitee;
}; // class Visitable<VisiteeType, VisitorType, ReturnType>


template<typename VisitorType,
         typename ReturnType = typename VisitorType::ReturnType>
using VisitableUPtr = std::unique_ptr<VisitableBase<VisitorType, ReturnType>>;

template<typename VisitorType, typename ReturnType, typename VisiteeType>
VisitableUPtr<VisitorType, ReturnType>
makeUniqueVisitable( VisiteeType const & visitee );

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType, typename VisitorType::ReturnType>
makeUniqueVisitable( VisiteeType const & visitee );


template<typename VisitorType,
         typename ReturnType = typename VisitorType::ReturnType>
using VisitableSPtr = std::shared_ptr<VisitableBase<VisitorType, ReturnType>>;

template<typename VisitorType, typename ReturnType, typename VisiteeType>
VisitableSPtr<VisitorType, ReturnType>
makeSharedVisitable( VisiteeType const & visitee );

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType, typename VisitorType::ReturnType>
makeSharedVisitable( VisiteeType const & visitee );

#include <visitor/Visitable.tpp>

#endif // Visitable_hpp

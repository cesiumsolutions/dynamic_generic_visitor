#ifndef Visitable_hpp
#define Visitable_hpp

#include <functional>
#include <typeinfo>

// ----------------------------------------------------------------------------
// VisitableBase
// ----------------------------------------------------------------------------

template<typename VisitorType>
class VisitableBase
{
public:
  virtual ~VisitableBase() = default;

  virtual std::type_info const & typeInfo() const                      = 0;
  virtual void                   accept( VisitorType & visitor ) const = 0;

}; // class VisitableBase<VisitorType>

// ----------------------------------------------------------------------------
// Visitable
// ----------------------------------------------------------------------------

template<typename VisiteeType, typename VisitorType>
class Visitable : public VisitableBase<VisitorType>
{
public:
  Visitable( VisiteeType const & visitee );

  std::type_info const & typeInfo() const override;
  void accept( VisitorType & visitor ) const override;

private:
  std::reference_wrapper<VisiteeType const> mVisitee;
}; // class Visitable<VisiteeType, VisitorType>

template<typename VisitorType>
using VisitableUPtr = std::unique_ptr<VisitableBase<VisitorType>>;

template<typename VisitorType, typename VisiteeType>
VisitableUPtr<VisitorType> makeUniqueVisitable( VisiteeType const & visitee );

template<typename VisitorType>
using VisitableSPtr = std::shared_ptr<VisitableBase<VisitorType>>;

template<typename VisitorType, typename VisiteeType>
VisitableSPtr<VisitorType> makeSharedVisitable( VisiteeType const & visitee );

#include <visitor/Visitable.tpp>

#endif // Visitable_hpp

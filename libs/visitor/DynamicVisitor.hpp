#ifndef DynamicVisitor_hpp
#define DynamicVisitor_hpp

#include <boost/any.hpp>
#include <boost/optional.hpp>

#include <functional>
#include <typeindex>
#include <unordered_map>

template<typename SignatureType>
class DynamicVisitor;

template<typename ReturnType, typename... ParameterTypes>
class DynamicVisitor<ReturnType( ParameterTypes... )>
{
public:
  using ResultType =
      typename std::conditional<std::is_same<ReturnType, void>::value,
                                bool,
                                boost::optional<ReturnType>>::type;

  using SignatureType = ResultType( ParameterTypes... );

  template<typename VisiteeType>
  using Handler = std::function<ReturnType( VisiteeType const & visitee,
                                            ParameterTypes... )>;

  template<typename VisiteeType>
  bool hasHandler() const;

  template<typename VisiteeType>
  void addHandler( Handler<VisiteeType> const & handler );

  template<typename VisiteeType>
  ResultType visit( VisiteeType const & visitee, ParameterTypes &&... params );

private:
  using AnyHandler    = std::function<ReturnType( boost::any const & visitee,
                                               ParameterTypes... )>;
  using AnyHandlerMap = std::unordered_map<std::type_index, AnyHandler>;
  AnyHandlerMap handlers;
}; // class DynamicVisitor<ReturnType (ParameterTypes...)>

#include <visitor/DynamicVisitor.tpp>

#endif // DynamicVisitor_hpp
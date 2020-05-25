#ifndef VisitableShape_hpp
#define VisitableShape_hpp

#include <shapes/ShapeVisitor.hpp>

#include <functional>
#include <memory>
#include <typeinfo>

class VisitableShapeBase
{
public:
  virtual ~VisitableShapeBase() = default;
  virtual std::type_info const & typeInfo() const = 0;
  virtual void accept( ShapeVisitor & visitor ) const = 0;
};

template<typename ShapeType>
class VisitableShape : public VisitableShapeBase
{
public:
  VisitableShape( ShapeType const & s ) : shape( std::cref( s ) )
  {
  }
  virtual ~VisitableShape() = default;

  std::type_info const & typeInfo() const override
  {
    return typeid(ShapeType);
  }

  void accept( ShapeVisitor & visitor ) const override
  {
    visitor.visit( shape.get() );
  }

private:
  std::reference_wrapper<ShapeType const> shape;
};

using VisitableShapeUPtr = std::unique_ptr<VisitableShapeBase>;

template<typename ShapeType>
VisitableShapeUPtr
makeUniqueVisitableShape( ShapeType const & shape )
{
  return std::make_unique<VisitableShape<ShapeType>>( shape );
}

#endif // VisitableShape_hpp
#ifndef Circle_hpp
#define Circle_hpp

#include <shapes/Shape.hpp>
#include <shapes/ShapeVisitor.hpp>

class Circle : public Shape
{
public:
  explicit Circle( float r = 1.0 ) : radius( r )
  {
  }
  ~Circle() = default;

  std::type_info const & typeInfo() const override
  {
    return typeid( Circle );
  }

  void accept( ShapeVisitor & visitor ) const override
  {
    visitor.visit( *this );
  }

  float radius = 1.0f;
};

#endif // Circle_hpp

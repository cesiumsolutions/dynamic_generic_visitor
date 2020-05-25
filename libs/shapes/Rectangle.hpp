#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <shapes/Shape.hpp>
#include <shapes/ShapeVisitor.hpp>

class Rectangle : public Shape
{
public:
  explicit Rectangle( float w = 1.0, float h = 1.0 ) : width( w ), height( h )
  {
  }
  ~Rectangle() = default;

  std::type_info const & typeInfo() const override
  {
    return typeid( Rectangle );
  }

  void accept( ShapeVisitor & visitor ) const override
  {
    visitor.visit( *this );
  }

  float width  = 1.0f;
  float height = 1.0f;
};

#endif // Rectangle_hpp

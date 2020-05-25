#ifndef Shape_hpp
#define Shape_hpp

#include <typeinfo>

class ShapeVisitor;

class Shape
{
public:
  virtual ~Shape() = default;

  virtual std::type_info const & typeInfo() const = 0;

  virtual void accept( ShapeVisitor & visitor ) const = 0;
};

#endif // Shape_hpp

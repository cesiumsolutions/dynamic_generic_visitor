#ifndef ShapeVisitor_hpp
#define ShapeVisitor_hpp

struct Rectangle;
struct Circle;

class ShapeVisitor
{
public:
  virtual ~ShapeVisitor() = default;

  virtual void visit( Rectangle const & r ) = 0;
  virtual void visit( Circle const & c )    = 0;
};

#endif // ShapeVisitor_hpp

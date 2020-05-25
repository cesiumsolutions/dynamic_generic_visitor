#ifndef AreaVisitor_hpp
#define AreaVisitor_hpp

#include <shapes/Area.hpp>
#include <shapes/ShapeVisitor.hpp>

class AreaVisitor : public ShapeVisitor
{
public:
  virtual ~AreaVisitor() = default;

  void visit( Rectangle const & r ) override
  {
    totalArea += area( r );
  }
  void visit( Circle const & c ) override
  {
    totalArea += area( c );
  }

  float totalArea = 0.0;
};

#endif // AreaVisitor_hpp

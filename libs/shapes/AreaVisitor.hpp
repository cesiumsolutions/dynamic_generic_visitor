#ifndef AreaVisitor_hpp
#define AreaVisitor_hpp

#include <shapes/Area.hpp>

#include <visitor/StaticVisitor.hpp>

class AreaVisitor : public StaticVisitor<float, Rectangle, Circle>
{
public:
  virtual ~AreaVisitor() = default;

  float visit( Rectangle const & r ) override
  {
    return area( r );
  }
  float visit( Circle const & c ) override
  {
    return area( c );
  }
};

#endif // AreaVisitor_hpp

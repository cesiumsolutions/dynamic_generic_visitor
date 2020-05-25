#ifndef AreaVisitor_hpp
#define AreaVisitor_hpp

#include <shapes/Area.hpp>

#include <visitor/StaticVisitor.hpp>

class AreaVisitor : public StaticVisitor<float( float ), Rectangle, Circle>
{
public:
  virtual ~AreaVisitor() = default;

  float visit( Rectangle const & r, float scale ) override
  {
    return scale * area( r );
  }
  float visit( Circle const & c, float scale ) override
  {
    return scale * area( c );
  }
};

#endif // AreaVisitor_hpp

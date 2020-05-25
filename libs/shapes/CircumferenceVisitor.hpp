#ifndef CircumferenceVisitor_hpp
#define CircumferenceVisitor_hpp

#include <shapes/Circumference.hpp>

#include <visitor/StaticVisitor.hpp>

class CircumferenceVisitor
    : public StaticVisitor<float( float ), Rectangle, Circle>
{
public:
  virtual ~CircumferenceVisitor() = default;

  float visit( Rectangle const & r, float scale ) override
  {
    return scale * circumference( r );
  }
  float visit( Circle const & c, float scale ) override
  {
    return scale * circumference( c );
  }
};

#endif // CircumferenceVisitor_hpp

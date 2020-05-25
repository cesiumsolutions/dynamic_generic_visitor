#ifndef CircumferenceVisitor_hpp
#define CircumferenceVisitor_hpp

#include <shapes/Circumference.hpp>

#include <visitor/StaticVisitor.hpp>

class CircumferenceVisitor : public StaticVisitor<float, Rectangle, Circle>
{
public:
  virtual ~CircumferenceVisitor() = default;

  float visit( Rectangle const & r ) override
  {
    return circumference( r );
  }
  float visit( Circle const & c ) override
  {
    return circumference( c );
  }
};

#endif // CircumferenceVisitor_hpp

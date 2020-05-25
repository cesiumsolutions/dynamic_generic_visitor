#ifndef CircumferenceVisitor_hpp
#define CircumferenceVisitor_hpp

#include <shapes/Circumference.hpp>

#include <visitor/StaticVisitor.hpp>

class CircumferenceVisitor : public StaticVisitor<Rectangle, Circle>
{
public:
  virtual ~CircumferenceVisitor() = default;

  void visit( Rectangle const & r ) override
  {
    totalCircumference += circumference( r );
  }
  void visit( Circle const & c ) override
  {
    totalCircumference += circumference( c );
  }

  float totalCircumference = 0.0;
};

#endif // CircumferenceVisitor_hpp

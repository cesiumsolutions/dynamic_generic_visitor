#ifndef CircumferenceVisitor_hpp
#define CircumferenceVisitor_hpp

#include <shapes/Circumference.hpp>
#include <shapes/ShapeVisitor.hpp>

class CircumferenceVisitor : public ShapeVisitor
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

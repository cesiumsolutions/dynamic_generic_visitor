#ifndef Circumference_hpp
#define Circumference_hpp

#include <shapes/Circle.hpp>
#include <shapes/Rectangle.hpp>

#include <boost/math/constants/constants.hpp>
namespace bmc = boost::math::constants;

float
circumference( Rectangle const & r )
{
  return 2 * r.width + 2 * r.height;
}

float
circumference( Circle const & c )
{
  return 2 * bmc::pi<float>() * c.radius;
}

#endif // Circumference_hpp

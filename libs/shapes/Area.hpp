#ifndef Area_hpp
#define Area_hpp

#include <shapes/Circle.hpp>
#include <shapes/Rectangle.hpp>

#include <boost/math/constants/constants.hpp>
namespace bmc = boost::math::constants;

float
area( Rectangle const & r )
{
  return r.width * r.height;
}

float
area( Circle const & c )
{
  return bmc::pi<float>() * c.radius * c.radius;
}

#endif // Area_hpp

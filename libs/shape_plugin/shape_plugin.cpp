#include "Triangle.hpp"

#include <visitor/DynamicVisitor.hpp>
#include <visitor/Visitable.hpp>

#include <iostream>
#include <memory>

#if WIN32
#  define EXPORT __declspec( dllexport )
#else
#  define EXPORT
#endif

using ShapeVisitor         = DynamicVisitor<float( float )>;
using VisitableShapePtr    = VisitableUPtr<ShapeVisitor>;
using VisitableShapePtrVec = std::vector<VisitableShapePtr>;

extern "C" {

EXPORT void
fillShapes( VisitableShapePtrVec * shapes )
{
  if ( shapes ) {
    shapes->push_back( makeUniqueVisitable<ShapeVisitor>(
        Triangle { { 3.0f, 4.0f, 5.0f } } ) );
  }
} // fillShapes

EXPORT void
fillAreaVisitor( ShapeVisitor * visitor )
{
  if ( visitor ) {
    visitor->addHandler<Triangle>(
        []( Triangle const & t, float s ) -> float { return s * area( t ); } );
  }
} // fillAreaVisitor

EXPORT void
fillCircumferenceVisitor( ShapeVisitor * visitor )
{
  if ( visitor ) {
    visitor->addHandler<Triangle>( []( Triangle const & t, float s ) -> float {
      return s * circumference( t );
    } );
  }
} // fillCircumferenceVisitor

} /* extern "C" */

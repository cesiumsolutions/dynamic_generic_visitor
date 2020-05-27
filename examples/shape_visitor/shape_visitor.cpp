#include <shapes/Area.hpp>
#include <shapes/Circumference.hpp>

#include <visitor/DynamicVisitor.hpp>
#include <visitor/Visitable.hpp>

#include <functional>
#include <iostream>
#include <vector>

struct NonShape
{
};

using ShapeVisitor         = DynamicVisitor<float( float )>;
using VisitableShapePtr    = VisitableUPtr<ShapeVisitor>;
using VisitableShapePtrVec = std::vector<VisitableShapePtr>;

ShapeVisitor makeAreaVisitor();
ShapeVisitor makeCircumferenceVisitor();

int
main( int, char ** )
{
  std::cout << "Running Generic DynamicVisitor with Signature Example\n\n";

  Rectangle rectangle { 2.0f, 3.0f };
  Circle    circle { 2.0f };
  NonShape  nonShape;
  float     scale = 2.0f;

  // Populate heterogeneous list of concrete Shape objects
  VisitableShapePtrVec shapes;
  shapes.push_back( makeUniqueVisitable<ShapeVisitor>( rectangle ) );
  shapes.push_back( makeUniqueVisitable<ShapeVisitor>( circle ) );
  // Note: Now we CAN insert a NonShape into the list of shapes. But if no
  // handler is registered for it, it will result in a runtime error/warning.
  shapes.push_back( makeUniqueVisitable<ShapeVisitor>( nonShape ) );

  // ==========================================================================
  std::cout << "Area Visitor:\n";

  // Visit the Shapes with the Area Visitor - checking valid accept result
  ShapeVisitor areaVisitor = makeAreaVisitor();
  float        totalArea   = 0.0f;
  for ( auto const & shape : shapes ) {
    auto result = shape->accept( areaVisitor, scale );
    if ( result ) {
      std::cout << "  - Area for shape [" << shape->typeInfo().name()
                << "]: " << *result << '\n';
      totalArea += *result;
    }
    else {
      std::cerr << "WARNING: Unrecognized type: " << shape->typeInfo().name()
                << '\n';
    }
  }
  float expectedArea = scale * area( rectangle ) + scale * area( circle );
  std::cout << "  Visited Area: " << totalArea << '\n'
            << "  Expected Area: " << expectedArea << '\n';

  // ==========================================================================
  std::cout << "\nCircumference Visitor:\n";

  // Visit the Shapes with the Circumference Visitor - checking valid result
  ShapeVisitor circumferenceVisitor = makeCircumferenceVisitor();
  float        totalCircumference   = 0.0f;
  for ( auto const & shape : shapes ) {
    auto result = shape->accept( circumferenceVisitor, scale );
    if ( result ) {
      std::cout << "  - Circumference for shape [" << shape->typeInfo().name()
                << "]: " << *result << '\n';
      totalCircumference += *result;
    }
    else {
      std::cerr << "WARNING: Unrecognized type: " << shape->typeInfo().name()
                << '\n';
    }
  }
  float expectedCircumference =
      scale * circumference( rectangle ) + scale * circumference( circle );
  std::cout << "  Visited Circumference: " << totalCircumference << '\n'
            << "  Expected Circumference: " << expectedCircumference << '\n';
}

ShapeVisitor
makeAreaVisitor()
{
  // Add the area functions as handlers to the DynamicVisitor
  ShapeVisitor areaVisitor;
  areaVisitor.addHandler<Rectangle>(
      []( Rectangle const & r, float s ) -> float { return s * area( r ); } );
  areaVisitor.addHandler<Circle>(
      []( Circle const & c, float s ) -> float { return s * area( c ); } );

  return areaVisitor;
} // makeAreaVisitor

ShapeVisitor
makeCircumferenceVisitor()
{
  // Add the circumference functions as handlers to the DynamicVisitor
  ShapeVisitor circumferenceVisitor;
  circumferenceVisitor.addHandler<Rectangle>(
      []( Rectangle const & r, float s ) -> float {
        return s * circumference( r );
      } );
  circumferenceVisitor.addHandler<Circle>(
      []( Circle const & c, float s ) -> float {
        return s * circumference( c );
      } );

  return circumferenceVisitor;
} // makeCircumferenceVisitor

#include <shapes/AreaVisitor.hpp>
#include <shapes/CircumferenceVisitor.hpp>

#include <visitor/StaticVisitor.hpp>
#include <visitor/Visitable.hpp>

#include <functional>
#include <iostream>
#include <vector>

struct NonShape
{
};

using ShapeVisitor         = StaticVisitor<float( float ), Rectangle, Circle>;
using VisitableShapePtr    = VisitableUPtr<ShapeVisitor>;
using VisitableShapePtrVec = std::vector<VisitableShapePtr>;

int
main( int, char ** )
{
  std::cout << "Running Generic StaticVisitor with Signature Example\n\n";

  Rectangle rectangle { 2.0f, 3.0f };
  Circle    circle { 2.0f };
  NonShape  nonShape;
  float     scale = 2.0f;

  // Populate heterogeneous list of concrete Shape objects
  VisitableShapePtrVec shapes;
  shapes.push_back( makeUniqueVisitable<ShapeVisitor>( rectangle ) );
  shapes.push_back( makeUniqueVisitable<ShapeVisitor>( circle ) );
  // Note: Compile error - can't insert a type that ShapeVisitor doesn't
  // recognize
  // shapes.push_back( makeUniqueVisitable<ShapeVisitor>( nonShape ) );
  (void)nonShape;

  // ==========================================================================
  std::cout << "Area Visitor:\n";

  // Visit the Shapes with the Area Visitor
  AreaVisitor areaVisitor;
  float       totalArea = 0.0f;
  for ( auto const & shape : shapes ) {
    float area = shape->accept( areaVisitor, scale );
    std::cout << "  - Area for shape[" << shape->typeInfo().name()
              << "]: " << area << '\n';
    totalArea += area;
  }
  float expectedArea = scale * area( rectangle ) + scale * area( circle );
  std::cout << "  Visited Area: " << totalArea << '\n'
            << "  Expected Area: " << expectedArea << '\n';

  // ==========================================================================
  std::cout << "\nCircumference Visitor:\n";

  // Visit the Shapes with the Circumference Visitor
  CircumferenceVisitor circumferenceVisitor;
  float                totalCircumference = 0.0f;
  for ( auto const & shape : shapes ) {
    float circumference = shape->accept( circumferenceVisitor, scale );
    std::cout << "  - Circumference for shape[" << shape->typeInfo().name()
              << "]: " << circumference << '\n';
    totalCircumference += circumference;
  }
  float expectedCircumference =
      scale * circumference( rectangle ) + scale * circumference( circle );
  std::cout << "  Visited Circumference: " << totalCircumference << '\n'
            << "  Expected Circumference: " << expectedCircumference << '\n';
}

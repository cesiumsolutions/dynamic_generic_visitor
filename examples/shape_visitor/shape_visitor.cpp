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

using ShapeVisitor         = StaticVisitor<Rectangle, Circle>;
using VisitableShapePtr    = VisitableUPtr<ShapeVisitor>;
using VisitableShapePtrVec = std::vector<VisitableShapePtr>;

int
main( int, char ** )
{
  std::cout << "Running Generic StaticVisitor Example\n\n";

  Rectangle rectangle { 2.0f, 3.0f };
  Circle    circle { 2.0f };
  NonShape  nonShape;

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
  for ( auto const & shape : shapes ) {
    std::cout << "  - Visiting shape[" << shape->typeInfo().name()
              << "]\n";
    shape->accept( areaVisitor );
  }
  float expectedArea = area( rectangle ) + area( circle );
  std::cout << "  Visited Area: " << areaVisitor.totalArea << '\n'
            << "  Expected Area: " << expectedArea << '\n';

  // ==========================================================================
  std::cout << "\nCircumference Visitor:\n";

  // Visit the Shapes with the Circumference Visitor
  CircumferenceVisitor circumferenceVisitor;
  for ( auto const & shape : shapes ) {
    std::cout << "  - Visiting shape[" << shape->typeInfo().name()
              << "]\n";
    shape->accept( circumferenceVisitor );
  }
  float expectedCircumference =
      circumference( rectangle ) + circumference( circle );
  std::cout << "  Visited Circumference: "
            << circumferenceVisitor.totalCircumference << '\n'
            << "  Expected Circumference: " << expectedCircumference << '\n';
}

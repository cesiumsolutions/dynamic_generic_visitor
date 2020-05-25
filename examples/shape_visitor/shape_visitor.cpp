#include <shapes/AreaVisitor.hpp>
#include <shapes/CircumferenceVisitor.hpp>

#include <functional>
#include <iostream>
#include <vector>

struct NonShape
{
};

using ShapeRef    = std::reference_wrapper<Shape>;
using ShapeRefVec = std::vector<ShapeRef>;

int
main( int, char ** )
{
  std::cout << "Running Classic Visitor example\n\n";

  Rectangle rectangle { 2.0f, 3.0f };
  Circle    circle { 2.0f };
  NonShape  nonShape;

  // Populate heterogeneous list of concrete Shape objects
  ShapeRefVec shapes;
  shapes.push_back( std::ref( rectangle ) );
  shapes.push_back( std::ref( circle ) );
  // Note: Compile error - can't insert a type that isn't derived from Shape
  // shapes.push_back( std::ref( nonShape ) );
  (void)nonShape;

  // ==========================================================================
  std::cout << "Area Visitor:\n";

  // Visit the Shapes with the Area Visitor
  AreaVisitor areaVisitor;
  for ( auto const & shape : shapes ) {
    std::cout << "  - Visiting shape[" << shape.get().typeInfo().name()
              << "]\n";
    shape.get().accept( areaVisitor );
  }
  float expectedArea = area( rectangle ) + area( circle );
  std::cout << "  Visited Area: " << areaVisitor.totalArea << '\n'
            << "  Expected Area: " << expectedArea << '\n';

  // ==========================================================================
  std::cout << "\nCircumference Visitor:\n";

  // Visit the Shapes with the Circumference Visitor
  CircumferenceVisitor circumferenceVisitor;
  for ( auto const & shape : shapes ) {
    std::cout << "  - Visiting shape[" << shape.get().typeInfo().name()
              << "]\n";
    shape.get().accept( circumferenceVisitor );
  }
  float expectedCircumference =
      circumference( rectangle ) + circumference( circle );
  std::cout << "  Visited Circumference: "
            << circumferenceVisitor.totalCircumference << '\n'
            << "  Expected Circumference: " << expectedCircumference << '\n';
}

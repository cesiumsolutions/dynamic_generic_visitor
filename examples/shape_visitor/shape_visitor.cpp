#include <shapes/Area.hpp>
#include <shapes/Circumference.hpp>

#include <visitor/DynamicVisitor.hpp>
#include <visitor/Visitable.hpp>

#include <boost/dll.hpp>
#include <boost/function.hpp>

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
void         loadPlugin( char const * const     pluginFilename,
                         VisitableShapePtrVec & shapes,
                         ShapeVisitor &         areaVisitor,
                         ShapeVisitor &         circumferenceVisitor );

boost::dll::shared_library sharedLib;

int
main( int argc, char ** argv )
{
  std::cout << "Running Generic DynamicVisitor with Plugin Example\n\n";

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

  ShapeVisitor areaVisitor          = makeAreaVisitor();
  ShapeVisitor circumferenceVisitor = makeCircumferenceVisitor();

  if ( argc >= 2 ) {
    loadPlugin( argv[1], shapes, areaVisitor, circumferenceVisitor );
  }

  // ==========================================================================
  std::cout << "Area Visitor:\n";

  // Visit the Shapes with the Area Visitor - checking valid accept result
  float totalArea = 0.0f;
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
  float expectedArea =
      scale * area( rectangle ) + scale * area( circle ) +
      scale * ( ( 3.0f * 4.0f ) / 2.0f ); // right triangle 3,4,5
  std::cout << "  Visited Area: " << totalArea << '\n'
            << "  Expected Area: " << expectedArea << '\n';

  // ==========================================================================
  std::cout << "\nCircumference Visitor:\n";

  // Visit the Shapes with the Circumference Visitor - checking valid result
  float totalCircumference = 0.0f;
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
      scale * circumference( rectangle ) + scale * circumference( circle ) +
      scale * ( 3.0f + 4.0f + 5.0f ); // Triangle{3,4,5}
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

void
loadPlugin( char const * const     pluginFilename,
            VisitableShapePtrVec & shapes,
            ShapeVisitor &         areaVisitor,
            ShapeVisitor &         circumferenceVisitor )
{
  try {
    std::cout << "Attempting to load Shape plugin from: " << pluginFilename
              << '\n';
    sharedLib.load( pluginFilename );

    using ShapeSig   = void( VisitableShapePtrVec * );
    using VisitorSig = void( ShapeVisitor * );

    // Request plugin to fill the Shapes vector
    boost::function<ShapeSig> fillShapes =
        sharedLib.get<ShapeSig>( "fillShapes" );
    if ( fillShapes ) {
      fillShapes( &shapes );
    }

    // Request plugin to add handlers to the Area Visitor
    boost::function<VisitorSig> fillAreaVisitor =
        sharedLib.get<VisitorSig>( "fillAreaVisitor" );
    if ( fillAreaVisitor ) {
      fillAreaVisitor( &areaVisitor );
    }

    // Request plugin to add handlers to the Circumference Visitor
    boost::function<VisitorSig> fillCircumferenceVisitor =
        sharedLib.get<VisitorSig>( "fillCircumferenceVisitor" );
    if ( fillCircumferenceVisitor ) {
      fillCircumferenceVisitor( &circumferenceVisitor );
    }
  }
  catch ( std::exception & e ) {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
  }
} // loadPlugin

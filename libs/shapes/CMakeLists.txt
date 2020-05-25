set( TARGET shapes )

set( HEADER_FILES
    Area.hpp
    AreaVisitor.hpp
    Circle.hpp
    Circumference.hpp
    CircumferenceVisitor.hpp
    Rectangle.hpp
    ShapeVisitor.hpp
    VisitableShape.hpp
)
source_group(
    \\ FILES
    ${HEADER_FILES}
)

add_custom_target(
    ${TARGET}
    SOURCES
        ${HEADER_FILES}
)

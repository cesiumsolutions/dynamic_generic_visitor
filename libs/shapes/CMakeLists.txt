set( TARGET shapes )

set( HEADER_FILES
    Area.hpp
    Circle.hpp
    Circumference.hpp
    Rectangle.hpp
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

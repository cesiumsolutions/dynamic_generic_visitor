set( TARGET shape_visitor )

set( SOURCE_FILES
    ${TARGET}.cpp
)
source_group(
    \\ FILES
    ${SOURCE_FILES}
)

add_executable(
    ${TARGET}
    ${SOURCE_FILES}
)

target_include_directories( ${TARGET} PRIVATE ${Boost_INCLUDE_DIR} . )
target_link_directories( ${TARGET} PRIVATE ${Boost_LIBRARY_DIRS} )
target_link_libraries( ${TARGET} ${Boost_LIBRARIES} )

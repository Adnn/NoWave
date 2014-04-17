project(NoWaveLib)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
#configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
#        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
#        @ONLY)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    ComponentActionController.h
    ComponentAddressee.h
    ComponentAlignment.h
    ComponentAnimationState.h
    ComponentBarrier.h
    ComponentDrugState.h
    ComponentInteraction.h
    ComponentKeyboard.h
    ComponentPlayer.h
    ComponentPosition.h
    ComponentScale.h
    ComponentSentence.h
    ComponentSpeed.h
    ComponentSprite.h
    ComponentTalkedTo.h
    ComponentTextList.h
    ComponentZBoundary.h
    ComponentZReorderable.h
    ComponentZord.h
    Factories.h
    InputSystem.h
    InteractionHandler.h
    NodeActor.h
    NodeAnimation.h
    NodeBarrier.h
    NodeControl.h
    NodeDepth.cpp
    NodeDepth.h
    NodeDisplay.h
    NodeInteraction.h
    NodeMove.h
    NodeMoveAnimation.h
    NodePlayerCollision.h
    NodeScaling.h
    NodeZBoundary.h
    NodeZOrder.h
    SystemAnimation.h
    SystemCollision.h
    SystemConversation.h
    SystemDepth.cpp
    SystemDepth.h
    SystemDisplay.h
    SystemDisplayDialog.h
    SystemInteraction.h
    SystemKeyboardControl.h
    SystemMove.h
    SystemMoveAnimation.h
    SystemScaling.h
    SystemZReorder.h
    app.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    ComponentActionController.cpp
    ComponentAnimationState.cpp
    ComponentBarrier.cpp
    ComponentInteraction.cpp
    ComponentKeyboard.cpp
    ComponentPlayer.cpp
    ComponentPosition.cpp
    ComponentScale.cpp
    ComponentSpeed.cpp
    ComponentSprite.cpp
    ComponentZBoundary.cpp
    ComponentZReorderable.cpp
    ComponentZord.cpp
    Factories.cpp
    InputSystem.cpp
    NodeActor.cpp
    NodeAnimation.cpp
    NodeBarrier.cpp
    NodeControl.cpp
    NodeDepth.cpp
    NodeDisplay.cpp
    NodeInteraction.cpp
    NodeMove.cpp
    NodeMoveAnimation.cpp
    NodePlayerCollision.cpp
    NodeScalable.cpp
    NodeScaling.cpp
    NodeZBoundary.cpp
    NodeZOrder.cpp
    SystemAnimation.cpp
    SystemCollision.cpp
    SystemConversation.cpp
    SystemDepth.cpp
    SystemDisplay.cpp
    SystemDisplayDialog.cpp
    SystemInteraction.cpp
    SystemKeyboardControl.cpp
    SystemMove.cpp
    SystemMoveAnimation.cpp
    SystemScaling.cpp
    SystemZReorder.cpp
    app.cpp
)


add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
)

include_directories(
    ${AuntEater_INCLUDE_DIR}
    ${Polycode_INCLUDE_DIR}
    ${Polycode_DEPENDENCIES_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${AuntEater_LIBRARIES}
    ${Polycode_LIBRARIES}
    ${Boost_LIBRARIES}
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
        PUBLIC_HEADER "${${PROJECT_NAME}_HEADERS}"
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

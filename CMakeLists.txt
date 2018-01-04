cmake_minimum_required(VERSION 2.8.3)
project(sema_ros)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nodelet
  message_generation
  std_msgs
)

add_message_files(FILES
  Values.msg
)

generate_messages(DEPENDENCIES
  std_msgs
)

catkin_package(CATKIN_DEPENDS
  roscpp
  nodelet
  message_runtime
  std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(libeapi SHARED IMPORTED)
set_target_properties(libeapi PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libEApi.so.1 )
add_library(libsema SHARED IMPORTED)
set_target_properties(libsema PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsema.so.3.0 )
add_library(libsemahwlinux SHARED IMPORTED)
set_target_properties(libsemahwlinux PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsema_hwlinux.so.1.5 )

add_library(${PROJECT_NAME}
  src/nodelet.cpp
  src/Sema.cpp
  src/Sema.h
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  libeapi
)

add_executable(${PROJECT_NAME}_node
  src/node.cpp
)
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
  libeapi
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
install(FILES nodelets.xml
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

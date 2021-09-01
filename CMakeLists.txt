project(GazeboOPCUA)
cmake_minimum_required(VERSION 3.7.0)
set(sdk_home $ENV{UASDK_BASE_DIR})
#/home/l1va/pywork/sdk
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${sdk_home}cmake/${CMAKE_MODULE_PATH})

#message(STATUS $ENV{UASDK_BASE_DIR} )
#message(STATUS ${sdk_home} )

# Use SDK CMake stuff
include(MessageUtils)
include(InstallPDBFiles)
include(InstallIfNewer)
include(ConfigureCompiler)
include(ConfigureUaStack)
include(ConfigureCppSdk)
find_package(UaLibXml2)
find_package(gazebo REQUIRED)


add_library(GazeboOPCUA SHARED src/objects/intern_instancefactory_internship.cpp src/objects/intern_jointtype.cpp
src/objects/intern_jointtypebase.cpp src/objects/intern_manipulatortype.cpp src/objects/intern_positiontype.cpp
src/objects/intern_positiontypebase.cpp src/objects/intern_nodemanagerinternship.cpp
src/objects/intern_nodemanagerinternshipbase.cpp src/objects/intern_manipulatortypebase.cpp
src/joint_state_publisher.h src/main.cpp ${sdk_home}examples/utilities/shutdown.cpp
${sdk_home}examples/utilities/opcserver.cpp)

#add_executable(Minimal src/objects/intern_instancefactory_internship.cpp src/objects/intern_jointtype.cpp src/objects/intern_jointtypebase.cpp src/objects/intern_manipulatortype.cpp src/objects/intern_positiontype.cpp src/objects/intern_positiontypebase.cpp src/objects/intern_nodemanagerinternship.cpp src/objects/intern_nodemanagerinternshipbase.cpp src/objects/intern_manipulatortypebase.cpp src/joint_state_publisher.h src/main.cpp /home/laggy/Desktop/sdk/examples/utilities/shutdown.cpp /home/laggy/Desktop/sdk/examples/utilities/opcserver.cpp)
include_directories(${GAZEBO_INCLUDE_DIRS})


include_directories(${sdk_home}examples/utilities)


add_library(uacoremodule INTERFACE)

target_include_directories(uacoremodule
        INTERFACE
        ${UACOREMODULE_INCLUDE}
        )

target_link_directories(uacoremodule
        INTERFACE
        ${UA_LIB_DIR}
)

target_link_libraries(uacoremodule
        INTERFACE
        ${UACOREMODULE_LIBRARY}
)

add_library(uamodule INTERFACE)
target_include_directories(uamodule
        INTERFACE
        ${UAMODULE_INCLUDE}
        )

target_link_directories(uamodule
        INTERFACE
        ${UA_LIB_DIR}
        )

target_link_libraries(uamodule
        INTERFACE
        ${UAMODULE_LIBRARY}
        )


add_library(uabase INTERFACE)
target_include_directories(uabase
        INTERFACE
        ${UABASE_INCLUDE}
        )

target_link_directories(uabase
        INTERFACE
        ${UA_LIB_DIR}
        )

target_link_libraries(uabase
        INTERFACE
        ${UABASE_LIBRARY}
        )

add_library(uastack INTERFACE)
target_include_directories(uastack
        INTERFACE
        ${UASTACK_INCLUDE}
        )

target_link_directories(uastack
        INTERFACE
        ${UA_LIB_DIR}
        )

target_link_libraries(uastack
        INTERFACE
        ${UASTACK_LIBRARY}
        )

#add_executable(Minimal src/objects/intern_instancefactory_internship.cpp src/objects/intern_jointtype.cpp src/objects/intern_jointtypebase.cpp src/objects/intern_manipulatortype.cpp src/objects/intern_positiontype.cpp src/objects/intern_positiontypebase.cpp src/objects/intern_nodemanagerinternship.cpp src/objects/intern_nodemanagerinternshipbase.cpp src/objects/intern_manipulatortypebase.cpp src/joint_state_publisher.h src/customnodemanager.h src/customnodemanager.cpp src/typeids.h src/manipulatorobject.h src/JointObject.h src/manipulatorobject.cpp src/main.cpp src/positionobject.cpp src/positionobject.h src/JointObject.cpp /home/laggy/Desktop/sdk/examples/utilities/shutdown.cpp /home/laggy/Desktop/sdk/examples/utilities/opcserver.cpp)
include_directories(src/objects)

#add_executable(src/objects/intern_jointtype.cpp src/objects/intern_jointtypebase.cpp src/objects/intern_manipulatortype.cpp src/objects/intern_positiontype.cpp src/objects/intern_positiontypebase.cpp src/objects/intern_nodemanagerinternship.cpp src/objects/intern_nodemanagerinternshipbase.cpp src/objects/intern_manipulatortypebase.cpp)
#include_directories(/home/laggy/Desktop/sdk/examples/utilities)
target_link_libraries(GazeboOPCUA
        PUBLIC
        uamodule
        uacoremodule
        uastack
        ${UAPKI_LIBRARY}
        uabase
        ${UASERVERCPP_LIBRARY}
        ${UAXMLPARSER_INCLUDE}
        ${UAXML_LIBRARY}
        ${LIBXML2_LIBRARIES}
        ${UAMODULE_LIBRARY}
        ${UACOREMODULE_LIBRARY}
        ${UAPKI_LIBRARY}
        ${UABASE_LIBRARY}
        ${OPENSSL_LIBRARIES}
        ${SYSTEM_LIBS}
        pthread
        )

target_include_directories(GazeboOPCUA
        PUBLIC
        ${UAPKI_INCLUDE}
        ${UAXMLPARSER_INCLUDE}
        )



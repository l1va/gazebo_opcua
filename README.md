# gazebo_opcua
Gazebo OPC UA integration

Currently supports creating manipulator/positon/velocity objects 
and simple set/read of values over OPC UA. Server is notified 
when updating one of the values. WIP: PubSub integration.

Was built for Ubuntu 18.04, Gazebo 9, OPC UA bundle v1.7.4. Might work with other envs.

![Snippet](images/example.png)


## Preparation
1. Download C++ based OPC UA Client/Server SDK from [HERE](https://www.unified-automation.com/downloads/opc-ua-development.html) (you need login at first)
2. Extract and set `export UASDK_BASE_DIR=PATH_TO_DOWNLOADED_SDK/sdk/`, 
better to add it in bashrc file

## Run
1. Go to the root of the project
2. To find the plugin: 
`export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:./build`
3. To find model files:
`export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:./models` 
4. `gazebo iiwa14.world`
Or better (paused and verbose): `gazebo -u iiwa14.world --verbose`

The simplest way to change value - download [UA Expert](https://www.unified-automation.com/downloads/opc-ua-clients.html)  
Run gazebo at first and UaExpert will find connection automatically.

Changes to values can be caught in the intern_nodemanagerinternship.cpp in the 
method 'beforeSetAttributeValue'

## Build
Build with debug flag because of license
`cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug && make && cd ..`

### Repeat
To repeat the same from scratch you need to create a tree of types in 
the [UaModeler](https://www.unified-automation.com/downloads/opc-ua-development) and generate
code for objects
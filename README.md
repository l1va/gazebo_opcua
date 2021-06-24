# building
Requires ```Unified-Automation's PubSub Sdk```[https://www.unified-automation.com/products/pubsub-sdk/c-ua-pubsub-sdk.html] 

After building the sdk, make sure to replace paths in CMakeLists.txt to your paths. (A little messy)

Then just run ```make```

# gazebo_opcua
Gazebo OPC UA integration

Currently supports creating manipulator/positon/velocity objects and simple set/read of values over OPC UA. Server is notified when updating one of the values. 
WIP: PubSub integration.

## Run
```gazebo iiwa14.world```

Or better (paused and verbose):

```gazebo -u iiwa14.world --verbose```

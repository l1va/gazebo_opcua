#include <intern_jointtype.h>
#include "opcserver.h"
#include "uaplatformlayer.h"
#include "uathread.h"
#include "xmldocument.h"
#include "shutdown.h"
#include "intern_datatypes.h"
#include "intern_identifiers.h"
#include "intern_manipulatortype.h"
#include "intern_manipulatortypebase.h"
#include "intern_nodemanagerinternship.h"

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

using namespace gazebo;
using namespace std;


int OpcServerMain(std::vector<physics::JointPtr> joints)
{
    cout << "STARTING" << endl;
    UaXmlDocument::initParser();
    int ret = 0;
    ret = UaPlatformLayer::init();

    if ( ret == 0 ) {
        cout << "OPC SERVER INIT SUCCESS" << endl;

        char* sdkDir = getenv( "UASDK_BASE_DIR" );
        UaString sConfigFileName = UaString("%1/bin/ServerConfig.xml").arg(sdkDir);

        try {
            OpcServer *pServer = new OpcServer;
            cout << pServer->setServerConfig(sConfigFileName, sdkDir) << endl; //sdkDir without 'bin' subdir?

            intern::NodeManagerinternship *pNodeManager = new intern::NodeManagerinternship(false);
            cout << pServer->addNodeManager(pNodeManager) << endl;

            // Start server object
            ret = pServer->start();
            if (ret == 0) {
                std::cout << "SERVER STARTED\n" << std::endl;

                printf("***************************************************\n");
                printf(" Press %s to shut down server\n", SHUTDOWN_SEQUENCE);
                printf("***************************************************\n");

                intern::ManipulatorType *manipulator1 = new intern::ManipulatorType(
                        UaNodeId("Manipulator1", pNodeManager->getNameSpaceIndex()),"Manipulator1",
                        pNodeManager->getNameSpaceIndex(), pNodeManager);
                pNodeManager->addNodeAndReference(OpcUaId_ObjectsFolder, manipulator1, OpcUaId_Organizes);

                for (auto x : joints) {
                    intern::JointType *joint1 = new intern::JointType(
                            UaNodeId(UaString(x->GetName().c_str()), pNodeManager->getNameSpaceIndex()),
                            x->GetName().c_str(), pNodeManager->getNameSpaceIndex(), pNodeManager);
                    pNodeManager->addNodeAndReference(
                            UaNodeId(UaString("%1.Joints").arg(manipulator1->nodeId().toString()),
                                     pNodeManager->getNameSpaceIndex()), joint1, OpcUaId_HasComponent);

                           //joint1->getPosition();
                }

                // Wait for user command to terminate the server thread.
                while (ShutDownFlag() == 0) {
                    UaThread::msleep(1000);
                }
                printf("***************************************************\n");
                printf(" Shutting down server\n");
                printf("***************************************************\n");

                pServer->stop(3, UaLocalizedText("", "User shutdown"));

            }else {
                cout << "FAILED TO START OPC SERVER" << ret << endl;
            }
            delete pServer;
            pServer = NULL;
        }
        catch(const std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    UaPlatformLayer::cleanup();
    UaXmlDocument::cleanupParser();
    return ret;
}

namespace gazebo {
    class GazeboOPCUAPlugin : public ModelPlugin {
    public:
        void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf){
            //RegisterSignalHandler();
            std::cout << "[Entry Point]::Load() OPC UA\n";

            std::vector<physics::JointPtr> joints = _parent->GetJoints();
            thread t1(OpcServerMain, joints);
            t1.detach();
        }
    };
    GZ_REGISTER_MODEL_PLUGIN (GazeboOPCUAPlugin)
}

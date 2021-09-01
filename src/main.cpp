#include <intern_jointtype.h>
#include "joint_state_publisher.h"
#include "opcserver.h"
#include "uaplatformlayer.h"
#include "uathread.h"
#if SUPPORT_XML_PARSER
#include "xmldocument.h"
#endif
#include "shutdown.h"
#include "intern_datatypes.h"
#include "intern_identifiers.h"
#include "intern_manipulatortype.h"
#include "intern_manipulatortypebase.h"
#include "intern_nodemanagerinternship.h"
//TODO: REFACTORME!

using namespace gazebo;
using namespace std;
int OpcServerMain(std::vector<physics::JointPtr> joints)
{
    int ret = 0;
    cout << "ATTEMPTING" << endl;
    //- Initialize the environment --------------
#if SUPPORT_XML_PARSER
    // Initialize the XML Parser
    UaXmlDocument::initParser();
#endif
    // Initialize the UA Stack platform layer
    ret = UaPlatformLayer::init();
    //-------------------------------------------

    if ( ret == 0 ) {
        cout << "OPC SERVER INIT SUCCESS" << endl;

        // Create configuration file name
        UaString sConfigFileName("/home/l1va/pywork/gazebo_opcua/build");

#if SUPPORT_XML_PARSER
        sConfigFileName += "/ServerConfig.xml";
#else
        sConfigFileName += "/ServerConfig.ini";
#endif
        try {
            OpcServer *pServer = new OpcServer;
            cout << pServer->setServerConfig(sConfigFileName, "/home/l1va/pywork/gazebo_opcua/build") << endl;
            cout << sConfigFileName.toUtf8() << endl;

            intern::NodeManagerinternship *pNodeManager = new intern::NodeManagerinternship(false);
            cout << pServer->addNodeManager(pNodeManager) << endl;

            // Start server object
            ret = pServer->start();


            if (ret != 0) {
                cout << "FAILED TO START OPC SERVER" << endl << ret << endl;
                delete pServer;
                pServer = 0;
            }
            //-------------------------------------------

            if (ret == 0) {
                printf("***************************************************\n");
                printf(" Press %s to shut down server\n", SHUTDOWN_SEQUENCE);
                printf("***************************************************\n");

                intern::ManipulatorType *manipulator1 = new intern::ManipulatorType(
                        UaNodeId("Manipulator1", pNodeManager->getNameSpaceIndex()),
                        "Manipulator1",
                        pNodeManager->getNameSpaceIndex(),
                        pNodeManager);
                pNodeManager->addNodeAndReference(OpcUaId_ObjectsFolder, manipulator1, OpcUaId_Organizes);

                std::cout << "SERVER STARTED\n" << std::endl;
                for (auto x : joints) {
                    intern::JointType *joint1 = new intern::JointType(
                            UaNodeId(UaString(x->GetName().c_str()), pNodeManager->getNameSpaceIndex()),
                            x->GetName().c_str(),
                            pNodeManager->getNameSpaceIndex(),
                            pNodeManager);
                    pNodeManager->addNodeAndReference(
                            UaNodeId(UaString("%1.Joints").arg(manipulator1->nodeId().toString()),
                                     pNodeManager->getNameSpaceIndex()), joint1,
                            OpcUaId_HasComponent);

                           joint1->getPosition();
                }

                // Wait for user command to terminate the server thread.
                while (ShutDownFlag() == 0) {
                    UaThread::msleep(1000);
                }
                printf("***************************************************\n");
                printf(" Shutting down server\n");
                printf("***************************************************\n");

                pServer->stop(3, UaLocalizedText("", "User shutdown"));
                delete pServer;
                pServer = NULL;
                //-------------------------------------------
            }
        }
        catch(const std::exception& e)
        {
            cout << e.what() << endl;
        }
    }

    //- Clean up the environment --------------
    // Clean up the UA Stack platform layer
    UaPlatformLayer::cleanup();
#if SUPPORT_XML_PARSER
    // Clean up the XML Parser
    UaXmlDocument::cleanupParser();
#endif
    //-------------------------------------------

    return ret;
}

JointStatePublisher::JointStatePublisher() {}
JointStatePublisher::~JointStatePublisher()
{
    if (this->nats_conn) {
        natsConnection_Destroy(this->nats_conn);
    }
}

typedef struct
{
    physics::JointControllerPtr jointController;
    std::string name;
}ParamStruct;

//TODO: Replace with custom msg handler
static void OnMsg(natsConnection *nc, natsSubscription *sub, natsMsg *msg, void *closure)
{
    std::cout << "Received msg\n";
    auto x = json::parse(natsMsg_GetData(msg));
    //std::cout << "1: \n" ;
    ParamStruct* p = (ParamStruct*) closure;
    //std::cout << "2: \n" ;
    //physics::JointControllerPtr joint = p->joint;
    //std::cout << "3: \n" ;
    std::cout << p->name << "4: \n" ;
    p->jointController->SetPositionTarget(p->name,x["Value"]);
    //free(closure);
    // Don't forget to destroy the message!
    natsMsg_Destroy(msg);
    //std::cout << "5: \n" ;
}

void JointStatePublisher::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    RegisterSignalHandler();

    std::cout << "[Entry Point]::Load() OPC UA\n";
    this->parent_ = _parent;
    this->world_ = _parent->GetWorld();

    // publish topic
    std::string robotNS = parent_->GetName();
    if (_sdf->HasElement("robotNamespace")) {
        robotNS = _sdf->GetElement("robotNamespace")->Get<std::string>();
        if (robotNS.empty()) robotNS = parent_->GetName();
    }

    this->publish_topic = robotNS + "/joint_states";

    std::cout << "Publish topic: " << this->publish_topic << "\n";

    // update rate
    this->update_rate_ = 1000.0;
    if (_sdf->HasElement("updateRate")) {
        this->update_rate_ = _sdf->GetElement("updateRate")->Get<double>();
    }
    if (this->update_rate_ > 0.0) {
        this->update_period_ = 1.0 / this->update_rate_;
    } else {
        this->update_period_ = 0.0;
    }
    this->last_update_time_ = this->world_->SimTime();

#if SUPPORT_XML_PARSER
    // Initialize the XML Parser
    UaXmlDocument::initParser();
#endif

    int UA_RET = UaPlatformLayer::init();
    auto szAppPath = getAppPath();

    if(UA_RET == 0)
    {
        auto sConfigFileName(szAppPath);
    }

    // Nats connect
    //natsStatus s;
    //s = natsConnection_ConnectTo(&this->nats_conn, NATS_DEFAULT_URL); //TODO: default url

    // bind on update
    //this->updateConnection = event::Events::ConnectWorldUpdateBegin(
            //std::bind(&JointStatePublisher::OnUpdate, this));

    physics::JointControllerPtr jc = this->parent_->GetJointController();
    std::map<std::string, physics::JointPtr> mjc = jc->GetJoints();
    for( auto const& [key, val] : mjc )
    {
        std::cout << key         // string (key)
                  << ':'
                  << val->GetName()        // string's value
                  << std::endl ;
    }

    std::string name = "";
    std::vector<physics::JointPtr> joints = this->parent_->GetJoints();
    for (int i = 0; i < joints.size(); i++) {
        name = joints[i]-> GetName();
        natsSubscription    *sub = NULL;
        std::cout << "Name: " << joints[i]->GetName() << "\n";
        std::cout << "Scoped Name: " << joints[i]->GetScopedName() << "\n";
        //natsConnection_Subscribe(&sub, this->nats_conn, (robotNS+"/"+ name+"/command").c_str(),OnMsg , &(joints[i]));
        ParamStruct* p = new ParamStruct();
        //std::cout << "Crea: ";
        p->jointController = jc;
        //std::cout << "set1: ";
        p->name = joints[i]->GetScopedName();
        //std::cout << "set2: ";
        //std::tuple<physics::JointPtr, std::string> param = std::make_tuple(joints[i].get(), joints[i]->GetScopedName());
        //natsConnection_Subscribe(&sub, this->nats_conn, (robotNS+"/"+ name+"/command").c_str(),OnMsg , p);

        gazebo::common::PID pid = gazebo::common::PID(1000,1,0.1,100,0.0,-1.0,0.0);
        jc->SetPositionPID(joints[i]-> GetScopedName(), pid);
    }
    jc->Update();
    thread t1(OpcServerMain, joints);
    t1.detach();
}

//No longer needed?
void JointStatePublisher::OnUpdate()
{

    std::cout << "Updated\n";
    common::Time current_time = this->world_->SimTime();
    if (current_time < this->last_update_time_)
    {
        this->last_update_time_ = current_time;
    }

    double seconds_since_last_update = (current_time - last_update_time_).Double();

    if (seconds_since_last_update > this->update_period_) {
        publishJointStates();
        this->last_update_time_+= common::Time(update_period_);
    }
}

void JointStatePublisher::publishJointStates()
{
    std::vector<physics::JointPtr> joints = this->parent_->GetJoints();

    std::vector<std::string> names ;
    std::vector<double> poss ;
    std::vector<double> vels ;
    for (int i = 0; i < joints.size(); i++) {
        names.push_back(joints[i]->GetName());
        poss.push_back(joints[i]->Position(0));
        vels.push_back(joints[i]->GetVelocity(0));
    }

    json obj;
    obj["name"] = names;
    obj["position"] = poss;
    obj["velocity"] = vels;

    std::string msg = obj.dump();

    //natsStatus s = natsConnection_PublishString(this->nats_conn,
           //                                     this->publish_topic.c_str(), msg.c_str());

    //std::cout << "Publish msg: Done." << "\n";
}

// DBG
#ifdef _WIN32_WCE
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPWSTR, int)
#else
int main(int, char*[])
#endif
{
    int ret = 0;

    RegisterSignalHandler();

    // Extract application path
    char* pszAppPath = getAppPath();

    //-------------------------------------------
    // Call the OPC server main method
    ret = OpcServerMain(std::vector<physics::JointPtr>());
    //-------------------------------------------

    if ( pszAppPath ) delete [] pszAppPath;

    return ret;
}

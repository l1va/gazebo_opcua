#include "intern_nodemanagerinternship.h"
#include "nodemanagerroot.h"
#include "intern_manipulatortype.h"
#include "intern_jointtype.h"
#include "iostream"

namespace intern {

    NodeManagerinternship::NodeManagerinternship(
            OpcUa_Boolean firesEvents,
            OpcUa_Int32 nHashTableSize)


            : NodeManagerinternshipBase(firesEvents, nHashTableSize) {
    }

    NodeManagerinternship::~NodeManagerinternship() {
    }

    UaStatus NodeManagerinternship::afterStartUp() {

        UaStatus ret = NodeManagerinternshipBase::afterStartUp();


        return ret;
    }


    UaStatus NodeManagerinternship::beforeShutDown() {
        UaStatus ret;
        return ret;
    }

    OpcUa_Boolean
    NodeManagerinternship::beforeSetAttributeValue(Session *pSession, UaNode *pNode, OpcUa_Int32 attributeId,
                                                   const UaDataValue &dataValue, OpcUa_Boolean &checkWriteMask) {
        std::cout << "Update Value" << std::endl;
        std::cout << pNode->nodeId().toString().toUtf8() << std::endl;
        std::cout << dataValue.value()->Value.Double << std::endl;
    }
}

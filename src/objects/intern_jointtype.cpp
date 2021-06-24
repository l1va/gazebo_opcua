#include "intern_jointtype.h"

namespace intern {

    JointType::JointType(
            const UaNodeId &nodeId,
            UaObject *pInstanceDeclarationObject,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : JointTypeBase(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
    }

    JointType::JointType(
            const UaNodeId &nodeId,
            const UaString &name,
            OpcUa_UInt16 browseNameNameSpaceIndex,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : JointTypeBase(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
    }

    JointType::JointType(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : JointTypeBase(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
    }

    JointType::~JointType() {
    }

    void JointType::createTypes() {

        JointTypeBase::createTypes();


    }

    void JointType::clearStaticMembers() {


        JointTypeBase::clearStaticMembers();
    }

}


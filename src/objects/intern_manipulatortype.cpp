#include "intern_manipulatortype.h"

namespace intern {

    ManipulatorType::ManipulatorType(
            const UaNodeId &nodeId,
            UaObject *pInstanceDeclarationObject,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : ManipulatorTypeBase(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
    }

    ManipulatorType::ManipulatorType(
            const UaNodeId &nodeId,
            const UaString &name,
            OpcUa_UInt16 browseNameNameSpaceIndex,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : ManipulatorTypeBase(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
    }

    ManipulatorType::ManipulatorType(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : ManipulatorTypeBase(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
    }


    ManipulatorType::~ManipulatorType() {
    }

    void ManipulatorType::createTypes() {

        ManipulatorTypeBase::createTypes();


    }

    void ManipulatorType::clearStaticMembers() {

        ManipulatorTypeBase::clearStaticMembers();
    }

}


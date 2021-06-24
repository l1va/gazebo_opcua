#include "intern_positiontype.h"

namespace intern {

    PositionType::PositionType(
            const UaNodeId &nodeId,
            UaObject *pInstanceDeclarationObject,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : PositionTypeBase(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
    }

    PositionType::PositionType(
            const UaNodeId &nodeId,
            const UaString &name,
            OpcUa_UInt16 browseNameNameSpaceIndex,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : PositionTypeBase(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
    }

    PositionType::PositionType(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : PositionTypeBase(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
    }

    PositionType::~PositionType() {
    }

    void PositionType::createTypes() {

        PositionTypeBase::createTypes();

    }

    void PositionType::clearStaticMembers() {


        PositionTypeBase::clearStaticMembers();
    }

}


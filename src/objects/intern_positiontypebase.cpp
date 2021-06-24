#include "intern_positiontypebase.h"
#include "intern_positiontype.h"
#include "uagenericnodes.h"
#include "nodemanagerroot.h"
#include "methodhandleuanode.h"
#include "intern_nodemanagerinternship.h"

#include "instancefactory.h"
#include "opcua_extensionobject.h"
namespace intern {

    bool PositionTypeBase::s_typeNodesCreated = false;
    OpcUa::BaseDataVariableType *PositionTypeBase::s_pX = NULL;
    OpcUa::BaseDataVariableType *PositionTypeBase::s_pY = NULL;
    OpcUa::BaseDataVariableType *PositionTypeBase::s_pZ = NULL;

    PositionTypeBase::PositionTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject,
                                       NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
        initialize();
    }

    PositionTypeBase::PositionTypeBase(const UaNodeId &nodeId, const UaString &name,
                                       OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig *pNodeConfig,
                                       UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
        initialize();
    }

    PositionTypeBase::PositionTypeBase(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
        UaStatus addStatus;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pX = NULL;
        m_pY = NULL;
        m_pZ = NULL;

        std::list<UaBase::BaseNode *> lstReferencedNodes = pBaseNode->hierarchicallyReferencedNodes();
        for (std::list<UaBase::BaseNode *>::const_iterator it = lstReferencedNodes.begin();
             it != lstReferencedNodes.end(); it++) {
            UaBase::BaseNode *pChild = *it;
            if (pChild->browseName() == UaQualifiedName("X", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pX) {
                    m_pX = (OpcUa::BaseDataVariableType *) pFactory->createVariable((UaBase::Variable *) pChild,
                                                                                    pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pX, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Variable *) pChild)->modellingRuleId().isNull()) {
                        m_pX->setModellingRuleId(((UaBase::Variable *) pChild)->modellingRuleId());
                    }
                }
            } else if (pChild->browseName() ==
                       UaQualifiedName("Y", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pY) {
                    m_pY = (OpcUa::BaseDataVariableType *) pFactory->createVariable((UaBase::Variable *) pChild,
                                                                                    pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pY, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Variable *) pChild)->modellingRuleId().isNull()) {
                        m_pY->setModellingRuleId(((UaBase::Variable *) pChild)->modellingRuleId());
                    }
                }
            } else if (pChild->browseName() ==
                       UaQualifiedName("Z", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pZ) {
                    m_pZ = (OpcUa::BaseDataVariableType *) pFactory->createVariable((UaBase::Variable *) pChild,
                                                                                    pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pZ, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Variable *) pChild)->modellingRuleId().isNull()) {
                        m_pZ->setModellingRuleId(((UaBase::Variable *) pChild)->modellingRuleId());
                    }
                }
            }
        }
        UA_ASSERT(m_pX);
        UA_ASSERT(m_pY);
        UA_ASSERT(m_pZ);
    }

    void PositionTypeBase::initialize() {
        UaStatus addStatus;
        UaVariant defaultValue;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pX = new OpcUa::BaseDataVariableType(this, s_pX, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pX, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());


        m_pY = new OpcUa::BaseDataVariableType(this, s_pY, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pY, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());


        m_pZ = new OpcUa::BaseDataVariableType(this, s_pZ, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pZ, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());


    }

    PositionTypeBase::~PositionTypeBase() {
    }

    void PositionTypeBase::createTypes() {
        if (s_typeNodesCreated == false) {
            s_typeNodesCreated = true;

            UaStatus addStatus;
            UaVariant defaultValue;
            NodeManagerRoot *pNodeManagerRoot = NodeManagerRoot::CreateRootNodeManager();
            OpcUa_Int16 nsTypeIdx = NodeManagerinternship::getTypeNamespace();
            OpcUa_Int16 nsSuperTypeIdx = NodeManagerRoot::getTypeNamespace();
            NodeManagerConfig *pTypeNodeConfig = pNodeManagerRoot->getNodeManagerByNamespace(
                    nsTypeIdx)->getNodeManagerConfig();

            OpcUa::GenericObjectType *pObjectType;
            pObjectType = new OpcUa::GenericObjectType(
                    UaNodeId(internId_PositionType, nsTypeIdx),
                    UaQualifiedName("PositionType", nsTypeIdx),
                    UaLocalizedText("", "PositionType"),
                    UaLocalizedText("", ""),
                    OpcUa_False,
                    &PositionType::clearStaticMembers);
            pTypeNodeConfig->addNodeAndReference(UaNodeId(OpcUaId_BaseObjectType, nsSuperTypeIdx), pObjectType,
                                                 OpcUaId_HasSubtype);


            defaultValue.setDouble(0.0);
            s_pX = new OpcUa::BaseDataVariableType(UaNodeId(internId_PositionType_X, nsTypeIdx), "X",
                                                   intern::NodeManagerinternship::getTypeNamespace(), defaultValue, 3,
                                                   pTypeNodeConfig);
            s_pX->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            s_pX->setValueRank(-1);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pX, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());


            defaultValue.setDouble(0.0);
            s_pY = new OpcUa::BaseDataVariableType(UaNodeId(internId_PositionType_Y, nsTypeIdx), "Y",
                                                   intern::NodeManagerinternship::getTypeNamespace(), defaultValue, 3,
                                                   pTypeNodeConfig);
            s_pY->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            s_pY->setValueRank(-1);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pY, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());


            defaultValue.setDouble(0.0);
            s_pZ = new OpcUa::BaseDataVariableType(UaNodeId(internId_PositionType_Z, nsTypeIdx), "Z",
                                                   intern::NodeManagerinternship::getTypeNamespace(), defaultValue, 3,
                                                   pTypeNodeConfig);
            s_pZ->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            s_pZ->setValueRank(-1);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pZ, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());

        }
    }

    void PositionTypeBase::clearStaticMembers() {
        s_typeNodesCreated = false;

        s_pX = NULL;
        s_pY = NULL;
        s_pZ = NULL;
    }

    UaNodeId PositionTypeBase::typeDefinitionId() const {
        UaNodeId ret(internId_PositionType, NodeManagerinternship::getTypeNamespace());
        return ret;
    }

    void PositionTypeBase::setX(OpcUa_Double X) {
        UaVariant value;
        value.setDouble(X);
        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_True, OpcUa_True);
        m_pX->setValue(NULL, dataValue, OpcUa_False);
    }

    OpcUa_Double PositionTypeBase::getX() const {
        UaVariant defaultValue;
        OpcUa_Double ret = 0;
        UaDataValue dataValue(m_pX->value(NULL));
        defaultValue = *dataValue.value();
        defaultValue.toDouble(ret);
        return ret;
    }

    void PositionTypeBase::setY(OpcUa_Double Y) {
        UaVariant value;
        value.setDouble(Y);
        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_True, OpcUa_True);
        m_pY->setValue(NULL, dataValue, OpcUa_False);
    }

    OpcUa_Double PositionTypeBase::getY() const {
        UaVariant defaultValue;
        OpcUa_Double ret = 0;
        UaDataValue dataValue(m_pY->value(NULL));
        defaultValue = *dataValue.value();
        defaultValue.toDouble(ret);
        return ret;
    }

    void PositionTypeBase::setZ(OpcUa_Double Z) {
        UaVariant value;
        value.setDouble(Z);
        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_True, OpcUa_True);
        m_pZ->setValue(NULL, dataValue, OpcUa_False);
    }

    OpcUa_Double PositionTypeBase::getZ() const {
        UaVariant defaultValue;
        OpcUa_Double ret = 0;
        UaDataValue dataValue(m_pZ->value(NULL));
        defaultValue = *dataValue.value();
        defaultValue.toDouble(ret);
        return ret;
    }

    OpcUa::BaseDataVariableType *PositionTypeBase::getXNode() {
        return m_pX;
    }

    const OpcUa::BaseDataVariableType *PositionTypeBase::getXNode() const {
        return m_pX;
    }

    OpcUa::BaseDataVariableType *PositionTypeBase::getYNode() {
        return m_pY;
    }

    const OpcUa::BaseDataVariableType *PositionTypeBase::getYNode() const {
        return m_pY;
    }

    OpcUa::BaseDataVariableType *PositionTypeBase::getZNode() {
        return m_pZ;
    }

    const OpcUa::BaseDataVariableType *PositionTypeBase::getZNode() const {
        return m_pZ;
    }


}



#include "intern_manipulatortypebase.h"
#include "intern_manipulatortype.h"
#include "uagenericnodes.h"
#include "nodemanagerroot.h"
#include "methodhandleuanode.h"
#include "intern_nodemanagerinternship.h"

#include "instancefactory.h"
#include "opcua_extensionobject.h"
namespace intern {

    bool ManipulatorTypeBase::s_typeNodesCreated = false;
    OpcUa::FolderType *ManipulatorTypeBase::s_pJoints = NULL;
    OpcUa::BaseDataVariableType *ManipulatorTypeBase::s_pName = NULL;

    ManipulatorTypeBase::ManipulatorTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject,
                                             NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
        initialize();
    }

    ManipulatorTypeBase::ManipulatorTypeBase(const UaNodeId &nodeId, const UaString &name,
                                             OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig *pNodeConfig,
                                             UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
        initialize();
    }

    ManipulatorTypeBase::ManipulatorTypeBase(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
        UaStatus addStatus;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pJoints = NULL;
        m_pName = NULL;

        std::list<UaBase::BaseNode *> lstReferencedNodes = pBaseNode->hierarchicallyReferencedNodes();
        for (std::list<UaBase::BaseNode *>::const_iterator it = lstReferencedNodes.begin();
             it != lstReferencedNodes.end(); it++) {
            UaBase::BaseNode *pChild = *it;
            if (pChild->browseName() == UaQualifiedName("Name", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pName) {
                    m_pName = (OpcUa::BaseDataVariableType *) pFactory->createVariable((UaBase::Variable *) pChild,
                                                                                       pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pName, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Variable *) pChild)->modellingRuleId().isNull()) {
                        m_pName->setModellingRuleId(((UaBase::Variable *) pChild)->modellingRuleId());
                    }
                }
            } else if (pChild->browseName() ==
                       UaQualifiedName("Joints", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pJoints) {
                    m_pJoints = (OpcUa::FolderType *) pFactory->createObject((UaBase::Object *) pChild, pNodeConfig,
                                                                             pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pJoints, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Object *) pChild)->modellingRuleId().isNull()) {
                        m_pJoints->setModellingRuleId(((UaBase::Object *) pChild)->modellingRuleId());
                    }
                }
            }
        }
        UA_ASSERT(m_pJoints);
        UA_ASSERT(m_pName);
    }

    void ManipulatorTypeBase::initialize() {
        OpcUa_Int16 nsIdx = m_pNodeConfig->getNameSpaceIndex();
        UaStatus addStatus;
        UaVariant defaultValue;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pJoints = new OpcUa::FolderType(UaNodeId(UaString("%1.Joints").arg(nodeId().toString()), nsIdx), s_pJoints,
                                          m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pJoints, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());

        m_pName = new OpcUa::BaseDataVariableType(this, s_pName, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pName, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());


    }

    ManipulatorTypeBase::~ManipulatorTypeBase() {
    }

    void ManipulatorTypeBase::createTypes() {
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
                    UaNodeId(internId_ManipulatorType, nsTypeIdx),
                    UaQualifiedName("ManipulatorType", nsTypeIdx),
                    UaLocalizedText("", "ManipulatorType"),
                    UaLocalizedText("", ""),
                    OpcUa_False,
                    &ManipulatorType::clearStaticMembers);
            pTypeNodeConfig->addNodeAndReference(UaNodeId(OpcUaId_BaseObjectType, nsSuperTypeIdx), pObjectType,
                                                 OpcUaId_HasSubtype);

            s_pJoints = new OpcUa::FolderType(UaNodeId(internId_ManipulatorType_Joints, nsTypeIdx), "Joints",
                                              intern::NodeManagerinternship::getTypeNamespace(), pTypeNodeConfig);
            s_pJoints->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pJoints, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());


            defaultValue.setString("");
            s_pName = new OpcUa::BaseDataVariableType(UaNodeId(internId_ManipulatorType_Name, nsTypeIdx), "Name",
                                                      intern::NodeManagerinternship::getTypeNamespace(), defaultValue,
                                                      3, pTypeNodeConfig);
            s_pName->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            s_pName->setValueRank(-1);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pName, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());

        }
    }

    void ManipulatorTypeBase::clearStaticMembers() {
        s_typeNodesCreated = false;

        s_pJoints = NULL;
        s_pName = NULL;
    }

    UaNodeId ManipulatorTypeBase::typeDefinitionId() const {
        UaNodeId ret(internId_ManipulatorType, NodeManagerinternship::getTypeNamespace());
        return ret;
    }

    void ManipulatorTypeBase::setName(const UaString &Name) {
        UaVariant value;
        value.setString(Name);
        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_True, OpcUa_True);
        m_pName->setValue(NULL, dataValue, OpcUa_False);
    }

    UaString ManipulatorTypeBase::getName() const {
        UaVariant defaultValue;
        UaString ret;
        UaDataValue dataValue(m_pName->value(NULL));
        defaultValue = *dataValue.value();
        ret = defaultValue.toString();
        return ret;
    }

    OpcUa::FolderType *ManipulatorTypeBase::getJoints() {
        return m_pJoints;
    }

    const OpcUa::FolderType *ManipulatorTypeBase::getJoints() const {
        return m_pJoints;
    }

    OpcUa::BaseDataVariableType *ManipulatorTypeBase::getNameNode() {
        return m_pName;
    }

    const OpcUa::BaseDataVariableType *ManipulatorTypeBase::getNameNode() const {
        return m_pName;
    }


}



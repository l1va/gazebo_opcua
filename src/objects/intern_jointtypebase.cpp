#include "intern_jointtypebase.h"
#include "intern_jointtype.h"
#include "uagenericnodes.h"
#include "nodemanagerroot.h"
#include "methodhandleuanode.h"
#include "intern_nodemanagerinternship.h"

#include "instancefactory.h"
#include "intern_instancefactory_internship.h"
#include "intern_positiontype.h"
#include "opcua_extensionobject.h"
namespace intern {

    bool JointTypeBase::s_typeNodesCreated = false;
    intern::PositionType *JointTypeBase::s_pPosition = NULL;
    OpcUa::BaseDataVariableType *JointTypeBase::s_pVelocity = NULL;

    JointTypeBase::JointTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject,
                                 NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, pInstanceDeclarationObject, pNodeConfig, pSharedMutex) {
        initialize();
    }

    JointTypeBase::JointTypeBase(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                                 NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(nodeId, name, browseNameNameSpaceIndex, pNodeConfig, pSharedMutex) {
        initialize();
    }

    JointTypeBase::JointTypeBase(
            UaBase::Object *pBaseNode,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex)
            : OpcUa::BaseObjectType(pBaseNode, pFactory, pNodeConfig, pSharedMutex) {
        UaStatus addStatus;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pPosition = NULL;
        m_pVelocity = NULL;

        std::list<UaBase::BaseNode *> lstReferencedNodes = pBaseNode->hierarchicallyReferencedNodes();
        for (std::list<UaBase::BaseNode *>::const_iterator it = lstReferencedNodes.begin();
             it != lstReferencedNodes.end(); it++) {
            UaBase::BaseNode *pChild = *it;
            if (pChild->browseName() ==
                UaQualifiedName("Velocity", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pVelocity) {
                    m_pVelocity = (OpcUa::BaseDataVariableType *) pFactory->createVariable((UaBase::Variable *) pChild,
                                                                                           pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pVelocity, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Variable *) pChild)->modellingRuleId().isNull()) {
                        m_pVelocity->setModellingRuleId(((UaBase::Variable *) pChild)->modellingRuleId());
                    }
                }
            } else if (pChild->browseName() ==
                       UaQualifiedName("Position", intern::NodeManagerinternship::getTypeNamespace())) {
                if (!m_pPosition) {
                    m_pPosition = (intern::PositionType *) pFactory->createObject((UaBase::Object *) pChild,
                                                                                  pNodeConfig, pSharedMutex);
                    addStatus = pNodeConfig->addNodeAndReference(this, m_pPosition, OpcUaId_HasComponent);
                    UA_ASSERT(addStatus.isGood());
                    if (!((UaBase::Object *) pChild)->modellingRuleId().isNull()) {
                        m_pPosition->setModellingRuleId(((UaBase::Object *) pChild)->modellingRuleId());
                    }
                }
            }
        }
        UA_ASSERT(m_pPosition);
        UA_ASSERT(m_pVelocity);
    }

    void JointTypeBase::initialize() {
        OpcUa_Int16 nsIdx = m_pNodeConfig->getNameSpaceIndex();
        UaStatus addStatus;
        UaVariant defaultValue;

        if (s_typeNodesCreated == false) {
            createTypes();
        }

        m_pPosition = new intern::PositionType(UaNodeId(UaString("%1.Position").arg(nodeId().toString()), nsIdx),
                                               s_pPosition, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pPosition, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());

        m_pVelocity = new OpcUa::BaseDataVariableType(this, s_pVelocity, m_pNodeConfig, m_pSharedMutex);
        addStatus = m_pNodeConfig->addNodeAndReference(this, m_pVelocity, OpcUaId_HasComponent);
        UA_ASSERT(addStatus.isGood());


    }

    JointTypeBase::~JointTypeBase() {
    }

    void JointTypeBase::createTypes() {
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
                    UaNodeId(internId_JointType, nsTypeIdx),
                    UaQualifiedName("JointType", nsTypeIdx),
                    UaLocalizedText("", "JointType"),
                    UaLocalizedText("", ""),
                    OpcUa_False,
                    &JointType::clearStaticMembers);
            pTypeNodeConfig->addNodeAndReference(UaNodeId(OpcUaId_BaseObjectType, nsSuperTypeIdx), pObjectType,
                                                 OpcUaId_HasSubtype);
            {
                std::list<UaBase::BaseNode *> lstBaseNodes;
                UaBase::Object *pChild = new UaBase::Object(UaNodeId(internId_JointType_Position, nsTypeIdx));
                lstBaseNodes.push_back(pChild);
                pChild->setBrowseName(UaQualifiedName("Position", intern::NodeManagerinternship::getTypeNamespace()));
                pChild->setDisplayName(UaLocalizedText("", "Position"));
                {
                    UaBase::BaseNode *pParent = pChild;
                    UaBase::BaseNode *pChild2;
                    UaBase::FullReference reference;
                    pChild2 = new UaBase::Variable(UaNodeId(internId_JointType_Position_X, nsTypeIdx));
                    lstBaseNodes.push_back(pChild2);
                    pChild2->setBrowseName(UaQualifiedName("X", intern::NodeManagerinternship::getTypeNamespace()));
                    pChild2->setDisplayName(UaLocalizedText("", "X"));
                    ((UaBase::Variable *) pChild2)->setAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setUserAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setValueRank(-1);
                    ((UaBase::Variable *) pChild2)->setDataTypeId(OpcUaId_Double);
                    ((UaBase::Variable *) pChild2)->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
                    ((UaBase::Variable *) pChild2)->setTypeDefinitionId(OpcUaId_BaseDataVariableType);
                    reference.setReferenceTypeId(OpcUaId_HasComponent);
                    reference.setSourceNode(pParent);
                    reference.setTargetNode(pChild2);
                    pParent->addFullReference(reference);
                    pChild2->addFullReference(reference);
                    pChild2->setParentNodeId(pParent->nodeId());
                    pChild2 = new UaBase::Variable(UaNodeId(internId_JointType_Position_Y, nsTypeIdx));
                    lstBaseNodes.push_back(pChild2);
                    pChild2->setBrowseName(UaQualifiedName("Y", intern::NodeManagerinternship::getTypeNamespace()));
                    pChild2->setDisplayName(UaLocalizedText("", "Y"));
                    ((UaBase::Variable *) pChild2)->setAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setUserAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setValueRank(-1);
                    ((UaBase::Variable *) pChild2)->setDataTypeId(OpcUaId_Double);
                    ((UaBase::Variable *) pChild2)->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
                    ((UaBase::Variable *) pChild2)->setTypeDefinitionId(OpcUaId_BaseDataVariableType);
                    reference.setReferenceTypeId(OpcUaId_HasComponent);
                    reference.setSourceNode(pParent);
                    reference.setTargetNode(pChild2);
                    pParent->addFullReference(reference);
                    pChild2->addFullReference(reference);
                    pChild2->setParentNodeId(pParent->nodeId());
                    pChild2 = new UaBase::Variable(UaNodeId(internId_JointType_Position_Z, nsTypeIdx));
                    lstBaseNodes.push_back(pChild2);
                    pChild2->setBrowseName(UaQualifiedName("Z", intern::NodeManagerinternship::getTypeNamespace()));
                    pChild2->setDisplayName(UaLocalizedText("", "Z"));
                    ((UaBase::Variable *) pChild2)->setAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setUserAccessLevel(3);
                    ((UaBase::Variable *) pChild2)->setValueRank(-1);
                    ((UaBase::Variable *) pChild2)->setDataTypeId(OpcUaId_Double);
                    ((UaBase::Variable *) pChild2)->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
                    ((UaBase::Variable *) pChild2)->setTypeDefinitionId(OpcUaId_BaseDataVariableType);
                    reference.setReferenceTypeId(OpcUaId_HasComponent);
                    reference.setSourceNode(pParent);
                    reference.setTargetNode(pChild2);
                    pParent->addFullReference(reference);
                    pChild2->addFullReference(reference);
                    pChild2->setParentNodeId(pParent->nodeId());
                }

                XmlUaNodeFactoryManager factory;
                intern::InstanceFactoryinternship factoryinternship(intern::NodeManagerinternship::getTypeNamespace());
                factory.addNamespace(&factoryinternship);

                s_pPosition = new intern::PositionType(pChild, &factory, pTypeNodeConfig, NULL);
                addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pPosition, OpcUaId_HasComponent);
                UA_ASSERT(addStatus.isGood());
                s_pPosition->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
                std::list<UaBase::BaseNode *>::iterator it = lstBaseNodes.begin();
                while (it != lstBaseNodes.end()) {
                    delete *it;
                    it++;
                }
            }


            defaultValue.setDouble(0.0);
            s_pVelocity = new OpcUa::BaseDataVariableType(UaNodeId(internId_JointType_Velocity, nsTypeIdx), "Velocity",
                                                          intern::NodeManagerinternship::getTypeNamespace(),
                                                          defaultValue, 3, pTypeNodeConfig);
            s_pVelocity->setModellingRuleId(OpcUaId_ModellingRule_Mandatory);
            s_pVelocity->setValueRank(-1);
            addStatus = pTypeNodeConfig->addNodeAndReference(pObjectType, s_pVelocity, OpcUaId_HasComponent);
            UA_ASSERT(addStatus.isGood());

        }
    }

    void JointTypeBase::clearStaticMembers() {
        s_typeNodesCreated = false;

        s_pPosition = NULL;
        s_pVelocity = NULL;
    }

    UaNodeId JointTypeBase::typeDefinitionId() const {
        UaNodeId ret(internId_JointType, NodeManagerinternship::getTypeNamespace());
        return ret;
    }

    void JointTypeBase::setVelocity(OpcUa_Double Velocity) {
        UaVariant value;
        value.setDouble(Velocity);
        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_True, OpcUa_True);
        m_pVelocity->setValue(NULL, dataValue, OpcUa_False);
    }

    OpcUa_Double JointTypeBase::getVelocity() const {
        UaVariant defaultValue;
        OpcUa_Double ret = 0;
        UaDataValue dataValue(m_pVelocity->value(NULL));
        defaultValue = *dataValue.value();
        defaultValue.toDouble(ret);
        return ret;
    }

    intern::PositionType *JointTypeBase::getPosition() {
        return m_pPosition;
    }

    const intern::PositionType *JointTypeBase::getPosition() const {
        return m_pPosition;
    }

    OpcUa::BaseDataVariableType *JointTypeBase::getVelocityNode() {
        return m_pVelocity;
    }

    const OpcUa::BaseDataVariableType *JointTypeBase::getVelocityNode() const {
        return m_pVelocity;
    }


}



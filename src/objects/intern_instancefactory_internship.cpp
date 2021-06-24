#include "intern_instancefactory_internship.h"
#include "intern_identifiers.h"
#include "intern_jointtype.h"
#include "intern_manipulatortype.h"
#include "intern_positiontype.h"
#include "intern_datatypes.h"


namespace intern {

    InstanceFactoryinternship::InstanceFactoryinternship(OpcUa_UInt16 namespaceIndex)
            : XmlUaNodeFactoryNamespace(namespaceIndex) {
    }

    OpcUa::BaseVariableType *InstanceFactoryinternship::createVariable(
            UaBase::Variable *pVariable,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex) {
        UA_ASSERT(pVariable->typeDefinitionId().namespaceIndex() == namespaceIndex());
        OpcUa_ReferenceParameter(pVariable);
        OpcUa_ReferenceParameter(pFactory);
        OpcUa_ReferenceParameter(pNodeConfig);
        OpcUa_ReferenceParameter(pSharedMutex);
        return NULL;
    }

    OpcUa::BaseObjectType *InstanceFactoryinternship::createObject(
            UaBase::Object *pObject,
            XmlUaNodeFactoryManager *pFactory,
            NodeManagerConfig *pNodeConfig,
            UaMutexRefCounted *pSharedMutex) {
        UA_ASSERT(pObject->typeDefinitionId().namespaceIndex() == namespaceIndex());
        if (pObject->typeDefinitionId().namespaceIndex() == namespaceIndex()) {
            switch (pObject->typeDefinitionId().identifierNumeric()) {
                case internId_JointType:
                    return new intern::JointType(pObject, pFactory, pNodeConfig, pSharedMutex);
                case internId_ManipulatorType:
                    return new intern::ManipulatorType(pObject, pFactory, pNodeConfig, pSharedMutex);
                case internId_PositionType:
                    return new intern::PositionType(pObject, pFactory, pNodeConfig, pSharedMutex);
                default:
                    UA_ASSERT(false);
                    return createGenericObject(pObject, pFactory, pNodeConfig, pSharedMutex);
            }
        }
        return NULL;
    }

    UaVariant InstanceFactoryinternship::defaultValue(const UaNodeId &dataTypeId, OpcUa_Int32 valueRank) const {
        UA_ASSERT(dataTypeId.namespaceIndex() == namespaceIndex());
        UaVariant value;
        OpcUa_ReferenceParameter(dataTypeId);
        OpcUa_ReferenceParameter(valueRank);
        return value;
    }

    void InstanceFactoryinternship::createType(const UaNodeId &typeId) const {
        UA_ASSERT(typeId.namespaceIndex() == namespaceIndex());
        if (typeId.namespaceIndex() != namespaceIndex()) {
            return;
        }
        UA_ASSERT(typeId.identifierType() == OpcUa_IdentifierType_Numeric);
        if (typeId.identifierType() != OpcUa_IdentifierType_Numeric) {
            return;
        }
        switch (typeId.identifierNumeric()) {
            case internId_JointType:
                intern::JointType::createTypes();
                break;
            case internId_ManipulatorType:
                intern::ManipulatorType::createTypes();
                break;
            case internId_PositionType:
                intern::PositionType::createTypes();
                break;
            default:
                return;
        }
    }

};

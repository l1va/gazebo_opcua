#ifndef __INSTSTANCEFACTORY_internship_
#define __INSTSTANCEFACTORY_internship_
#include <basenodes.h>
#include "opcua_basevariabletype.h"
#include "opcua_baseobjecttype.h"
#include <instancefactory.h>
#include "intern_identifiers.h"

class XmlUaNodeFactoryManager;

namespace intern {

    class dll_intern_EXPORT InstanceFactoryinternship : public XmlUaNodeFactoryNamespace {
    public:
        InstanceFactoryinternship(OpcUa_UInt16 namespaceIndex);

        virtual OpcUa::BaseVariableType *createVariable(
                UaBase::Variable *pVariable,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        virtual OpcUa::BaseObjectType *createObject(
                UaBase::Object *pObject,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        virtual UaVariant defaultValue(const UaNodeId &dataTypeId, OpcUa_Int32 valueRank) const;

        virtual void createType(const UaNodeId &typeId) const;
    };

};
#endif //__INSTSTANCEFACTORY_internship_

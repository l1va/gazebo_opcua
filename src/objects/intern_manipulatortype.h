#ifndef __INTERN_MANIPULATORTYPE_H__
#define __INTERN_MANIPULATORTYPE_H__

#include "intern_manipulatortypebase.h"

namespace intern {

    class dll_intern_EXPORT ManipulatorType :
            public ManipulatorTypeBase {
        UA_DISABLE_COPY(ManipulatorType);

    protected:

        virtual ~ManipulatorType();

    public:

        ManipulatorType(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject, NodeManagerConfig *pNodeConfig,
                        UaMutexRefCounted *pSharedMutex = NULL);

        ManipulatorType(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                        NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        ManipulatorType(
                UaBase::Object *pBaseNode,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        static void createTypes();

        static void clearStaticMembers();


    protected:

    private:
    };

}

#endif


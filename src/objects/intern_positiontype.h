#ifndef __INTERN_POSITIONTYPE_H__
#define __INTERN_POSITIONTYPE_H__

#include "intern_positiontypebase.h"

namespace intern {

    class dll_intern_EXPORT PositionType :
            public PositionTypeBase {
        UA_DISABLE_COPY(PositionType);

    protected:

        virtual ~PositionType();

    public:

        PositionType(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject, NodeManagerConfig *pNodeConfig,
                     UaMutexRefCounted *pSharedMutex = NULL);

        PositionType(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                     NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        PositionType(
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


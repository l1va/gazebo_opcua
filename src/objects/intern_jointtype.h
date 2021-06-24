#ifndef __INTERN_JOINTTYPE_H__
#define __INTERN_JOINTTYPE_H__

#include "intern_jointtypebase.h"

namespace intern {

    class dll_intern_EXPORT JointType :
            public JointTypeBase {
        UA_DISABLE_COPY(JointType);

    protected:

        virtual ~JointType();

    public:

        JointType(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject, NodeManagerConfig *pNodeConfig,
                  UaMutexRefCounted *pSharedMutex = NULL);

        JointType(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                  NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        JointType(
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


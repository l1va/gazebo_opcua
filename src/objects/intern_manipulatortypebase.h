#ifndef __INTERN_MANIPULATORTYPEBASE_H__
#define __INTERN_MANIPULATORTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "intern_datatypes.h"
#include "intern_identifiers.h"
#include "intern_instancefactory_internship.h"
#include "opcua_basedatavariabletype.h"
#include "opcua_foldertype.h"

namespace intern {

    class dll_intern_EXPORT ManipulatorTypeBase :
            public OpcUa::BaseObjectType {
        UA_DISABLE_COPY(ManipulatorTypeBase);

    protected:
        virtual ~ManipulatorTypeBase();

    public:

        ManipulatorTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject,
                            NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        ManipulatorTypeBase(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                            NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        ManipulatorTypeBase(
                UaBase::Object *pBaseNode,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        static void createTypes();

        static void clearStaticMembers();

        virtual UaNodeId typeDefinitionId() const;


        virtual void setName(const UaString &Name);

        virtual UaString getName() const;

        virtual OpcUa::FolderType *getJoints();

        virtual const OpcUa::FolderType *getJoints() const;

        virtual OpcUa::BaseDataVariableType *getNameNode();

        virtual const OpcUa::BaseDataVariableType *getNameNode() const;

    protected:


        static OpcUa::FolderType *s_pJoints;
        OpcUa::FolderType *m_pJoints;


        static OpcUa::BaseDataVariableType *s_pName;
        OpcUa::BaseDataVariableType *m_pName;


    private:
        void initialize();

    private:
        static bool s_typeNodesCreated;
    };

}

#endif



#ifndef __INTERN_JOINTTYPEBASE_H__
#define __INTERN_JOINTTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "intern_datatypes.h"
#include "intern_identifiers.h"
#include "intern_instancefactory_internship.h"
#include "opcua_basedatavariabletype.h"

namespace intern {

    class PositionType;

    class dll_intern_EXPORT JointTypeBase :
            public OpcUa::BaseObjectType {
        UA_DISABLE_COPY(JointTypeBase);

    protected:
        virtual ~JointTypeBase();

    public:

        JointTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject, NodeManagerConfig *pNodeConfig,
                      UaMutexRefCounted *pSharedMutex = NULL);

        JointTypeBase(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                      NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        JointTypeBase(
                UaBase::Object *pBaseNode,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        static void createTypes();

        static void clearStaticMembers();

        virtual UaNodeId typeDefinitionId() const;


        virtual void setVelocity(OpcUa_Double Velocity);

        virtual OpcUa_Double getVelocity() const;

        virtual intern::PositionType *getPosition();

        virtual const intern::PositionType *getPosition() const;

        virtual OpcUa::BaseDataVariableType *getVelocityNode();

        virtual const OpcUa::BaseDataVariableType *getVelocityNode() const;

    protected:


        static intern::PositionType *s_pPosition;
        intern::PositionType *m_pPosition;


        static OpcUa::BaseDataVariableType *s_pVelocity;
        OpcUa::BaseDataVariableType *m_pVelocity;


    private:
        void initialize();

    private:
        static bool s_typeNodesCreated;
    };

}

#endif



#ifndef __INTERN_POSITIONTYPEBASE_H__
#define __INTERN_POSITIONTYPEBASE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "intern_datatypes.h"
#include "intern_identifiers.h"
#include "intern_instancefactory_internship.h"
#include "opcua_basedatavariabletype.h"

namespace intern {

    class dll_intern_EXPORT PositionTypeBase :
            public OpcUa::BaseObjectType {
        UA_DISABLE_COPY(PositionTypeBase);

    protected:
        virtual ~PositionTypeBase();

    public:

        PositionTypeBase(const UaNodeId &nodeId, UaObject *pInstanceDeclarationObject, NodeManagerConfig *pNodeConfig,
                         UaMutexRefCounted *pSharedMutex = NULL);

        PositionTypeBase(const UaNodeId &nodeId, const UaString &name, OpcUa_UInt16 browseNameNameSpaceIndex,
                         NodeManagerConfig *pNodeConfig, UaMutexRefCounted *pSharedMutex = NULL);

        PositionTypeBase(
                UaBase::Object *pBaseNode,
                XmlUaNodeFactoryManager *pFactory,
                NodeManagerConfig *pNodeConfig,
                UaMutexRefCounted *pSharedMutex = NULL);

        static void createTypes();

        static void clearStaticMembers();

        virtual UaNodeId typeDefinitionId() const;


        virtual void setX(OpcUa_Double X);

        virtual OpcUa_Double getX() const;

        virtual void setY(OpcUa_Double Y);

        virtual OpcUa_Double getY() const;

        virtual void setZ(OpcUa_Double Z);

        virtual OpcUa_Double getZ() const;

        virtual OpcUa::BaseDataVariableType *getXNode();

        virtual const OpcUa::BaseDataVariableType *getXNode() const;

        virtual OpcUa::BaseDataVariableType *getYNode();

        virtual const OpcUa::BaseDataVariableType *getYNode() const;

        virtual OpcUa::BaseDataVariableType *getZNode();

        virtual const OpcUa::BaseDataVariableType *getZNode() const;

    protected:


        static OpcUa::BaseDataVariableType *s_pX;
        OpcUa::BaseDataVariableType *m_pX;

        static OpcUa::BaseDataVariableType *s_pY;
        OpcUa::BaseDataVariableType *m_pY;

        static OpcUa::BaseDataVariableType *s_pZ;
        OpcUa::BaseDataVariableType *m_pZ;


    private:
        void initialize();

    private:
        static bool s_typeNodesCreated;
    };

}

#endif



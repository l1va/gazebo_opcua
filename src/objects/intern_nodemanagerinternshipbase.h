#ifndef _INTERN_NODEMANAGERINTERNSHIPBASE_H__
#define _INTERN_NODEMANAGERINTERNSHIPBASE_H__

#include "uamutex.h"
#include "uabasenodes.h"
#include "nodemanagerbase.h"
#include "uaobjecttypes.h"
#include "intern_identifiers.h"

class XmlUaNodeFactoryNamespace;

namespace intern {

    class dll_intern_EXPORT NodeManagerinternshipBase : public NodeManagerBase {
        UA_DISABLE_COPY(NodeManagerinternshipBase);

        NodeManagerinternshipBase();

    public:
        /* construction / destruction */
        NodeManagerinternshipBase(OpcUa_Boolean firesEvents, OpcUa_Int32 nHashTableSize = 10007);

        virtual ~NodeManagerinternshipBase() {};


        virtual UaStatus afterStartUp();

        virtual XmlUaNodeFactoryNamespace *getUaNodeFactory(OpcUa_UInt16 namespaceIndex) const;


        static OpcUa_UInt16 getTypeNamespace();


    private:
        UaStatus createDataTypeNodes();

        UaStatus createReferenceTypeNodes();

        UaStatus addAdditionalHierarchicalReferences();

        UaStatus addAdditionalNonHierarchicalReferences();


    protected:
        UaMutex m_mutex;
        static OpcUa_UInt16 s_namespaceIndex;
    };

}

#endif


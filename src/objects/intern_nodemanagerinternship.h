#ifndef _INTERN_NODEMANAGERINTERNSHIP_H__
#define _INTERN_NODEMANAGERINTERNSHIP_H__

#include "intern_nodemanagerinternshipbase.h"

namespace intern {

    class dll_intern_EXPORT NodeManagerinternship : public NodeManagerinternshipBase {
        UA_DISABLE_COPY(NodeManagerinternship);

        NodeManagerinternship();

    public:
        NodeManagerinternship(OpcUa_Boolean firesEvents, OpcUa_Int32 nHashTableSize = 10007);

        virtual ~NodeManagerinternship();


        virtual UaStatus afterStartUp();

        virtual UaStatus beforeShutDown();

        virtual OpcUa_Boolean beforeSetAttributeValue(Session *pSession,
                                                      UaNode *pNode,
                                                      OpcUa_Int32 attributeId,
                                                      const UaDataValue &dataValue,
                                                      OpcUa_Boolean &checkWriteMask
        );

    };
}

#endif


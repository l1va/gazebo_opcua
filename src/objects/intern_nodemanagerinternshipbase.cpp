#include "intern_nodemanagerinternshipbase.h"
#include "intern_instancefactory_internship.h"

// Include type headers
#include <uabasenodes.h>
#include "instancefactory.h"
#include "intern_jointtype.h"
#include "intern_manipulatortype.h"
#include "intern_positiontype.h"
#include "nodemanagerroot.h"
#include "opcua_foldertype.h"

namespace intern {
    OpcUa_UInt16 NodeManagerinternshipBase::s_namespaceIndex = 0;

    NodeManagerinternshipBase::NodeManagerinternshipBase(
            OpcUa_Boolean firesEvents,
            OpcUa_Int32 nHashTableSize)

            : NodeManagerBase("http://yourorganisation.org/manipulator/", firesEvents, nHashTableSize) {
        m_defaultLocaleId = "en";
    }

    UaStatus NodeManagerinternshipBase::afterStartUp() {
        UaStatus ret;

        s_namespaceIndex = getNameSpaceIndex();

        ret = createDataTypeNodes();
        UA_ASSERT(ret.isGood());
        ret = createReferenceTypeNodes();
        UA_ASSERT(ret.isGood());

        JointType::createTypes();
        ManipulatorType::createTypes();
        PositionType::createTypes();

        ret = addAdditionalHierarchicalReferences();
        UA_ASSERT(ret.isGood());
        if (ret.isBad()) return ret;
        ret = addAdditionalNonHierarchicalReferences();
        UA_ASSERT(ret.isGood());
        if (ret.isBad()) return ret;

        return ret;
    }

    XmlUaNodeFactoryNamespace *NodeManagerinternshipBase::getUaNodeFactory(OpcUa_UInt16 namespaceIndex) const {
        InstanceFactoryinternship *pRet = new InstanceFactoryinternship(namespaceIndex);
        return pRet;
    }

    OpcUa_UInt16 NodeManagerinternshipBase::getTypeNamespace() {
        return s_namespaceIndex;
    }

    UaStatus NodeManagerinternshipBase::createDataTypeNodes() {
        UaStatus ret;
        return ret;
    }

    UaStatus NodeManagerinternshipBase::createReferenceTypeNodes() {
        UaStatus ret;

        return ret;
    }


    UaStatus NodeManagerinternshipBase::addAdditionalHierarchicalReferences() {
        UaStatus ret;

        return ret;
    }

    UaStatus NodeManagerinternshipBase::addAdditionalNonHierarchicalReferences() {
        UaStatus ret;

        return ret;
    }


}




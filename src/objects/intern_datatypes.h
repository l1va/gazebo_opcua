#ifndef __INTERN_DATATYPES_H__
#define __INTERN_DATATYPES_H__

#include <opcua_proxystub.h>
#include <opcua_builtintypes.h>
#include <opcua_exclusions.h>
#include <opcua_types.h>

#include "intern_identifiers.h"

#define INTERN_EXTENSIONOBJECT_GET_ENCODEABLE(xExpectedType, xExtensionObject) \
    (intern_##xExpectedType*)((((xExtensionObject)->Encoding == OpcUa_ExtensionObjectEncoding_EncodeableObject && \
    (xExtensionObject)->Body.EncodeableObject.Type != OpcUa_Null && \
    (xExtensionObject)->Body.EncodeableObject.Type->TypeId == internId_##xExpectedType && \
    OpcUa_StrCmpA((xExtensionObject)->Body.EncodeableObject.Type->NamespaceUri, "http://yourorganisation.org/manipulator/") == 0 && \
    (xExtensionObject)->Body.EncodeableObject.Object != OpcUa_Null))?((xExtensionObject)->Body.EncodeableObject.Object):OpcUa_Null)

namespace intern {

}

namespace intern
{
    /** Class used to handle data type registration
    */
    class DataTypes
    {
    public:
        static void registerStructuredTypes();
    private:
        static bool s_dataTypesAdded;
    };
}

#endif // __INTERN_DATATYPES_H__


#ifndef __INTERN_IDENTIFIERS_H__
#define __INTERN_IDENTIFIERS_H__

#define intern_NameSpaceUri "http://yourorganisation.org/manipulator/"

#include "version_coremodule.h"
#if (PROD_MAJOR != 1 || (PROD_MAJOR == 1 && PROD_MINOR < 7) || (PROD_MAJOR == 1 && PROD_MINOR == 7 && PROD_MINOR2 < 0))
#error The code is generated for SDK version 1.7.0
#endif

/*============================================================================
* ObjectType Identifiers
 *===========================================================================*/
#define internId_JointType 1004
#define internId_ManipulatorType 1002
#define internId_PositionType 1003

/*============================================================================
* VariableType Identifiers
 *===========================================================================*/

/*============================================================================
* DataType Identifiers
 *===========================================================================*/

/*============================================================================
* ReferenceType Identifiers
 *===========================================================================*/

/*============================================================================
* Object Identifiers
 *===========================================================================*/
#define internId_JointType_Position 5001
#define internId_ManipulatorType_Joints 5002

/*============================================================================
* Variable Identifiers
 *===========================================================================*/
#define internId_JointType_Position_X 6005
#define internId_JointType_Position_Y 6006
#define internId_JointType_Position_Z 6007
#define internId_JointType_Velocity 6004
#define internId_ManipulatorType_Name 6008
#define internId_PositionType_X 6001
#define internId_PositionType_Y 6002
#define internId_PositionType_Z 6003

/*============================================================================
* Method Identifiers
 *===========================================================================*/


#ifdef _WIN32
#ifdef _dll_intern_BUILD_DLL
# define dll_intern_EXPORT __declspec(dllexport)
#elif defined _dll_intern_USE_DLL
# define dll_intern_EXPORT __declspec(dllimport)
#else
# define dll_intern_EXPORT
#endif
#else
# define dll_intern_EXPORT
#endif

///////////////////////////////////////////////
// Private Class Hiding Macros
#define INTERN_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private *>(d_ptr); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private *>(d_ptr); } \
    friend class Class##Private; \
    Class##Private *d_ptr;

#define INTERN_DECLARE_PUBLIC(Class) \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define INTERN_D(Class) Class##Private * const d = d_func()
#define INTERN_CD(Class) const Class##Private * const d = d_func()
#define INTERN_Q(Class) Class * const q = q_func()

#endif // __INTERN_IDENTIFIERS_H__


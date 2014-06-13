#ifndef JSTESTPLUGIN_H
#define JSEMAILPLUGIN_H

#include "Emailplugin.h"
#include <dpl/shared_ptr.h>
#include <JavaScriptCore/JavaScript.h>
#include <CommonsJavaScript/JSPendingOperationPrivateObject.h>
#include <CommonsJavaScript/PrivateObject.h>

namespace DeviceAPI {
namespace Emailplugin {

typedef WrtDeviceApis::CommonsJavaScript::PrivateObject<EmailpluginPtr, WrtDeviceApis::CommonsJavaScript::NoOwnership> EmailpluginPrivObject;

class JSEmailplugin
{
public:
	static const JSClassDefinition* getClassInfo();

	static const JSClassRef getClassRef();

private:
	/**
		* The callback invoked when an object is first created.
		*/
	static void initialize(JSContextRef context,
						   JSObjectRef object);

	/**
		* The callback invoked when an object is finalized.
		*/
	static void finalize(JSObjectRef object);

	/**
		* The callback invoked when an object is used as the target of an 'instanceof' expression.
		*/
	static bool hasInstance(JSContextRef ctx,
							JSObjectRef constructor,
							JSValueRef possibleInstance,
							JSValueRef* exception);

	static JSValueRef addAccount(JSContextRef context,
				JSObjectRef object,
				JSObjectRef thisObject,
				size_t argumentCount,
				const JSValueRef arguments[],
				JSValueRef* exception);
	static JSValueRef deleteAccount(JSContextRef context,
				JSObjectRef object,
				JSObjectRef thisObject,
				size_t argumentCount,
				const JSValueRef arguments[],
				JSValueRef* exception);
	
	/**
		 * This structure contains properties and callbacks that define a type of object.
		 */
	static JSClassDefinition m_classInfo;

	/**
		 * This structure describes a statically declared function.
		 */
	static JSStaticFunction m_function[];

	static JSClassRef m_jsClassRef;
};

}
}

#endif // JSEMAILPLUGIN_H

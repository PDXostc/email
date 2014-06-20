/*******************************************************************************
*File name           :JSEmailplugin.h
*Functionality       :This file defines JSemailPlugin object and exports webapp 
					  callable functions.   
* Author             :TCS & JLR
* Owner              :JLR
* Last Date Modified :23/07/2014
********************************************************************************/
#ifndef JSTESTPLUGIN_H
#define JSEMAILPLUGIN_H
//common header files needed by the JS Object
#include "Emailplugin.h"
#include <dpl/shared_ptr.h>
#include <JavaScriptCore/JavaScript.h>
#include <CommonsJavaScript/JSPendingOperationPrivateObject.h>
#include <CommonsJavaScript/PrivateObject.h>

//declare the email plugin JS object class.
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
   //Add account function
	static JSValueRef addAccount(JSContextRef context,
				JSObjectRef object,
				JSObjectRef thisObject,
				size_t argumentCount,
				const JSValueRef arguments[],
				JSValueRef* exception);
	//delete account function.
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

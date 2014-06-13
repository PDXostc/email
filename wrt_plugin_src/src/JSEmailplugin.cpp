#include "JSEmailplugin.h"
#include "Emailplugin.h"

#include <Logger.h>
#include <Commons/Exception.h>
#include <CommonsJavaScript/Utils.h>
#include <CommonsJavaScript/JSCallbackManager.h>
#include <JSWebAPIErrorFactory.h>
#include <ArgumentValidator.h>
#include <CommonsJavaScript/Converter.h>
#include <dpl/scoped_ptr.h>
#include <sstream>
#include <map>

#include <json-glib/json-gvariant.h>	

namespace DeviceAPI {
namespace Emailplugin {

using namespace DPL;
using namespace DeviceAPI::Common;
using namespace WrtDeviceApis::Commons;
using namespace WrtDeviceApis::CommonsJavaScript;

JSClassDefinition JSEmailplugin::m_classInfo = {
	0,
	kJSClassAttributeNone,
	"Emailplugin",
	0,
	NULL,
	m_function,
	initialize,
	finalize,
	NULL, //HasProperty,
	NULL, //GetProperty,
	NULL, //SetProperty,
	NULL, //DeleteProperty,
	NULL, //GetPropertyNames,
	NULL, //CallAsFunction,
	NULL, //CallAsConstructor,
	hasInstance,
	NULL, //ConvertToType
};

JSStaticFunction JSEmailplugin::m_function[] = {
	{ "addAccount", JSEmailplugin::addAccount, kJSPropertyAttributeNone },
	{ "deleteAccount", JSEmailplugin::deleteAccount, kJSPropertyAttributeNone },
	{ 0, 0, 0 }
};

const JSClassRef JSEmailplugin::getClassRef()
{
	if (!m_jsClassRef)
	{
		m_jsClassRef = JSClassCreate(&m_classInfo);
	}
	return m_jsClassRef;
}

const JSClassDefinition* JSEmailplugin::getClassInfo()
{
	return &m_classInfo;
}

JSClassRef JSEmailplugin::m_jsClassRef = JSClassCreate(JSEmailplugin::getClassInfo());

void JSEmailplugin::initialize(JSContextRef context, JSObjectRef object)
{
	EmailpluginPrivObject* priv = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(object));
	if (!priv)
	{
		EmailpluginPtr emailplugin(new EmailpluginMaster());
		priv = new EmailpluginPrivObject( context, emailplugin);
		if(!JSObjectSetPrivate(object, static_cast<void*>(priv)))
		{
			LoggerE("Object can't store private data.");
			delete priv;
		}
	}

	LoggerD("JSEmailplugin::initialize ");
}

void JSEmailplugin::finalize(JSObjectRef object)
{
	EmailpluginPrivObject* priv = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(object));
	JSObjectSetPrivate(object, NULL);
	LoggerD("Deleting timeutil");
	delete priv;
}

bool JSEmailplugin::hasInstance(JSContextRef context,
		JSObjectRef constructor,
		JSValueRef possibleInstance,
		JSValueRef* exception)
{
	return JSValueIsObjectOfClass(context, possibleInstance, getClassRef());
}


JSValueRef JSEmailplugin::addAccount(JSContextRef context,
				JSObjectRef object,
				JSObjectRef thisObject,
				size_t argumentCount,
				const JSValueRef arguments[],
				JSValueRef* exception)
{
	LoggerD("Entered addAccount");
	EmailpluginPrivObject* privateObject = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(thisObject));
	if (NULL == privateObject)
	{
		LoggerE("private object is null");
                return JSValueMakeUndefined(context);
	}

	EmailpluginPtr emailplugin(privateObject->getObject());

        JSContextRef gContext = privateObject->getContext();
        LoggerD("Validating arguments: " << argumentCount);
	ArgumentValidator validator(context, argumentCount, arguments);

        std::stringstream json;
        json<<"";
        Converter converter(context);
	std::string emailId = validator.toString(0);
	std::string acntId = validator.toString(1);
	std::string passWord = validator.toString(2);
	std::string server = validator.toString(3);
        JSObjectRef successCallback = validator.toFunction(4, false);
        JSObjectRef errorCallback = validator.toFunction(5, true);
        JSValueProtect(context, successCallback);
        JSValueProtect(context, errorCallback);

	LoggerD("calling emailplugin::addAccount");
	int error = emailplugin->addAccount(emailId,acntId,passWord,server,successCallback, errorCallback, gContext);
	LoggerD("ugin::addAccount %d",error);
        JSStringRef jsonString = converter.toJSStringRef(json.str());
        return JSValueMakeFromJSONString(context, jsonString);
}


JSValueRef JSEmailplugin::deleteAccount(JSContextRef context,
				JSObjectRef object,
				JSObjectRef thisObject,
				size_t argumentCount,
				const JSValueRef arguments[],
				JSValueRef* exception)
{
	LoggerD("Entered deleteAccount");
	EmailpluginPrivObject* privateObject = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(thisObject));
	if (NULL == privateObject)
	{
		LoggerE("private object is null");
                return JSValueMakeUndefined(context);
	}

	EmailpluginPtr emailplugin(privateObject->getObject());

        JSContextRef gContext = privateObject->getContext();
        LoggerD("Validating arguments: " << argumentCount);
	ArgumentValidator validator(context, argumentCount, arguments);

        std::stringstream json;
        json<<"";
        Converter converter(context);
	int acntId = validator.toNumber(0,true);
        JSObjectRef successCallback = validator.toFunction(1, false);
        JSObjectRef errorCallback = validator.toFunction(2, true);
        JSValueProtect(context, successCallback);
        JSValueProtect(context, errorCallback);

	LoggerD("calling emailplugin::deleteAccount");
	int error = emailplugin->deleteAccount(acntId,successCallback, errorCallback, gContext);
        JSStringRef jsonString = converter.toJSStringRef(json.str());
	LoggerD("ugin::addAccount %d",error);
        return JSValueMakeFromJSONString(context, jsonString);
}



}
}

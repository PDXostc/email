/*******************************************************************************
*File name           :JsEmailPlugin.cpp
*Functionality       :Provides JS email plugin object.This is the entry point
        			  WRT plugin.This is based on the existing vehicle WRT plugin 
        			  template from the Tizen.
* Author             :TCS & JLR
* Owner              :JLR
* Last Date Modified :09/08/2014
********************************************************************************/
#include "JSEmailplugin.h"
#include "Emailplugin.h"

#include <Logger.h>
#include <Commons/Exception.h>
#include <CommonsJavaScript/Utils.h>
#include <CommonsJavaScript/JSCallbackManager.h>
#include <JSWebAPIErrorFactory.h>
#include <ArgumentValidator.h>
#include <CommonsJavaScript/Converter.h>
#include <sstream>

//Define email plugin JS class
namespace DeviceAPI {
namespace Emailplugin {

using namespace DPL;
using namespace DeviceAPI::Common;
using namespace WrtDeviceApis::Commons;
using namespace WrtDeviceApis::CommonsJavaScript;

JSClassDefinition JSEmailplugin::m_classInfo = {
	0,
	kJSClassAttributeNone,
	"Emailplugin",    //class name
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
//functions to be exported to webapp.
JSStaticFunction JSEmailplugin::m_function[] = {
	{ "addAccount", JSEmailplugin::addAccount, kJSPropertyAttributeNone },
	{ "deleteAccount", JSEmailplugin::deleteAccount, kJSPropertyAttributeNone },
	{ "updateSeenFlag", JSEmailplugin::updateSeenFlag, kJSPropertyAttributeNone },
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
////helper function part of the template
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
//helper function part of the template
void JSEmailplugin::finalize(JSObjectRef object)
{
	EmailpluginPrivObject* priv = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(object));
	JSObjectSetPrivate(object, NULL);
	LoggerD("Deleting timeutil");
	delete priv;
}
//helper function part of the template
bool JSEmailplugin::hasInstance(JSContextRef context,
		JSObjectRef constructor,
		JSValueRef possibleInstance,
		JSValueRef* exception)
{
	return JSValueIsObjectOfClass(context, possibleInstance, getClassRef());
}

/*****************************************************************************************************
* Function Name: addAccount() 
* Details:This function is caled from webapp to add account. 
*
* Input params: Has default set of parameters as part of the JS function prototype.
*               Arguments are retrieved from 'arguments'arry.  
*   
*   	 
* Out Params:
*       None
*    
* Return:None 
 
******************************************************************************************************/

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
    //Get Email plugin object handle.Creation of the object has already happened while
	//loading the WRT.
	EmailpluginPtr emailplugin(privateObject->getObject());

        JSContextRef gContext = privateObject->getContext();
        LoggerD("Validating arguments: " << argumentCount);
	ArgumentValidator validator(context, argumentCount, arguments);

        std::stringstream json;
        json<<"";
        Converter converter(context);
        //retrieve all the input params to be sent to email plugin cpp class.
	std::string emailId = validator.toString(0);
	std::string acntId = validator.toString(1);
	std::string passWord = validator.toString(2);
	std::string server = validator.toString(3);
        JSObjectRef successCallback = validator.toFunction(4, false);
        JSObjectRef errorCallback = validator.toFunction(5, true);
        JSValueProtect(context, successCallback);
        JSValueProtect(context, errorCallback);

	LoggerD("calling emailplugin::addAccount");
	//Calling the emailplugin to add account.
	emailplugin->addAccount(emailId,acntId,passWord,server,successCallback, errorCallback, gContext);
        JSStringRef jsonString = converter.toJSStringRef(json.str());
        return JSValueMakeFromJSONString(context, jsonString);
}

/*****************************************************************************************************
* Function Name: deleteAccount() 
* Details:This function is caled from webapp to add account. 
*
* Input params: Has default set of parameters as part of the JS function prototype.
*               Arguments are retrieved from 'arguments'arry.  
*   
*   	 
* Out Params:
*       None
*    
* Return:None 
 
******************************************************************************************************/
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
    //Get Email plugin object handle.Creation of the object has already happened while
	//loading the WRT.
	EmailpluginPtr emailplugin(privateObject->getObject());

        JSContextRef gContext = privateObject->getContext();
        LoggerD("Validating arguments: " << argumentCount);
        ArgumentValidator validator(context, argumentCount, arguments);

        std::stringstream json;
        json<<"";
        Converter converter(context);
        //retrieve all the input params to be sent to email plugin cpp class.        
        int acntId = validator.toNumber(0,true);
        JSObjectRef successCallback = validator.toFunction(1, false);
        JSObjectRef errorCallback = validator.toFunction(2, true);
        JSValueProtect(context, successCallback);
        JSValueProtect(context, errorCallback);

        LoggerD("calling emailplugin::deleteAccount");
        //Delate tha account.
        emailplugin->deleteAccount(acntId,successCallback, errorCallback, gContext);
        JSStringRef jsonString = converter.toJSStringRef(json.str());
        return JSValueMakeFromJSONString(context, jsonString);
}

JSValueRef JSEmailplugin::updateSeenFlag(JSContextRef context, JSObjectRef object, JSObjectRef thisObject, size_t argumentCount,
					      const JSValueRef arguments[], JSValueRef* exception)
{
	EmailpluginPrivObject* privateObject = static_cast<EmailpluginPrivObject*>(JSObjectGetPrivate(thisObject));
	if(!privateObject)
	{
		DeviceAPI::Common::UnknownException err("Private object is NULL.");
		return JSWebAPIErrorFactory::postException(context, exception, err);
	}

	EmailpluginPtr emailplugin(privateObject->getObject());
	if(!emailplugin)
	{
		DeviceAPI::Common::UnknownException err("Email plugin object is NULL.");
		return JSWebAPIErrorFactory::postException(context, exception, err);
	}

	ArgumentValidator validator(context, argumentCount, arguments);
	JSContextRef gContext=privateObject->getContext();

	// mandatory args
	int accID=validator.toNumber(0);
	int mailID=validator.toNumber(1);
	bool seenFlag=validator.toBool(2);

	// optional args
	JSObjectRef successCallback=validator.toFunction(3, true);
	JSObjectRef errorCallback=validator.toFunction(4, true);
	JSValueProtect(context, successCallback);
	JSValueProtect(context, errorCallback);

	LoggerE("calling updateSeenFlag now");
	emailplugin->updateSeenFlag(accID,mailID,seenFlag,successCallback,errorCallback,gContext);

	return JSValueMakeUndefined(context);
}

}
}

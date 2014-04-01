#include "Emailplugin.h"
#include "email_stubs.h"
#include <gio/gio.h>
#include <stdexcept>
#include <list>
#include <Logger.h>

#include <Commons/ThreadPool.h>
#include <CommonsJavaScript/Converter.h>
#include <json-glib/json-gvariant.h>	

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp> 

namespace DeviceAPI
{
namespace Emailplugin
{
	
using namespace WrtDeviceApis::Commons;
using namespace WrtDeviceApis::CommonsJavaScript;


class DataClass
{
public:
	std::string uuid;
};


EmailpluginMaster::EmailpluginMaster()
{

}

GVariant* jsValueToGVariant(JSContextRef ctx, JSValueRef jsVal, std::string signature)
{
	LoggerE("Entered");

	JSType type = JSValueGetType(ctx, jsVal);

	LoggerE("JSType: " << type <<" signature: "<<signature);

	Converter converter(ctx);

	if(type == kJSTypeString)
	{
		std::string result = converter.toString(jsVal);
		
		return g_variant_new(signature.c_str(), result.c_str());
	}

	else if(type == kJSTypeNumber)
	{
		if(signature == "i" || signature == "y")
		{
			return g_variant_new(signature.c_str(), converter.toInt(jsVal));
		}
		
		else if(signature == "q")
		{
			return g_variant_new(signature.c_str(), converter.toULong(jsVal));
		}
		else if(signature == "d")
		{
			return g_variant_new(signature.c_str(), converter.toDouble(jsVal));
		}
		
	}

	else if(type == kJSTypeBoolean)
	{
		return g_variant_new(signature.c_str(), converter.toBool(jsVal));
	}

	else if(type == kJSTypeObject)
	{

	}

	return nullptr;
}

std::string mapToJSon(std::map<std::string, GVariant*> propertyMap)
{
	std::stringstream json;

	json<<"{";

	for(auto itr = propertyMap.begin(); itr != propertyMap.end(); itr++)
	{
		if(json.str() != "{") json<<",";

		std::string key = (*itr).first;

		/// make lowerCamelCase:
		std::transform(key.begin(), key.begin()+1, key.begin(), ::tolower);

		GVariant* var = (*itr).second;

		gsize size;
			
		json<<"\""<<key<<"\" : "<<json_gvariant_serialize_data(var,&size);
			
		//g_variant_unref(var);

	}

	json << "}";
	
	return json.str();
}


EmailpluginMaster::ErrorType EmailpluginMaster::addAccount(std::string emailid,std::string acntId,std::string pwd,std::string server,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("addAccount Entered");

        EmailpluginSubscribeCB * cbObj = new EmailpluginSubscribeCB;
        cbObj->callback = successCallback;
        cbObj->errorCallback = errorCallback;
        cbObj->context = context;
	LoggerE("email id param %s, %s, %s %s",emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());

   	bool  flag=false;

	flag = add_account_with_validation(emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());
        JSObjectCallAsFunction(cbObj->context, cbObj->callback, NULL, 0, NULL, NULL);
	LoggerE("addAccount exiting %d",flag);
	return None;
}


EmailpluginMaster::ErrorType EmailpluginMaster::deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("deleteAccount Entered");
        EmailpluginSubscribeCB * cbObj = new EmailpluginSubscribeCB;
        cbObj->callback = successCallback;
        cbObj->errorCallback = errorCallback;
        cbObj->context = context;
	
LoggerE("email id to delete %d ",acntId);

   	bool  flag=false;

	flag = delete_account(acntId);
          
        JSObjectCallAsFunction(cbObj->context, cbObj->callback, NULL, 0, NULL, NULL);
	LoggerE("deleteAccount exiting");
        return None;

}


}
}

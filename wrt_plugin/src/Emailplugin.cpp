/*******************************************************************************
*File name:        Emailplugin.cpp
*Functionality:    This file exports the email functions which are  called from
                   JSEmailplugin.cpp.This is the entry point to the Email library.
                   This file calls functions from email_stubs.cpp which form the 
                   core of email functionality.
                   Specifically this file provides just 2 functions.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
*Last Date Modified: 23/07/2014
********************************************************************************/

/*This header file exports Email functions to the JSON(JS*.cpp) file  */
#include "Emailplugin.h"
/*included here to call the core email functions*/
#include "email_stubs.h"

/*following header files are taken as is from the Vehicle sample WRT file module as is*/
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

/*Email Object class and namespace creation
  The following section of the code is taken as is from Vehicle WRT plugin.
  Only name changes are done.
*/
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


/**********************************************************************************************************
Function Name: addAccount()
Details: This fucntion is used to create an account.Takes emailId,Account/Service ID and password as input.
           This function internally calls the core function from email_stubs.cpp.
           Only  function specific parameters are explained.The generic parameters which are part the 
           WRT Plugin library creation template are not defined.

Input parameters: 
                     emailid : Email Id of which an account to be created
                     acntId  : service Name or Account name whose account need to be created. 
                     pwd     : Password for the email account.          

Output Parameters : NONE

Return Values     : SUCCESS OR FAIL
************************************************************************************************************/


EmailpluginMaster::ErrorType EmailpluginMaster::addAccount(std::string emailid,std::string acntId,std::string pwd,std::string server,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("addAccount Entered");
       //Keep the Cobj parameters as is if needed.Used from Vehicle Example. 
        EmailpluginSubscribeCB * cbObj = new EmailpluginSubscribeCB;
        cbObj->callback = successCallback;
        cbObj->errorCallback = errorCallback;
        cbObj->context = context;
	LoggerE("email id param %s, %s, %s %s",emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());

         //Make a call to the core function to create local account for the email id,service name and passwor
         //mentioned.
	int flag = add_account_with_validation(emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());
        JSObjectCallAsFunction(cbObj->context, flag==TRUE?cbObj->callback:cbObj->errorCallback, NULL, 0, NULL, NULL);
	LoggerE("addAccount exiting %d",flag);
	return None;
}


/**********************************************************************************************************
Function Name: deleteAccount()
Details: This fucntion is used to delete an account.Takes AccountID as input.
           This function internally calls the core function from email_stubs.cpp.
           Only  function specific parameters are explained.The generic parameters which are part the 
           WRT Plugin library creation template are not defined.

Input parameters: 
                     acntId  : email id   whose account need to be deleted. 

Output Parameters : NONE

Return Values     : SUCCESS OR FAIL
************************************************************************************************************/

EmailpluginMaster::ErrorType EmailpluginMaster::deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("deleteAccount Entered");
       //Keep the Cobj parameters as is if needed.Used from Vehicle Example. 
        EmailpluginSubscribeCB * cbObj = new EmailpluginSubscribeCB;
        cbObj->callback = successCallback;
        cbObj->errorCallback = errorCallback;
        cbObj->context = context;
	
        LoggerE("email id to delete %d ",acntId);

   	bool  flag=false;
        //Make a call to the core function to delete the account matching to the email id.
	flag = delete_account(acntId);
          
        JSObjectCallAsFunction(cbObj->context, cbObj->callback, NULL, 0, NULL, NULL);
	LoggerE("deleteAccount exiting");
        return None;

}


}
}

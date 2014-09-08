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
*Last Date Modified: 09/08/2014
********************************************************************************/

/*This header file exports Email functions to the JSON(JS*.cpp) file  */
#include "Emailplugin.h"
/*included here to call the core email functions*/
#include "email_stubs.h"

#include <Logger.h>
#include <CommonsJavaScript/Converter.h>

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

/**********************************************************************************************************
Function Name: addAccount()
Details: This fucntion is used to create an account.Takes emailId,Account/Service ID and password as input.
           This function internally calls the core function from email_stubs.cpp.
           Only  function specific parameters are explained.The generic parameters which are part the 
           WRT Plugin library creation template are not defined.

Input parameters:    emailid : Email Id of which an account to be created
                     acntId  : service Name or Account name whose account need to be created. 
                     pwd     : Password for the email account.          

Output Parameters : NONE
************************************************************************************************************/

void EmailpluginMaster::addAccount(const std::string &emailid,const std::string &acntId,const std::string &pwd,
					const std::string &server,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("addAccount email id param %s, %s, %s %s",emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());

        // Make a call to the core function to create local account for the email id,service name and password
	int flag = add_account_with_validation(emailid.c_str(),acntId.c_str(),pwd.c_str(),server.c_str());
        JSObjectCallAsFunction(context, flag?successCallback:errorCallback, NULL, 0, NULL, NULL);
	LoggerE("addAccount exiting %d",flag);
}

/**********************************************************************************************************
Function Name: deleteAccount()
Details: This fucntion is used to delete an account.Takes AccountID as input.
           This function internally calls the core function from email_stubs.cpp.
           Only  function specific parameters are explained.The generic parameters which are part the 
           WRT Plugin library creation template are not defined.

Input parameters: acntId  : email id   whose account need to be deleted. 

Output Parameters : NONE
************************************************************************************************************/

void EmailpluginMaster::deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
        LoggerE("deleteAccount entered: email id to delete %d ",acntId);

        //Make a call to the core function to delete the account matching to the email id.
	bool flag = delete_account(acntId);
          
        JSObjectCallAsFunction(context, flag?successCallback:errorCallback, NULL, 0, NULL, NULL);
	LoggerE("deleteAccount exiting");
}

/**********************************************************************************************************
Function Name: updateSeenFlag()
Details: This function exists solely as a workaround for a bug in WRT. Seen flags do not sync with the server properly.

Input parameters: accountId, mailId 

Output Parameters : NONE
************************************************************************************************************/
void EmailpluginMaster::updateSeenFlag(int accountId, int mailId, bool isReadChangeStatus, JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context)
{
	LoggerE("updating seen flag for mail item %d",mailId);
	
	bool flag=update_seen_flag(accountId,mailId,isReadChangeStatus);
	JSValueRef value=JSValueMakeNumber(context,mailId);
	const JSValueRef arguments[1]={ value };
	JSObjectCallAsFunction(context,flag?successCallback:errorCallback,NULL,1,arguments,NULL);
}

}
}

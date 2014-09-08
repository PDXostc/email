/*******************************************************************************
*File name:        Emailplugin.h
*Functionality:    This file exports the email functions which are  called from
                   JSEmailplugin.cpp.This is the entry point to the Email library.
                   Specifically this file provides just 2 functions.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
* Modified Date: 09/08/2014
**********************************************************************************/

#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

//The below header files taken as is from the original Vehicle example. 
#include <string>
#include <dpl/shared_ptr.h>
#include <JavaScriptCore/JavaScript.h>

namespace DeviceAPI {
namespace Emailplugin {

class EmailpluginMaster
{
public:
        //Adds am account based on the input acnt ID.
	void addAccount(const std::string &email,const std::string &acnt,const std::string &pass, const std::string &server,
	                                        JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context);
        //Deletes an account based on the input acnt ID
	void deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context);

	// update seen flag (wrt-plugin-tizen contains a bug which causes IMAP server to be out of sync)	
	void updateSeenFlag(int accountId, int mailId, bool isReadChangeStatus, JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context);
};

typedef DPL::SharedPtr<EmailpluginMaster> EmailpluginPtr;

}
}
#endif // EMAILPLUGIN_H

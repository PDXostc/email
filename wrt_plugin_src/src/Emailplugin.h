/*******************************************************************************
*File name:        Emailplugin.h
*Functionality:    This file exports the email functions which are  called from
                   JSEmailplugin.cpp.This is the entry point to the Email library.
                   Specifically this file provides just 2 functions.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
* Modified Date: 23/07/2013
**********************************************************************************/

#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

//The below header files taken as is from the original Vehicle example. 
#include <list>
#include <string>
#include <map>
#include <dpl/mutex.h>
#include <dpl/shared_ptr.h>
#include <JavaScriptCore/JavaScript.h>
#include <gio/gio.h>
#include <Logger.h>

class AbstractPropertyType;

namespace DeviceAPI {
namespace Emailplugin {

class EmailpluginSubscribeCB
{
public: 
	JSObjectRef callback;
	JSObjectRef errorCallback;
	JSContextRef context;
};


class EmailpluginMaster
{
public:
        //Error codes for the API
	enum ErrorType {
		None = 0,
		NotSupported = 1,
		PermissionDenied = 2,
		InvalidArguments = 3,
		Unknown = 10
	};


	EmailpluginMaster();
	
private: /// methods:

public:
        //Called from JS object 
       
        //Adds am account based on the input acnt ID.
	EmailpluginMaster::ErrorType addAccount(std::string email,std::string acnt,std::string pass, std::string server,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context );
        //Deletes am account based on the input acnt ID
	EmailpluginMaster::ErrorType deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context);

};

typedef DPL::SharedPtr<EmailpluginMaster> EmailpluginPtr;


}
}
#endif // EMAILPLUGIN_H

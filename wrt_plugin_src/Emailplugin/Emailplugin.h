#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

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
	EmailpluginMaster::ErrorType addAccount(std::string email,std::string acnt,std::string pass, std::string server,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context );
	EmailpluginMaster::ErrorType deleteAccount(int acntId,JSObjectRef successCallback, JSObjectRef errorCallback, JSContextRef context);

};

typedef DPL::SharedPtr<EmailpluginMaster> EmailpluginPtr;


}
}
#endif // EMAILPLUGIN_H

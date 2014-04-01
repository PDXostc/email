#ifndef EMAIL_STUBS_H
#define EMAIL_STUBS_H

#include <stdio.h>
/* These functions are exported to the Emailplugin.cpp*/

gboolean delete_account(int acntId );
gboolean add_account_with_validation(const char* emailid,const char* acnt,const char* pwd,const char *server );

#endif //EMAIL_STUBS_H

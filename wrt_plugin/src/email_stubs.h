/*******************************************************************************
*File name:        email_stubs.h
*Functionality:    This file exports  the basic email functions.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
* Last Date Modified: 23/07/2014
********************************************************************************/
#ifndef EMAIL_STUBS_H
#define EMAIL_STUBS_H

#include <stdio.h>
/* These functions are exported to the Emailplugin.cpp*/
//Delete an account.
gboolean delete_account(int acntId );
//Add an account matching to the email id.
gboolean add_account_with_validation(const char* emailid,const char* acnt,const char* pwd,const char *server );

#endif //EMAIL_STUBS_H

/*******************************************************************************
*File name:        email_stubs.h
*Functionality:    This file exports  the basic email functions.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
* Last Date Modified: 09/08/2014
********************************************************************************/
#ifndef EMAIL_STUBS_H
#define EMAIL_STUBS_H

/* These functions are exported to the Emailplugin.cpp*/
//Delete an account.
bool delete_account(int acntId );
//Add an account matching to the email id.
bool add_account_with_validation(const char* emailid,const char* acnt,const char* pwd,const char *server );
bool update_seen_flag(int accID, int mailID, bool change_status);

#endif //EMAIL_STUBS_H

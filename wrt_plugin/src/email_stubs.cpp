/*******************************************************************************
*File name:        email_stubs.cpp
*Functionality:    This file exports the email functions which are  called from
                   Emailplugin.cpp. This file provides just 2 functions.
                   This file is partilally  reused from the email-service/utilite/test-account.c file.
                   This provides two basic functions to add and delete accounts.
                   1. addAccount.
                   2. Delete Account.
  
* Author      : TCS & JLR
* Owner       : JLR
* Last Date Modified: 23/07/2014
********************************************************************************/
/* common header */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <glib.h>

#include <db-util.h>
#include <email-api.h>
#include <email-api-account.h>
#include <email-api-network.h>
#include <sys/time.h>
#include <sys/times.h>
#include <memory.h>

#include <Logger.h>

#include "email_stubs.h"

/* internal defines */
//Define an array with the supported mail servers.We can create accounts only for these.
//If you want to add new server support update the count and list.
//also, add a new switch Case with relevent port details.
#define MAIL_SERVER_COUNT  10
char *emailServer[MAIL_SERVER_COUNT]= {"MsExchange","MobileMe","Gmail","Yahoo","Aol","Other"};

/******************************************************************** 
 * Function Name: create_account_object()
 * Details      : This functions creates an email account structure with all
 *                the relevent fields filled in. this structure is passed to
 *                the email-services library to create the account.
 * Input Params:
 *              address_string = email Id of the user for whom an account needs to be created
 *              id_string = Account IDentification string.
 *              password_string= Password for the mail.
 *              server = server name.
 * Out Params:
 *             result_account = Populated email structure based on input params.
 *                              To be used in verifying and creating account
 *  Return: TRUE   :On successfull addition
 *          FALSE  :On failure                                                    
 *************************************************************** */
bool create_account_object(email_account_t **result_account,const char* address_string,const char* id_string,const char* password_string,const char *server )
{
	email_account_t *account = NULL;
	int samsung3g_account_index;
	int result_from_scanf = 0;
	int account_type=0xff;

	 // Verify if the new account to be created is listed in the server list.
	 //If not flag the error.
        for(int i=0;i <MAIL_SERVER_COUNT;i++)
	{
	  if(strcmp(emailServer[i],server)==0)
	  {
             account_type = i;
             break;
	  }
	}       
        
	if(account_type == 0xff)
	{
	   LoggerE("Invaldi server name %s\n",server);
           return false;  
	}
        
	//Create email account structure.
	account = (email_account_t*)malloc(sizeof(email_account_t));
	memset(account, 0x00, sizeof(email_account_t));

	typedef struct {
		int is_preset_account;
		int index_color;
	} user_data_t;
	user_data_t data = (user_data_t) {1, 0};
	/* if user_data_t has any pointer member, please don't use sizeof(). */
	/* You need to serialize user_data to buffer and then take its length */
	int data_length = sizeof(data);

	/* Common Options.Set up the structure */
	account->retrieval_mode                          = EMAIL_IMAP4_RETRIEVAL_MODE_ALL;
	account->incoming_server_secure_connection	     = 1;
	account->outgoing_server_type                    = EMAIL_SERVER_TYPE_SMTP;
	account->auto_download_size			             = 2;
	account->outgoing_server_use_same_authenticator  = 1;
	account->pop_before_smtp                         = 0;
	account->incoming_server_requires_apop           = 0;
	account->logo_icon_path                          = NULL;
	account->user_data                               = malloc (data_length);
	memcpy( account->user_data, (void*) &data, data_length );
	account->user_data_length                        = data_length;
	account->options.priority                        = EMAIL_MAIL_PRIORITY_HIGH;
	account->options.keep_local_copy                 = 1;
	account->options.req_delivery_receipt            = 0;
	account->options.req_read_receipt                = 0;
	account->options.download_limit                  = 0;
	account->options.block_address                   = 0;
	account->options.block_subject                   = 0;
	account->options.display_name_from               = NULL;
	account->options.reply_with_body                 = 0;
	account->options.forward_with_files              = 0;
	account->options.add_myname_card                 = 0;
	account->options.add_signature                   = 0;
	account->options.signature                       = NULL;
	account->options.add_my_address_to_bcc           = EMAIL_ADD_MY_ADDRESS_OPTION_ALWAYS_ADD_TO_BCC;
	account->check_interval                          = 0;
	account->keep_mails_on_pop_server_after_download = 1;
	account->default_mail_slot_size                  = 200;
    //Now pass the user inputs like email id,password ,server name etc.
	account->account_name                            = strdup(address_string);
	account->user_display_name                       = strdup(id_string);
	account->user_email_address                      = strdup(address_string);
	account->reply_to_address                        = strdup(address_string);
	account->return_address                          = strdup(address_string);

	account->incoming_server_user_name               = strdup(address_string);
	account->incoming_server_password                = strdup(password_string);
	account->outgoing_server_user_name               = strdup(address_string);
	account->outgoing_server_password	         = strdup(password_string);
   //Now pass the server specific details like incoming,outgoing port numbers.
   //connection type, authentication etc.These should match with the
   //server side details. The details of which can be found online.
	//If you want to add a new server,add a new 'case' with appropriate details.
	switch (account_type) {

                case 0:/*  MsExchange*/
                        account->incoming_server_type  = EMAIL_SERVER_TYPE_POP3;
                        account->incoming_server_address= strdup("outlook.office365.com");
                        account->incoming_server_port_number = 993;
                        account->incoming_server_secure_connection      = 1;
                        account->outgoing_server_address    = strdup("smtp.office365.com");
                        account->outgoing_server_port_number = 587;
                        account->outgoing_server_secure_connection = 1;
                        account->outgoing_server_need_authentication = 1;
                        break;

                case 1:/*  MobileMe*/
                        account->incoming_server_type  = EMAIL_SERVER_TYPE_POP3;
                        account->incoming_server_address= strdup("mail.me.com");
                        account->incoming_server_port_number = 143;
                        account->incoming_server_secure_connection      = 1;
                        account->outgoing_server_address    = strdup("mail.me.com");
                        account->outgoing_server_port_number = 25;
                        account->outgoing_server_secure_connection = 1;
                        account->outgoing_server_need_authentication = 1;
                        break;

//GMail POP3
/*		case 1:
			account->incoming_server_type  = EMAIL_SERVER_TYPE_POP3;
			account->incoming_server_address= strdup("pop.gmail.com");
			account->incoming_server_port_number = 995;
			account->incoming_server_secure_connection	= 1;
			account->outgoing_server_address    = strdup("smtp.gmail.com");
			account->outgoing_server_port_number = 465;
			account->outgoing_server_secure_connection = 1;
			account->outgoing_server_need_authentication = 1;
			break;
*/
		case 2: /*  Gmail IMAP4 */
			account->incoming_server_type  = EMAIL_SERVER_TYPE_IMAP4;
			account->incoming_server_address= strdup("imap.gmail.com");
			account->incoming_server_port_number = 993;
			account->incoming_server_secure_connection	= 1;
			account->outgoing_server_address    = strdup("smtp.gmail.com");
			account->outgoing_server_port_number = 465;
			account->outgoing_server_secure_connection = 1;
			account->outgoing_server_need_authentication = 1;
			break;

		case 3: /* Yahoo IMAP ID */
			account->incoming_server_type  = EMAIL_SERVER_TYPE_IMAP4;
			account->incoming_server_address= strdup("imap.mail.yahoo.com");
			account->incoming_server_port_number = 993;
			account->incoming_server_secure_connection	= 1;
			account->outgoing_server_address    = strdup("smtp.mail.yahoo.com");
			account->outgoing_server_port_number = 465;
			account->outgoing_server_secure_connection = 1;
			account->outgoing_server_need_authentication = 1;
			break;

		case 4: /*  AOL */
			account->incoming_server_type  = EMAIL_SERVER_TYPE_IMAP4;
			account->incoming_server_address= strdup("imap.aol.com");
			account->incoming_server_port_number = 993;
			account->incoming_server_secure_connection	= 1;
			account->outgoing_server_address    = strdup("smtp.aol.com");
			account->outgoing_server_port_number = 587;
			account->outgoing_server_secure_connection = 1;
			account->outgoing_server_need_authentication = 1;
			break;


		case 5: /*  Other */
			account->incoming_server_type  = EMAIL_SERVER_TYPE_IMAP4;
			account->incoming_server_address= strdup("imap.aol.com");
			account->incoming_server_port_number = 143;
			account->incoming_server_secure_connection	= 0;
			account->outgoing_server_address    = strdup("smtp.aol.com");
			account->outgoing_server_port_number = 587;
			account->outgoing_server_secure_connection = 0;
			account->outgoing_server_need_authentication = 1;
			break;
//Hotmail
/*
		case x: 
			account->incoming_server_type  = EMAIL_SERVER_TYPE_POP3;
			account->incoming_server_address= strdup("pop3.live.com");
			account->incoming_server_port_number = 995;
			account->incoming_server_secure_connection	= 1;
			account->outgoing_server_address    = strdup("smtp.live.com");
			account->outgoing_server_port_number = 587;
			account->outgoing_server_secure_connection  = 0x02;
			account->outgoing_server_need_authentication = 1;
			break;
*/

		default:
			LoggerE("Invalid Account Number\n");
			email_free_account(&account, 1);
			return false;
	}
	account->account_svc_id = 77; // omg!!

	if(result_account)
		*result_account = account;

	return (*result_account!=0);
}

/*****************************************************************************************************
 * Function Name: delete_account()
* Details:This is the  function called from the Emailplugin object to
*         delete account.
* Input params:
*   	 account_id: email id to be deleted.
*   	 
* Out Params:None
*    
* Return: 
*     true   :On successfull addition.
*     false  :On failure. 
******************************************************************************************************/
bool delete_account(int account_id)
{
        email_account_t *account=NULL;
        int err = EMAIL_ERROR_NONE;
        //Check if  the account is already created and available in the system.
        if( (err = email_get_account(account_id, WITHOUT_OPTION,&account)) < 0) {
                LoggerE ("email_get_account failed \n");
                LoggerE("delete_account failed\n");
        }
        else {
        	    //Account is locally created.You can go ahead with the delete.
                LoggerE("email_get_account result account_name - %s \n", account->account_name);

                if((err = email_delete_account(account_id)) < 0)
                        LoggerE ("email_delete_account failed[%d]\n", err);
                else
                        LoggerE ("email_delete_account successful \n");
        }
        return (err==EMAIL_ERROR_NONE);
}

/*****************************************************************************************************
 * Function Name: add_account_with_validation()
 * Details      : This is the main function called from Emailplugin.cpp to create the account.
 *                This internally calls other fucntions from email-services library.
 * Input Params:
 *              emailid = email Id of the user for whom an account needs to be created
 *              acnt = Account IDentification string.
 *              pwd= Password for the mail.
 *              server = server name.
 * 
 * Out Params  :None              
 * 
 *  Return: true   :On successful addition
 *          false  :On failure     
******************************************************************************************************/
bool add_account_with_validation(const char* emailid,const char* acnt,const char* pwd,const char* server )
{

	LoggerE ("inside add_account_with_validation\n");
	int err = EMAIL_ERROR_NONE;
	email_account_t *account = NULL;
	int handle;
        
	// first create an account objects. This object will have all the details needed to
	// create an email account using the email library.
	// Hence pass on the input params. 
	if(!create_account_object(&account,emailid,acnt,pwd,server)) {
		LoggerE ("add_account_with_validation error\n");
		return false;
	}
        
	// Actually account creation addition happens here.
	// Structure filled from previous call is passed here.
	err = email_add_account_with_validation(account, &handle);
	if( err < 0)
		LoggerE ("email_add_account_with_validation error : %d\n", err);
	else	
		LoggerE("email_add_account succeeded. account_id =%d \n", account->account_id);
        
	// Just delete the temporary structure malloced earlier inside the
	// create_account_object function.
	err = email_free_account(&account, 1);

	return (err==EMAIL_ERROR_NONE);
}

bool update_seen_flag(int accID, int mailID, bool change_status)
{
    return (accID > -1 && EMAIL_ERROR_NONE != email_set_flags_field(accID, &mailID, 0, EMAIL_FLAGS_SEEN_FIELD, change_status, 1));
}

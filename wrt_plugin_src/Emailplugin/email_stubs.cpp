/*
 This file is partilally  reused from the email-service/utilite/test-account.c file.
 This provides two basic functions to add and delete accounts.
*/



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

#define GWB_RECV_SERVER_ADDR  	    "pop.gawab.com"
#define GWB_SMTP_SERVER_ADDR  	    "smtp.gawab.com"
#define VDF_RECV_SERVER_ADDR        "imap.email.vodafone.de"
#define VDF_SMTP_SERVER_ADDR        "smtp.email.vodafone.de"

/*  SAMSUNG 3G TEST */
#define S3G_RECV_SERVER_ADDR		"165.213.73.235"
#define S3G_RECV_SERVER_PORT		EMAIL_POP3_PORT
#define S3G_RECV_USE_SECURITY		0
#define S3G_RECV_IMAP_USE_SECURITY	1
#define S3G_SMTP_SERVER_ADDR		"165.213.73.235"
#define S3G_SMTP_SERVER_PORT		465
#define S3G_SMTP_AUTH		        1
#define S3G_SMTP_USE_SECURITY	        1
#define S3G_KEEP_ON_SERVER		1



/*****************************************************************************************************
    This function creates an email_acount structure with all the necessary parameters 
    like server,username,pasword etc.
    input params:
   	 emailid: email id to be added.
	 actn:Account name
	 pwd:password
    outparams:
         result_account: filled in email acnt structure for further processing.
    
    Return: TRUE   :On successfull addition
            FALSE  :On failure 
******************************************************************************************************/
#define MAIL_SERVER_COUNT  10
char *emailServer[MAIL_SERVER_COUNT]= {"MsExchange","MobileMe","Gmail","Yahoo","Aol","Other"};

gboolean  create_account_object(email_account_t **result_account,const char* address_string,const char* id_string,const char* password_string,const char *server )
{
	email_account_t *account = NULL;
	int samsung3g_account_index;
	int result_from_scanf = 0;
	int account_type=0xff;

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

	account = (email_account_t*)malloc(sizeof(email_account_t));
	memset(account, 0x00, sizeof(email_account_t));

	LoggerE("1\n");

	typedef struct {
		int is_preset_account;
		int index_color;
	} user_data_t;
	user_data_t data = (user_data_t) {1, 0};
	/* if user_data_t has any pointer member, please don't use sizeof(). */
	/* You need to serialize user_data to buffer and then take its length */
	int data_length = sizeof(data);

	/* Common Options */
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

	account->account_name                            = strdup(address_string);
	account->user_display_name                       = strdup(id_string);
	account->user_email_address                      = strdup(address_string);
	account->reply_to_address                        = strdup(address_string);
	account->return_address                          = strdup(address_string);

	account->incoming_server_user_name               = strdup(address_string);
	account->incoming_server_password                = strdup(password_string);
	account->outgoing_server_user_name               = strdup(address_string);
	account->outgoing_server_password	         = strdup(password_string);

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
			return FALSE;
			break;
	}
	account->account_svc_id = 77;

	LoggerE("2\n");
	if(result_account)
		*result_account = account;

	return TRUE;
}

/*****************************************************************************************************
    This is the main function called from the Emailplugin object to add account.
    input params:
   	 emailid: email id to be added.
	 actn:Account name
	 pwd:password
    
    Return: TRUE   :On successfull addition
            FALSE  :On failure 
******************************************************************************************************/
gboolean delete_account(int account_id)
{
        email_account_t *account=NULL;
        int err = EMAIL_ERROR_NONE;

        if( (err = email_get_account(account_id, WITHOUT_OPTION,&account)) < 0) {
                LoggerE ("email_get_account failed \n");
                LoggerE("delete_account failed\n");
        }
        else {
                LoggerE("email_get_account result account_name - %s \n", account->account_name);

                if((err = email_delete_account(account_id)) < 0)
                        LoggerE ("email_delete_account failed[%d]\n", err);
                else
                        LoggerE ("email_delete_account successful \n");
        }
        return err;
}

/*****************************************************************************************************
    This is the main function called from the Emailplugin object to add account.
    input params:
   	 emailid: email id to be added.
	 actn:Account name
	 pwd:password
    
    Return: TRUE   :On successfull addition
            FALSE  :On failure 
******************************************************************************************************/
gboolean add_account_with_validation(const char* emailid,const char* acnt,const char* pwd,const char* server )
{

		LoggerE ("inside add_account_with_validation\n");
	int err = EMAIL_ERROR_NONE;
	email_account_t *account = NULL;
	int handle;

	if(!create_account_object(&account,emailid,acnt,pwd,server)) {
		LoggerE ("add_account_with_validation error\n");
		return FALSE;
	}

	err = email_add_account_with_validation(account, &handle);
	if( err < 0) {
		LoggerE ("email_add_account_with_validation error : %d\n", err);
		err = email_free_account(&account, 1);
		return FALSE;
	}

	LoggerE ("email_add_account succeed. account_id =%d \n", account->account_id);

	err = email_free_account(&account, 1);

	return TRUE;
}


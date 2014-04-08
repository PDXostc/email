var stubTesting = false; // Make it true to Test only the GUI Screens


var currentScreenLoaded = null;
var selectedAccountType = null;
var count =0;
var FIXED = 0;
var currentEmailAccountSelected = null;
var currentMailId = null;
var currentServiceId = null;
var INBOX = "Inbox : ";
var syncId = null;
var gMessagesListenerId = null;
var mailType = null;//check for mail type ex- Inbox,Drafts etc...
var accountInfo = [{id:"1",name:"name"},{id:"2",name:"name2"}];
//var accountInfo = new Array();

var accountDetails = new Array();
var draftMailTypeCounter = 0;
var filesArray = new Array();
var fileAttached = new Array();
var fileCounter = 0;

var timerStarted = null;
var lastAccountId = 0;

var _TIMER_ACCOUNT = 30000;

/************Services Variables Declaration***************************/
var emailService = new Array();
var selectedService = {};

/************End of Services Variables ***************************/

//Messages for Stub testing //TODO: Can be remove later  
var mailMessages = [ {
	to : ["dasda","uiouiou","mnmlk"],
	from : "fromAddress first",
	date : "02nd March 2013",
	mailBody : "Mail Body of the first mail",
	subject : "Subject of First Mail",
	isRead : false,
	mailId : "1",
	folderId:"9",
	hasAttachment : true,
	attachments:[{filePath:"abc/defr",mimeType:"img",id:1},{filePath:"abc/defr",mimeType:"img",id:2},{filePath:"abc/defr",mimeType:"img",id:3},{filePath:"abc/defr",mimeType:"img",id:4}]
}, {
	to : "toAddress Second",
	from : "fromAddress second",
	date : "03nd March 2013",
	mailBody : "Mail Body of the second mail",
	subject : "Subject of Second Mail",
	isRead : true,
	mailId : "2",
	folderId:"9",
	hasAttachment : false,
	attachments:[{filePath:"abc/defr",name:"filename3"}]
}, {
	to : "toAddress third",
	from : "fromAddress third",
	date : "04nd March 2013",
	mailBody : "Mail Body of the third mail",
	subject : "Subject of Third Mail",
	isRead : false,
	mailId : "3",
	folderId:"9",
	hasAttachment : false,
	attachments:[{filePath:"abc/defr",name:"filename5"}]
}, {
	to : "toAddress fourth",
	from : "fromAddress fourth",
	date : "05nd March 2013",
	mailBody : "Mail Body of the fourth mail",
	subject : "Subject of Fourth Mail",
	isRead : true,
	mailId : "4",
	folderId:"6",
	hasAttachment : false,
	attachments:[{filePath:""},{filePath:""}]
} ];

//Messages for Stub testing //TODO: Can be remove later  
var searchedmailMessages = [ {
	to : "toAddress",
	from : "fromAddress",
	date : "02nd March 2013",
	mailBody : "Mail Body of the first mail for search result",
	subject : "Search result : Subject Line one ",
	isRead : true,
	mailId : "1"
}, {
	to : "toAddress",
	from : "fromAddress",
	date : "02nd March 2013",
	mailBody : "Mail Body of the second mail for search result",
	subject : "Search result : Subject Line two",
	isRead : true,
	mailId : "2"
}, {
	to : "toAddress",
	from : "fromAddress",
	date : "02nd March 2013",
	mailBody : "Mail Body of the third mail for search result",
	subject : "Search result : Subject Line three",
	isRead : true,
	mailId : "3"
} ];

//Funtion to check whether Accounts already added 
function checkAccountAvailablity(){
	if (stubTesting) {
		if (accountInfo.length > 0) {

			loadChangeAccountScreen();
			lastAccountId = accountInfo[accountInfo.length-1].id ;
		} else {
			$("#addAccountDiv").css({"visibility":"visible"});
			$("#addAccountDetailsDiv").show();
		}
	}
	else
	{
		//TODO:
		tizen.messaging.getMessageServices("messaging.email", serviceListCB, errorCallbackAccount);

		$(".Sync").bind("vclick", registerListeners);
		console.log("Email Services have been read");

	}
}

//Save the user details and add the account
function saveDetails()
{
	console.log("Save button Pressed");
	
	//alert("hi")
	var emailAddress = $("#EmailAddressTextbox").val();
	var userName = $("#UsernameTextbox").val();
	var password = $("#PasswordTextbox").val();
	var description = $("#DescriptionTextbox").val();
	var emailType = selectedAccountType;
	if(stubTesting){
		try{
			var emailAddress = $("#EmailAddressTextbox").val();
			var userName = $("#UsernameTextbox").val();
			var password = $("#PasswordTextbox").val();
			var description = $("#DescriptionTextbox").val();


			
			currentEmailAccountSelected = emailAddress;
			console.log("Email Address :: "+emailAddress);
			console.log("User Name :: "+userName);
			console.log("Password :: "+password);
			console.log("Email Descriptions :: "+description);
			console.log("Email Type :: "+emailType);

			accountInfo.push({id : emailAddress, name : emailAddress});
			accountDetails.push({emailAddress:emailAddress,userName:userName,password:password,description:description,emailType:emailType})
			
			$("#progressDiv").css({"visibility":"visible"});
		}catch (e) {
			// TODO: handle exception
			console.error(e);
		}
	}else {
		//TODO: Need to CALL WRT API and verify newly added Acount
		console.log("Email Address :: "+emailAddress);
		console.log("User Name :: "+userName);
		console.log("Password :: "+password);
		console.log("Email Descriptions :: "+description);
		console.log("Email Type :: "+emailType);
		
		console.log("WRT Plugin called for ");
		
		//Added to display visibility of progress div
		$("#progressDiv").css({"visibility":"visible"});
		
		tizen.emailplugin.addAccount(emailAddress,userName,password,emailType,successCB,errorCB);
		
	}
	if(timerStarted){
		clearTimeout(timerStarted);
	}
	
	console.log("Timer started for "+_TIMER_ACCOUNT)
	
	//$("#progressDiv").css({"visibility":"visible"});
		timerStarted = setTimeout(_timer,_TIMER_ACCOUNT);
}

var _timer = function(){
	console.log("Timer completed")
	
	$("#progressDiv").css({"visibility":"hidden"});
	
	$("#EmailAddressTextbox").val('');
	$("#UsernameTextbox").val('');
	$("#PasswordTextbox").val('');
	$("#DescriptionTextbox").val('');
	
	//Check for the newly added Account
	checkAccountAvailablity();
	
	console.log("lastAccountId  "+lastAccountId);
	
	//Recent added account would be current selected
	currentEmailAccountSelected = lastAccountId ;
	
	loadInboxScreen();
}


var successCB = function(){
	console.log("Account Added succesfully");
}

var errorCB = function(){
	console.log("Account not added");
}

//Retrieve mail list filtering filter key(If present else get all mail list)
var retriveMail = function(type) {

	console.log("Inside Retrive mail");
	
	console.log("Inside Retrive mail,type:: "+type);
	
	draftMailTypeCounter = 0;

	mailType = type;
	if (stubTesting) {

		for(var i = 0 ; i < mailMessages.length; i++){
			if(mailType === "draft"){
				populateDraftScreen(mailMessages[i]);
			}else{
				populateInboxScreen(mailMessages[i]);
			}
			if(mailMessages[i].folderId == "6"){
				draftMailTypeCounter = draftMailTypeCounter + 1;
			}
		}

	} else {
		//CALL WRT API and update ARRAY : "mailMessages"
		mailMessages = new Array();
		
		console.log("Inside Retrive mail, currentEmailAccountSelected :: "+currentEmailAccountSelected);
		
		var id = currentEmailAccountSelected;
		console.log("EmailService  "+JSON.stringify(emailService));
		var index = getArrayItemByProperty(emailService,"id",id);
		if(index)
		{
			selectedService = emailService[index.index];
			//console.log("SelectedService Stringfy:: "+JSON.stringify(selectedService));
			selectedService.messageStorage.findMessages( 
					new tizen.AttributeFilter("id", "CONTAINS", id), messageArrayCB,errorCallbackAccount);
//				new tizen.AttributeFilter("type", "EXACTLY", "messaging.email"), messageArrayCB);
		}
		else
		{
			console.log("Message Id Error");
		}
	}
}

//Retrieve mail list filtering with received message ID
var retriveMailFilterWithId = function (mailId) {

	loadMailFullViewScreen();
	var index = getArrayItemByProperty(mailMessages,
			"mailId", mailId);
	if (index.item) {
		setViewMails(index.item);
	} else {
		console.log(mailId
				+ " ::: MessageId received is incorrect");
	}
}

//Retrieve mail list filtering with next received message ID
var retriveMailFilterWithNextId = function() {
	var index = getArrayItemByProperty(mailMessages,
			"mailId", currentMailId);
	if (index.item !== null) {
		var nextMailItemIndex = index.index + 1;
		var nextMailItem = mailMessages[nextMailItemIndex];
		console.log("Next mail Item:"+JSON.stringify(nextMailItem))
		try{
			if(nextMailItem.folderId == "9"){
				setViewMails(nextMailItem);
			}else{
				currentMailId = nextMailItem.mailId;
				retriveMailFilterWithNextId();
			}
		}catch (e) {
			console.log(currentMailId
					+ " ::: is Last Mail from Inbox");
			return false;
		}

	} else {
		console.log(currentMailId
				+ " ::: MessageId received is incorrect");
	}
	return true;
}

//delete Mail Success call back
function deleteSuccessCallback() {
	console.log("Messages were deleted");
	if(currentScreenLoaded == "InboxScreen"){
		loadInboxScreen();
	}
}

//Deleting the "messages.length" number of mails 
function deleteMessageArrayCB(messages) {
	if (messages.length > 0) {
		console.log("deleting messages... "+messages.length);

		selectedService.messageStorage.removeMessages(messages, deleteSuccessCallback, errorCallback);
	} else {
		console.log("No messages found");
	}
}

//Delete mail request matching with mail Id
function deleteMailRequestByMailIds(mailIDs) {
	if(stubTesting){
		for (var i= 0 ; i< mailIDs.length; i++){
			var index = getArrayItemByProperty(mailMessages,"mailId",mailIDs[i]);
			if (index.index > -1) {
				mailMessages.splice(index.index, 1);
			}
		}
	}else{
		console.log("Inside the Delete mail by ID Function");
		//Called delete mails Web API
		try
		{
			for (var i= 0 ; i< mailIDs.length; i++){
				console.log("Mail Ids to be deleted are :" +JSON.stringify(mailIDs));
				var filter = new tizen.AttributeFilter("id", "CONTAINS",  mailIDs[i]);
				selectedService.messageStorage.findMessages(filter, deleteMessageArrayCB);
			}
		}
		catch(e)
		{
			console.log(e);
		}
	}
}

//Delete Account request
function deleteAccountRequest(searchIDs) {
	if(stubTesting){
		for (var i= 0 ; i< searchIDs.length; i++){
			var index = getArrayItemByProperty(accountInfo,"id",searchIDs[i]);
			if (index.index > -1) {
				accountInfo.splice(index.index, 1);
			}
		}
		
	}else{
		//TODO: Need to call delete account WRT Plug-in calls
		console.log("searchIDs[i] ID :: "+searchIDs[i]);
		//tizen.emailplugin.deleteAccount()
		for (var i= 0 ; i< searchIDs.length; i++){
			console.log("JSON stringify :: "+JSON.stringify(accountInfo))
			var index = getArrayItemByProperty(accountInfo,"id",searchIDs[i]);
			if (index && index.index > -1) {
				console.log("Index of Service ID for deletion :: "+index.index)
				console.log("Calling Delete Account WRT with ID :: "+accountInfo[index.index].id);
				tizen.emailplugin.deleteAccount(accountInfo[index.index].id,deleteAccSuccessCB,deleteErrCB);
				accountInfo.splice(index.index, 1);
			}
		}
		
	}
	if(accountInfo.length > 0){
		loadChangeAccountScreen();
	}else{
		loadAddAccountScreen();
	}
}

var deleteAccSuccessCB = function(){
	console.log("Account deleted succes");
	if(accountInfo.length > 0){
		loadChangeAccountScreen();
	}else{
		loadAddAccountScreen();
	}
}

var deleteErrCB = function(){
	console.log("Account not deleted");
}

/*
 * get array item by property value
 * search the data list for an item containing certain data
 * @param String data - the data string to look for
 * @return Object { itemId:Number, item:Object }
 */
var getArrayItemByProperty = function(array, property, value)
{
	var item = null;

	for (var i=0; i<array.length; i++)
	{
		if (value == array[i][property])
		{
			item = {
					index : i,
					item : array[i]
			};
			break;
		}
	}
	return item;
};

/******************************Services calls***********************************************/
//Sync with the Services
function syncEmails() {
	if(!stubTesting){
		console.log("Sync, inside function");
		console.log("Sync ID:" +syncId);
		if (syncId) {
			console.log("Other sync is in progress");
		} else {
			try {
				syncId = selectedService.sync(function() {
					console.log("Synchronization succeeded");
					syncId = null;
				}, function(err) {
					console.log("Synchronization failed:" + err.message);
					syncId = null;
				});
				console.log("Sync all started");
			} catch (exc) {
				console.log("Sync exc: " + exc.code + ":" + exc.message);
				syncId = null;
			}
		}
	}
}

//Define the error callback.
function errorCallbackAccount(err) {
	console.log(err.name + " error: " + err.message);
}

//Define the error callback.
function errorCallback(err) {
	console.log(err.name + " error: " + err.message);
}

//List of all the services available
function serviceListCB(services) { 
	accountInfo = new Array();
	console.log("Service  :: "+services);
	console.log("Service JSON.stringify :: "+JSON.stringify(services));
	if(services.length > 0 && services[0].name){

		console.log("Service callback :: "+services.length);
		
		for(var i = 0 ; i < services.length ; i++)
		{
			console.log("Service id :: "+services[i].id);
			console.log("Service name :: "+services[i].name);
			accountInfo.push({id : services[i].id , name : services[i].name});
			lastAccountId = services[i].id ;
		}
		emailService = services; 
		loadChangeAccountScreen();
	}else
	{
		//$("#addAccountDiv").css({"visibility":"visible"});
		//$("#addAccountDetailsDiv").show();
		loadAddAccountScreen();
		console.log("Service Not available callback :: showing loadAddAccountScreen");
	}
}

//Define success callback and load the mails on the screen
function loadMessageBody(message) {

	console.log ("from: " + message.from + "loaded.");
	var mailMsg = {};
	mailMsg["subject"] = message.subject;
	mailMsg["from"] = message.from;
	mailMsg["to"] = message.to[0];
	mailMsg["mailId"]= message.id;
	mailMsg["isRead"] = message.isRead;
	mailMsg["mailBody"] = message.body.plainBody;
	mailMsg["date"] = message.timestamp.toString();
	mailMsg["folderId"] = message.folderId;

	mailMessages.push(mailMsg);

	if(mailType === "draft"){
		populateDraftScreen(mailMsg);
	}else{
		populateInboxScreen(mailMsg);
	}
}

//Search Mail from existing mail record call
//The search mail is modified to accept only mail Body items during search.
function searchMailCall() {

	//clearing the old displayed mail
	clearInboxMails();

	var searchItem = $("#searchMailText").val();
	console.log("Need to Search::: "+searchItem);
	if(searchItem){
		if(stubTesting){
			loadInboxScreen("mailSearch");
		}else{
			var filter =  new tizen.AttributeFilter('plainBody', 'CONTAINS', searchItem);
			selectedService.messageStorage.findMessages(filter,messageArrayCB);
		}
	}else{
		console.log("Please Add Text into search Box");
	}
}

//Load the mails on the screen
function messageArrayCB(messages) {
	console.log('Messages: ' + messages.length);
	for(var i=0 ;i<messages.length;i++){
		try{
			console.log(i+" message one by one:: "+JSON.stringify(messages[i]));
			var mailMsg = {};
			var attachments = new Array();
			mailMsg["subject"] = messages[i].subject;
			console.log('Subject:: '+mailMsg["subject"]);
			mailMsg["from"] = messages[i].from;
			console.log('from:: '+mailMsg["from"]);
			mailMsg["to"] = messages[i].to;
			console.log('to:: '+mailMsg["to"]);
			mailMsg["mailId"]= messages[i].id;
			console.log('mailId:: '+mailMsg["mailId"]);
			mailMsg["isRead"] = messages[i].isRead;
			console.log('isRead:: '+mailMsg["isRead"]);
			mailMsg["mailBody"] = messages[i].body.plainBody;
			console.log('mailBody:: '+mailMsg["mailBody"]);
			mailMsg["date"] = messages[i].timestamp.toString();
			console.log('date:: '+mailMsg["date"]);
			mailMsg["folderId"] = messages[i].folderId;
			console.log('folderId:: '+mailMsg["folderId"]);

			mailMsg["hasAttachment"] = messages[i].hasAttachment;
			console.log('hasAttachment:'+mailMsg["hasAttachment"]);

			console.log('messages[i].attachments.length:  '+messages[i].attachments.length);

			for(var j = 0; j< messages[i].attachments.length;j++){
				attachments.push({filePath :messages[i].attachments[j].filePath , id : messages[i].attachments[j].id , mimeType : messages[i].attachments[j].mimeType})
				console.log("Attachment:" +JSON.stringify(messages[i].attachments[j]));
				console.log(j+' file Path :'+messages[i].attachments[j].filePath);
				console.log(j+' file id :'+messages[i].attachments[j].id);
				console.log(j+' mimeType :'+messages[i].attachments[j].mimeType);
			}

			mailMsg["attachments"] = attachments;
			mailMessages.push(mailMsg);

			//If folder id is 6 then increase the draft mail counter by 1
			if(messages[i].folderId == "6"){
				draftMailTypeCounter = draftMailTypeCounter + 1;
			}
			
			console.log("Checking mail type draft or inbox : "+mailType);
			if(mailType === "draft"){
				populateDraftScreen(mailMsg);
			}else{
				populateInboxScreen(mailMsg);
			}

			fillDraftCount();
		}catch(ex) {
			console.log("Get exception: " + ex.name + ":" + ex.message);
		}
	} 
}

//Send mail matched with the mailId
function sendMailWithId(id) {

	console.log("Sending draft mail of mailID "+id);
	var index = getArrayItemByProperty(mailMessages,
			"mailId", id);
	if (index.item) {
		var to = [];
		var cc = [];
		var bcc = [];
		var from = index.item.from;
		var subject = index.item.subject;
		var mailbody = index.item.mailBody;
		var hasAttachment = index.item.hasAttachment;

		if(index.item.to){
			to = index.item.to;
		}else{
			to = null;
		}

		if(index.item.cc){
			cc = index.item.cc;
		}else{
			cc = null;
		}

		if(index.item.bcc){
			bcc = index.item.bcc;
		}else{
			bcc = null;
		}
		console.log(to+" "+cc+" "+ bcc+" "+from+" "+subject+" "+mailbody);
		if(stubTesting){
			deleteMailRequestByMailIds(id);
			loadDraftScreen();
		}else{
			var msg = new tizen.Message("messaging.email",{id:id});

			selectedService.sendMessage(msg, messageSentCallback, errorCallback);
			inboxButtonSeleted();
		}
	} else {
		console.log(mailId
				+ " ::: MessageId is incorrect");
	}

}

//Send Mail from Compose screen
function sendMail() {
	console.log("Inside Send Mail Function");
	var to = [];
	var cc = [];
	var bcc = [];
	var from = $("#fromComposeDiv").text();;
	var subject = $("#subMember").val();
	var mailbody = $("#bodyDetails").val();
	var hasAttachment = false;
	var attachmentArray = new Array();

	if(fileAttached.length>0){
		hasAttachment = true;
	}



	if($("#toMember").val()){
		to = $("#toMember").val().split(';');
	}else{
		to = null;
	}

	if($("#ccMember").val()){
		cc = $("#ccMember").val().split(';');
	}else{
		cc = null;
	}

	if($("#bccMember").val()){
		bcc = $("#bccMember").val().split(';');
	}else{
		bcc = null;
	}

	if(stubTesting){
		loadInboxScreen("saveToDraft");
	}else{
		console.log("To:" +to+ "-CC:" +cc+ "-bcc:" +bcc);
		var msg = new tizen.Message("messaging.email",{to:to,cc:cc,bcc:bcc,from:from,subject:subject,plainBody:mailbody ,hasAttachment : hasAttachment});    

		for (var i = 0 ; i < fileAttached.length; i++){
			attachmentArray.push(new tizen.MessageAttachment(fileAttached[i]));
		}
		msg.attachments = attachmentArray;

		selectedService.sendMessage(msg, messageSentCallback, errorCallback);

		//inboxButtonSeleted();
		loadInboxScreen("saveToDraft");
	}

}

//Define the success callback.
var messageSentCallback = function(recipients) {
	console.log("Message sent successfully to " + recipients.length + " recipients.");
}


//Listener registered
function registerListeners() {
	var messagesChangeCB = {
			messagesadded : function(messages) {
				console.log("Tracking message :<br/>" + messages.length + " message(s) added");
			},
			messagesupdated : function(messages) {
				console.log("Tracking message :<br/>" + messages.length + " message(s) updated");
			},
			messagesremoved : function(messages) {
				console.log("Tracking message :<br/>" + messages.length + " message(s) removed");
			}
	}

	try {

		gMessagesListenerId = selectedService.messageStorage.addMessagesChangeListener(messagesChangeCB);
		console.log("Listening for Messages Change started");

		$(".Sync").unbind("vclick", registerListeners);
		$(".Sync").bind("vclick", unregisterListeners);
		console.log("Tracking started");
	} catch (exc) {
		console.log("addChangeListeners error:" + exc.message);
	}
}

//Sync Listners unregistered 
function unregisterListeners() {
	selectedService.messageStorage.removeChangeListener(gMessagesListenerId);
	$(".Sync").unbind("vclick", unregisterListeners);
	$(".Sync").bind("vclick", registerListeners);
	console.log("Tracking stopped");
}

//Filesystem Access : Success callback
function onsuccessFile(files) {
	console.log("There are " + files.length  + " in the selected folder");
	for(var i = 0 ; i < files.length ; i++){
		console.log(i+" :: Files content :: "+JSON.stringify(files[i]));
		if(files[i].isFile){
			filesArray.push(files[i]);
			fileCounter = fileCounter + 1;
		}
	}
	console.log("Files count :: "+fileCounter);

	//Populate the files on the Files Attachment screen
	if(files.length>0){
		populateAttachmentScreen();
	}
}

//Error callback while listing files
function onerrorFile(error) {
	console.log("The error " + error.message + " occurred when listing the files in the selected folder");
}

//List all the files from the root folders like "documents","downloads","images","music" and "videos"
function listAllFiles() {
	filesArray = new Array();
	fileCounter = 0;
	console.log("documents ListAllFiles Calling........");
	tizen.filesystem.resolve(
			"documents",
			function(dir){
				dir.listFiles(onsuccessFile, onerrorFile);
			}, function(e){
				console.log("Error " + e.message);
			}, "r"
	);
	console.log(" downloads ListAllFiles Calling........");
	tizen.filesystem.resolve(
			"downloads",
			function(dir){
				dir.listFiles(onsuccessFile, onerrorFile);
			}, function(e){
				console.log("Error " + e.message);
			}, "r"
	);
	console.log(" images ListAllFiles Calling........");
	tizen.filesystem.resolve(
			"images",
			function(dir){
				dir.listFiles(onsuccessFile, onerrorFile);
			}, function(e){
				console.log("Error " + e.message);
			}, "r"
	);
	console.log(" music ListAllFiles Calling........");
	tizen.filesystem.resolve(
			"music",
			function(dir){
				dir.listFiles(onsuccessFile, onerrorFile);
			}, function(e){
				console.log("Error " + e.message);
			}, "r"
	);
	console.log(" videos ListAllFiles Calling........");
	tizen.filesystem.resolve(
			"videos",
			function(dir){
				dir.listFiles(onsuccessFile, onerrorFile);
			}, function(e){
				console.log("Error " + e.message);
			}, "r"
	);
}






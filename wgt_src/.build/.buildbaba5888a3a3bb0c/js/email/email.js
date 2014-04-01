function deleteMail() {
	var element = document.getElementById('inboxScreen');
	element.style.opacity = "0.5";

	var element = document.getElementById('draftScreen');
	element.style.opacity = "0.5";

	var popUp = document.getElementById('deleteEmailPopDiv');
	popUp.style.visibility="visible";
}

function inboxButtonSeleted() {

	//Clear the search field if any pre - populated data available
	$("#searchMailText").val("");

	loadInboxScreen();
}

function deleteMailFromCompose() {
	var idToDelete = currentMailId;
	var status = retriveMailFilterWithNextId();
	var idToDeleteArray = [idToDelete];

	console.log(idToDeleteArray);
	deleteMailRequestByMailIds(idToDeleteArray);

	//Status false means deleted the last mail , Now redirecting to Inbox screen
	if(!status){
		inboxButtonSeleted();
	}
}

function deleteEmailYes() {
	$(".CheckBoxSelectAll").removeAttr("checked");
	var searchMailIDs = $(".InboxHandler input:checkbox:checked").map(function(){
		return $(this).val();
	}).toArray();
	console.log(searchMailIDs);

	deleteMailRequestByMailIds(searchMailIDs);
	deleteEmailNo(); //called to change the load the remove the popUp once mail delete request sent

	if(currentScreenLoaded === "InboxScreen"){
		loadInboxScreen();
	}else if(currentScreenLoaded === "DraftScreen") {
		loadDraftScreen();
	}
}

function deleteEmailNo() {

	var element = document.getElementById('inboxScreen');
	element.style.opacity = "1";

	var element = document.getElementById('draftScreen');
	element.style.opacity = "1";

	var popUp = document.getElementById('deleteEmailPopDiv');
	popUp.style.visibility="hidden";
}

function homeSelected() {
	saveMailToDraft();

	tizen.application.getCurrentApplication().exit();
}

function useThisAccount() {
	console.log("Inside use This Account Function");
	currentEmailAccountSelected = $('#chooseEmailAccount').find('input[type=checkbox]:checked').filter(':last').val();
	loadInboxScreen();

}

function deleteAccountYes() {
	var searchIDs = $("#chooseEmailAccount input:checkbox:checked").map(function(){
		return $(this).val();
	}).toArray();
	console.log(searchIDs);

	deleteAccountRequest(searchIDs);
}

function deleteAccountNo() {
	loadChangeAccountScreen();
}

function deleteThisAccount() {

	loadDeleteAccConfirmationScreen();

}

function loadDraftScreen() {

	clearInboxMails();
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#draftScreen").css({"visibility":"visible"});
	$("#draftScreen").show(400,populateDraft);
	$("#fileAttachmentDiv").hide();

	currentScreenLoaded = "DraftScreen";
	$("#searchMailText").val("");
}

function loadDeleteAccConfirmationScreen() {
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").css({"visibility":"visible"});
	$("#deleteAccountDiv").show();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();

	currentScreenLoaded = "DeleteAccConfirmationScreen";
	$("#searchMailText").val("");
}

function loadMailFullViewScreen() {
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").css({"visibility":"visible"});
	$("#inboxScreenFullView").show();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();

	currentScreenLoaded = "MailFullViewScreen";
	$("#searchMailText").val("");
}



function loadInboxScreen(type) {
	if(!type){
		saveMailToDraft();
	}
	clearInboxMails();
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").css({"visibility":"visible"});
	$("#inboxScreen").show(400,populateInbox);
	$("#inboxScreenFullView").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();

	currentScreenLoaded = "InboxScreen";
}

function loadAddAccountScreen() {
	saveMailToDraft();
	$("#addAccountDiv").css({"visibility":"visible"});
	$("#addAccountDiv").show();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();
	currentScreenLoaded = "AddAccountScreen";
	$("#searchMailText").val("");
}

function loadChangeAccountScreen() {
	saveMailToDraft();
	clearChooseAccounts();
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").css({"visibility":"visible"});
	$("#chooseEmailAccount").show(400,function () {
		chooseEmailAccount();
	});
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();
	currentScreenLoaded = "ChangeAccountScreen";
	$("#searchMailText").val("");
}

function addAccount(accountType)
{
	saveMailToDraft();
	selectedAccountType = accountType;
	console.log("Accont type Selected is :: "+selectedAccountType);
	$("#addAccountDiv").css({"visibility":"hidden"});
	$("#addAccountDiv").hide();
	$("#composeCtrlDiv").hide();
	$("#deleteAccountDiv").hide();
	$("#addAccountDetailsDiv").css({"visibility":"visible"});
	$("#addAccountDetailsDiv").show();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();
	currentScreenLoaded = "AddAccount";
	$("#searchMailText").val("");
}

function loadComposeScreen(type){
	saveMailToDraft();
	populateComposeScreen(type);
	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#deleteAccountDiv").hide();
	$("#composeCtrlDiv").css({"visibility":"visible"});
	$("#composeCtrlDiv").show();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").hide();
	fillDraftCount();
	currentScreenLoaded = "ComposeScreen";
	$("#searchMailText").val("");
}

function loadAttachmentScreen(){

	$("#addAccountDiv").hide();
	$("#addAccountDetailsDiv").hide();
	$("#chooseEmailAccount").hide();
	$("#inboxScreen").hide();
	$("#inboxScreenFullView").hide();
	$("#deleteAccountDiv").hide();
	$("#composeCtrlDiv").hide();
	$("#composeCtrlDiv").hide();
	$("#draftScreen").hide();
	$("#fileAttachmentDiv").css({"visibility":"visible"});
	$("#fileAttachmentDiv").show(400,listAllFiles);
	currentScreenLoaded = "AddAttachment";
	$("#searchMailText").val("");
}



function populateComposeScreen(type) {
	var to = $("#to").text();
	var from = $("#from").text();
	var date = $("#date").text();
	var subject = $("#subject").text();
	var mailBody = $("#mailBody").text();
	var attachmentSrc = $("#attachmentDiv").attr('src');
	switch(type){
	case "ReplyAll":
		clearAttachmentsCompose();
		var allToAddress = from+","+to;
		$("#toMember").val(allToAddress);
		$("#ccMember").val('');
		$("#bccMember").val('');
		mailBody = "\n\n\n\n\n\n\n\n\n\n--------------------------------------------------------------------\nFrom : "+from+"\n"+"To : "+to+"\n\n\n"+subject+"\n\n"+date+"\n\n\n"+mailBody+"";
		$("#bodyDetails").val(mailBody);
		subject = "Re:"+subject;
		$("#subMember").val(subject);
		break;
	case "Reply":
		clearAttachmentsCompose();
		$("#toMember").val(from);
		$("#ccMember").val('');
		$("#bccMember").val('');
		mailBody = "\n\n\n\n\n\n\n\n\n\n--------------------------------------------------------------------\nFrom : "+from+"\n"+"To : "+to+"\n\n\n"+subject+"\n\n"+date+"\n\n\n"+mailBody+"";
		$("#bodyDetails").val(mailBody);
		subject = "Re:"+subject;
		$("#subMember").val(subject);
		break;
	case "Forward":
		$("#toMember").val('');
		$("#ccMember").val('');
		$("#bccMember").val('');
		mailBody = "\n\n\n\n\n\n\n\n\n\n--------------------------------------------------------------------\nFrom : "+from+"\n"+"To : "+to+"\n\n\n"+subject+"\n\n"+date+"\n\n\n"+mailBody+"";
		$("#bodyDetails").val(mailBody);
		subject = "Fw:"+subject;
		$("#subMember").val(subject);
		clearAttachmentsCompose();
		break;
	case "draft":
		//Do nothing
		break;
	default :
		$("#toMember").val('');
	$("#ccMember").val('');
	$("#bccMember").val('');
	$("#subMember").val('');
	$("#bodyDetails").val('');
	clearAttachmentsCompose();
	break;
	}
}

function populateAttachFilesOnCompose(array){
	fileAttached = array;

	var output = document.getElementById('composeAttach');
	var i  = array.length - 1 ;
	var val="";
	while(i>=0)
	{
		var ele = document.createElement("div");
		ele.style.top = "10%";
		ele.style.left = (1+(i*30))+"%";
		ele.className = "attachDivClass";
		var eleImage = document.createElement("div");
		eleImage.style.left = "8%";
		eleImage.style.top = "1%";
		eleImage.style.height = "70%";
		eleImage.style.width = "40%";

		//This Functionality is called for the Image adding for different contexts 
		var tempName = array[i];
		if(tempName.indexOf("pdf")!=-1)
		{
			eleImage.id = "pdfIcon";
		}
		else if(tempName.indexOf("txt")!=-1)
		{
			eleImage.id = "textIcon";
		}
		else if(tempName.indexOf("gif")!=-1)
		{
			eleImage.id = "gifIcon";
		}
		else if(tempName.indexOf("jpeg")!=-1 || tempName.indexOf("jpg")!=-1 || tempName.indexOf("png")!=-1)
		{
			eleImage.id = "jpegIcon";
		}
		else
		{
			// called in Default
			eleImage.id = "textIcon";
		}

		var localFileNameIndex = getArrayItemByProperty(filesArray,"fullPath",array[i]);
		var fileName = "";
		if(localFileNameIndex){
			fileName = filesArray[localFileNameIndex.index].name;
		}

		var eleText = document.createElement("div");
		eleText.innerHTML=fileName;
		console.log('Account Name:' +eleText.innerHTML);
		eleText.style.left = "8%";
		eleText.style.top = "80%";
		eleText.style.height = "8%";
		eleText.style.width = "60%";
		eleText.className = "attachName";

		ele.appendChild(eleText);
		ele.appendChild(eleImage);
		output.appendChild(ele);

		i--;
	}
	loadComposeScreen("draft");
}

function populateAttachFilesOnViewMail(array){

	var output = document.getElementById('viewAttachment');
	var i  = array.length - 1 ;
	var val="";
	while(i>=0)
	{
		var ele = document.createElement("div");
		ele.style.top = "10%";
		ele.style.left = (1+(i*30))+"%";
		ele.className = "attachDivClass";
		var eleImage = document.createElement("div");
		eleImage.style.left = "8%";
		eleImage.style.top = "1%";
		eleImage.style.height = "70%";
		eleImage.style.width = "40%";

		//This Functionality is called for the Image adding for diffrent contexts 
		var tempName = array[i];
		if(tempName.indexOf("pdf")!=-1)
		{
			eleImage.id = "pdfIcon";
		}
		else if(tempName.indexOf("txt")!=-1)
		{
			eleImage.id = "textIcon";
		}
		else if(tempName.indexOf("gif")!=-1)
		{
			eleImage.id = "gifIcon";
		}
		else if(tempName.indexOf("jpeg")!=-1 || tempName.indexOf("jpg")!=-1 || tempName.indexOf("png")!=-1 ||tempName.indexOf("bmp")!=-1 ||tempName.indexOf("image")!=-1)
		{
			eleImage.id = "jpegIcon";
		}
		else
		{
			// called in Default
			eleImage.id = "textIcon";
		}

		console.log("eleImage.id ::: "+eleImage.id)


		var eleText = document.createElement("div");
		eleText.innerHTML=array[i];
		console.log('Account Name:' +eleText.innerHTML);
		eleText.style.left = "8%";
		eleText.style.top = "80%";
		eleText.style.height = "8%";
		eleText.style.width = "60%";
		eleText.className = "attachName";

		ele.appendChild(eleText);
		ele.appendChild(eleImage);
		output.appendChild(ele);

		i--;
	}
}


function populateAttachmentScreen() {


	var output = document.getElementById('attachFiledDiv');
	var i =filesArray.length - 1;
	var val="";

	while(i>=0)
	{
		var ele = document.createElement("div");
		ele.style.top = (15+(i*5))+"%";
		var eleImage = document.createElement("div");
		eleImage.style.top = (1+(i*90))+"%";
		eleImage.style.left = "470%";
		eleImage.style.height = "110%";
		eleImage.style.width = "90%";
		eleImage.className = "MessagIcon";

		//This Functionality is called for the Image adding for diffrent contexts 
		var tempName = filesArray[i].name;
		if(tempName.indexOf("pdf")!=-1)
		{
			eleImage.id = "pdfIcon";
		}
		else if(tempName.indexOf("txt")!=-1)
		{
			eleImage.id = "textIcon";
		}
		else if(tempName.indexOf("gif")!=-1)
		{
			eleImage.id = "gifIcon";
		}
		else if(tempName.indexOf("jpeg")!=-1 || tempName.indexOf("jpg")!=-1 || tempName.indexOf("png")!=-1)
		{
			eleImage.id = "jpegIcon";
		}
		else
		{
			// called in Default
			eleImage.id = "textIcon";
		}

		var eleText = document.createElement("div");
		eleText.innerHTML=filesArray[i].name;
		console.log('Account Name:' +eleText.innerHTML);
		eleText.style.top = (29+(i*90))+"%";
		eleText.style.left = "30%";
		eleText.className = "LabelCtrl";

		var attachmentCheckBox = document.createElement('input');
		attachmentCheckBox.type = "checkbox";
		attachmentCheckBox.className = "chooseEmailCheckBox";
		attachmentCheckBox.style.top = (20+(i*90))+"%";
		attachmentCheckBox.style.left = "700%";
		attachmentCheckBox.style.height = "70%";
		attachmentCheckBox.style.width = "70%";
		attachmentCheckBox.id = "chooseAttachmentCheckBox" + i;
		attachmentCheckBox.value = filesArray[i].fullPath;

		ele.className = "mailDivPart";

		ele.appendChild(eleImage);
		ele.appendChild(eleText);
		ele.appendChild(attachmentCheckBox);

		output.appendChild(ele);

		i--;
	}

}

function draftSelected() {
	loadDraftScreen();
}

var populateDraft = function() {
	retriveMail("draft");
	fillDraftCount();
}

var populateInbox = function ()
{
	setInboxTitle();
	retriveMail();
	fillDraftCount();

}

function fillDraftCount() {
	$(".draftIcon").html(draftMailTypeCounter);
}

function chooseEmailAccount()
{
	var output = document.getElementById('emailAccounts');
	var i=accountInfo.length -1 ;

	var val="";
	while(i>=0)
	{

		var ele = document.createElement("div");
		ele.style.top = (5+(i*5))+"%";
		var eleImage = document.createElement("img");
		eleImage.style.top = (15+(i*90))+"%";
		eleImage.style.left = "25%";
		eleImage.className = "MessagIcon";
		var eleText = document.createElement("div");
		eleText.innerHTML=accountInfo[i].name;
		console.log('Account Name:' +eleText.innerHTML);
		eleText.style.top = (4+(i*90))+"%";
		eleText.style.left = "100%";
		eleText.className = "LabelCtrl";

		var emailCheckBox = document.createElement('input');
		emailCheckBox.type = "checkbox";
		emailCheckBox.className = "chooseEmailCheckBox";
		emailCheckBox.style.top = (20+(i*90))+"%";
		emailCheckBox.style.left = "600%";
		emailCheckBox.id = "chooseEmailCheckBox" + i;
		emailCheckBox.value = accountInfo[i].id;
		console.log('Account ID:'+accountInfo[i].id);
		ele.className = "mailDivPart";

		ele.appendChild(eleImage);
		ele.appendChild(eleText);
		ele.appendChild(emailCheckBox);

		output.appendChild(ele);

		i--;
	}


}

//Set Inbox Title
function setInboxTitle() {
	var currentEmailSelectedName = null;

	console.log('currentEmailAccountSelected:'+currentEmailAccountSelected);

	var index = getArrayItemByProperty(accountInfo,"id",currentEmailAccountSelected);

	for(var i in accountInfo)
	{
		console.log("Aproperty = "+i);
		console.log("Aproperty VALUE = "+accountInfo[i]);
	}

	for(var i in index)
	{
		console.log("Iproperty = "+i);
		console.log("Iproperty VALUE = "+index[i]);
	}

	currentEmailSelectedName = accountInfo[index.index].name;

	var inboxDiv = document.getElementById('InboxLabelCtrl');
	inboxDiv.innerText = INBOX + currentEmailSelectedName;

	var inboxFullDiv = document.getElementById('InboxFullViewLabelCtrl');
	inboxFullDiv.innerText = INBOX + currentEmailSelectedName;

	var inboxComposeDiv = document.getElementById('InboxComposeLabelCtrl');
	inboxComposeDiv.innerText = INBOX + currentEmailSelectedName;

	var inboxComposeFromDiv = document.getElementById('fromComposeDiv');
	inboxComposeFromDiv.innerText = currentEmailSelectedName;
}

function populateDraftScreen(msg) {
	if(msg.folderId == "6"){
		var outputInboxScreen = document.getElementById("DraftDiv");
		var messageItemBody = document.createElement('div');
		messageItemBody.className = "MsgItemBody";
		messageItemBody.id = "MsgItemID" + count;

		messageItemBody.style.top = (count + FIXED) + "%";


		var messageItemBodySubject = document.createElement('label');
		messageItemBodySubject.innerText = msg.subject;
		messageItemBodySubject.className = "MsgItemBodySubject";

		var messageItemBodyBody = document.createElement('label');
		messageItemBodyBody.innerText = msg.mailBody;
		messageItemBodyBody.className = "MsgItemBodyBody";

		var messageItemBodyCheckBox = document.createElement('input');
		messageItemBodyCheckBox.type = "checkbox";
		messageItemBodyCheckBox.className = "MessageItemBodyCheckBox";
		messageItemBodyCheckBox.id = "messageItemBodyCheckBox" +count;
		messageItemBodyCheckBox.value = msg.mailId;
		messageItemBodyCheckBox.addEventListener("click",
				selectCheckBox.bind(this, msg.mailId), false);



		messageItemBody.appendChild(messageItemBodySubject);
		messageItemBody.appendChild(messageItemBodyBody);
		messageItemBody.appendChild(messageItemBodyCheckBox);

		outputInboxScreen.appendChild(messageItemBody);

		FIXED = FIXED + 10;
	}
}

function populateInboxScreen(msg)
{
	if(msg.folderId != "4" && msg.folderId != "6"){
		var outputInboxScreen = document.getElementById('InboxDiv');
		var messageItemBody = document.createElement('div');
		messageItemBody.className = "MsgItemBody";
		messageItemBody.id = "MsgItemID" + count;

		messageItemBody.style.top = (count + FIXED) + "%";

		var messageItemIsRead = document.createElement('div');
		messageItemIsRead.className = "MsgItemBodyIsRead";
		if (msg.isRead) {
			messageItemIsRead.style.visibility = 'hidden';
		} else {
			messageItemIsRead.style.visibility = 'visible';
		}

		var messageItemBodySubject = document.createElement('label');
		messageItemBodySubject.innerText = msg.subject;
		messageItemBodySubject.className = "MsgItemBodySubject";
		messageItemBodySubject.addEventListener("click",
				retriveMailFilterWithId.bind(this, msg.mailId), false);

		var messageItemBodyBody = document.createElement('label');
		messageItemBodyBody.innerText = msg.mailBody;
		messageItemBodyBody.className = "MsgItemBodyBody";
		messageItemBodyBody.addEventListener("click",
				retriveMailFilterWithId.bind(this, msg.mailId), false);

		var messageItemBodyCheckBox = document.createElement('input');
		messageItemBodyCheckBox.type = "checkbox";
		messageItemBodyCheckBox.className = "MessageItemBodyCheckBox";
		messageItemBodyCheckBox.id = "messageItemBodyCheckBox" +count;
		messageItemBodyCheckBox.value = msg.mailId;
		messageItemBodyCheckBox.addEventListener("click",
				selectCheckBox.bind(this, msg.mailId), false);

		messageItemBody.appendChild(messageItemIsRead);
		messageItemBody.appendChild(messageItemBodySubject);
		messageItemBody.appendChild(messageItemBodyBody);
		messageItemBody.appendChild(messageItemBodyCheckBox);

		outputInboxScreen.appendChild(messageItemBody);

		FIXED = FIXED + 10;
	}
}

//Clear the populated mails if any
function clearInboxMails() {
	var el = document.getElementById('InboxDiv');
	while (el.hasChildNodes()) {
		el.removeChild(el.lastChild);
	}

	var elDraft = document.getElementById('DraftDiv');
	while (elDraft.hasChildNodes()) {
		elDraft.removeChild(elDraft.lastChild);
	}
	count = 0;
	FIXED = 0;
}

//Clear the populated mails if any
function clearChooseAccounts() {
	var el = document.getElementById('emailAccounts');
	while (el.hasChildNodes()) {
		el.removeChild(el.lastChild);
	}
}

//Clear the attachments from compose screen
function clearAttachmentsCompose() {

	console.log("Clearing....attach from compose");

	var el = document.getElementById('composeAttach');
	while (el.hasChildNodes()) {
		el.removeChild(el.lastChild);
	}
	fileAttached = new Array();
	var attachFiledDiv = document.getElementById('attachFiledDiv');
	while (attachFiledDiv.hasChildNodes()) {
		attachFiledDiv.removeChild(attachFiledDiv.lastChild);
	}
}

//Clear the attachments from compose screen
function clearAttachmentsViewMail() {
	console.log("Clearing....attach from compose");
	var el = document.getElementById('viewAttachment');
	while (el.hasChildNodes()) {
		el.removeChild(el.lastChild);
	}
}

//Populated the Mail onto the View Mail Screen
function setViewMails(message){
	setInboxTitle();
	fillDraftCount();
	try{
		var messageFrom = message.from;
		var messageTo = message.to;
		var messageSubject = message.subject;
		var messageDate = message.date;
		var messageBody = message.mailBody;
		currentMailId = message.mailId;

		clearAttachmentsViewMail();
		var attachFilesArray = [];

		for(var i=0;i<message.attachments.length;i++){
			//attachFilesArray[i] = message.attachments[i].name;
			attachFilesArray[i] = message.attachments[i].mimeType;
			console.log("Attachment mimeType:" +attachFilesArray[i]);
		}

		if(message.hasAttachment){
			populateAttachFilesOnViewMail(attachFilesArray)
		}

		$("#from").text(messageFrom);
		$("#to").text(messageTo);
		$("#subject").text(messageSubject);
		$("#date").text(messageDate);
		$("#mailBody").text(messageBody);

	}catch(e)
	{
		console.warn("Last Mail : Cannot do Next Operation")
	}
}

function selectCheckBox(type) {
	if(type === "All"){
		if($(".CheckBoxSelectAll").is(':checked')){
			$(".MessageItemBodyCheckBox").attr("checked", "checked");
		}else{
			$(".MessageItemBodyCheckBox").removeAttr("checked");
		}
	}else{
		$(".CheckBoxSelectAll").removeAttr("checked");
	}
}



function saveMailToDraft() {
	if(currentScreenLoaded === "ComposeScreen" && ($("#subMember").val() || $("#bodyDetails").val())){
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
			console.log("Mail message length "+mailMessages.length)
			var mailMsg = {};
			mailMsg["subject"] = subject;
			mailMsg["from"] = from;
			if(to){
				mailMsg["to"] = to[0];
			}
			if(mailMessages[mailMessages.length-1]){
				mailMsg["mailId"]= (parseInt(mailMessages[mailMessages.length-1].mailId)+1).toString();
			}else{
				mailMsg["mailId"]="1";
			}
			mailMsg["isRead"] = false;
			mailMsg["mailBody"] = mailbody;
			mailMsg["date"] = "3 march";
			mailMsg["folderId"] = "6";

			mailMessages.push(mailMsg);
		}else{

			var msg = new tizen.Message("messaging.email",{to:to,cc:cc,bcc:bcc,from:from,subject:subject,plainBody:mailbody,hasAttachment : hasAttachment}); 


			for (var i = 0 ; i < fileAttached.length; i++){
				attachmentArray.push(new tizen.MessageAttachment(fileAttached[i]));
			}
			msg.attachments = attachmentArray;

			selectedService.messageStorage.addDraftMessage(msg, draftSentSuccessCallback, errorCallback);
		}
	}
}

function draftSentSuccessCallback() {
	console.log("Draft Saved Successfully")
}

function editContinueCompose() {

	var mailIdToEdit = $('#DraftDiv').find('input[type=checkbox]:checked').filter(':last').val();

	var index = getArrayItemByProperty(mailMessages,
			"mailId", mailIdToEdit);
	if (index.item) {

		console.log("index.item.to:" +index.item.to);
		console.log("index.item.cc:" +index.item.cc);
		console.log("index.item.bcc:" +index.item.bcc);
		console.log("index.item.subject:" +index.item.subject);


		if(index.item.to){
			$("#toMember").val(index.item.to);
		}else{
			$("#toMember").val("");
		}

		if(index.item.cc){
			$("#ccMember").val(index.item.cc);
		}else{
			$("#ccMember").val("");
		}

		if(index.item.bcc){
			$("#bccMember").val(index.item.bcc);
		}else{
			$("#bccMember").val("");
		}

		$("#bodyDetails").val(index.item.mailBody);

		subject = "Re:"+subject;
		$("#subMember").val(index.item.subject);

		//While editing any old draft msg , attachment wont be available 
		clearAttachmentsCompose();

		loadComposeScreen("draft");

	} else {
		console.log(mailId
				+ " ::: MessageId received is incorrect");
	}

}

function sendDraftMail() {
	var mailIDsToSendMail = $("#DraftDiv input:checkbox:checked").map(function(){
		return $(this).val();
	}).toArray();
	console.log(mailIDsToSendMail);
	for(var i = 0;i<mailIDsToSendMail.length;i++){
		sendMailWithId(mailIDsToSendMail[i]);
	}
}

function attachFile() {
	console.log("Before:::: "+JSON.stringify(attachFiles));
	var attachFiles = $("#attachFiledDiv input:checkbox:checked").map(function(){
		return $(this).val();
	}).toArray();
	console.log(JSON.stringify(attachFiles));
	populateAttachFilesOnCompose(attachFiles);
	$("#attachFiledDiv").removeAttr("checked");
}

function cancelFileAttachment() {
	loadComposeScreen("draft");
}

var init = function() {
	checkAccountAvailablity();
}
$(document).ready(init);

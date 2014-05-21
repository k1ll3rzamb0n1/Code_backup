var url = "perlDBconnect.pl";

function searchDBScreen() {
	$("#selectSearch").hide();
	$("#Search").show();
	$("#cartButton").show();
	$("#editUserButton").show();
	$("#orderButton").show();
	$("#orderHistory").hide();
}

function checkUniqueUser(){
if($("#newUserName").val() == ''){
		$("#validUser").hide();
		$("#invalidUser").hide();
}else{
$.post(url, {username: $("#newUserName").val(), Case: 6},
 function(data) {
	if(data.invalid){
		$("#invalidUser").show();
		$("#validUser").hide()
   }else{
		$("#validUser").show()
		$("#invalidUser").hide();
   }
 }, 
 "json"
);
}
}

function createNewUser(){

$("#start").hide();
$("#NewUserCreation").show();

}

function sendNewUserRequest(){
$.post(url, {userid: $("#newUserName").val(), password: $("#newPass").val(), fname: $("#newFname").val(), lname: $("#newLname").val(), address: $("#newAddress").val(), city: $("#newCity").val(), state: $("#newState").val(), zip: $("#newZip").val(), Case: 7},
function(data){
if(data.approved){
alert("Welcome "+ data.userid);
$("#NewUserCreation").hide();
showLogin();
}else{
alert(data.denied);
}
}

);
}

function editUserScreen(){
	populateUserScreen();
	$("#cart").hide();
	$("#selectSearch").hide();
	$("#Search").hide();
	$("#cartButton").show();
	$("#searchButton").show();
	$("#UserInfo").show();
	$("#editUserInfoB1").hide();
	$("#editUserButton").hide();
	$("#orderButton").show();
	$("#orderHistory").hide();
}

function populateUserScreen(){
	$.post(url, {Case: 8, userid: $("#useridSpan").html()},
	function(data){
	$("#UserInfo span").empty();
		$("#UIfname").append(data.fname);
		$("#UIlname").append(data.lname);
		$("#UIuserid").append(data.userid);
		$("#UIphone").append(data.phone);
		$("#UIaddress").append(data.address);
		$("#UIcity").append(data.city);
		$("#UIstate").append(data.state);
		$("#UIzip").append(data.zip);
		$("#UIemail").append(data.email);
	}
	);
}

function showLogin() {
	$("#start").hide();
	$("#loginScreen").show();
}

function buildTable(data){

	var i = 0;
	var length = data.length;
	var table = data.data;
	$('#myTable tbody').empty();
	
	if(length == 0){
		$("#invalidSearch").show();
	}else{
		$("#invalidSearch").hide();
	}
	
	for(i = 0; i < length; i++){
		$("#myTable tbody").append("<tr><td id=\"isbn\">"+ table[i]["isbn"] +"</td> <td id=\"title\">"+ table[i]["title"] +"</td> <td id=\"author\">"+ table[i]["author"] +"</td><td id=\"subject\">"+ table[i]["subject"] +"</td><td id=\"price\">"+ table[i]["price"] +"</td><td><input type=\"number\" id=\"quantity\"/></td><td><button id=\"test\" class=\"addToCart\" onclick=\"addToCart(this)\">add</button></td> </tr>");
	}

}

function search(){

$.post(url, {title: $("#searchTitle").val(), author: $("#searchAuthor").val(), isbn: $("#searchISBN").val(), subject: $("#searchSubject").val(), price: $("#searchPrice").val(), Case: 2}, 
function(data){ buildTable(data) }, "json");

}

function login(){

$.post(url, {username: $("#userName").val(), password: $("#password").val(), Case: 1},
 function(data) {
	if(data.error){
		$("#loginFailed").show();
   }else{
		$("#loginScreen").hide();
		$(".loggedIn").show();
		$("#useridSpan").append(data.userid);
   }
 }, 
 "json"
);
}

function cart(){
	$("#cart").show();
	$("#UserInfo").hide();
	$("#Search").hide();
	$("#cartButton").hide();
	$("#searchButton").show();
	$("#editUserButton").show();
	$("#orderButton").show();
	$("#orderHistory").hide();
}

$(document).ready(function(){
	$("#start").show();
});

function addToCart( item ){

var parent = $(item).parents('tr');
var quantity = parent.find("#quantity").val();

if(quantity != 0){

var title = parent.find("#title").html();
var author = parent.find("#author").html();
var isbn = parent.find("#isbn").html();
var subject = parent.find("#subject").html();
var price = parent.find("#price").html();
var t = price*quantity;
var total = t.toFixed(2);

$("#myCartTable tbody").append(
								"<tr>"+ 
									"<td id=\"isbn\">" + isbn +"</td>"+ 
									"<td id=\"title\">" + title +"</td>"+ 
									"<td>" + author +"</td>"+ 
									"<td>" + subject +"</td>"+ 
									"<td id=\"price\">" + price +"</td>"+
									"<td><span id=\"cartQspan\"> "+quantity+"</span><input type=\"number\" id=\"cartQuantity\" value=\""+quantity+"\" style=\"display: none\"/>"+
									"</td> <td> <input type=\"checkbox\" id=\"orderMe\"/> </td> "+
									"<td id=\"totals\">"+ total +"</td> "+
									"<td> <button id=\"editRow\" onclick=\"toggleCartItem(this)\">Edit Quantity</button><button id=\"finishEditRow\" onclick=\"exceptNewCartQ(this)\" style=\"display: none\" >Accept quantity</button></td><td> <input type=\"button\" id=\"deleteRowItem\" value=\"Delete Row Item\" onclick=\"deleteCartItem(this)\"/> </td>"+
								"</tr>" );

alert("Added To Cart");
}
}

function deleteCartItem(button){

	$(button).parents('tr').empty();

}

function toggleCartItem(button){
	$(button).hide();
	$(button).siblings("#finishEditRow").show();
	parent.find("#deleteRowItem").show();
	var parent = $(button).parents('tr');
	parent.find("#cartQuantity").show();
}

function exceptNewCartQ(button){

	$(button).hide();
	$(button).siblings("#editRow").show();
	var parent = $(button).parents('tr');
	parent.find("#cartQspan").text(parent.find("#cartQuantity").val());
	parent.find("#cartQuantity").hide();
	
	var quantity = parent.find("#cartQspan").html();
	var price = parent.find("#price").html();
	var t = price*quantity;
	var total = t.toFixed(2);
	
	parent.find("#totals").html(total);

}

function editUserInfoItem(button){
	$(button).hide();
	$(button).siblings(".exceptChanges").show();
	var parent = $(button).parents('tr');
	parent.find(".changes").show();
}

function excpetUserInfoItem(button){
	$(button).hide();
	$(button).siblings(".editRow").show();
	var parent = $(button).parents('tr');
	var change = parent.find(".changes").val();
	var my_span = parent.find('span');
	if(change != ''){
	my_span.empty();
	my_span.html(change);
	}
	parent.find(".changes").hide();

}

function updateUserInformation(){
	$.post(url, {userid: $("#UIuserid").html(), fname: $("#UIfname").html(), lname: $("#UIlname").html(), address: $("#UIaddress").html(), city: $("#UIcity").html(), state: $("#UIstate").html(), zip: $("#UIzip").html(), phone: $("#UIphone").html(), email: $("#UIemail").html(), Case: 9}, 
	function(data)
	{ if(data.success){
		alert(data.success);
	}else{
		alert(data.error);
	} 
	}
	, "json");
}

function showSearch(){

$("#searchButton").hide();
$("#cartButton").show();

$("#cart").hide();
$("#Search").show();
$("#editUserButton").show();
$("#UserInfo").hide();

$("#orderHistory").hide();
$("#orderButton").show();

}

function placeOrder(){

var onumber;
var cont = 1;
if($("#myCartTable").find(':checkbox').is(':checked')){
//$.post(url, {Case: 4}, function(data){ onumber = data }, "json");
//$.post(url, {ono: onumber, userid: $("#useridSpan").html(), Case: 5}, function(string){alert(string.error)}, "json");

$.ajax({
  type: 'POST',
  url: url,
  data: {Case: 4},
  success: function(data){ onumber = data},
  dataType: "json",
  async:false
});
$.ajax({
  type: 'POST',
  url: url,
  data: {ono: onumber, userid: $("#useridSpan").html(), Case: 5},
  success: function(data){if(data.error){cont = 0}},
  dataType: "json",
  async:false
});

if(cont){

$("#myCartTable").find(':checkbox').each( function(){
												if($(this).is(':checked')){
													var trow = $(this).parents('tr');
													$.post(url, {isbn: trow.find("#isbn").html(), quantity: trow.find("#cartQspan").html(), price: trow.find("#totals").html(), ono: onumber, Case: 3}, function(data){alert(data)}, "json");
													trow.remove();
												}});	

		alert("Order Placed");
		}else{
		alert("Order Not Placed");
		}
}

}

function buildOrders(data){
	
	
	var i =0;
	var length = data.length;
	var otab = data.data;

	if(length == 0){
		$("#NoOrders").show();
	}else{
		$("#NoOrders").hide();
		$("#orderTableBody").empty();
		for(i =0; i<length; i++){
			$("#orderTableBody").append("<tr><td>"+ otab[i]["ono"] +"</td><td>"+ otab[i]["isbn"] +"</td><td>"+ otab[i]["quantity"] +"</td><td>"+ otab[i]["price"] +"</td><td>"+ otab[i]["received"] +"</td><td>"+ otab[i]["shipped"] +"</td></tr>");		
		}
	}
}

function orderTable(){
	$.post(url, {Case: 10, userid: $("#useridSpan").html()},
	function(data){
		if(data.success){
			buildOrders(data);
		}else{
		alert("error building orders table");
		}
	}
	,"json");
}

function openOrdersTable(){
	$("#editUserButton").show();
	$("#cartButton").show();
	$("#searchButton").show();
	$("#UserInfo").hide();
	$("#cart").hide();
	$("#Search").hide();
	$("#orderButton").hide();
	$("#orderHistory").show();
}
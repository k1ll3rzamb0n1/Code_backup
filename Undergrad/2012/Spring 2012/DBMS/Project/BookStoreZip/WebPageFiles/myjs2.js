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

$.post(url, {Case: 10, userid: $("#useridSpan").html()},
function(data){
	if(data.success){
		buildOrders(data);
	}else{
	alert("error building orders table");
	}
}
,"json");


#!/usr/bin/perl -w



use CGI;
use JSON;
use DBI;
use Time::Local;
use strict;
use warnings;

# read the CGI params
my $cgi = CGI->new;
my $case = $cgi->param("Case");

# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;


if($case == 1){  
# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;

	my $username = $cgi->param("username");
	my $password = $cgi->param("password");
	
	# check the username and password in the database
	my $query = qq{SELECT userid FROM members WHERE userid=? and password=?};

	my $sth = $dbh->prepare($query) or die $dbh->errstr;

	$sth->execute($username, $password) or die $sth->errstr;

	my ($userID) = $sth->fetchrow_array;

	# create a JSON string according to the database result
	my $json = ($userID) ? 
	  qq{{"success" : "login is successful", "userid" : "$userID"}} : 
	  qq{{"error" : "username or password is wrong"}};

	# return JSON string
	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
}elsif($case == 2){
# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;

my ($title, $aname, $isbn, $price, $subject);

	$title = $cgi->param("title") or $title = '%';
	$aname = $cgi->param("author") or $aname = '%';
	$isbn = $cgi->param("isbn") or $isbn = '%';
	$price = $cgi->param("price") or $price = '%';
	$subject = $cgi->param("subject") or $subject = '%';
	
	$title = '%'.$title.'%';
	$aname = '%'.$aname.'%';
	$isbn = '%'.$isbn.'%';
	$price = '%'.$price.'%';
	$subject = '%'.$subject.'%';

	my $query = qq{select * from books b, authors a where a.isbn = b.isbn AND title like ? AND aname like ? AND a.isbn like ? AND price like ? AND subject like ?};

	my $sth = $dbh->prepare($query) or die $dbh->errstr;

	$sth->execute($title, $aname, $isbn, $price, $subject) or die $sth->errstr;
	
	my ($isbn1, $isbn2, @rowarray);
	
	while(($isbn1, $title, $price, $subject, $aname, $isbn2) = $sth->fetchrow_array){
	
	my %row = ( "isbn" => $isbn1, "title" => $title, "price" => $price, "subject" => $subject, "author" => $aname);
	push(@rowarray, \%row);
	
	}
	my $length = @rowarray;
	my %data = ("data" => \@rowarray, "length" => $length);
	
	my $json = to_json(\%data);
		
	print $cgi->header(-type => "aplication/json", -charset => "utf-8");
	print $json;

}elsif($case == 3){
	# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsadmin", "toor") or die $DBI::errstr;

my ($ono, $isbn, $price, $quantity);

$ono = $cgi->param("ono[]"); 
$isbn = $cgi->param("isbn");
$price = $cgi->param("price");
$quantity = $cgi->param("quantity");

$isbn = "$isbn";

my $json = "isbn";

	my $query = qq{INSERT INTO odetails VALUES( ?, ?, ?, ?)};
	my $sth = $dbh->prepare($query) or die $dbh->errstr;

	my $json = ($sth->execute($ono, $isbn, $quantity, $price)) ?
	qq{success: "Inserted"}:
	qq{error: "Not Inserted"};

	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
	

}elsif($case == 4){

my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsadmin", "toor") or die $DBI::errstr;

my $query = qq{select MAX(ono) from orders};
my $sth = $dbh->prepare($query) or die $dbh->errstr;
$sth->execute();

my $ono = $sth->fetchrow_array;

$ono++;

my $json = encode_json[$ono];
	
	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;


}elsif($case ==5){

my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsadmin", "toor") or die $DBI::errstr;

my ($userid, $ono);

$userid = $cgi->param("userid");
$ono = $cgi->param("ono[]");

my ($DAY, $MONTH, $YEAR) = (localtime)[3,4,5];

$YEAR+=1900;
if($MONTH < 10){
$MONTH = "0$MONTH";
}
if($DAY < 10){
$DAY = "0$DAY";
}


my $date = "$YEAR-$MONTH-$DAY";

my $query = qq{INSERT INTO orders VALUES( ?, ?, ?, NULL, NULL, NULL, NULL, NULL)};

 my $sth = $dbh->prepare($query) or die $dbh->errstr;

my $json = ($sth->execute($userid, $ono, $date)) ? 
	  qq{{"success" : "Order Successful"}} : 
	  qq{{"error" : "Order not Successful"}};

	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;

}elsif($case==6){

# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;

	my $username = $cgi->param("username");
	
	# check the username and password in the database
	my $query = qq{SELECT userid FROM members WHERE userid=?};

	my $sth = $dbh->prepare($query) or die $dbh->errstr;

	$sth->execute($username) or die $sth->errstr;

	my ($userID) = $sth->fetchrow_array;

	# create a JSON string according to the database result
	my $json = ($userID) ? 
	  qq{{"invalid" : "User name already taken", "userid" : "$userID"}} : 
	  qq{{"valid" : "username not in DB"}};

	# return JSON string
	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
}elsif($case==7){

my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsadmin", "toor") or die $DBI::errstr;

my ($userid, $password, $fname, $lname, $address, $city, $state, $zip, $phone, $email);

$userid = $cgi->param("userid");
$password = $cgi->param("password");
$fname = $cgi->param("fname");
$lname = $cgi->param("lname");
$address = $cgi->param("address");
$city = $cgi->param("city");
$state = $cgi->param("state");
$zip = $cgi->param("zip");
$phone = $cgi->param("phone");
$email = $cgi->param("email");


my $query = qq{INSERT INTO members VALUES( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )};

my $sth = $dbh->prepare($query) or die $dbh->errstr;

my $json = ($sth->execute($fname, $lname, $address, $city, $state, $zip, $phone, $email, $userid, $password)) ? 
	  qq{{"approved" : "User account creation success", "userid": "$userid"}} : 
	  qq{{"denied" : "User account creation failed"}};

	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
}elsif($case == 8){

# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;

	my $username = $cgi->param("userid");
	
	# check the username and password in the database
	my $query = qq{SELECT * FROM members WHERE userid=?};

	my $sth = $dbh->prepare($query) or die $dbh->errstr;

	$sth->execute($username) or die $sth->errstr;

	
	my ($fname, $lname, $address, $city, $state, $zip, $phone, $email, $userID, $password ) = $sth->fetchrow_array;
	
	my %data = ("fname" => $fname, "lname" => $lname, "address" => $address, "city" => $city, "state" => $state, "zip" => $zip, "phone" => $phone, "email" => $email, "userid" => $userID);

	
	
	# create a JSON string according to the database result
	my $json = to_json(\%data);
	# return JSON string
	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
}elsif($case == 9){

# connect to the database
my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsadmin", "toor") or die $DBI::errstr;

	my $username = $cgi->param("userid");
	my $fname = $cgi->param("fname");
	my $lname = $cgi->param("lname");
	my $address = $cgi->param("address");
	my $city = $cgi->param("city");
	my $state = $cgi->param("state");
	my $zip = $cgi->param("zip");
	my $phone = $cgi->param("phone");
	my $email = $cgi->param("email");
	
		# check the username and password in the database
		my $query = qq{UPDATE members SET fname = ?, lname = ?, address = ?, city = ?, state = ?, zip = ?, phone = ?, email = ? WHERE userid = ?};

		my $sth = $dbh->prepare($query) or die $dbh->errstr;
		
	my $json = ($sth->execute($fname, $lname, $address, $city, $state, $zip, $phone, $email, $username)) ?
			qq{{"success": "Update Successful"}} :
			qq{{"error": "Update Failed}};

	# return JSON string
	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
}elsif($case==10){

my $dbh = DBI->connect("DBI:mysql:BOOKSTORE:localhost","bsuser", "password") or die $DBI::errstr;

my $userid = $cgi->param("userid");

my $query = qq{SELECT o.ono, o.received, o.shipped, d.isbn, d.qty, d.price FROM odetails d, orders o WHERE o.ono = d.ono AND userid = ?};

my $sth = $dbh->prepare($query) or die $dbh->errstr;

if($sth->execute($userid)){

my ($ono, $recvd, $shipped, $isbn, $qty, $price, @rowArray, %data);

while(($ono, $recvd, $shipped, $isbn, $qty, $price) = $sth->fetchrow_array){

my %row = ("ono" => $ono, "isbn" => $isbn, "quantity" => $qty, "price" => $price, "received" => $recvd, "shipped" => $shipped, "exist" => "YAY");
push(@rowArray, \%row);
}

my $length = @rowArray;
%data = ("data" => \@rowArray, "length" => $length, "success" => "Select Returned");

my $json = to_json(\%data);


	print $cgi->header(-type => "application/json", -charset => "utf-8");
	print $json;
	}else{
	my $json = qq{{"error", "Query Failed"}};
	}
}







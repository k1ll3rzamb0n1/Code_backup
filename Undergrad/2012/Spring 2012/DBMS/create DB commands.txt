DELETE FROM odetails;
DELETE FROM orders;
DELETE FROM cart;
DELETE FROM creditcards;
DELETE FROM authors;
DELETE FROM members;
DELETE FROM books;
drop table if exists odetails, cart, creditCards, authors, orders, books, members;


create table books (
  isbn char(10),
  title VARCHAR(128) NOT NULL,
  price DECIMAL(7,2) NOT NULL,
  subject VARCHAR(30) NOT NULL,
  primary key (isbn)
);

create table authors (
	aname VARCHAR(20),
	isbn char (10),
	primary key (aname, isbn),
	foreign key (isbn) references books (isbn)
);

create table members (
  fname VARCHAR(20) NOT NULL,
  lname VARCHAR(20) NOT NULL,
  address VARCHAR(50) NOT NULL,
  city VARCHAR(30) NOT NULL,
  state VARCHAR(20) NOT NULL,
  zip INT(5) NOT NULL,
  phone CHAR(12),
  email VARCHAR(40),
  userid VARCHAR(20),
  password VARCHAR(20),
  primary key (userid)
);


create table creditCards (
	userid VARCHAR(20),
	cardnumber INT(5),
	creditcardtype VARCHAR(10),
	creditcardnumber CHAR(16),
	address VARCHAR(50) NOT NULL,
	city VARCHAR(30) NOT NULL,
	state VARCHAR(20) NOT NULL,
	zip INT(5) NOT NULL,
	primary key (userid, cardnumber),
	foreign key (userid) references members (userid)
);


create table orders (
  userid VARCHAR(20) NOT NULL,
  ono INT(5),
  received date NOT NULL,
  shipped date,
  shipAddress VARCHAR(50),
  shipCity VARCHAR(30),
  shipState VARCHAR(20),
  shipZip INT(5),
  primary key (ono),
  foreign key (userid) references members (userid)
);


create table odetails (
  ono INT(5),
  isbn char(10),
  qty INT(5) NOT NULL,
  price DECIMAL(7,2) NOT NULL,
  primary key (ono,isbn),
  foreign key (ono) references orders (ono),
  foreign key (isbn) references books (isbn)
);


create table cart (
  userid VARCHAR(20),
  isbn char(10),
  qty INT(5) NOT NULL,
  primary key (userid,isbn),
  foreign key (userid) references members (userid),
  foreign key (isbn) references books (isbn)
);


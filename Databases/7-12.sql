         --7--
--dobavqne na korteji
--insert into starsin(movietitle, movieyear, starname)
--values ('Interstellar', 2014, 'Anne Hathaway')
--mojem da propusnem spisuka s atributi, sled kato sme dali stoinost na vsqko
--trqbva da znaem reda!!!
--neshto ne priema Null -> no ako ima stoinost po podrazbirane -> DEFAULT
--insert into t default values; -> vmukva se kortej sus stoinostite po podrazbirane -> (null, null, 'pc')
--mojem poveche da vmukvame (), (), ();
--dobavqne s podzaqvka
--insert into t1 (a1, b1, c1) select a2, b2, c2 (* ako sa vsichki) from t2 where c2 = 'pc';
--pak mojem da propusnem spisuka s atributi; obshto vzeto sushtata rabota
--mojem da promenqme stoinosti na sushtestvuvashti korteji
--update t1 set a1 = a1 * 8 where b1 < 5;
--update laptop set speed = (select max(speed) from laptop), hd = ram/2, price = DEFAULT
--iztrivane na korteji
--from -> moje i bez nego
--delete from starsin
--delete from starsin where starname = 'Anne Hathaway' and movietitle = 'Interstellar' and movieyear = 2014;
--delete from moviexec where networth < 10000000;
--delete from product where model not in (select model from pc) and type = 'pc';

--use movies;

--insert into MOVIESTAR(name, gender, BIRTHDATE)
--values ('Nicole Kidman', 'F','1967-06-20')

--delete from MOVIEEXEC
--where NETWORTH < 30000000

--delete from MOVIESTAR
--where ADDRESS is Null

--use pc;

--insert into product(model, maker, type)
--values(1100, 'C', 'pc')

--insert into pc(code, model, speed, ram, hd, cd, price)
--values(12, 1100, 2400, 2048, 500, '52x', 299)

--delete from pc
--where model = 1100

--delete from laptop
--where model in (select p.model from Product as p where p.type = 'Laptop'
--and p.maker not in(select maker from product where type = 'Printer'))

--update product
--set maker = 'A'
--where maker = 'B'

--update pc
--set price = price / 2, hd = hd + 20

--update laptop
--set screen = screen + 1
--where model in (select model from product where type = 'Laptop' and maker = 'B')

--use ships;

--insert into CLASSES(class, type, country, numGuns, bore, displacement)
--values ('Nelson', 'bb', 'UK', 9, 16, 34000)

--insert into ships(name, class, launched)
--values ('Nelson', 'Nelson', 1927), ('Rodney', 'Nelson', 1927)

--delete from ships
--where name in (select o.ship from OUTCOMES as o where o.result = 'sunk')

--update CLASSES
--set bore = bore * 2.5, DISPLACEMENT = displacement / 1.1


         --8--
--tipove danni
--bit -> 1, 0 ili Null (pak celochislena stoinost)
--decimal (5, 2) -> 123.45 / numeric
--char(5) -> 'abc__' -> nakraq se ignorirat; za nizove s edna i sushta ili mnogo blizka duljina
--varchar(5) -> 'abc' -> ne se dobavqt intervali, + oshte 2 baita za broq chars
--definirane na shema na relaciq
--create database name;
--create table name (col1 tip_danni1(razmer), ...)
--identity -> za koloni s tip nqkakvo chislo, generira posledovatelni chisla mai, ne garantira unikalnost
--id INT IDENTITY(1, 1) -> broeneto zaposhva ot 1, increment s 1; ne zadavame qvno stoinost -> moje da se razreshava ili ne
--select title, year, studioname as coloredStudio
--into coloredMovie
--from movie where incolor ='y'
--
--alter table moviestar
--add phone varchar(16) default 'unknown'
--
--alter table moviestar
--drop column phone
--bez default -> add default 'unknown' for phone
--not null ogranichenie
--drop table name; drop database name

-- vij za Null i po podrazbirane stoinosti!!!

--1
--create table Products (maker CHAR(1), model varchar(4), type varchar(7))
--create table Printer (code INT, model varchar(4), price decimal(10,2))

--insert into Products(maker, model, type)
--values('C', '1000', 'pc'), ('A', '1010', 'printer'), ('B', '2000', 'printer')

--insert into Printer(code, model, price)
--values(1, '1000', 120.33), (2, '1010', 100.10), (3, '2000', 170.90)

--alter table Printer
--add type varchar(6), color char(1) default 'y'

--alter table Printer
--drop column price

--drop table Printer
--drop table Products

--2
--create database Facebook
--use Facebook;

--create table Users (id int identity(1, 1) primary key, email varchar(50), password varchar(50), registration date)

--create table Friends (user_id int, friend_id int, foreign key(user_id) references Users(id), foreign key(friend_id) references Users(id))

--CREATE TABLE Walls (
--    user_id INT,
--    author_id INT,
--    message TEXT,
--    post_date DATE,
--    FOREIGN KEY (user_id) REFERENCES Users(id),
--    FOREIGN KEY (author_id) REFERENCES Users(id)
--);

--CREATE TABLE Groups (
--    id INT IDENTITY(1,1) PRIMARY KEY,
--    name VARCHAR(50),
--    description TEXT DEFAULT ''
--);

--CREATE TABLE GroupMembers (
--    group_id INT,
--    user_id INT,
--    FOREIGN KEY (group_id) REFERENCES Groups(id),
--    FOREIGN KEY (user_id) REFERENCES Users(id)
--);

--INSERT INTO Users (email, password, registration)
--VALUES
--    ('ivan@mail.com', 'pass123', '2023-01-01'),
--    ('maria@mail.com', 'abc456', '2023-01-05'),
--    ('peter@mail.com', 'qwerty', '2023-02-10'),
--    ('sofia@mail.com', '123456', '2023-03-15');

--INSERT INTO Friends (user_id, friend_id)
--VALUES
--    (1, 2),
--    (1, 3),
--    (1, 4),
--    (2, 1);

--INSERT INTO Walls (user_id, author_id, message, post_date)
--VALUES
--    (1, 2, 'Hi Ivan!', '2023-04-01'),
--    (1, 3, 'What is up?', '2023-04-02'),
--    (2, 1, 'Hello Maria!', '2023-04-03');

--INSERT INTO Groups (name)
--VALUES
--    ('Travel Lovers'),
--    ('Movie Fans');

--INSERT INTO GroupMembers (group_id, user_id)
--VALUES
--    (1, 1),
--    (1, 2),
--    (2, 3),
--    (2, 4);


	         --9--
--pravila, nalagashti ogranicheniq
--kogato promenqme bazite danni
--1. purvichen klyuch
--ne e zaduljitelno da ima pk, no e hubavo
--2. unique ogranichenie
--3. vunshen klyuch - fk
--name char(30) (constraint pk_m) primary key
--constraint <name> - ne e zaduljitelno, ako trqbva da go triem
--ili
--constraint pk_m primary key (name)
--constraint pk_m primary key (name, year)
--constraint pk_m unique key (name)
--check ogranichenie

--1
--create database Flights
--use Flights;

--create table Airline (code INT not null primary key, name varchar(50) not null unique, country varchar(50))

--create table Airport (code int not null primary key, name varchar(50) not null, country varchar(50) not null, city varchar(50)
--	unique (name, country))  --here the combination name, country must be unique

--create table Airplane (code int not null primary key, type varchar(50), seats int not null check (seats > 0), year int)

--create table Customer (id int primary key, fname varchar(30) not null, lname varchar(30) not null, email varchar(30)
--	unique check (email like '%@%._%'))

--create table Agency (name varchar(100) primary key, country varchar(100), city varchar(100), phone varchar(20))

--create table Flight (fnumber int not null primary key, airline_operator int not null, dep_airport int not null,
--					arr_airport int not null, flilght_time time, flight_duration int, airplane int,
--					FOREIGN KEY (airline_operator) references Airline(code),
--					foreign key (dep_airport) references Airport(code),
--					FOREIGN KEY (ARR_AIRPORT) REFERENCES AIRPORT(code),
--					FOREIGN KEY (airplane) REFERENCES AIRPLANE(code),
--					CHECK (DEP_AIRPORT <> ARR_AIRPORT) -- Flight cannot depart and arrive at the same airport
--)

--CREATE TABLE BOOKING (
--    CODE VARCHAR(20) PRIMARY KEY,
--    AGENCY_NAME VARCHAR(100) NOT NULL,
--    AIRLINE_CODE int NOT NULL,
--    FLIGHT_NUMBER int NOT NULL,
--    CUSTOMER_ID INT NOT NULL,
--    BOOKING_DATE DATE NOT NULL,
--    FLIGHT_DATE DATE NOT NULL,
--    PRICE DECIMAL(10, 2) NOT NULL CHECK (PRICE >= 0),
--    STATUS INT NOT NULL CHECK (STATUS IN (0, 1)), -- 0 for unconfirmed, 1 for confirmed
--    FOREIGN KEY (AGENCY_NAME) REFERENCES AGENCY(NAME),
--    FOREIGN KEY (AIRLINE_CODE) REFERENCES AIRLINE(CODE),
--    FOREIGN KEY (FLIGHT_NUMBER) REFERENCES FLIGHT(FNUMBER),
--    FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMER(ID),
--    CHECK (FLIGHT_DATE >= BOOKING_DATE)
--);


	         --10--
-- index - otdelen obekt

--USE master
--GO
--if exists (select * from sysdatabases where name='FLIGHTS')
--	DROP DATABASE FLIGHTS
--GO

--CREATE DATABASE FLIGHTS
--GO
--USE FLIGHTS
--GO

--/* CREATE TABLES */

--CREATE TABLE AIRLINES(
--    CODE CHAR(2) NOT NULL,
--    NAME VARCHAR(20) UNIQUE NOT NULL,
--    COUNTRY VARCHAR(50) NOT NULL,
--    PRIMARY KEY (CODE)
--);

--CREATE TABLE AIRPORTS(
--    CODE CHAR(3) NOT NULL,
--    NAME VARCHAR(50) UNIQUE NOT NULL,
--    COUNTRY VARCHAR(50) NOT NULL,
--    CITY VARCHAR(50) NOT NULL,
--    PRIMARY KEY (CODE)
--);

--CREATE TABLE AIRPLANES(
--    CODE CHAR(3) NOT NULL,
--    TYPE VARCHAR(30) NOT NULL,
--    SEATS INT NOT NULL,
--    YEAR INT NOT NULL,
--    PRIMARY KEY (CODE)
-- );

--CREATE TABLE FLIGHTS(
--    FNUMBER CHAR(10) NOT NULL PRIMARY KEY,
--    AIRLINE_OPERATOR CHAR(2) NOT NULL REFERENCES AIRLINES(CODE),
--    DEP_AIRPORT CHAR(3) NOT NULL REFERENCES AIRPORTS(CODE),
--    ARR_AIRPORT CHAR(3) NOT NULL REFERENCES AIRPORTS(CODE),
--    FLIGHT_TIME TIME NOT NULL,
--    FLIGHT_DURATION INT NOT NULL,
--    AIRPLANE CHAR(3) NOT NULL REFERENCES AIRPLANES(CODE)
-- );

--CREATE TABLE CUSTOMERS(
--    ID INT NOT NULL PRIMARY KEY,
--    FNAME VARCHAR(50) NOT NULL,
--    LNAME VARCHAR(50) NOT NULL,
--    EMAIL VARCHAR(50)
--);

--CREATE TABLE AGENCIES(
--    NAME VARCHAR(100) NOT NULL PRIMARY KEY,
--    COUNTRY VARCHAR(50) NOT NULL,
--    CITY VARCHAR(50) NOT NULL,
--    PHONE VARCHAR(50)
-- );

--CREATE TABLE BOOKINGS(
--    CODE CHAR(6) NOT NULL PRIMARY KEY,
--    AGENCY VARCHAR(100) NOT NULL REFERENCES AGENCIES(NAME),
--    AIRLINE_CODE CHAR(2) NOT NULL REFERENCES AIRLINES(CODE),
--    FLIGHT_NUMBER CHAR(10) NOT NULL REFERENCES FLIGHTS(FNUMBER),
--    CUSTOMER_ID INT NOT NULL REFERENCES CUSTOMERS(ID),
--    BOOKING_DATE DATE NOT NULL,
--    FLIGHT_DATE DATE NOT NULL,
--    PRICE DECIMAL (9,2) NOT NULL,
--    STATUS INT NOT NULL
--);

--/* INSERT DATA */

----airlines
--INSERT INTO AIRLINES
--VALUES  ('AZ', 'Alitalia', 'Italy'),
--		('BA', 'British Airways', 'United Kingdom'),
--		('LH', 'Lufthansa', 'Germany'),
--		('SR', 'Swissair', 'Switzerland'),
--		('FB', 'Bulgaria Air', 'Bulgaria'),
--		('SU', 'Aeroflot', 'Russian Federation'),
--		('AF', 'Air France', 'France'),
--		('TK', 'Turkish Airlines', 'Turkey'),
--		('AA', 'American Airlines', 'United States'),
--		('OA', 'Olympic Air', 'Greece'),
--		('A3', 'Aegean Airlines', 'Greece'),
--		('ET', 'Ethiopian Airlines', 'Ethiopia'),
--		('U2', 'EasyJet', 'United Kingdom'),
--		('DL', 'Delta Air Lines', 'France');
--select * from airlines;
----airports
--INSERT INTO AIRPORTS
--VALUES	('SVO', 'Sheremetyevo', 'Russian Federation', 'Moscow'),
--		('DME', 'Domodedovo', 'Russian Federation', 'Moscow'),
--		('SOF', 'Sofia International', 'Bulgaria', 'Sofia'),
--		('BOJ', 'Burgas International', 'Bulgaria', 'Burgas'),
--		('CDG', 'Charles De Gaulle', 'France', 'Paris'),
--		('ORY', 'Orly', 'France', 'Paris'),
--		('LBG', 'Le Bourget', 'France', 'Paris'),
--		('JFK', 'John F Kennedy International', 'United States','New York'),
--		('ORD', 'Chicago O''Hare International', 'United States', 'Chicago'),
--		('IST', 'Ataturk International', 'Turkey', 'Istanbul'),
--		('ESB', 'Esenboga International', 'Turkey', 'Ankara'),
--		('AHN', 'Athens', 'Greece', 'Athens'),
--		('FKB', 'Karlsruhe', 'Germany', 'Karlsruhe'),
--		('TXL', 'Tegel', 'Germany', 'Berlin'),
--		('BER', 'Berlin Metropolitan Area', 'Germany', 'Berlin'),
--		('MUC', 'Franz Josef Strauss', 'Germany', 'Munich'),
--		('GVA', 'Geneve-Cointrin', 'Switzerland', 'Geneve'),
--		('BRN', 'Belp', 'Switzerland', 'Berne'),
--		('FCO', 'Leonardo da Vinci International', 'Italy', 'Rome'),
--		('LIN', 'Linate', 'Italy', 'Milan'),
--		('LHR', 'London Heathrow', 'United Kingdom', 'London');
--select * from airports;
----airplanes
--INSERT INTO AIRPLANES
--VALUES	('319', 'Airbus A319', 150, 2003),
--		('320', 'Airbus A320', 280, 2013),
--		('321', 'Airbus A321', 150, 2018),
--		('100', 'Fokker 100', 80, 2000),
--		('738', 'Boeing 737-800', 90, 2020),
--		('735', 'Boeing 737-800', 90, 2016),
--		('AT5', 'ATR 42�0', 50, 1995),
--		('DH4', 'De Havilland DHC-8-400', 70, 1992);
--select * from airplanes;
----flights
--INSERT INTO FLIGHTS
--VALUES	('FB1363', 'SU', 'SOF', 'SVO', '12:45', 100, '738'),
--		('FB1364', 'SU', 'SVO', 'SOF', '10:00', 120, '321'),
--		('SU2060', 'SU', 'SVO', 'SOF', '11:10', 110, '738'),
--		('SU2061', 'SU', 'SOF', 'SVO', '13:00', 110, '320'),
--		('FB363', 'FB', 'SOF', 'SVO', '15:10', 110, '738'),
--		('FB364', 'FB', 'SVO', 'SOF', '21:05', 120, '738'),
--		('FB437', 'FB', 'SOF', 'MUC', '09:10', 120, '319'),
--		('FB438', 'FB', 'MUC', 'SOF', '12:10', 90, '738'),
--		('TK1027', 'TK', 'IST', 'SOF', '07:00', 100, '738'),
--		('TK1028', 'TK', 'SOF', 'IST', '10:00', 100, 'AT5'),
--		('OA307', 'OA', 'AHN', 'SOF', '09:25', 40, '738'),
--		('OA308', 'OA', 'SOF', 'AHN', '10:25', 40, '738'),
--		('EZY3159', 'U2', 'LHR', 'SOF', '10:05', 90, '738'),
--		('EZY3160', 'U2', 'SOF', 'LHR', '12:45', 90, '738'),
--		('EZY1931', 'U2', 'LHR', 'SOF', '10:15', 90, '738'),
--		('EZY1932', 'U2', 'SOF', 'LHR', '13:05', 90, '738'),
--		('LH1702', 'LH', 'MUC', 'SOF', '10:10', 100, '738'),
--		('LH1703', 'LH', 'SOF', 'MUC', '13:10', 100, '738'),
--		('FB851', 'FB', 'SOF', 'LHR', '13:30', 100, '738'),
--		('FB852', 'FB', 'LHR', 'SOF', '16:30', 100, '100'),
--		('LH1426', 'LH', 'FKB', 'SOF', '11:05', 120, '738'),
--		('LH1427', 'LH', 'SOF', 'FKB', '13:45', 120, '735'),
--		('FB457', 'FB', 'SOF', 'CDG', '09:10', 100, '319'),
--		('FB458', 'FB', 'ORY', 'SOF', '12:10', 100, '738'),
--		('TK1037', 'TK', 'ESB', 'SOF', '07:00', 90, '738'),
--		('TK1038', 'TK', 'SOF', 'ESB', '10:00', 90, 'AT5');
--select * from flights
--INSERT INTO CUSTOMERS (ID, FNAME, LNAME, EMAIL)
--VALUES	(1, 'Petar', 'Milenov', 'petter@mail.com'),
--		(2, 'Dimitar', 'Petrov', 'petrov@mail.com'),
--		(3, 'Ivan', 'Ivanov', 'ivanov@mail.com'),
--		(4, 'Petar', 'Slavov', 'slavov@mail.com'),
--		(5, 'Bogdan', 'Bobov', 'bobov@mail.com'),
--		(6, 'Petar', 'Kirov', 'kirov@mail.com'),
--		(7, 'Vladimir', 'Petrov', 'vladov@mail.com');
--select * from customers;
--INSERT INTO AGENCIES
--VALUES	('Travel One', 'Bulgaria', 'Sofia', '0783482233'),
--		('Travel Two', 'Bulgaria', 'Plovdiv', '02882234'),
--		('Travel Tour', 'Bulgaria', 'Sofia', NULL),
--		('Aerotravel', 'Bulgaria', 'Varna', '02884233'),
--		('Aerofly', 'Bulgaria', 'Sofia', '02882533'),
--		('Fly Tour', 'Bulgaria', 'Sofia', '02881233');
--select * from agencies;
--INSERT INTO BOOKINGS
--VALUES	('YN298P', 'Travel One', 'FB', 'FB1363', 1, '2021-04-27', '2021-12-25', 300, 0),
--		('YA298P', 'Travel Two', 'TK', 'TK1038', 2, '2021-04-27', '2021-12-25', 300, 1),
--		('YB298P', 'Travel Tour', 'TK', 'TK1037', 3, '2021-04-27', '2021-05-25', 400, 0),
--		('YC298P', 'Travel One', 'TK', 'TK1028', 4, '2021-04-27', '2021-11-25', 350, 0),
--		('YD298P', 'Travel Tour', 'TK', 'TK1028', 1, '2021-04-27', '2021-12-20', 250, 1),
--		('YE298P', 'Aerofly', 'TK', 'TK1027', 2, '2021-04-27', '2021-12-21', 150, 0),
--		('YJ298P', 'Aerofly', 'SU', 'SU2061', 3, '2021-04-27', '2021-12-05', 500, 1),
--		('YS298P', 'Aerofly', 'SU', 'SU2061', 4, '2021-04-27', '2021-11-15', 400, 0),
--		('YK298P', 'Aerofly', 'SU', 'SU2060', 1, '2021-04-26', '2021-08-08', 350, 0),
--		('YM298P', 'Aerotravel', 'OA', 'OA308', 2, '2021-04-26', '2021-07-10', 350, 1),
--		('YN198P', 'Aerotravel', 'OA', 'OA307', 3, '2021-04-26', '2021-11-25', 450, 0),
--		('YN498P', 'Aerofly', 'LH', 'LH1703', 1, '2021-04-26', '2021-05-25', 300, 1),
--		('YN598P', 'Aerotravel', 'FB', 'FB1363', 5, '2021-04-26', '2021-06-25', 300, 0),
--		('YN698P', 'Fly Tour', 'FB', 'FB852', 6, '2021-04-26', '2021-07-25', 330, 1),
--		('YL298P', 'Fly Tour', 'FB', 'FB851', 7, '2021-04-26', '2021-05-25', 360, 0),
--		('YZ298P', 'Fly Tour', 'FB', 'FB458', 1, '2021-04-26', '2021-06-25', 380, 1),
--		('YN268P', 'Fly Tour', 'FB', 'FB457', 2, '2021-04-26', '2021-12-21', 390, 0);
--select * from bookings;


--create view about_flights
--as
--select A.name as airline_name, A.code as operator, F.FNUMBER AS Flight_Number, COUNT(B.CODE) AS Confirmed_Passengers
--FROM
--    FLIGHTS AS F
--INNER JOIN
--    AIRLINES AS A ON F.AIRLINE_OPERATOR = A.CODE
--LEFT JOIN
--    BOOKINGS AS B ON F.FNUMBER = B.FLIGHT_NUMBER AND B.STATUS = 1 -- Join only confirmed bookings
--GROUP BY
--    A.CODE, A.NAME, F.FNUMBER;

--select * from about_flights

--create view most_reservations
--as
--select b.AGENCY, b.customer_id, COUNT(b.CODE) AS reservations
--from Bookings as b
--group by b.AGENCY, b.customer_id
--having
--COUNT(B.CODE) = (
--        -- Тази подзаявка намира максималния брой резервации за текущата агенция
--        SELECT MAX(reservations)
--        FROM (
--            SELECT
--                B2.AGENCY,
--                B2.CUSTOMER_ID,
--                COUNT(B2.CODE) AS ReservationsCount
--            FROM
--                BOOKINGS AS B2
--            WHERE
--                B2.AGENCY = B.AGENCY -- Свързваме подзаявката с външната заявка по агенция
--            GROUP BY
--                B2.AGENCY, B2.CUSTOMER_ID
--        ) AS MaxReservationsPerCustomer
--    );
-- obedinqvame 2 tablici booking i s tqh sravnqvame

--create view agency_sofia
--as
--select *
--from AGENCIES
--where city = 'Sofia'
--WITH CHECK OPTION;

--create view agency_no_ph
--as
--select *
--from AGENCIES
--where PHONE is Null
--WITH CHECK OPTION;

	         --11--
--UPDATE F
--SET F.num_pass = (SELECT COUNT(B.CODE) FROM BOOKINGS B WHERE B.FLIGHT_NUMBER = F.FNUMBER AND B.STATUS = 1)
--FROM FLIGHTS F;

--UPDATE A
--SET A.num_book = (SELECT COUNT(B.CODE) FROM BOOKINGS B WHERE B.AGENCY = A.NAME)
--FROM AGENCIES A;

--CREATE TRIGGER trg_Bookings_Insert
--ON BOOKINGS
--AFTER INSERT
--AS
--BEGIN
--    -- Защита срещу множество редове (multi-row inserts)
--    SET NOCOUNT ON;

--    -- Актуализиране на num_pass в таблицата FLIGHTS
--    -- Увеличава num_pass само ако вмъкнатата резервация е потвърдена (STATUS = 1)
--    UPDATE F
--    SET F.num_pass = F.num_pass + 1
--    FROM FLIGHTS F
--    INNER JOIN inserted i ON F.FNUMBER = i.FLIGHT_NUMBER
--    WHERE i.STATUS = 1;

--    -- Актуализиране на num_book в таблицата AGENCIES
--    -- Увеличава num_book за всяка вмъкната резервация
--    UPDATE A
--    SET A.num_book = A.num_book + 1
--    FROM AGENCIES A
--    INNER JOIN inserted i ON A.NAME = i.AGENCY;
--END;

--CREATE TRIGGER trg_Bookings_Delete
--ON BOOKINGS
--AFTER DELETE
--AS
--BEGIN
--    -- Защита срещу множество редове (multi-row deletes)
--    SET NOCOUNT ON;

--    -- Актуализиране на num_pass в таблицата FLIGHTS
--    -- Намалява num_pass само ако изтритата резервация е била потвърдена (STATUS = 1)
--    UPDATE F
--    SET F.num_pass = F.num_pass - 1
--    FROM FLIGHTS F
--    INNER JOIN deleted d ON F.FNUMBER = d.FLIGHT_NUMBER
--    WHERE d.STATUS = 1;

--    -- Актуализиране на num_book в таблицата AGENCIES
--    -- Намалява num_book за всяка изтрита резервация
--    UPDATE A
--    SET A.num_book = A.num_book - 1
--    FROM AGENCIES A
--    INNER JOIN deleted d ON A.NAME = d.AGENCY;
--END;

--CREATE TRIGGER trg_Bookings_Update
--ON BOOKINGS
--AFTER UPDATE
--AS
--BEGIN
--    -- Защита срещу множество редове (multi-row updates)
--    SET NOCOUNT ON;

--    -- Проверяваме дали колоната STATUS е била променена
--    IF UPDATE(STATUS)
--    BEGIN
--        -- Случай 1: Статусът се променя от непотвърден (0) на потвърден (1)
--        UPDATE F
--        SET F.num_pass = F.num_pass + 1
--        FROM FLIGHTS F
--        INNER JOIN inserted i ON F.FNUMBER = i.FLIGHT_NUMBER
--        INNER JOIN deleted d ON F.FNUMBER = d.FLIGHT_NUMBER AND i.CODE = d.CODE -- Присъединяване и по CODE за сигурност
--        WHERE d.STATUS = 0 AND i.STATUS = 1;

--        -- Случай 2: Статусът се променя от потвърден (1) на непотвърден (0)
--        UPDATE F
--        SET F.num_pass = F.num_pass - 1
--        FROM FLIGHTS F
--        INNER JOIN inserted i ON F.FNUMBER = i.FLIGHT_NUMBER
--        INNER JOIN deleted d ON F.FNUMBER = d.FLIGHT_NUMBER AND i.CODE = d.CODE
--        WHERE d.STATUS = 1 AND i.STATUS = 0;
--    END

	         --12--
--CREATE DATABASE FurnitureCompany;
--GO

---- Switch to the newly created database
--USE FurnitureCompany;
--GO

--/* CREATE TABLES */

---- Table: CUSTOMER
---- Customer_ID is an IDENTITY column, meaning it auto-increments.
---- Customer_Name, Customer_Address, Customer_City, and City_Code are required.
--CREATE TABLE CUSTOMER (
--    Customer_ID INT IDENTITY(1,1) PRIMARY KEY, -- Auto-incrementing primary key
--    Customer_Name VARCHAR(100) NOT NULL,
--    Customer_Address VARCHAR(255) NOT NULL,
--    Customer_City VARCHAR(100) NOT NULL,
--    City_Code VARCHAR(10) NOT NULL -- Assuming this is like a postal code or city identifier
--);
--GO

---- Table: PRODUCT
---- Product_ID is the primary key.
---- Product_Description, Standard_Price, and Product_Line_ID are required.
---- Product_Finish has a CHECK constraint to ensure valid values.
--CREATE TABLE PRODUCT (
--    Product_ID INT PRIMARY KEY,
--    Product_Description VARCHAR(255) NOT NULL,
--    Product_Finish VARCHAR(50) NOT NULL,
--    Standard_Price DECIMAL(10, 2) NOT NULL CHECK (Standard_Price >= 0), -- Price cannot be negative
--    Product_Line_ID INT NOT NULL, -- Assuming this is a foreign key to a Product_Line table, but not defined here
--    -- CHECK constraint for Product_Finish values
--    CONSTRAINT CK_Product_Finish CHECK (Product_Finish IN (
--        'череша', 'естествен ясен', 'бял ясен', 'червен дъб', 'естествен дъб', 'орех'
--    ))
--);
--GO

---- Table: ORDER_T (using _T to avoid conflict with SQL reserved word ORDER)
---- Order_ID is the primary key.
---- Order_Date and Customer_ID are required.
---- Customer_ID is a foreign key referencing CUSTOMER.Customer_ID.
--CREATE TABLE ORDER_T (
--    Order_ID INT PRIMARY KEY,
--    Order_Date DATE NOT NULL,
--    Customer_ID INT NOT NULL,
--    -- Foreign key constraint linking to the CUSTOMER table
--    FOREIGN KEY (Customer_ID) REFERENCES CUSTOMER(Customer_ID)
--);
--GO

---- Table: ORDER_LINE
---- This is a junction table for many-to-many relationship between ORDER_T and PRODUCT.
---- Composite primary key (Order_ID, Product_ID) ensures uniqueness for each line item in an order.
---- Ordered_Quantity is required and must be positive.
---- Order_ID is a foreign key referencing ORDER_T.Order_ID.
---- Product_ID is a foreign key referencing PRODUCT.Product_ID.
--CREATE TABLE ORDER_LINE (
--    Order_ID INT NOT NULL,
--    Product_ID INT NOT NULL,
--    Ordered_Quantity INT NOT NULL CHECK (Ordered_Quantity > 0), -- Quantity must be positive
--    -- Composite primary key
--    PRIMARY KEY (Order_ID, Product_ID),
--    -- Foreign key constraint linking to the ORDER_T table
--    FOREIGN KEY (Order_ID) REFERENCES ORDER_T(Order_ID),
--    -- Foreign key constraint linking to the PRODUCT table
--    FOREIGN KEY (Product_ID) REFERENCES PRODUCT(Product_ID)
--);
--GO

--insert into CUSTOMER values
--('Иван Петров', 'ул. Лавеле 8', 'София', '1000'),
--('Камелия Янева', 'ул. Иван Шишман 3', 'Бургас', '8000'),
--('Васил Димитров', 'ул. Абаджийска 87', 'Пловдив', '4000'),
--('Ани Милева', 'бул. Владислав Варненчик 56', 'Варна','9000');
--insert into PRODUCT values
--(1000, 'офис бюро', 'череша', 195, 10),
--(1001, 'директорско бюро', 'червен дъб', 250, 10),
--(2000, 'офис стол', 'череша', 75, 20),
--(2001, 'директорски стол', 'естествен дъб', 129, 20),
--(3000, 'етажерка за книги', 'естествен ясен', 85, 30),
--(4000, 'настолна лампа', 'естествен ясен', 35, 40);
--insert into ORDER_T values
--(100, '2013-01-05', 1),
--(101, '2013-12-07', 2),
--(102, '2014-10-03', 3),
--(103, '2014-10-08', 2),
--(104, '2015-10-05', 1),
--(105, '2015-10-05', 4),
--(106, '2015-10-06', 2),
--(107, '2016-01-06', 1);
--insert into ORDER_LINE values
--(100, 4000, 1),
--(101, 1000, 2),
--(101, 2000, 2),
--(102, 3000, 1),
--(102, 2000, 1),
--(106, 4000, 1),
--(103, 4000, 1),
--(104, 4000, 1),
--(105, 4000, 1),
--(107, 4000, 1);

--select p.Product_ID, p.Product_Description, count(o.Ordered_Quantity)
--from PRODUCT as p inner join ORDER_LINE as o
--on p.Product_ID = o.Product_ID
--group by p.Product_ID, p.Product_Description

--select p.Product_ID, p.Product_Description, count(o.Ordered_Quantity)
--from PRODUCT as p left join ORDER_LINE as o
--on p.Product_ID = o.Product_ID
--group by p.Product_ID, p.Product_Description

--select c.Customer_Name, sum(p.Standard_Price * ol.Ordered_Quantity)
--from CUSTOMER as c inner join ORDER_T as ot
--on c.Customer_ID = ot.Customer_ID
--inner join ORDER_LINE as ol
--on ot.Order_ID = ol.Order_ID
--inner join PRODUCT as p
--on p.Product_ID = ol.Product_ID
--group by c.Customer_Name

--use pc;

--select distinct p1.maker
--from product as p1
--where p1.model in (select p.model from product as p inner join product as p2 on p.maker = p2.maker
--where p2.type = 'Laptop' and p.type = 'Printer')

--update pc
--set price = price * 0.95
--where model in (select p.model from product as p where p.type = 'pc' and p.maker in
--(select pr.maker from product as pr inner join printer as pri on pr.model = pri.model
--where pr.type = 'Printer' group by pr.maker having avg(pri.price) > 800));

--select hd, min(price)
--from pc
--where hd >= 10 and hd <= 30
--group by hd

--use ships;

--create view battle1
--as
--select b.name from battles as b
--inner join  OUTCOMES as o
--on b.NAME = o.BATTLE
--group by b.name
--having count(o.ship) > (
--        SELECT count(ship)
--        FROM Outcomes
--        WHERE battle = 'Guadalcanal'
--);

--select * from battle1

--CREATE VIEW v_Battles_MoreCountries
--AS
--SELECT
--    B.name AS BattleName -- Име на битката
--FROM
--    Battles AS B
--INNER JOIN
--    Outcomes AS O ON B.name = O.battle
--INNER JOIN
--    Ships AS S ON O.ship = S.name
--INNER JOIN
--    Classes AS C ON S.class = C.class
--GROUP BY
--    B.name
--HAVING
--    COUNT(DISTINCT C.country) > (
--        -- Подзаявка за броя на участващите страни в битката при Guadalcanal
--        SELECT COUNT(DISTINCT C2.country)
--        FROM Outcomes AS O2
--        INNER JOIN Ships AS S2 ON O2.ship = S2.name
--        INNER JOIN Classes AS C2 ON S2.class = C2.class
--        WHERE O2.battle = 'Guadalcanal'
--    );

--select * from v_Battles_MoreCountries

--delete from OUTCOMES
--where battle in (select battle from OUTCOMES group by battle having count(ship) = 1)

--DELETE FROM Outcomes
--WHERE result = 'sunk' and
--ship IN (
--    SELECT
--        ship
--    FROM
--        Outcomes
--    WHERE
--        result = 'sunk' -- Филтрираме само потопени кораби
--    GROUP BY
--        ship
--    HAVING
--        COUNT(result) >= 2
--)

--NOT FINISHED
--CREATE VIEW v_BattleCountries
--AS
--SELECT DISTINCT
--    O.battle AS BattleName, -- Име на битката
--    C.country AS Country    -- Държава на кораба
--FROM
--    Outcomes AS O
--INNER JOIN
--    Ships AS S ON O.ship = S.name
--INNER JOIN
--    Classes AS C ON S.class = C.class;

SELECT
    C.country AS CountryName,
    COUNT(DISTINCT O.battle) AS NumberOfBattles
FROM
    Classes AS C
LEFT JOIN
    Ships AS S ON C.class = S.class
LEFT JOIN
    Outcomes AS O ON S.name = O.ship
GROUP BY
    C.country
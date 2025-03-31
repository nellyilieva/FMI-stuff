         --1--
--use movies;

--select address from STUDIO
--where name  = 'Disney'

--select birthdate from moviestar
--where name = 'Jack Nicholson'

--select starname from STARSIN
--where MOVIEYEAR = 1980 or MOVIETITLE = '%Knight%'

--select name from MOVIEEXEC
--where NETWORTH > 10000000

--select name from MOVIESTAR
--where GENDER = 'M' or ADDRESS = 'Prefect Rd'

--use pc;

--select model, speed as MHz, hd as GB from pc
--where price < 1200

--select distinct maker from product
--where type = 'Printer'

--select model, ram, screen from laptop
--where price > 1000

--select * from printer
--where color = 'y'

--select model, speed, hd from pc
--where (cd = '12x' or cd = '16x') and price < 2000

--use ships;

--select class, country from CLASSES
--where NUMGUNS < 10

--select name as shipName from ships
--where LAUNCHED < 1918

--select ship, BATTLE from OUTCOMES
--where result = 'sunk'

--select name from ships
--where name = class

--select name from ships
--where name like 'R%'

--select name from ships
--where name like '% %'

--!!! like for partial matches or pattern
--!!! '% %' -> have at least 1 interval


         --2--
--from movie cross join movieexec или from movie, movieexec за да използваме и двете таблици
--ако в една от двете таблици няма кортеж -> празното множество
--[inner] join -> казваме задължително какво ни е условието за свързване
--select ... from a inner join b on keyA = keyB where ...
--on -> условие за свързване, where -> условие за търсене
--union -> трябва да имаме еднакъв брой атрибути, съвметимост на типа на данните, правим отделни query-та
--intersect -> с приоритет и except; могат да се 'обединяват'
--union -> без поватрящи се, union all -> с повтарящи се
--a except b -> in a but not in b
--a intersect b -> in a and b

--use movies;

--select name from STARSIN inner join MOVIESTAR
--on STARNAME = NAME
--where gender = 'M' and MOVIETITLE = 'The Usual Suspects'

--select distinct starname from MOVIE, STARSIN
--where STUDIONAME = 'MGM' and MOVIEYEAR = 1995

--select distinct name from movie inner join MOVIEEXEC
--on CERT# = PRODUCERC#
--where STUDIONAME = 'MGM'

--select m1.title from movie as m1, movie as m2
--where m2.title = 'Star Wars' and m1.LENGTH > m2.LENGTH

--select e1.name from MOVIEEXEC as e1, MOVIEEXEC as e2
--where e2.name = 'Stephen Spielberg' and e1.NETWORTH > e2.NETWORTH

--use pc;

--select maker, speed from product inner join laptop
--on product.model = laptop.model
--where hd > 9

--select product.model, pc.price from product
--inner join pc on product.model = pc.model
--where maker = 'B'
--union
--select product.model, laptop.price from product
--inner join laptop on product.model = laptop.model
--where maker = 'B'
--union
--select product.model, printer.price from product
--inner join printer on product.model = printer.model
--where maker = 'B'

--select maker from product
--inner join laptop on product.model = laptop.model
--except
--select maker from product
--inner join pc on product.model = pc.model

--select distinct p1.hd from pc as p1
--inner join pc as p2 on p1.hd = p2.hd and p1.code != p2.code
--intersect
--select distinct hd from pc
--or just
--select distinct p1.hd from pc as p1
--inner join pc as p2 on p1.hd = p2.hd and p1.code != p2.code

--select distinct p1.model, p2.model
--from pc as p1 inner join pc as p2
--on p1.speed = p2.speed and p1.ram = p2.ram and p1.model < p2.model

--за да сме сигурни че всяка двойка я има по веднъж
--сравняваме model по азбучен ред, така че винаги p1.model < p2.model

--select distinct maker from product
--inner join pc as pc1 on product.model = pc1.model
--inner join pc as pc2 on product.model = pc2.model
--where pc1.speed >= 400 and pc2.speed >= 400 and pc1.code != pc2.code

--use ships;

--select name from classes
--inner join ships on classes.class = ships.class
--where displacement > 50000

--select name, DISPLACEMENT, NUMGUNS from classes
--inner join ships on classes.class = ships.class
--inner join OUTCOMES on ships.name = OUTCOMES.ship and OUTCOMES.BATTLE = 'Guadalcanal'

--select c1.country from CLASSES as c1
--inner join CLASSES as c2
--on c1.COUNTRY = c2.COUNTRY
--where c1.type = 'bb' and c2.type = 'bc'

--select o1.ship from OUTCOMES as o1
--inner join OUTCOMES as o2 on o1.SHIP = o2.SHIP
--where o1.RESULT = 'damaged' and o2.RESULT != 'sunk' and o1.BATTLE != o2.BATTLE

         --3--
--top x -> изведи първите x

--use movies;

--select name from MOVIEEXEC
--where name in (select name from MOVIESTAR where gender = 'F' and NETWORTH > 10000000)

--select name from MOVIESTAR
--where name not in (select name from MOVIEEXEC)

--select title from movie
--where movie.LENGTH > (select LENGTH from movie where title = 'Star Wars')

--select title, name from movie inner join MOVIEEXEC
--on cert# = producerc#
--where NETWORTH > (select NETWORTH from MOVIEEXEC where name = 'Merv Griffin')
--!!!!!!check

--use pc;

--select maker from product
--where model in (select model from pc where speed > 500)

--select code, model, price from printer
--where price >= all(select price from printer)

--select * from laptop
--where speed < all (select speed from pc)

--select top 1 model, price from (select model, price from pc union all select model, price from laptop union all select model, price from printer)
--as total order by price DESC

--select maker from product
--where model in (select model from printer where color = 'y' and price <= all (select price from printer where color = 'y'))

--select maker from product
--where model in (select model from pc where ram <= all (select ram from pc) and speed >= all(select speed from pc where ram <= all (select ram from pc)))

--use ships;

--select distinct country from classes
--where numguns >= all (select numguns from classes)

--select distinct class from ships
--where name in (select ship from OUTCOMES where result = 'sunk')

--select class, name from ships
--where class in (select class from CLASSES where bore = 16)

--select battle from OUTCOMES
--where ship in (select name from ships where class = 'Kongo')

--select s.class, s.name from ships as s
--join CLASSES as c on s.class = c.class
--where c.NUMGUNS >= all (select c2.numguns from classes as c2 where c2.bore = c.bore)


         --4--
--външни съединения -> когато ни интересуват NULL стойности

--use movies;

--select title, name from movie inner join MOVIEEXEC
--on PRODUCERC# = CERT#
--where name in (select name from MOVIEEXEC inner join movie on PRODUCERC# = CERT# where title = 'Star Wars')

--select distinct name from MOVIEEXEC inner join movie
--on PRODUCERC# = CERT#
--inner join STARSIN
--on title = MOVIETITLE and year = MOVIEYEAR
--where STARNAME = 'Harrison Ford'

--select distinct studioname, starname from movie inner join STARSIN
--on title = MOVIETITLE and year = MOVIEYEAR
--inner join STUDIO
--on STUDIONAME = studio.name
--where MOVIETITLE = title

--select starname, NETWORTH, title from STARSIN inner join movie
--on title = MOVIETITLE and year = MOVIEYEAR
--inner join MOVIEEXEC
--on producerc# = CERT#
--where NETWORTH >= all (select NETWORTH from MOVIEEXEC)

--select name from MOVIESTAR left join STARSIN
--on name = STARNAME
--where MOVIETITLE is Null

--use pc;

--select p.maker, p.model, p.type from product as p left join laptop as l
--on p.model = l.model
--left join pc on p.model = pc.model
--left join printer as pr
--on p.model = pr.model
--where l.model is Null and pc.model is Null and pr.model is Null

--select distinct p1.maker from product as p1
--join product as p2 on p1.maker = p2.maker
--where p1.type = 'Laptop' and p2.type = 'Printer'

--select distinct l1.hd from laptop as l1
--inner join laptop as l2	
--on l1.hd = l2.hd AND l1.model != l2.model

--select * from pc left join product
--on product.model = pc.model
--where maker is Null

--use ships;

--select * from ships inner join classes
--on classes.class = ships.class
-- we don't need the Null condition because inner join automatically removes rows where classes.class would be NULL
--where classes.class is not Null

--select * from classes left join ships
--on classes.class = ships.class
--where ships.name is not Null
--or classes.class in (select name from ships)

--select country, ships.name from classes inner join ships
--on classes.class = ships.class
--left join outcomes on ships.name = OUTCOMES.ship
--where battle is Null
--ORDER BY country, ships.name;

--select name as 'Ship Name' from ships
--inner join classes on classes.class = ships.class
--where numguns >= 7 and LAUNCHED = 1916

--select ship, name, date from OUTCOMES inner join BATTLES
--on OUTCOMES.BATTLE = BATTLES.name
--where result = 'sunk'
--order by name

--select name, displacement, launched from ships inner join classes
--on classes.class = ships.class
--where ships.name = ships.class

--select classes.* from classes left join ships
--on classes.class = ships.class
--where launched is Null

--select name, displacement, numguns, result from ships inner join classes
--on classes.class = ships.class
--inner join OUTCOMES on OUTCOMES.SHIP = ships.name
--where battle = 'North Atlantic'


         --5--
-- sum, avg, min, max, count
-- we use them with group by
-- we don't use them in WHERE
-- to filter them -> HAVING
-- Null is ignored
-- when i have normal column to show with the other one, i need to use group by!!!

--use pc;

--select avg(speed) from pc

--select maker, avg(screen) from laptop inner join product
--on product.model = laptop.model
--where type = 'Laptop'
--group by maker

--select avg(speed) from laptop
--where price > 1000

--select maker, avg(price) from pc
--inner join product
--on product.model = pc.model
--where maker = 'A'
--group by maker

--select 
--    maker,
--    avg(combined.price) as average_combined_price
--from (
--    select p.maker, pc.price
--    from product p
--    inner join pc on p.model = pc.model
--    where p.maker = 'B' and p.type = 'PC'
    
--    union all
    
--    select p.maker, l.price
--    from product p
--    inner join laptop l on p.model = l.model
--    where p.maker = 'B' and p.type = 'Laptop'
--) as combined
--group by maker;

--select speed, avg(price) from pc
--group by speed

--select maker, count(distinct code) from product
--inner join pc on product.model = pc.model
--where product.type = 'PC'
--group by maker
--having count(distinct code) >= 3

--select top 1 maker, max(price) from product
--inner join pc on pc.model = product.model
--group by maker

--select speed, avg(price) from pc
--where speed > 800
--group by speed

--select maker, avg(hd) from pc
--inner join product on product.model = pc.model
--where maker in (select distinct maker from product where type = 'Printer')
--group by maker

--use ships;

--select count(class) from classes
--where type = 'bb'

--select class, avg(numguns) from classes
--where type = 'bb'
--group by class

--select avg(numguns) from classes

--select classes.class, min(launched), max(launched) from classes
--inner join ships on classes.class = ships.class
--group by classes.class

--select classes.class, count(result) from classes
--inner join ships on classes.class = ships.class
--inner join OUTCOMES on OUTCOMES.ship = ships.name
--where result = 'sunk'
--group by classes.class

--select classes.class, count(result) from classes
--inner join ships on classes.class = ships.class
--inner join OUTCOMES on OUTCOMES.ship = ships.name
--where result = 'sunk'
--group by classes.class
--having count(ships.name) > 2

--select country, avg(bore) from classes
--group by country


         --6--
-- LIKE -> за сравнение на символни низове по шаблон
-- Null -> в аритметична операция, резултатът е Null; сравняваме с нещо неизвестно(Null) -> UNKNOWN, няма да бъдат включени накрая
-- UNION, INTERSECT, EXCEPT
-- from (subq as t1) join t2 on ...
-- in, >= all(subq), > any, exists

--use movies;

--select title, year, length
--from movie
--where (length > 120 or length is Null ) and year < 2000

--select name, gender
--from MOVIESTAR
--where name like 'J%' and BIRTHDATE > 1948
--order by name desc

--select studioname, count(distinct starname) from movie
--inner join starsin on title = MOVIETITLE and year = MOVIEYEAR
--group by STUDIONAME

--select name, count(distinct MOVIETITLE) from MOVIESTAR
--left join starsin on starname = name
--group by name
-- we use left join to return and the actors who don't have data in starsin
-- inner join will only return the ones who have data in starsin !!!

--select m1.studioname, m1.title, m1.year from movie as m1
--where m1.year >= all(select m2.year from movie m2 where m2.STUDIONAME = m1.STUDIONAME)
--or
--select m1.studioname, m1.title, m1.year from movie as m1
--join (select studioname, max(year) as max_year from movie group by STUDIONAME) as t
--on m1.STUDIONAME = t.STUDIONAME and m1.YEAR = t.max_year
-- we don't see the columns from t table because we don't select them in the outer SELECT clause !!!

--select name from MOVIESTAR
--where BIRTHDATE >= all(select BIRTHDATE from MOVIESTAR where gender = 'M')
--and gender = 'M' -> works
--or
--select name from MOVIESTAR
--where BIRTHDATE = (select max(BIRTHDATE) from MOVIESTAR where gender = 'M') -> no repetition, somehow better
--or
--select m.name from MOVIESTAR as m
--join (select max(BIRTHDATE) as bd from MOVIESTAR where gender = 'M') as t
--on m.BIRTHDATE = t.bd -> it is an option, i do not prefer it

--SELECT si.starname, m.studioname, COUNT(*) AS movie_count
--FROM starsin as si
--inner join movie as m ON si.movietitle = m.title AND si.movieyear = m.year
--GROUP BY si.starname, m.studioname
--HAVING COUNT(*) = (SELECT MAX(movie_count) FROM (SELECT COUNT(*) AS movie_count FROM starsin as si2
--inner join movie as m2 ON si2.movietitle = m2.title AND si2.movieyear = m2.year
--WHERE m2.studioname = m.studioname
--GROUP BY si2.starname) AS studio_movies);

--select movietitle, movieyear, count(starname) as cs from starsin
--group by MOVIETITLE, movieyear
--having count(starname) > 2

--use ships;

--select distinct ship from OUTCOMES
--where ship like 'C%' or ship like 'K%'

--select distinct name, country from ships
--inner join classes
--on classes.class = ships.class
--left join outcomes
--on OUTCOMES.ship = ships.name
--where result != 'sunk' or OUTCOMES.ship is Null
--When we add WHERE result != 'sunk', this evaluates to:
--TRUE for ships that participated but weren't sunk
--FALSE for ships that participated and were sunk
--NULL (not TRUE) for ships that never participated (because result is NULL)
--SQL only includes rows where the WHERE condition evaluates to TRUE
--that is way we need the null condition despite the usage of left join

--select country, count(distinct o.ship) from classes
--left join ships
--on CLASSES.class = ships.class
--left join (select ship from OUTCOMES where result = 'sunk') as o
--on o.SHIP = ships.NAME
--group by country

--select battle from outcomes
--inner join ships on OUTCOMES.SHIP = ships.NAME
--group by battle
--having count(distinct ships.name) > (select count(distinct ships.name) from ships inner join outcomes on OUTCOMES.SHIP = ships.NAME
--where battle = 'Guadalcanal')

--select battle from outcomes
--inner join ships on OUTCOMES.SHIP = ships.NAME
--inner join classes on classes.class = ships.class
--group by battle
--having count(distinct classes.country) > (select count(distinct classes.country) from CLASSES inner join ships on classes.class = ships.class
--inner join OUTCOMES on OUTCOMES.SHIP = ships.NAME where battle = 'Surigao Strait')
--ok

--select name, displacement, numguns from CLASSES
--inner join ships on classes.class = ships.class
--where DISPLACEMENT <= all (select DISPLACEMENT from classes)
--and NUMGUNS >= all (select NUMGUNS from CLASSES where DISPLACEMENT <= all (select DISPLACEMENT from classes))
--or
--select name, displacement, numguns from CLASSES
--inner join ships on classes.class = ships.class
--where DISPLACEMENT = (select min(DISPLACEMENT) from classes)
--and NUMGUNS = (select max(NUMGUNS) from CLASSES where DISPLACEMENT = (select min(DISPLACEMENT) from classes))
--basically the difference is in the problem and how it is said !!!

--select count(distinct o1.ship) from outcomes as o1
--inner join outcomes as o2
--on o1.SHIP = o2.SHIP
--inner join BATTLES as b1
--on o1.battle = b1.name
--inner join BATTLES as b2
--on o2.battle = b2.name
--where o1.result = 'damaged'
--and o2.RESULT = 'ok'
--and b1.date < b2.date

--select distinct o1.ship from outcomes as o1
--inner join outcomes as o2
--on o1.SHIP = o2.SHIP
--inner join BATTLES as b1
--on o1.battle = b1.name
--inner join BATTLES as b2
--on o2.battle = b2.name
--where o1.result = 'damaged'
--and o2.RESULT = 'ok'
--and b1.date < b2.date
--and (select count(distinct o3.ship) from outcomes as o3 where o3.battle = o2.battle) > 
--(select count(distinct o4.ship)
--    from outcomes as o4
--    where o4.battle = o1.battle)

--use pc;

--select model from laptop
--where screen in (11, 15)
--group by model
--having count(model) = 2
--or
--select distinct l1.model, l2.model, l1.screen, l2.screen, l1.code, l2.code from laptop as l1
--inner join laptop as l2
--on l1.model = l2.model
--where l1.screen = 11 and l2.screen = 15

--select distinct pc.model from pc
--inner join product as p
--on pc.model = p.model
--where pc.price < (select min(l.price) from laptop as l inner join product as pl
--on pl.model = l.model
--where p.maker = pl.maker)

--select pc.model, avg(pc.price) from pc
--inner join product as p
--on pc.model = p.model
--group by pc.model, p.maker
--having avg(pc.price) < (select min(l.price) from laptop as l inner join product as pl
--on pl.model = l.model
--where p.maker = pl.maker)

--select pc.code, maker, pc.price, count(pc2.code) from pc
--inner join product on product.model = pc.model
--left join pc as pc2 on pc2.price >= pc.price
--group by pc.code, maker, pc.price
--order by pc.price
----or
--SELECT COMP.CODE, PRODUCT.MAKER, COMP.PRICE,
--       (SELECT COUNT(PC.CODE) FROM PC WHERE PC.PRICE >= COMP.PRICE)
--FROM PC AS COMP JOIN PRODUCT
--                     ON COMP.MODEL = PRODUCT.MODEL
--GROUP BY COMP.CODE, PRODUCT.MAKER, COMP.PRICE
--ORDER BY COMP.PRICE


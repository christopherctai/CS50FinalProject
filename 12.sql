SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Helena Bonham Carter") AND movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp"));

SELECT COUNT(*) title FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE name IN ("Johnny Depp", "Helena Bonham Carter");

SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name IN ("Johnny Depp", "Helena Bonham Carter"));


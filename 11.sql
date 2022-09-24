SELECT title FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Chadwick Boseman"))) ORDER BY title DESC LIMIT 5;

SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE name = "Chadwick Boseman"
ORDER by rating
DESC
LIMIT 10;
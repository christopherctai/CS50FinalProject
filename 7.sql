SELECT ratings.rating, movies.title FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010 ORDER BY rating DESC, title;
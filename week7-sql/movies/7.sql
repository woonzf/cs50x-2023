SELECT title, rating
  FROM movies
  JOIN ratings
    ON ratings.movie_id = movies.id
 WHERE year = 2010
   AND rating NOT NULL
 ORDER BY rating DESC, title;

SELECT title
  FROM movies
       INNER JOIN stars
       ON stars.movie_id = movies.id

       INNER JOIN ratings
       ON ratings.movie_id = stars.movie_id
 WHERE person_id =
       (SELECT id
          FROM people
         WHERE name = "Chadwick Boseman")
 ORDER BY rating DESC
 LIMIT 5;

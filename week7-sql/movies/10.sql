SELECT DISTINCT name
  FROM people
       INNER JOIN directors
       ON directors.person_id = people.id

       INNER JOIN movies
       ON movies.id = directors.movie_id

       INNER JOIN ratings
       ON ratings.movie_id = movies.id
 WHERE rating >= 9;

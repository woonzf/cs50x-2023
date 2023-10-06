SELECT DISTINCT name
  FROM people
  JOIN stars
    ON stars.person_id = people.id
 WHERE movie_id IN
       (SELECT id
          FROM movies
          JOIN stars
            ON stars.movie_id = movies.id
         WHERE person_id =
               (SELECT id
                  FROM people
                 WHERE name = "Kevin Bacon"
                   AND birth = 1958))
   AND name <> "Kevin Bacon";

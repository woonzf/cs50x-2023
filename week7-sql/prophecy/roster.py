from cs50 import SQL
import csv


db = SQL("sqlite:///roster.db")

with open("students.csv") as file:
    reader = csv.DictReader(file)
    for line in reader:
        db.execute(
            "INSERT INTO students (id, student_name) VALUES (?, ?)",
            line["id"],
            line["student_name"],
        )
        db.execute(
            "INSERT INTO houses (house, head) SELECT ?, ? \
                   WHERE NOT EXISTS (SELECT * FROM houses WHERE house = ?)",
            line["house"],
            line["head"],
            line["house"],
        )
        db.execute(
            "INSERT INTO assignments (student_id, house_id) VALUES (?, (SELECT id FROM houses WHERE house = ?))",
            line["id"],
            line["house"],
        )

import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for line in reader:
        state = line["state"]
        cases = int(line["cases"])

        if state not in previous_cases:
            previous_cases[state] = cases
            new_cases[state] = []
        else:
            new = cases - previous_cases[state]

            if len(new_cases[state]) == 14:
                new_cases[state].pop(0)

            new_cases[state].append(new)
            previous_cases[state] = cases

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        cases = new_cases[state][-7:]
        average = round(sum(cases) / 7)

        cases = new_cases[state][:7]
        average2 = round(sum(cases) / 7)

        try:
            percent = round((average / average2) * 100)
        except ZeroDivisionError:
            raise ZeroDivisionError

        if percent > 100:
            percent %= 100
            word = "an increase"
        else:
            percent = 100 - percent
            word = "a decrease"

        print(f"{state} had a 7-day average of {average} and {word} of {percent}%.")


main()

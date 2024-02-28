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


def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for row in reader:
        if row['state'] not in previous_cases:
            previous_cases[row['state']] = row['cases']
            # Basically saying that the state in said row is a key and the value is the number of cases in the row
            new_cases[row['state']] = []
            # We must use the value as a list, so we can get several values inside. The key is the name of the state and the value is the number of cases
        else:
            cases = int(row['cases']) - int(previous_cases[row['state']])
            # The number of new cases is the number of total cases today minus the total of yesterday.
            previous_cases[row['state']] = row['cases']
            # Updating the cases for the next iteration.
            new_cases[row['state']].append(cases)
            # Appending to the list we created in the first instance.
            if len(new_cases[row['state']]) > 14:
                # and removing if there's more than 14 members in the list. Thank God for dynamic lists.
                new_cases[row['state']].pop(0)

    return new_cases


def comparative_averages(new_cases, states):

    for state in range(len(states)):
        sd_average = sum((new_cases[states[state]][7:14])) / 7
        psd_average = sum((new_cases[states[state]][0:7])) / 7
        try:
            percentage = ((sd_average - psd_average) / psd_average) * 100
        except ZeroDivisionError:
            percentage = 0
        print(f"{states[state]} had a 7-day average of {round(sd_average)}", end="")
        if round(sd_average) > round(psd_average):
            print(f" and an increase of {percentage:.2f}%.")
        if round(sd_average) < round(psd_average):
            print(f" and a decrease of {abs(percentage):.2f}%.")
        if round(sd_average) == round(psd_average) or percentage == 0:
            print(f" while it had an average of 0 cases in the previous week.")


main()

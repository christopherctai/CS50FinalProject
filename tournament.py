# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row["rating"] = int(row["rating"])
            teams.append(row)

    # Define a dictionary counts
    counts = {
        "Uruguay": 0,
        "Portugal": 0,
        "France": 0,
        "Argentina": 0,
        "Brazil": 0,
        "Mexico": 0,
        "Belgium": 0,
        "Japan": 0,
        "Spain": 0,
        "Russia": 0,
        "Croatia": 0,
        "Denmark": 0,
        "Sweden": 0,
        "Switzerland": 0,
        "Colombia": 0,
        "England": 0,
        "Norway": 0,
        "Australia": 0,
        "Cameroon": 0,
        "United States": 0,
        "Italy": 0,
        "China PR": 0,
        "Netherlands": 0,
        "Germany": 0,
        "Nigeria": 0,
        "Canada": 0
    }


    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""

    while not len(teams) == 1:
        teams = simulate_round(teams)
        if len(teams) == 1:
            name_of_winner = teams[0]
            return name_of_winner['team']

"""
    if len(teams) == 1:
        print(teams)
        return teams

    winners = simulate_round(teams)
    simulate_tournament(winners)

"""

if __name__ == "__main__":
    main()

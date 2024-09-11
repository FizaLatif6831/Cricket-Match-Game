# Cricket Match Simulator
This project simulates a cricket match between two teams of seven players each. The simulation uses randomization for toss, player performance, and score generation. The game runs for a configurable number of overs (from a configuration.txt file) and includes functions for score calculation, player dismissal, and scoreboard display. Each batsman and bowler has unique probabilities for scoring and getting out, and the match progresses based on standard cricket rules. The second innings includes the target score and remaining overs to enhance gameplay.

Here are the key functionalities of the Cricket Match Simulator:

- **Team Setup:**
  - Two teams of seven players each.
  - Each player has attributes: runs scored, balls faced, balls bowled, runs given, and wickets taken.
  - First five players are batsmen; the last five players of Team B are bowlers.

- **Match Configuration:**
  - Number of overs is read from a `configuration.txt` file.
  - Each bowler can bowl a maximum of total overs divided by 5.

- **Toss and Batting Order:**
  - Toss is simulated randomly to decide which team bats first.
  - The batting team sends two players at a time to the field, with the striker changing based on score or end of over.

- **Bowling Order:**
  - Bowlers come from the last five players of Team B, with Player 7 starting as Bowler 1.

- **Ball Simulation:**
  - Each ball bowled is triggered by pressing `ENTER`.
  - The result of each ball is randomly generated (between -1 to 6).
    - If `-1` is generated, the batsman is out.
    - Scores 1, 3, 5 change the striker for the next ball.

- **Player Probability:**
  - Batsmen (Players 1-5) have a 10% chance of getting out and 90% chance of scoring 0-6.
  - Bowlers (Players 6-7) have a 50% chance of getting out or scoring between 0-6.

- **Scoreboard Functions:**
  - Scoreboard is drawn after each ball with updated player stats.
  - Dismissed batsman's scorecard is shown before continuing.
  - A function calculates the total team score and total wickets fallen.

- **Innings and Match Flow:**
  - First innings ends when all overs are bowled or all players are dismissed.
  - Second innings is played similarly, with the target score and remaining overs displayed.
  - Match ends when the second innings target is met or all overs are completed.

- **Interactive Gameplay:**
  - Players control ball delivery and game flow by pressing `ENTER` for each ball.

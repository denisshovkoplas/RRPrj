# Russian Roulette Game

## Game Overview

Welcome to Russian Roulette — luck-driven survival game where you and the computer face off.
Each player takes turns pulling the trigger on a revolver, trying to survive the round and reach the winning score first.

Key Features:
- Customize the revolver: select number of chambers (3-6) and bullets.
- Play against a computer opponent.
- Revolver and chamber results are drawn in ASCII art.
- Play or Quit each player's turn to manage your score.
- Scoring system:
  - Survive: +1 point
  - Hit a bullet: -1 point
  - Quit before a bullet: +2 points
  - Quit before a blank: -2 points


## Requirements

- A C++ compiler.
- Standard C++ libraries (iostream, iomanip, limits, random).


## How to Compile and Run

1. Download the Code and Compile It.

2. Run the Executable.


## How the Program Works

- You will be prompted whether you want to play the game.
- Configure the game settings:
  - Select the number of chambers (3 to 6).
  - Select the number of bullets (1 to chambers - 1).
  - Set a winning score (5 to 20).
- Gameplay proceeds with you and the computer taking turns:
  - During your turn, you can either (P)lay or (Q)uit.
  - Scoring depends on whether the chamber had a bullet or was empty.
- The game ends when either the player or computer reaches the winning score or falls below the negative winning score.


## Testing

The following aspects were tested:

- Chamber and Bullet Setup:
  - Chamber sizes tested: 3, 4, 5, 6 chambers.
  - Bullets tested from 1 up to chambers - 1.

- Player Actions:
  - Played and quit under different scenarios.
  - Verified points gained for empty chambers.
  - Verified points lost for bullet chambers.
  - Verified points change for quitting decisions.

- Winning Conditions:
  - Confirmed correct ending when winning score is achieved.
  - Confirmed correct ending when falling below negative winning score.

- Input Validation:
  - Entered invalid inputs such as characters and out-of-bound numbers.
  - Confirmed program prompts for valid entries.

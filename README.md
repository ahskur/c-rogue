# c-rogue

This project is a C implementation of the classic Rogue game, based on the tutorial series by the YouTuber BadCodingHabits.
## About

Rogue is a dungeon crawling video game developed in 1980. It is one of the earliest examples of the roguelike genre, known for its procedurally generated dungeons and permanent death mechanics. This repository contains the source code for a C implementation of Rogue, following the tutorial by badcodinghabits on YouTube.

## Features

- Procedurally generated dungeons
- Turn-based gameplay
- Permadeath mechanics
- ASCII graphics
- Classic roguelike elements

## Requirements

To build and run this project, you will need:

- A C compiler (e.g., GCC)
- The ncurses library

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/ahskur/c-rogue.git
    cd c-rogue
    ```

2. **Build the project**:
    ```sh
    gcc -o rogue main.c -lncurses
    ```

## Usage

After building the project, you can run the game with:

```sh
./rogue

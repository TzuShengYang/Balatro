# BALATRO Game

A lightweight C++ terminal-based poker game.

## Project Structure

```plaintext
├── main.cpp         # Entry point of the game
├── users.json       # JSON file for storing user credentials and data
├── README.md        # Project documentation
├── src/             # Source code directory
│   ├── Game.cpp
│   ├── GameManager.cpp
│   ├── Interface.cpp
│   ├── Item.cpp
│   ├── LoginSystem.cpp
│   └── Player.cpp
└── inc/             # Header files directory
    ├── Game.h
    ├── GameManager.h
    ├── Interface.h
    ├── InterfaceNo.h
    ├── Item.h
    ├── LoginSystem.h
    ├── Player.h
    └── json.hpp
```

## Repository

Project repository on GitHub: [https://github.com/TzuShengYang/Balatro](https://github.com/TzuShengYang/Balatro)

## Authors

* **楊子聖** 113511037
* **劉昱呈** 113511005

## Features

1. **Control Configuration**

   * Use **W**, **A**, **S**, **D**, keys to navigate and select options.
   * Press **=** (equals) as the Enter key to confirm selections.
   * Press **-** key as the backspace to delete word while sign in or sign up.
2. **Login System**

   * User authentication with **Save** and **Load** functionality.
   * Credentials and player data stored in JSON format for persistence.
3. **Currency & Inventory System**

   * Accumulate and spend in-game currency.
   * Manage items through an inventory interface.
4. **User-Friendly Configuration**

   * Straightforward configuration file for key mappings and game settings.
   * Easily customize controls and game parameters to suit your preferences.

## Compilation Instructions

Build the project using `g++` with C++11 support:

```bash
g++ -std=c++11 main.cpp src/Game.cpp src/GameManager.cpp src/Interface.cpp src/Item.cpp src/LoginSystem.cpp src/Player.cpp -o BALATRO
```

## Known Issues

* The `users.json` file **must contain at least an empty JSON object (`{}`)**.
* If the file is completely empty, the game will encounter errors during login or user data operations.

## Running the Game

After compilation, launch the game executable:

```bash
./BALATRO
```

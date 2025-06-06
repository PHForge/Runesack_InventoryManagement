
# Runesack - Inventory Management System 🎮

**Runesack** is a retro-style text-based game built in C, featuring an interactive inventory system, a shop for buying and selling items, and an adventure mode where players embark on thrilling quests. The game supports bilingual text (English and French) and persistent data storage for inventory and items.

![Language](https://img.shields.io/badge/language-C-green.svg) ![License](https://img.shields.io/badge/license-MIT-blue.svg)

<br>

## Features 📋

- **Adventure Mode**: Embark on one of 15 unique quests, such as exploring dark forests or solving riddles, earning PHGold, items, or both as rewards.
- **Shop System**: Buy and sell items from a randomized selection using PHGold as currency. Features a user-friendly interface for purchasing from a curated list or selling inventory items.
- **Multilingual Support**: Play in English or French, with all text dynamically localized for an immersive experience in either language.
- **Item Database**: Create and store custom items in `items.txt`, with detailed attributes like type (weapon, armor, etc.), rarity, state, and unique effects, enabling rich item variety.
- **Dynamic Inventory System**: Manage items with weight, value, and type constraints, ensuring inventory stays within the maximum weight limit. Persistent storage in `inventory.txt` preserves progress.
- **Interactive Menu**:
  - **Go on an Adventure**: Launch a thrilling quest from a selection of 15 randomized scenarios, earning rewards based on your journey’s outcome.
  - **Visit Shop**: Access the shop to buy from a dynamic selection of items or sell inventory items to earn PHGold.
  - **Browse Inventory**: View detailed information about your items, including name, weight, value, and attributes, alongside total inventory weight and PHGold balance.
  - **Settings**: Switch between English and French, adjust the maximum inventory weight, or create new items to add to the game’s database.
  - **Credits**: Read a heartfelt dedication to my wife and son, acknowledging their unwavering support during development.
  - **Quit**: Exit the game gracefully, saving your inventory to ensure progress is preserved for your next session.
- **Save/Load System**: Automatically saves inventory to `inventory.txt` upon quitting and loads it on startup. Custom items are saved to `items.txt` during creation, ensuring persistent game state.
- **Retro ASCII Art**: Enjoy a nostalgic interface with an ASCII art banner displayed at startup, evoking classic text-based RPGs.
- **Robust Memory Management**: Carefully designed with dynamic memory allocation and deallocation to prevent leaks and ensure stable performance.

<br>

## System Requirements ⚙️

The following components are required to build, run, or contribute to this project:

| Component          | Requirement                              | Notes                                      |
|--------------------|------------------------------------------|--------------------------------------------|
| Language | C                                      | Core language used for the project         |
| Compiler       | GCC                                      | Ensure GCC is installed (e.g., MinGW for Windows) |
| Libraries      | Standard C Libraries (stdio.h, string.h, stdlib.h, time.h, locale.h, windows.h) | Included with standard C installations      |
| IDE/Editor     | VS Code or any C-compatible IDE/terminal | Other IDEs like Code::Block or CLion can be used |
| Version Control | Git                                     | Required to clone the repository           |

> [!TIP]
> For optimal setup, install GCC via [MinGW](https://www.mingw-w64.org/) on Windows or use a package manager like `apt` or `brew` on Linux/macOS to install Git and GCC.

<br>

## Installation </>

1. **Clone the Repository**:
	```bash
	git clone https://github.com/PHForge/Runesack_InventoryManagement.git
	cd Runesack_InventoryManagement
	```

2. **Compile the Project**:
	- Windows: Use MinGW and run:
		```bash
		gcc -g -finput-charset=UTF-8 -fexec-charset=UTF-8 main.c utils.c item.c inventory.c item_db.c shop.c adventure.c -o runesack
		```
	- Linux/macOS: Ensure GCC is installed (`sudo apt install gcc` or `brew install gcc`) and run:
		```bash
		gcc -g -finput-charset=UTF-8 -fexec-charset=UTF-8 main.c utils.c item.c inventory.c item_db.c shop.c adventure.c -o runesack
		```

4. **Run the Game**:
	```bash
	./runesack
	```

<br>

## Project Structure 🗂️

```bash
Runesack_InventoryManagementSystem/
├── adventure.c		# Adventure mode logic
├── adventure.h		# Header for adventure functions
├── inventory.c		# Inventory management
├── inventory.h		# Header for inventory functions
├── item.c		# Item creation and printing
├── item.h		# Header for item & item_db functions
├── item_db.c		# Item database management
├── main.c		# Main game loop and menu
├── shop.c		# Shop system for buying/selling
├── shop.h		# Header for shop functions
├── utils.c		# Utility functions (random, localization)
├── utils.h		# Header for utility functions
├── inventory.txt	# Persistent inventory storage
├── items.txt		# Persistent item database
├── LICENSE		# MIT License
├── .gitignore		# Ignore compiled files
└── README.md		# This file
```

<br>

## License 🧾

This project is licensed under the **MIT License** - see the LICENSE file for details.

<br>

## Crédits ☕

> Developed by PHForge. 
> Feel free to reach out via [GitHub](https://github.com/PHForge) for feedback or collaboration ideas!

> Special thanks ❤️ to my wife and son for their patience and love.

<br>

## Example Output 💻

```bash

   ____ _  _ _  _ ____ ____ ____ ____ _  _
   |__/ |  | |\ | |___ [__  |__| |    |_/
   |  \ |__| | \| |___ ___] |  | |___ | \_


        by PHForge


=== Inventory Management System ===         Wallet: 250 PHGold

1. Go on an adventure
2. Visit shop
3. Browse inventory
4. Settings
5. Credits
6. Quit

Your choice:
```
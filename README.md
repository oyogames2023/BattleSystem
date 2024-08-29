
# BattleSystem Library [查看中文版本](README_zh.md)

## Introduction

The BattleSystem library is a versatile and powerful C++ library designed to facilitate the creation and management of complex game systems, particularly focusing on combat mechanics and interactive gameplay elements. It provides a robust framework that supports the integration of customizable skill, damage, and state components, making it an ideal choice for developers looking to enhance the gameplay experience.

## Features

- **Component-Based Architecture:** Utilizes a modular approach allowing for scalable and maintainable code structure.
- **Cross-Platform Compatibility:** Fully supports both Windows and Linux operating systems.
- **Dynamic Skill Management:** Includes classes for handling various types of skills and their effects within games.
- **Damage Calculation:** Sophisticated system for managing different types of damage based on various conditions.
- **State Management:** Supports applying and managing diverse states to game entities to simulate effects like buffs and debuffs.

## Getting Started

### Prerequisites

- C++17 compiler or later
- CMake 3.10 or higher

### Building the Library

Clone the repository and navigate to the project directory:

```bash
git clone https://yourrepository.com/BattleSystem.git
cd BattleSystem
```

Configure the project with CMake:

```bash
cmake -S . -B build
```

Build the project:

```bash
cmake --build build
```

### Installation

Install the library to the desired location:

```bash
cmake --install build --prefix /path/to/install
```

## Usage

Include the library in your C++ project:

```cpp
#include <BattleSystem/SkillComponent.h>
#include <BattleSystem/DamageComponent.h>
```

Create and manage components:

```cpp
auto skill = new SkillComponentBase();
skill->ActivateSkill();

auto damage = new DamageComponentBase();
int damageValue = damage->CalculateDamage();
```

## Contributing

Contributions to the BattleSystem library are welcome. Please feel free to fork the repository, make your changes, and submit a pull request.

## License

The BattleSystem library is licensed under the MIT License. See the `LICENSE` file in the repository for more details.

---

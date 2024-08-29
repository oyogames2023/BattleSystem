
# BattleSystem 库 - [English](README.md)

## 介绍

BattleSystem 库是一个多功能强大的 C++ 库，专为游戏系统的创建和管理而设计，特别强调战斗机制和交互式游戏元素。它提供了一个健壮的框架，支持自定义技能、伤害和状态组件的集成，非常适合希望提升游戏玩家体验的开发者。

## 特点

- **组件化架构：** 采用模块化方法，实现可扩展和可维护的代码结构。
- **跨平台兼容性：** 完全支持 Windows 和 Linux 操作系统。
- **动态技能管理：** 包括处理游戏中各种技能及其效果的类。
- **伤害计算：** 管理基于不同条件的各种伤害类型的复杂系统。
- **状态管理：** 支持对游戏实体应用和管理多种状态，模拟增益和减益效果。

## 入门指南

### 前提条件

- C++17 编译器或更高版本
- CMake 3.10 或更高版本

### 构建库

克隆仓库并导航至项目目录：

```bash
git clone https://yourrepository.com/BattleSystem.git
cd BattleSystem
```

使用 CMake 配置项目：

```bash
cmake -S . -B build
```

构建项目：

```bash
cmake --build build
```

### 安装

将库安装到所需位置：

```bash
cmake --install build --prefix /path/to/install
```

## 使用

在 C++ 项目中包含库：

```cpp
#include <BattleSystem/SkillComponent.h>
#include <BattleSystem/DamageComponent.h>
```

创建和管理组件：

```cpp
auto skill = new SkillComponentBase();
skill->ActivateSkill();

auto damage = new DamageComponentBase();
int damageValue = damage->CalculateDamage();
```

## 贡献

欢迎为 BattleSystem 库做出贡献。请随时 Fork 仓库，进行更改，并提交 Pull Request。

## 许可证

BattleSystem 库在 MIT 许可证下授权。有关更多细节，请查看仓库中的 `LICENSE` 文件。

---

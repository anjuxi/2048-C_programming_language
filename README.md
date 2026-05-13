# 2048 游戏 - EGE 图形界面版本

一个使用 EGE (Easy Graphics Engine) 图形库开发的经典 2048 游戏。

## 游戏特性

- 🎨 **图形化界面**：精美的彩色方块设计
- ⌨️ **流畅操作**：支持键盘方向键控制
- 🏆 **计分系统**：实时显示游戏分数
- 🎯 **胜利/失败检测**：达到 2048 获胜，无法移动时游戏结束
- 🔄 **重新开始**：按 R 键随时重新开始

## 编译运行

### 环境要求

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://isocpp.org/)
[![MinGW](https://img.shields.io/badge/MinGW-64%20bit-green.svg)](http://www.mingw-w64.org/)
[![EGE](https://img.shields.io/badge/EGE-20.08%2B-orange.svg)](https://xege.org/)

### 编译命令

```bash
g++ 2048.cpp -o 2048.exe -ID:\mingw64\include -LD:\mingw64\lib -lgraphics -lgdi32 -lgdiplus -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
```

### 运行

```bash
./2048.exe
```

## 操作说明

| 按键 | 功能         |
| ---- | ------------ |
| ↑    | 向上移动     |
| ↓    | 向下移动     |
| ←    | 向左移动     |
| →    | 向右移动     |
| R    | 重新开始游戏 |

## 游戏规则

1. 游戏在 4x4 的网格上进行
2. 使用方向键移动方块
3. 相同数字的方块碰撞时会合并成它们的和
4. 每次移动后会在空白位置随机生成一个 2 或 4
5. 达到 2048 即为胜利
6. 无法移动且没有空格时游戏结束

## 技术实现

- **语言**：C++11
- **图形库**：EGE (Easy Graphics Engine)
- **编译器**：MinGW-w64
- **平台**：Windows

## 作者信息

**谙弆悕博士（Ailan Anjuxi）**

- 📧 邮箱：anjuxi.ME@outlook.com
- 📞 SIP 电话：sip:anjuxi@sip.linphone.org


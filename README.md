# 挑战2048 - 控制台版

## 简介
这是一款基于C语言开发的经典2048数字合并游戏，运行于Windows控制台环境。通过方向键操作数字方块，体验策略与运气的碰撞，挑战合成2048的终极目标！

## 功能特性
- 🕹️ 经典4x4棋盘布局
- 🎯 实时分数统计与步数记录
- ⏱️ 游戏计时功能
- 🎨 彩色数字显示（不同数字不同颜色）
- 🏆 胜利/失败条件判断
- 🔄 支持重新开始游戏
- 📋 内置游戏规则说明

## 运行环境
- 操作系统：Windows
- 编译依赖：`gcc`编译器（需支持C99标准）

## 编译与运行
1. 克隆仓库或下载源代码
git clone https://github.com/yourusername/2048-console-game.git
2. 使用gcc编译（需添加`-lwinmm`链接Windows库）
gcc main.c -o 2048.exe -Wall -lwinmm
3. 运行游戏
./2048.exe

## 游戏操作
| 按键          | 功能               |
|---------------|--------------------|
| ↑ ↓ ← →       | 移动数字方块       |
| ESC           | 退出游戏           |
| 1/2/3/4       | 主菜单选项选择     |

## 游戏规则
1. 每次移动会在空白处随机生成2或4
2. 相同数字的方块碰撞时会合并为它们的和
3. 合并后的数字将累计到游戏得分
4. 当棋盘被填满且无法合并时游戏失败
5. 成功合成2048方块即获得胜利

## 代码结构

├── main.c                 # 主程序入口
├── 核心功能
│   ├── 界面绘制          # draw_game_box()
│   ├── 数字合并逻辑      # add()
│   ├── 移动判断          # if_up()/if_down()等
│   └── 游戏状态检测      # game_win()/game_faile()
└── 辅助模块
    ├── 颜色管理          # text_colors()
    ├── 光标控制          # gotoxy()
    └── 菜单系统          # choice()

## 已知限制
- 仅支持Windows系统运行
- 依赖控制台窗口尺寸（建议使用标准CMD窗口）

## 许可证
[MIT License](LICENSE) © 2023 [Your Name]

> 提示：游戏过程中按ESC可随时退出，成功合成大数字时会有彩色惊喜哦！🎉 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>          //标准输入输出函数库
#include <conio.h>          //控制台输入输出函数库
#include <Windows.h>        //Windows API函数库 设置CMD控制台窗口
#include <math.h>           //引入数学函数库

int step = 0;
int score = 0;
long int game_time;
int box[4][4] = { 0 };
HANDLE hout;                //控制台句柄

/***************函  数  声  明***********/
void gotoxy(int x, int y);  //将屏幕光标移动到指定位置
int color(int c);           //设置文本颜色
int text_colors(int number);//根据数字修改颜色
void draw_game_box(void);   //绘制游戏界面
void add(int item[], int result[]);       //合并数字
int if_move(int item[]);    //判断数组中的数字是否可以进行移动操作
                            //若可以移动，返回1；否则返回0

void game_play(void);       //开始游戏
void replay(void);          //重新开始
int if_2_n(int x);          //判断一个数是否为2的n次方

int if_up(void);            //判断是否可以向上移动，若可以（方格中的数相加是2^n），则返回1；否则返回0
int if_down(void);          //判断是否可以向下移动，若可以（方格中的数相加是2^n），则返回1；否则返回0
int if_left(void);          //判断是否可以向左移动，若可以（方格中的数相加是2^n），则返回1；否则返回0
int if_right(void);         //判断是否可以向右移动，若可以（方格中的数相加是2^n），则返回1；否则返回0
int box_max(void);          //返回棋盘中最大的数
int game_faile(void);       //判断游戏是否失败
int game_win(void);         //判断游戏是否胜利
int key_control(int key);      //根据按键输入控制数字的移动
void close(void);           //关闭游戏
void title(void);           //绘制标题
void choice(void);          //选择框
void regulation(void);      //游戏规则介绍
void explanation(void);     //游戏操作说明
void close_manu(void);

/**
  * 设置标题
  */
void title(void)
{
    color(11);                      //淡浅绿色
    gotoxy(10, 1);                  //输出2048字符画
    printf("#######   #######   ##   ##   #######");
    gotoxy(10, 2);
    printf("     ##   ##   ##   ##   ##   ##   ##");
    gotoxy(10, 3);
    printf("#######   ##   ##   ##   ##   #######");
    gotoxy(10, 4);
    printf("##        ##   ##   #######   ##   ##");
    gotoxy(10, 5);
    printf("#######   #######        ##   #######");
}

/**
  * 设置文字颜色
  */
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//定位光标位置
    return 0;
}

/**
  * 设置屏幕光标位置
  */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/**
  * 菜单选项
  */
void choice(void)
{
    system("title 挑战2048");
    title();            //打印标题
    int n;
    int i, j = 1;
    gotoxy(22, 7);
    color(13);
    printf("挑 战 2 0 4 8");
    color(14);                          //黄色边框
    for (i = 8; i <= 22; i++)           //输出上下边框==
    {
        for (j = 0; j <= 55; j++)      //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 8 || i == 22)
            {
                printf("=");
            }
            else if (j == 0 || j == 54)
            {
                printf("||");
            }
        }
    }
    color(12);
    gotoxy(12, 12);
    printf("1. 开始游戏");
    gotoxy(33, 12);
    printf("2. 游戏规则");
    gotoxy(12, 15);
    printf("3. 按键说明");
    gotoxy(33, 15);
    printf("4. 退出游戏");
    gotoxy(12, 18);
    color(5);
    printf("请选择[1 2 3 4]:[ ]\b\b");      //输入选项
    scanf("%d", &n);

    switch (n)
    {
        case 1:
            game_play();                      //游戏开始函数
            break;
        case 2:
            regulation();                     //游戏规则函数
            break;
        case 3:
            explanation();                    //按键说明函数
            break;
        case 4:
            close_manu();                          //关闭游戏函数
            break;
    }
}


/**
  * 绘制游戏界面  4*4的网格
  * 
  */
void draw_game_box(void)
{
    title();            //打印标题
    int i, j, k;
    gotoxy(6, 7);                      //屏幕坐标位置
    color(12);                          //淡浅绿色
    printf("游戏分数：%ld", score);
    color(13);                          //粉色
    gotoxy(39, 7);                      //屏幕坐标位置
    printf("执行步数：%d\n", step);
    color(14);                          //黄色
    for (j = 8; j < 33; j += 5)         //打印棋盘方格
    {
        gotoxy(7, j);
        for (k = 1; k < 44; k++)
        {
            printf("-");
        }
        printf("\n");
    }
    for(i=9;i<13;i++)
    {
        gotoxy(8, i);
        printf("|         |         |         |         |");
    }
    for (i = 14; i < 18; i++)
    {
        gotoxy(8, i);
        printf("|         |         |         |         |");
    }
    for (i = 19; i < 23; i++)
    {
        gotoxy(8, i);
        printf("|         |         |         |         |");
    }
    for (i = 24; i < 28; i++)
    {
        gotoxy(8, i);
        printf("|         |         |         |         |");
    }
    gotoxy(22, 7);
    color(10);                                          //绿色
    printf("已用时：%ld 秒", time(NULL) - game_time);     //输出游戏运行时间
}

/**
  * 根据数字修改颜色
  * 
  */
int text_colors(int number)
{
    switch(number)                       //格子中出现的数字 (2^n) (0<n<12) 显示为不同的颜色
    {
        case 2:
            return color(12);           //红色
            break;
        case 4:
            return color(11);           //亮蓝色
            break;
        case 8:
            return color(13);           //粉色
            break;
        case 16:
            return color(10);           //绿色
            break;
        case 32:
            return color(14);           //黄色
            break;
        case 64:
            return color(6);           //白色
            break;
        case 128:
            return color(5);            //淡蓝色
            break;
        case 256:
            return color(8);            //灰色
            break;
        case 512:
            return color(3);            //淡灰色
            break;
        case 1024:
            return color(9);            //淡黄色
            break;
        case 2048:
            return color(7);            //淡紫色
            break;
    }
    return 0;
}

/**
  * 合并相同数字
  */
void add(int item[], int result[])
{
    int i = 0, j = 0;
    int temp1[4] = { 0 };

    // 第一步：压缩非零元素
    for (i = 0; i < 4; i++) {
        if (item[i] != 0) {
            temp1[j++] = item[i];
        }
    }

    // 第二步：合并相邻相同元素
    for (i = 0; i < 3; i++) {
        if (temp1[i] == temp1[i + 1] && temp1[i] != 0) {
            temp1[i] *= 2;
            score += temp1[i];  // 更新分数
            temp1[i + 1] = 0;
        }
    }

    // 第三步：再次压缩到result数组
    j = 0;
    memset(result, 0, sizeof(int) * 4); // 清空结果数组
    for (i = 0; i < 4; i++) {
        if (temp1[i] != 0) {
            result[j++] = temp1[i];
        }
    }
}

/**
  * 判断数字是否可以移动。返回 1 表示可以移动，返回 0 表示不能移动
  */
int if_move(int item[])
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (item[i] != 0 && item[i] == item[i + 1])//如果两个相邻位上数字相同，能移动，返回1
        {
            return 1;
        }
        if (item[i] == 0 && item[i + 1] != 0)
        {
            return 1;
        }
    }
    return 0;
}


/**
  * 键盘控制移动
  */
  /**
   * 键盘控制移动
   */
int key_control(int key)
{
    int i, j;
    switch (key)
    {
    case 72: // 上移
        j = 0;
        for (int col = 0; col < 4; col++)
        {
            int tp[4] = { box[0][col], box[1][col], box[2][col], box[3][col] };
            int result[4];
            add(tp, result);

            // 判断是否可移动
            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // 更新数据
            box[0][col] = result[0];
            box[1][col] = result[1];
            box[2][col] = result[2];
            box[3][col] = result[3];
        }
        return j != 4;

    case 80: // 下移
        j = 0;
        for (int col = 0; col < 4; col++)
        {
            int tp[4] = { box[3][col], box[2][col], box[1][col], box[0][col] };
            int result[4];
            add(tp, result);

            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // 注意顺序反转
            box[3][col] = result[0];
            box[2][col] = result[1];
            box[1][col] = result[2];
            box[0][col] = result[3];
        }
        return j != 4;

    case 75: // 左移
        j = 0;
        for (int row = 0; row < 4; row++)
        {
            int tp[4] = { box[row][0], box[row][1], box[row][2], box[row][3] };
            int result[4];
            add(tp, result);

            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            box[row][0] = result[0];
            box[row][1] = result[1];
            box[row][2] = result[2];
            box[row][3] = result[3];
        }
        return j != 4;

    case 77: // 右移
        j = 0;
        for (int row = 0; row < 4; row++)
        {
            int tp[4] = { box[row][3], box[row][2], box[row][1], box[row][0] };
            int result[4];
            add(tp, result);

            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // 注意顺序反转
            box[row][3] = result[0];
            box[row][2] = result[1];
            box[row][1] = result[2];
            box[row][0] = result[3];
        }
        return j != 4;
        case 27:	//按ESC
            gotoxy(20, 23);
            color(12);
            printf("确定退出游戏吗? (y/n)");
            char c = getch();           //获得键盘输入
            if (c == 'y' || c == 'Y')     //如果输入的是大写或者小写的y
            {
                exit(0);                //退出游戏
            }
            if (c == 'n' || c == 'N')      //如果输入的是大写或者小写的n
            {
                gotoxy(20, 23);
                printf("                        ");   //继续游戏
            }
            break;
        default:
            return 0;
    }
}

/**
  *判断是否胜利
  */
int game_win(void)
{
    int flag=0;
    if (box_max() == 0)
    {
        system("cls");
        title();            //打印标题
        gotoxy(1, 7);
        color(2);
        //输出胜利信息
        printf("##       ##       ##   #####    ##        ##     ####\n");
        gotoxy(1, 8);
        printf(" ##     ####     ##     ##      ## ##     ##      ##\n");
        gotoxy(1, 9);
        printf("  ##   ##  ##   ##      ##      ##   ##   ##      #\n");
        gotoxy(1, 10);
        printf("   ## ##    ## ##       ##      ##     ## ##       \n");
        gotoxy(1, 11);
        printf("    ###      ###      #####     ##       ###     ##\n");
        gotoxy(18, 14);
        color(12);
        printf("胜利啦，你真棒！！！");
        flag = 1;
    }
    return flag;// flag 的值正常是 0 ，返回 1 表示游戏胜利
}

/**
  * 返回棋盘中的最大数
  * 
  */
int box_max(void)
{
    int max = box[0][0];
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (box[i][j] > max)
            {
                max = box[i][j];
            }
        }
    }
    return max;
}

/**
  *判断游戏是否失败
  */
int game_faile(void)
{
    int flag = 0;
    int max;
    // 当上下左右都不能移动时，游戏失败
    if ((if_up() + if_down() + if_left() + if_right()) == 0)
    {
        system("cls");
        gotoxy(15, 2);
        color(14);
        printf("合并出的最大数为：");
        gotoxy(15, 4);
        color(13);
        printf("无法移动，游戏失败！");//输出失败信息
        gotoxy(30, 2);
        color(11);
        max = box_max();
        printf("%d", max);
        gotoxy(2, 6);
        color(4);
        printf("###########  ##          ##  ##  ##           ###\n");//画出 “END!” 字符
        gotoxy(2, 7);
        printf("##           ## ##       ##  ##     ##        ##  \n");
        gotoxy(2, 8);
        printf("##           ##   ##     ##  ##         ##    ##\n");
        gotoxy(2, 9);
        printf("##########   ##     ##   ##  ##          ##   #\n");
        gotoxy(2, 10);
        printf("##           ##      ##  ##  ##         ##    \n");
        gotoxy(2, 11);
        printf("##           ##       ## ##  ##      ##       \n");
        gotoxy(2, 12); 
        printf("###########  ##          ##  ##  ##         ####\n");
        flag = 1;
    }
    return flag;// flag 的值正确是0，返回 1 表示游戏失败
}


/**
  * 判断是否可以向上移动。若可以（方格中的数相加是2^n），则返回1；否则返回0
  */
int if_up(void)
{
    int i, j;
    int flag = 0;
    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 3; i++)
        {
            //如果上下两个格子的数字相加是2^n，并且下面的格子中有数
            if ((if_2_n(box[i][j] + box[i + 1][j]) ==1) && box[i+1][j])
            {
                flag = 1;//可以上移
            }
        }
    }
    return flag;
}

/**
  * 判断是否可以向下移动。若可以（方格中的数相加是2^n），则返回1；否则返回0
  */
int if_down(void)
{
    int i, j;
    int flag = 0;
    for (j = 0; j < 4; j++)
    {
        for (i = 3; i > 0; i--)
        {
            //如果上下两个格子的数字相加是2^n，并且上面的格子中有数
            if ((if_2_n(box[i][j] + box[i - 1][j]) == 1) && box[i-1][j])
            {
                flag = 1;//可以下移
            }
        }
    }
    return flag;
}

/**
  * 判断是否可以向左移动。若可以（方格中的数相加是2^n），则返回1；否则返回0
  */
int if_left(void)
{
    int i, j;
    int flag = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            //如果左右两个格子的数字相加是2^n，并且右边的格子中有数
            if ((if_2_n(box[i][j] + box[i][j + 1]) == 1) && box[i][j + 1])
            {
                flag = 1;//可以左移
            }
        }
    }
    return flag;
}

/**
  * 判断是否可以向右移动。若可以（方格中的数相加是2^n），则返回1；否则返回0
  */
int if_right(void)
{
    int i, j;
    int flag = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 3; j > 0; j--)
        {
            //如果左右两个格子的数字相加是2^n，并且左边的格子中有数
            if ((if_2_n(box[i][j] + box[i][j - 1]) == 1) && box[i][j - 1])
            {
                flag = 1;//可以右移
            }
        }
    }
    return flag;
}

/**
  * 判断一个数是否为 2 的 n 次方
  */
int if_2_n(int x)
{
    int flag = 0;
    int n1 = 0;
    int n2 = 1;
    for (n1 = 1; n1 <= 11; n1++)
    {
        if (x == pow(2, n1))
        {
            flag = 1;
            if (n1 > n2)
            {
                n2 = n1;
            }
            return flag;
        }
    }
    return flag;
}

/**
  * 开始游戏
  */
void game_play(void)
{
    system("cls");//清屏
    int i = 0, j = 0;
    game_time = time(NULL);
    draw_game_box();
    int a, b;
    srand(time(NULL));
    do
    {
        a = rand() % 4;
        b = rand() % 4;
    } while (box[a][b] != 0);

    if (rand() % 4 == 0)
    {
        box[a][b] = 4;
    }
    else
    {
        box[a][b] = 2;
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (box[i][j] == 0)
            {
                continue;
            }
            gotoxy(13 + j * 10, 10 + i * 5);
            int c = box[i][j];
            text_colors(c);
            printf("%d", c);
        }
    }
    while (1)
    {
        // kbhit() 检查当前是否有键盘输入。如果有则返回为 1 ，否则返回 0 
        while (kbhit())
        {
            // 如果按下的按键不是在 key_control() 函数中定义的，会没有反应，直到按下定义的按键
            if (!key_control(getch()))
            {
                continue;
            }
            draw_game_box();
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    if (box[i][j] == 0)
                    {
                        continue;
                    }
                    gotoxy(13 + j * 10, 10 + i * 5);// 合并后的数出现的位置
                    int c = box[i][j];
                    text_colors(c);
                    printf("%d", c);
                }
            }

            do
            {
                a = rand() % 4;
                b = rand() % 4;
            } while (box[a][b] != 0);

            if (rand() % 4 == 0)
            {
                box[a][b] = 4;
            }
            else
            {
                box[a][b] = 2;
            }

            step++;
            gotoxy(13 + b * 10, 10 + a * 5);
            int c = box[a][b];
            text_colors(c);
            printf("%d", c);
        }

        // 只要 game_faile 或者 game_win() 任意一个函数返回 1 ，也就是成功或者失败都会出现下面的内容
        if (game_faile() + game_win() != 0)
        {
            int n;
            gotoxy(100, 120);
            color(12);
            printf("我还要重新玩一局-------1");
            gotoxy(120, 140);
            printf("\n我不想玩了，退出吧------2\n");
            gotoxy(140, 160);
            color(11);
            scanf("%d", &n);
            switch (n)
            {
            case 1:
                replay();
                break;
            case 2:
                close();
                break;
            }
        }
    }
}

/**
  * 重新游戏
  * 
  */
void replay(void)
{
    system("cls");
    score = 0;
    step = 0;
    memset(box, 0, 16 * sizeof(int));
    game_play();
}

/**
  * 退出函数
  * 
  */
void close(void)
{
    exit(0);
}

/**
  * 退出函数
  *
  */
void close_manu(void)
{
    gotoxy(10, 18);
    color(4);
    printf("这么好玩的游戏确定退出吗? ^_^ (y/n)");
    char c = getch();           //获得键盘输入
    if (c == 'y' || c == 'Y')     //如果输入的是大写或者小写的y
    {
        exit(0);                //退出游戏
    }
    if (c == 'n' || c == 'N')      //如果输入的是大写或者小写的n
    {
        system("cls");
        choice();
    }
}

/**
  * 游戏界面介绍
  * 
  */
void regulation()
{
    int i, j = 1;
    system("cls");
    color(13);
    gotoxy(25, 1);
    printf("游戏规则");
    color(2);
    for (i = 3; i <= 15; i++)
    {
        for (j = 0; j <= 54; j++)
        {
            gotoxy(j, i);
            if (i == 3 || i == 15)
            {
                printf("=");
            }
            else if (j == 0 || j == 54)
            {
                printf("||");
            }
        }
    }
    color(3);
    gotoxy(3, 4);
    printf(" tip1: 玩家可以通过 ↑  ↓  ←  → 方向键移动方块");
    color(10);
    gotoxy(3, 6);
    printf(" tip2: 按ESC键退出游戏");
    color(14);
    gotoxy(3, 8);
    printf(" tip3: 玩家选择的方向上，若有相同数字则合并");
    color(11);
    gotoxy(3, 10);
    printf(" tip4: 每移动一步，空位随机出现一个 2 或者 4 ");
    color(14);
    gotoxy(3, 12);
    printf(" tip5: 棋盘被数字填满，无法进行有效移动，游戏失败");
    color(5);
    gotoxy(3, 14);
    printf(" tip6: 棋盘上出现 2048 ，游戏胜利");
    getch();
    system("cls");
    main();
}

/**
  * 按键说明
  * 
  */
void explanation(void)
{
    gotoxy(10, 18);
    color(3);
    printf(" 通过 ↑ ↓ ← → 键进行操作 ");
    gotoxy(31, 18);
    printf(" ESC键退出游戏");
    getch();
    system("cls");
    main();
}


/**
* 主函数。程序入口
*/
int main()
{
    /*game_win();*/
    /*game_faile();*/
    //draw_game_box();
    choice();           //菜单选项
    /*getch();*/
    return 0;
}



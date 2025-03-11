#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>          //��׼�������������
#include <conio.h>          //����̨�������������
#include <Windows.h>        //Windows API������ ����CMD����̨����
#include <math.h>           //������ѧ������

int step = 0;
int score = 0;
long int game_time;
int box[4][4] = { 0 };
HANDLE hout;                //����̨���

/***************��  ��  ��  ��***********/
void gotoxy(int x, int y);  //����Ļ����ƶ���ָ��λ��
int color(int c);           //�����ı���ɫ
int text_colors(int number);//���������޸���ɫ
void draw_game_box(void);   //������Ϸ����
void add(int item[], int result[]);       //�ϲ�����
int if_move(int item[]);    //�ж������е������Ƿ���Խ����ƶ�����
                            //�������ƶ�������1�����򷵻�0

void game_play(void);       //��ʼ��Ϸ
void replay(void);          //���¿�ʼ
int if_2_n(int x);          //�ж�һ�����Ƿ�Ϊ2��n�η�

int if_up(void);            //�ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
int if_down(void);          //�ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
int if_left(void);          //�ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
int if_right(void);         //�ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
int box_max(void);          //����������������
int game_faile(void);       //�ж���Ϸ�Ƿ�ʧ��
int game_win(void);         //�ж���Ϸ�Ƿ�ʤ��
int key_control(int key);      //���ݰ�������������ֵ��ƶ�
void close(void);           //�ر���Ϸ
void title(void);           //���Ʊ���
void choice(void);          //ѡ���
void regulation(void);      //��Ϸ�������
void explanation(void);     //��Ϸ����˵��
void close_manu(void);

/**
  * ���ñ���
  */
void title(void)
{
    color(11);                      //��ǳ��ɫ
    gotoxy(10, 1);                  //���2048�ַ���
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
  * ����������ɫ
  */
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//��λ���λ��
    return 0;
}

/**
  * ������Ļ���λ��
  */
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/**
  * �˵�ѡ��
  */
void choice(void)
{
    system("title ��ս2048");
    title();            //��ӡ����
    int n;
    int i, j = 1;
    gotoxy(22, 7);
    color(13);
    printf("�� ս 2 0 4 8");
    color(14);                          //��ɫ�߿�
    for (i = 8; i <= 22; i++)           //������±߿�==
    {
        for (j = 0; j <= 55; j++)      //������ұ߿�||
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
    printf("1. ��ʼ��Ϸ");
    gotoxy(33, 12);
    printf("2. ��Ϸ����");
    gotoxy(12, 15);
    printf("3. ����˵��");
    gotoxy(33, 15);
    printf("4. �˳���Ϸ");
    gotoxy(12, 18);
    color(5);
    printf("��ѡ��[1 2 3 4]:[ ]\b\b");      //����ѡ��
    scanf("%d", &n);

    switch (n)
    {
        case 1:
            game_play();                      //��Ϸ��ʼ����
            break;
        case 2:
            regulation();                     //��Ϸ������
            break;
        case 3:
            explanation();                    //����˵������
            break;
        case 4:
            close_manu();                          //�ر���Ϸ����
            break;
    }
}


/**
  * ������Ϸ����  4*4������
  * 
  */
void draw_game_box(void)
{
    title();            //��ӡ����
    int i, j, k;
    gotoxy(6, 7);                      //��Ļ����λ��
    color(12);                          //��ǳ��ɫ
    printf("��Ϸ������%ld", score);
    color(13);                          //��ɫ
    gotoxy(39, 7);                      //��Ļ����λ��
    printf("ִ�в�����%d\n", step);
    color(14);                          //��ɫ
    for (j = 8; j < 33; j += 5)         //��ӡ���̷���
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
    color(10);                                          //��ɫ
    printf("����ʱ��%ld ��", time(NULL) - game_time);     //�����Ϸ����ʱ��
}

/**
  * ���������޸���ɫ
  * 
  */
int text_colors(int number)
{
    switch(number)                       //�����г��ֵ����� (2^n) (0<n<12) ��ʾΪ��ͬ����ɫ
    {
        case 2:
            return color(12);           //��ɫ
            break;
        case 4:
            return color(11);           //����ɫ
            break;
        case 8:
            return color(13);           //��ɫ
            break;
        case 16:
            return color(10);           //��ɫ
            break;
        case 32:
            return color(14);           //��ɫ
            break;
        case 64:
            return color(6);           //��ɫ
            break;
        case 128:
            return color(5);            //����ɫ
            break;
        case 256:
            return color(8);            //��ɫ
            break;
        case 512:
            return color(3);            //����ɫ
            break;
        case 1024:
            return color(9);            //����ɫ
            break;
        case 2048:
            return color(7);            //����ɫ
            break;
    }
    return 0;
}

/**
  * �ϲ���ͬ����
  */
void add(int item[], int result[])
{
    int i = 0, j = 0;
    int temp1[4] = { 0 };

    // ��һ����ѹ������Ԫ��
    for (i = 0; i < 4; i++) {
        if (item[i] != 0) {
            temp1[j++] = item[i];
        }
    }

    // �ڶ������ϲ�������ͬԪ��
    for (i = 0; i < 3; i++) {
        if (temp1[i] == temp1[i + 1] && temp1[i] != 0) {
            temp1[i] *= 2;
            score += temp1[i];  // ���·���
            temp1[i + 1] = 0;
        }
    }

    // ���������ٴ�ѹ����result����
    j = 0;
    memset(result, 0, sizeof(int) * 4); // ��ս������
    for (i = 0; i < 4; i++) {
        if (temp1[i] != 0) {
            result[j++] = temp1[i];
        }
    }
}

/**
  * �ж������Ƿ�����ƶ������� 1 ��ʾ�����ƶ������� 0 ��ʾ�����ƶ�
  */
int if_move(int item[])
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (item[i] != 0 && item[i] == item[i + 1])//�����������λ��������ͬ�����ƶ�������1
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
  * ���̿����ƶ�
  */
  /**
   * ���̿����ƶ�
   */
int key_control(int key)
{
    int i, j;
    switch (key)
    {
    case 72: // ����
        j = 0;
        for (int col = 0; col < 4; col++)
        {
            int tp[4] = { box[0][col], box[1][col], box[2][col], box[3][col] };
            int result[4];
            add(tp, result);

            // �ж��Ƿ���ƶ�
            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // ��������
            box[0][col] = result[0];
            box[1][col] = result[1];
            box[2][col] = result[2];
            box[3][col] = result[3];
        }
        return j != 4;

    case 80: // ����
        j = 0;
        for (int col = 0; col < 4; col++)
        {
            int tp[4] = { box[3][col], box[2][col], box[1][col], box[0][col] };
            int result[4];
            add(tp, result);

            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // ע��˳��ת
            box[3][col] = result[0];
            box[2][col] = result[1];
            box[1][col] = result[2];
            box[0][col] = result[3];
        }
        return j != 4;

    case 75: // ����
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

    case 77: // ����
        j = 0;
        for (int row = 0; row < 4; row++)
        {
            int tp[4] = { box[row][3], box[row][2], box[row][1], box[row][0] };
            int result[4];
            add(tp, result);

            if (memcmp(tp, result, sizeof(tp)) == 0) j++;

            // ע��˳��ת
            box[row][3] = result[0];
            box[row][2] = result[1];
            box[row][1] = result[2];
            box[row][0] = result[3];
        }
        return j != 4;
        case 27:	//��ESC
            gotoxy(20, 23);
            color(12);
            printf("ȷ���˳���Ϸ��? (y/n)");
            char c = getch();           //��ü�������
            if (c == 'y' || c == 'Y')     //���������Ǵ�д����Сд��y
            {
                exit(0);                //�˳���Ϸ
            }
            if (c == 'n' || c == 'N')      //���������Ǵ�д����Сд��n
            {
                gotoxy(20, 23);
                printf("                        ");   //������Ϸ
            }
            break;
        default:
            return 0;
    }
}

/**
  *�ж��Ƿ�ʤ��
  */
int game_win(void)
{
    int flag=0;
    if (box_max() == 0)
    {
        system("cls");
        title();            //��ӡ����
        gotoxy(1, 7);
        color(2);
        //���ʤ����Ϣ
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
        printf("ʤ�����������������");
        flag = 1;
    }
    return flag;// flag ��ֵ������ 0 ������ 1 ��ʾ��Ϸʤ��
}

/**
  * ���������е������
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
  *�ж���Ϸ�Ƿ�ʧ��
  */
int game_faile(void)
{
    int flag = 0;
    int max;
    // ���������Ҷ������ƶ�ʱ����Ϸʧ��
    if ((if_up() + if_down() + if_left() + if_right()) == 0)
    {
        system("cls");
        gotoxy(15, 2);
        color(14);
        printf("�ϲ����������Ϊ��");
        gotoxy(15, 4);
        color(13);
        printf("�޷��ƶ�����Ϸʧ�ܣ�");//���ʧ����Ϣ
        gotoxy(30, 2);
        color(11);
        max = box_max();
        printf("%d", max);
        gotoxy(2, 6);
        color(4);
        printf("###########  ##          ##  ##  ##           ###\n");//���� ��END!�� �ַ�
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
    return flag;// flag ��ֵ��ȷ��0������ 1 ��ʾ��Ϸʧ��
}


/**
  * �ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
  */
int if_up(void)
{
    int i, j;
    int flag = 0;
    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 3; i++)
        {
            //��������������ӵ����������2^n����������ĸ���������
            if ((if_2_n(box[i][j] + box[i + 1][j]) ==1) && box[i+1][j])
            {
                flag = 1;//��������
            }
        }
    }
    return flag;
}

/**
  * �ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
  */
int if_down(void)
{
    int i, j;
    int flag = 0;
    for (j = 0; j < 4; j++)
    {
        for (i = 3; i > 0; i--)
        {
            //��������������ӵ����������2^n����������ĸ���������
            if ((if_2_n(box[i][j] + box[i - 1][j]) == 1) && box[i-1][j])
            {
                flag = 1;//��������
            }
        }
    }
    return flag;
}

/**
  * �ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
  */
int if_left(void)
{
    int i, j;
    int flag = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            //��������������ӵ����������2^n�������ұߵĸ���������
            if ((if_2_n(box[i][j] + box[i][j + 1]) == 1) && box[i][j + 1])
            {
                flag = 1;//��������
            }
        }
    }
    return flag;
}

/**
  * �ж��Ƿ���������ƶ��������ԣ������е��������2^n�����򷵻�1�����򷵻�0
  */
int if_right(void)
{
    int i, j;
    int flag = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 3; j > 0; j--)
        {
            //��������������ӵ����������2^n��������ߵĸ���������
            if ((if_2_n(box[i][j] + box[i][j - 1]) == 1) && box[i][j - 1])
            {
                flag = 1;//��������
            }
        }
    }
    return flag;
}

/**
  * �ж�һ�����Ƿ�Ϊ 2 �� n �η�
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
  * ��ʼ��Ϸ
  */
void game_play(void)
{
    system("cls");//����
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
        // kbhit() ��鵱ǰ�Ƿ��м������롣������򷵻�Ϊ 1 �����򷵻� 0 
        while (kbhit())
        {
            // ������µİ��������� key_control() �����ж���ģ���û�з�Ӧ��ֱ�����¶���İ���
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
                    gotoxy(13 + j * 10, 10 + i * 5);// �ϲ���������ֵ�λ��
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

        // ֻҪ game_faile ���� game_win() ����һ���������� 1 ��Ҳ���ǳɹ�����ʧ�ܶ���������������
        if (game_faile() + game_win() != 0)
        {
            int n;
            gotoxy(100, 120);
            color(12);
            printf("�һ�Ҫ������һ��-------1");
            gotoxy(120, 140);
            printf("\n�Ҳ������ˣ��˳���------2\n");
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
  * ������Ϸ
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
  * �˳�����
  * 
  */
void close(void)
{
    exit(0);
}

/**
  * �˳�����
  *
  */
void close_manu(void)
{
    gotoxy(10, 18);
    color(4);
    printf("��ô�������Ϸȷ���˳���? ^_^ (y/n)");
    char c = getch();           //��ü�������
    if (c == 'y' || c == 'Y')     //���������Ǵ�д����Сд��y
    {
        exit(0);                //�˳���Ϸ
    }
    if (c == 'n' || c == 'N')      //���������Ǵ�д����Сд��n
    {
        system("cls");
        choice();
    }
}

/**
  * ��Ϸ�������
  * 
  */
void regulation()
{
    int i, j = 1;
    system("cls");
    color(13);
    gotoxy(25, 1);
    printf("��Ϸ����");
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
    printf(" tip1: ��ҿ���ͨ�� ��  ��  ��  �� ������ƶ�����");
    color(10);
    gotoxy(3, 6);
    printf(" tip2: ��ESC���˳���Ϸ");
    color(14);
    gotoxy(3, 8);
    printf(" tip3: ���ѡ��ķ����ϣ�������ͬ������ϲ�");
    color(11);
    gotoxy(3, 10);
    printf(" tip4: ÿ�ƶ�һ������λ�������һ�� 2 ���� 4 ");
    color(14);
    gotoxy(3, 12);
    printf(" tip5: ���̱������������޷�������Ч�ƶ�����Ϸʧ��");
    color(5);
    gotoxy(3, 14);
    printf(" tip6: �����ϳ��� 2048 ����Ϸʤ��");
    getch();
    system("cls");
    main();
}

/**
  * ����˵��
  * 
  */
void explanation(void)
{
    gotoxy(10, 18);
    color(3);
    printf(" ͨ�� �� �� �� �� �����в��� ");
    gotoxy(31, 18);
    printf(" ESC���˳���Ϸ");
    getch();
    system("cls");
    main();
}


/**
* ���������������
*/
int main()
{
    /*game_win();*/
    /*game_faile();*/
    //draw_game_box();
    choice();           //�˵�ѡ��
    /*getch();*/
    return 0;
}



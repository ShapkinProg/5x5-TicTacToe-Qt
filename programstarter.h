#ifndef PROGRAMSTARTER_H
#define PROGRAMSTARTER_H
#include <QObject>
#include<QPushButton>
#include <QString>
#include <QMessageBox>
#define MIN(a,b) a>b ? b : a
#define MAXLENGTH(a,b) a+b>4 ? 4 : a + b
class ProgramStarter : public QObject {

    Q_OBJECT

public: void setButtons(QPushButton** buttons, short *sx1, short *sy1, short *lenx1, short *leny1, short size1)
 {
        buttons1 = buttons;
        sx = sx1;
        sy = sy1;
        lenx = lenx1;
        leny = leny1;
        size = size1;
        memset (BoardPrice, 0, sizeof(BoardPrice [0])*size*size);
 }
public: void setP(int p1)
 {
    p = p1;
    tempp = p1;
 }
public: void setTempP()
 {
    p = tempp;
 }
public: void setDef()
 {
        memset (BoardPrice, 0, sizeof(BoardPrice [0])*size*size);
        jj = 0;
        ii = 0;
        pobeda = 0;
 }
public: void Player(int id)
    {
        int j = id / size;
        int i = id % size;
        buttons1[j][i].setText("X");
        BoardPrice[j][ i] = 0;
        SelectCell(j, i, 'X');
        CheckWin(j, i, 'X');

    }
public:void Bot()
    {
        int i, j;
        int max = 0;
        for (int k = *sx; k < *sx+*leny; ++k)
        {
            for (int l1 = *sy; l1 < *sy+*lenx; ++l1)
            {
                if (BoardPrice[k][l1] >= max)
                {
                    i = l1;
                    j = k;
                    max = BoardPrice[k][l1];
                }
            }
        }
        if (max <= 3)
        {
            int S = rand() % 100;
            i = *sy;
            j = *sx;
            while (S > 0)
            {
                if (j == *sx+*leny)
                {
                    if (i == *sy+*lenx)
                    {
                        i = *sy;
                    }
                    else
                        __asm{
                        inc i
                    }

                    j = *sx;
                }
                else    __asm{
                    inc j
                }
                if (BoardPrice[j][i] == max)
                    __asm{
                    dec S
                }
            }
        }
        fieldadd(j, i, 'b');
        buttons1[jj][ii].setStyleSheet("background-color: #2a5fdb");
       // buttons1[j][i].setStyleSheet("color:green");
        buttons1[j][i].setText("0");
        buttons1[j][i].setStyleSheet("background-color: #3390d6");
        jj = j;
        ii = i;
        BoardPrice[j][i] = 0;
        SelectCell(j, i, '0');
        CheckWin(j, i, '0');
    }
public: void SelectCell(int j, int i, char x)
    {
        char arr[1], arr1[1];
        QString s, s1;

        if (x == '0')
        {
            s = "0";
            s1 = "X";
            arr[0] = '0';
            arr1[0] = 'X';
        }
        else
        {
            s1 = "0";
            s = "X";
            arr[0] = 'X';
            arr1[0] = '0';
        }


        //Проверка горизонтали
        for (int k = 1; k < 5; ++k)
        {
            if (j + k < *sx+*leny)
            {
                if (buttons1[j + k][i].text() == "")
                {
                    BoardPrice[j + k][i] = 0;
                    CheckPrice(j + k, i, arr[0]);
                    CheckPrice(j + k, i, arr1[0]);
                }
                if (buttons1[j + k][i].text() == s1)
                    break;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if (j - k >= *sx)
            {
                if (buttons1[j - k][i].text() == "")
                {
                    BoardPrice[j - k][i] = 0;
                    CheckPrice(j - k, i, arr[0]);
                    CheckPrice(j - k, i, arr1[0]);
                }
                if (buttons1[j - k][i].text() == s1)
                    break;
            }
        }
        //Проверка Вертикали
        for (int k = 1; k < 5; ++k)
        {
            if (i + k < *sy+*lenx)
            {
                if (buttons1[j][i + k].text() == "")
                {
                    BoardPrice[j][i + k] = 0;
                    CheckPrice(j, i + k, arr[0]);
                    CheckPrice(j, i + k, arr1[0]);

                }
                if (buttons1[j][i + k].text() == s1)
                    break;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if (i - k >= *sy)
            {
                if (buttons1[j][i - k].text() == "")
                {
                    BoardPrice[j][i - k] = 0;
                    CheckPrice(j, i - k, arr[0]);
                    CheckPrice(j, i - k, arr1[0]);

                }
                if (buttons1[j][i - k].text() == s1)
                    break;
            }
        }
        //ПРоверка диагонали 1
        for (int k = 1; k < 5; ++k)
        {
            if ((j + k < *sx+*leny) && (i + k < *sy+*lenx))
            {
                if (buttons1[j + k][i + k].text() == "")
                {
                    BoardPrice[j + k][i + k] = 0;
                    CheckPrice(j + k, i + k, arr[0]);
                    CheckPrice(j + k, i + k, arr1[0]);

                }
                if (buttons1[j + k][i + k].text() == s1)
                    break;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if ((j - k >= *sx) && (i - k >= *sy))
            {
                if (buttons1[j - k][i - k].text() == "")
                {
                    BoardPrice[j - k][i - k] = 0;
                    CheckPrice(j - k, i - k, arr[0]);
                    CheckPrice(j - k, i - k, arr1[0]);
                }
                if (buttons1[j - k][i - k].text() == s1)
                    break;
            }
        }
        //Проверка диагонали 2
        for (int k = 1; k < 5; ++k)
        {
            if ((j + k < *sx+*leny) && (i - k >= *sy))
            {
                if (buttons1[j + k][i - k].text() == "")
                {
                    BoardPrice[j + k][i - k] = 0;
                    CheckPrice(j + k, i - k, arr[0]);
                    CheckPrice(j + k, i - k, arr1[0]);
                }
                if (buttons1[j + k][i - k].text() == s1)
                    break;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if ((j - k >= *sx) && (i + k < *sy+*lenx))
            {
                if (buttons1[j - k][i + k].text() == "")
                {
                    BoardPrice[j - k][i + k] = 0;
                    CheckPrice(j - k, i + k, arr[0]);
                    CheckPrice(j - k, i + k, arr1[0]);
                }
                if (buttons1[j - k][i + k].text() == s1)
                    break;
            }
        }
    }
public:void CheckPrice(int j, int i, char x)
    {
        int Space = 1;
        int Length1 = 0;
        int Length2 = 0;
        int Attack1 = 1;
        int Attack2 = 1;
        QString s, s1;
        if (x == 48)
        {
            s = "0";
            s1 = "X";

        }
        else
        {
            s1 = "0";
            s = "X";

        }

        //Проверка горизонтали
        for (int k = 1; k < 5; ++k)
        {
            if (j + k < *sx+*leny)
            {
                if (buttons1[j + k][i].text() == s)
                {
                    Length1++;
                }
                if (buttons1[j + k][i].text() == "")
                {
                    if (Length1 == 0) Space++;
                    else
                    {
                        if (buttons1[j + k][i].text() == "")
                            Attack1++;
                        break;
                    }
                }
                if (buttons1[j + k][i].text() == s1)
                {
                    break;
                }//выдление + игра выделение после победы
            }
            else break;
        }
        for (int k = 1; k < 5; ++k)
        {
            if (j - k >= *sx)
            {
                if (buttons1[j - k][ i].text() == s)
                {
                    Length2++;
                }
                if (buttons1[j - k][i].text() == "")
                {
                    if (Length2 == 0) Space++;
                    else
                    {
                        if (buttons1[j - k][i].text() == "")
                            Attack2++;
                        break;
                    }
                }
                if (buttons1[j - k][i].text() == s1)
                {
                    break;
                }
            }
            else break;
        }


        if (p == 1)
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        else if (Space < 3)
        {
            BoardPrice[j][i] += PriceList(MAXLENGTH(Length1, Length2), MIN(Attack1, Attack2), x);
        }
        else
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        Length1 = 0;
        Length2 = 0;
        Attack1 = 1;
        Attack2 = 1;
        Space = 1;

        //Проверка вертикали
        for (int k = 1; k < 5; ++k)
        {
            if (i + k < *sy+*lenx)
            {
                if (buttons1[j][i + k].text() == s)
                {
                    Length1++;
                }
                if (buttons1[j][i + k].text() == "")
                {
                    if (Length1 == 0) Space++;
                    else
                    {
                        if (buttons1[j][i + k].text() == "")
                            Attack1++;
                        break;
                    }
                }
                if (buttons1[j][i + k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        for (int k = 1; k < 5; ++k)
        {
            if (i - k >= *sy)
            {
                if (buttons1[j][i - k].text() == s)
                {
                    Length2++;
                }
                if (buttons1[j][i - k].text() == "")
                {
                    if (Length2 == 0) Space++;
                    else
                    {
                        if (buttons1[j][i - k].text() == "")
                            Attack2++;
                        break;
                    }
                }
                if (buttons1[j][i - k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        if (p == 1)
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        else if (Space < 3)
        {
            BoardPrice[j][i] += PriceList(MAXLENGTH(Length1, Length2), MIN(Attack1, Attack2), x);
        }

        else
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        Length1 = 0;
        Length2 = 0;
        Attack1 = 1;
        Attack2 = 1;
        Space = 1;


        //Проверка Диагонали 1

        for (int k = 1; k < 5; ++k)
        {
            if ((j + k < *sx+*leny) && (i + k < *sy+*lenx))
            {
                if (buttons1[j + k][i + k].text() == s)
                {
                    Length1++;
                }
                if (buttons1[j + k][i + k].text() == "")
                {
                    if (Length1 == 0) Space++;
                    else
                    {
                        if (buttons1[j + k][i + k].text() == "")
                            Attack1++;
                        break;
                    }
                }
                if (buttons1[j + k][i + k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        for (int k = 1; k < 5; ++k)
        {
            if ((j - k >= *sx) && (i - k >= *sy))
            {
                if (buttons1[j - k][i - k].text() == s)
                {
                    Length2++;
                }
                if (buttons1[j - k][i - k].text() == "")
                {
                    if (Length2 == 0) Space++;
                    else
                    {
                        if (buttons1[j - k][i - k].text() == "")
                            Attack2++;
                        break;
                    }
                }
                if (buttons1[j - k][i - k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        if (p == 1)
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        else if (Space < 3)
        {
            BoardPrice[j][i] += PriceList(MAXLENGTH(Length1, Length2), MIN(Attack1, Attack2), x);
        }
        else
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        Length1 = 0;
        Length2 = 0;
        Attack1 = 1;
        Attack2 = 1;
        Space = 1;

        //Проверка Диагонали 2
        for (int k = 1; k < 5; ++k)
        {
            if ((j + k < *sx+*leny) && (i - k >= *sy))
            {
                if (buttons1[j + k][i - k].text() == s)
                {
                    Length1++;
                }
                if (buttons1[j + k][i - k].text() == "")
                {
                    if (Length1 == 0) Space++;
                    else
                    {
                        if (buttons1[j + k][i - k].text() == "")
                            Attack1++;
                        break;
                    }
                }
                if (buttons1[j + k][i - k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        for (int k = 1; k < 5; ++k)
        {
            if ((j - k >= *sx) && (i + k < *sy+*lenx))
            {
                if (buttons1[j - k][i + k].text() == s)
                {
                    Length2++;
                }
                if (buttons1[j - k][i + k].text() == "")
                {
                    if (Length2 == 0) Space++;
                    else
                    {
                        if (buttons1[j - k][i + k].text() == "")
                            Attack2++;
                        break;
                    }
                }
                if (buttons1[j - k][i + k].text() == s1)
                {
                    break;
                }
            }
            else break;
        }
        if (p == 1)
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }
        else if (Space < 3)
        {
            BoardPrice[j][i] += PriceList(MAXLENGTH(Length1, Length2), MIN(Attack1, Attack2), x);
        }
        else
        {
            BoardPrice[j][i] += PriceList(Length1, Attack1, x);
            BoardPrice[j][i] += PriceList(Length2, Attack2, x);
        }

    }
public:void CheckWin(int j, int i,char x)
    {
        int cs = 0;
        int cs1 = 0;
        int course = 1;
        //Проверка вертикаль
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j + k < *sx+*leny-2) && (buttons1[j + k][ i].text() == "0"))
                {
                    course++;

                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {

                        buttons1[j + k][ i].setStyleSheet("background-color: #3390d6");
                       // buttons1[j + k][ i].setStyleSheet("color: black");
                    }
                    win(x);
                    return;
                }

            }
            else if (x == 'X')
            {
                if ((j + k < *sx+*leny-2) && (buttons1[j + k][ i].text() == "X"))
                {
                    __asm{
                        int course
                    }
                    //course++;

                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j + k][i].setStyleSheet("background-color: red");
                       // buttons1[j + k][i].setStyleSheet("color: black");
                    }

                    win(x);
                    return;
                }

            }
        }
        cs = course;
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j - k >= *sx+2) && (buttons1[j - k][ i].text() == "0"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i].setStyleSheet("background-color: #3390d6");
                        }
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i].setStyleSheet("background-color: #3390d6");
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j - k][ i].setStyleSheet("background-color: #3390d6");
                        }
                    }


                    win(x);
                    return;
                }
            }
            else if (x == 'X')
            {
                if ((j - k >= *sx+2) && (buttons1[j - k][ i].text() == "X"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i].setStyleSheet("background-color: red");

                        }
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i].setStyleSheet("background-color: red");

                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j - k][ i].setStyleSheet("background-color: red");

                        }
                    }
                    win(x);
                    return;
                }
            }

        }
        course = 1;
        cs1 = 0;
        //проверка горизонт
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((i + k < *sy+*lenx-2) && (buttons1[j][ i + k].text() == "0"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j][ i + k].setStyleSheet("background-color: #3390d6");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }
            else
            {
                if ((i + k < *sy+*lenx-2) && (buttons1[j][ i + k].text() == "X"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j][ i + k].setStyleSheet("background-color: red");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }

        }
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((i - k >= *sy+2) && (buttons1[j][ i - k].text() == "0"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j][ i + k].setStyleSheet("background-color: #3390d6");

                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j][ i - k].setStyleSheet("background-color: #3390d6");

                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j][ i - k].setStyleSheet("background-color: #3390d6");

                        }
                    }

                    win(x);
                    return;
                }
            }
            else
            {
                if ((i - k >= *sy+2) && (buttons1[j][ i - k].text() == "X"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j][ i + k].setStyleSheet("background-color: red");

                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j][ i - k].setStyleSheet("background-color: red");

                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j][ i - k].setStyleSheet("background-color: red");
                     //       buttons1[j][ i - k].setStyleSheet("color: black");
                        }
                    }
                    win(x);
                    return;
                }
            }
        }
        course = 1;
        cs1 = 0;
        //проверка 1 диагонали
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j + k < *sx+*leny-2) && (i + k < *sy+*lenx-2) && (buttons1[j + k][ i + k].text() == "0"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j + k][ i + k].setStyleSheet("background-color: #3390d6");
                    //    buttons1[j + k][ i + k].setStyleSheet("color: black");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }
            else
            {
                if ((j + k < *sx+*leny-2) && (i + k < *sy+*lenx-2) && (buttons1[j + k][ i + k].text() == "X"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j + k][ i + k].setStyleSheet("background-color: red");
                   //     buttons1[j + k][ i + k].setStyleSheet("color: black");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j - k >= *sx+2) && (i - k >= *sy+2) && (buttons1[j - k][ i - k].text() == "0"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i + k].setStyleSheet("background-color: #3390d6");
                         //   buttons1[j + k][ i + k].setStyleSheet("color: black");
                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i - k].setStyleSheet("background-color: #3390d6");
                         //   buttons1[j - k][ i - k].setStyleSheet("color: black");
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j - k][ i - k].setStyleSheet("background-color: #3390d6");
                        //    buttons1[j - k][ i - k].setStyleSheet("color: black");
                        }
                    }
                    win(x);
                    return;
                }
            }
            else
            {
                if ((j - k >= *sx+2) && (i - k >= *sy+2) && (buttons1[j - k][ i - k].text() == "X"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i + k].setStyleSheet("background-color: red");
                        //    buttons1[j + k][ i + k].setStyleSheet("color: black");
                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i - k].setStyleSheet("background-color: red");
                         //   buttons1[j - k][ i - k].setStyleSheet("color: black");
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j - k][ i - k].setStyleSheet("background-color: red");
                         //   buttons1[j - k][ i - k].setStyleSheet("color: black");
                        }
                    }
                    win(x);
                    return;
                }
            }
        }
        course = 1;
        cs1 = 0;
        //проверка 2 диагонали
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j + k < *sx+*leny-2) && (i - k >= *sy+2) && (buttons1[j + k][ i - k].text() == "0"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j + k][ i - k].setStyleSheet("background-color: #3390d6");
                     //   buttons1[j + k][ i - k].setStyleSheet("color: black");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }
            else
            {
                if ((j + k < *sx+*leny-2) && (i - k >= *sy+2) && (buttons1[j + k][ i - k].text() == "X"))
                {
                    course++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        buttons1[j + k][ i - k].setStyleSheet("background-color: #3390d6");
                     //   buttons1[j + k][ i - k].setStyleSheet("color: black");
                    }
                    win(x);
                    return;
                }
                cs = course;
            }
        }
        for (int k = 1; k < 5; ++k)
        {
            if (x == 48)
            {
                if ((j - k >= *sx+2) && (i + k < *sy+*lenx-2) && (buttons1[j - k][ i + k].text() == "0"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i - k].setStyleSheet("background-color: #3390d6");
                         //   buttons1[j + k][ i - k].setStyleSheet("color: black");
                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i + k].setStyleSheet("background-color: #3390d6");
                        //    buttons1[j - k][ i + k].setStyleSheet("color: black");
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            buttons1[j - k][ i + k].setStyleSheet("background-color: #3390d6");
                        //    buttons1[j - k][ i + k].setStyleSheet("color: black");
                        }
                    }
                    win(x);
                    return;
                }
            }
            else
            {
                if ((j - k >= *sx+2) && (i + k < *sy+*lenx-2) && (buttons1[j - k][ i + k].text() == "X"))
                {
                    course++;
                    cs1++;
                }
                else
                {
                    break;
                }
                if (course == 5)
                {
                    if (cs + cs1 == 5)
                    {
                        for (int k = 0; k < cs; k++)
                        {
                            buttons1[j + k][ i - k].setStyleSheet("background-color: red");
                          //  buttons1[j + k][ i - k].setStyleSheet("color: black");
                        }
                        for (int k = 0; k <= cs1; k++)
                        {
                            buttons1[j - k][ i + k].setStyleSheet("background-color: red");
                         //   buttons1[j - k][ i + k].setStyleSheet("color: black");
                        }
                    }
                    else
                    {
                        for (int k = 0; k < 5; k++)
                        {

                            buttons1[j - k][ i + k].setStyleSheet("background-color: red");
                            //buttons1[j - k][ i + k].setStyleSheet("color: black");
                        }
                    }
                    win(x);
                    return;
                }
            }
        }
    }

public:void win(char x)
{
    pobeda = 1;
    QMessageBox msgBox;
    if (x == 48)
    {
        msgBox.setText("0 выиграли");

    }
    else if (x == 88)
    {
        msgBox.setText("X выиграли");
    }
    msgBox.exec();
}
public: int PriceList(int Length, int Potential, char Who)
{

    if (Who == 'X')
    {
        switch (Length)
        {
        case 1:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 3;
            }

            break;

        case 2:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 15;
            case 2:
                return 55;
            }

            break;
        case 3:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 45;
            case 2:
                return 550;
            }

            break;
        case 4:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 1000;
            case 2:
                return 1000;
            }

            break;
        default: return 0;
        }
    }
    else
    {
        switch (Length)
        {
        case 1:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 3;
            }

            break;

        case 2:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 10;
            case 2:
                return 50;
            }

            break;
        case 3:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 40;
            case 2:
                return 500;
            }

            break;
        case 4:
            switch (Potential)
            {
            case 0:
                return 0;
            case 1:
                return 1000;
            case 2:
                return 1000;
            }

            break;
        default: return 0;
        }
    }
    return 0;
}
public: void fieldadd(int i, int j, char who)
    {
        if(i == *sx && !pobeda)
        {
            for(int n = 0; n < *lenx; n++)
            {
                if(who == 'p')
                buttons1[i-1][*sy+n].show();
                buttons1[i-1][*sy+n].setStyleSheet("background-color: gray");
                if(who == 'p')
                buttons1[i-2][*sy+n].show();
                buttons1[i-2][*sy+n].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *lenx-2; n++)
            {
                buttons1[i][*sy+n].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[i][*sy+n].show();
                buttons1[i+1][*sy+n].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[i+1][*sy+n].show();
            }

            (*sx) -=2;
            (*leny)+=2;
        }
        if(i == *sx+1 && !pobeda)
        {
            for(int n = 0; n < *lenx; n++)
            {
                if(who == 'p')
                buttons1[i-2][*sy+n].show();
                buttons1[i-2][*sy+n].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *lenx-2; n++)
            {
                buttons1[i][*sy+n].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[i][*sy+n].show();
            }

            (*sx) -=1;
            (*leny)+=1;
        }
        if(j == *sy+1 && !pobeda)
        {
            for(int n = 0; n < *leny; n++)
            {
                if(who == 'p')
                buttons1[*sx+n][j-2].show();
                buttons1[*sx+n][j-2].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *leny-2; n++)
            {
                buttons1[*sx+n][j].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[*sx+n][j].show();
            }

            (*sy) -=1;
            (*lenx)+=1;
        }
        if(j == *sy && !pobeda)
        {
            for(int n = 0; n < *leny; n++)
            {
                if(who == 'p')
                buttons1[*sx+n][j-1].show();
                buttons1[*sx+n][j-1].setStyleSheet("background-color: gray");
                if(who == 'p')
                buttons1[*sx+n][j-2].show();
                buttons1[*sx+n][j-2].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *leny-2; n++)
            {
                buttons1[*sx+n][j].setStyleSheet("background-color: none");
                buttons1[*sx+n][j+1].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[*sx+n][j].show();
                if(who == 'b')
                    buttons1[*sx+n][j+1].show();
            }
            (*sy) -=2;
            (*lenx)+=2;
        }
        if(i == *sx+*leny-1 && !pobeda)
        {
            for(int n = 0; n < *lenx; n++)
            {
                if(who == 'p')
                buttons1[i+1][*sy+n].show();
                buttons1[i+1][*sy+n].setStyleSheet("background-color: gray");
                if(who == 'p')
                buttons1[i+2][*sy+n].show();
                buttons1[i+2][*sy+n].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *lenx-2; n++)
            {
                buttons1[i][*sy+n].setStyleSheet("background-color: none");
                buttons1[i-1][*sy+n].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[i][*sy+n].show();
                if(who == 'b')
                    buttons1[i-1][*sy+n].show();
            }

            (*leny)+=2;
        }
        if(i == *sx+*leny-2 && !pobeda)
        {
            for(int n = 0; n < *lenx; n++)
            {
                if(who == 'p')
                buttons1[i+2][*sy+n].show();
                buttons1[i+2][*sy+n].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *lenx-2; n++)
            {
                buttons1[i][*sy+n].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[i][*sy+n].show();
            }

            (*leny)+=1;
        }
        if(j == *sy+*lenx-2 && !pobeda)
        {
            for(int n = 0; n < *leny; n++)
            {
                if(who == 'p')
                buttons1[*sx+n][j+2].show();
                buttons1[*sx+n][j+2].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *leny-2; n++)
            {
                buttons1[*sx+n][j].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[*sx+n][j].show();
            }

            (*lenx)+=1;
        }
        if(j == *sy+*lenx-1 && !pobeda)
        {
            for(int n = 0; n < *leny; n++)
            {
                if(who == 'p')
                buttons1[*sx+n][j+1].show();
                buttons1[*sx+n][j+1].setStyleSheet("background-color: gray");
                if(who == 'p')
                buttons1[*sx+n][j+2].show();
                buttons1[*sx+n][j+2].setStyleSheet("background-color: gray");

            }
            for(int n = 2; n < *leny-2; n++)
            {
                buttons1[*sx+n][j].setStyleSheet("background-color: none");
                buttons1[*sx+n][j-1].setStyleSheet("background-color: none");
                if(who == 'b')
                    buttons1[*sx+n][j].show();
                if(who == 'b')
                     buttons1[*sx+n][j-1].show();
            }
            (*lenx)+=2;
        }
    }

 public slots:
    void startProgram()
    {
        QObject *senderObj = sender();
        t = senderObj->objectName();
        tag = t.toInt();
        i = tag / size;
        j = tag % size;
        fieldadd(i, j, 'p');
        if(buttons1[i][j].text() == "" && !pobeda)
        if(p == 0)
        {
            if(hod == 'X')
            {
                buttons1[i][j].setText("X");
            }
            else
            {
                buttons1[i][j].setText("0");
            }
            CheckWin(tag / size, tag % size, hod);
            if (hod == 'X')
             hod = '0';
            else hod = 'X';
        }
         else
            {
             Player(tag);
            if (!pobeda)
              {
                Bot();
              }
            }
    }
    void change1()
    {
        tempp = 0;
        QMessageBox msgBox;
        if(nottice)
        {
            msgBox.setText("Changes will take effect after restarting the field");
            msgBox.exec();
        }
        nottice = 0;
    }
    void change2()
    {
        tempp = 1;
        QMessageBox msgBox;
        if(nottice)
        {
            msgBox.setText("Changes will take effect after restarting the field");
            msgBox.exec();
        }
        nottice = 0;
    }
    void change3()
    {
        tempp = 2;
        QMessageBox msgBox;
        if(nottice)
        {
            msgBox.setText("Changes will take effect after restarting the field");
            msgBox.exec();
        }
        nottice = 0;
    }

private:
    QPushButton** buttons1;
    QString t;
    int tag;
    int p;
    int i;
    int nottice = 1;
    int tempp;
    int jj = 0;
    int ii = 0;
    int j;
    short BoardPrice[100][100];
    short size;
    short *sx;
    short *sy;
    short hod;
    short *lenx;
    short *leny;
public:
    short pobeda = 0;
};
#endif // PROGRAMSTARTER_H

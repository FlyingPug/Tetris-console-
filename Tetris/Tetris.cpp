// Tetris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <thread> 
#include <stdio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using std::cout;
using std::endl;
using std::thread;



struct vector2d
{
    public:
    int x, y;
    void swap()
    {
        int n = x;
        x = y;
        y = n;
    }
    void set(int x1, int y1)
    {
        x = x1;
        y = y1;
    }
};

class figure
{
    public:
        vector2d* vectors = new vector2d[3];
        vector2d mainpos;
        bool active;
        figure()
        {
            int r; 
            mainpos.x = 5;
            mainpos.y = 0;
            
          
                r = 1 + rand() % 7;
                switch (r)
                {
                case 1:
                    vectors[0].set(1, 0);
                    vectors[1].set(-1, 0);
                    vectors[2].set(-2, 0);
                    break;
                case 2:
                    vectors[0].set(1, 0);
                    vectors[1].set(-1, 0);
                    vectors[2].set(-1, 1);
                    break;
                case 3:
                    vectors[0].set(-1, 0);
                    vectors[1].set(1, 0);
                    vectors[2].set(1, 1);
                    break;
                case 4:
                    vectors[0].set(1, 0);
                    vectors[1].set(1, 1);
                    vectors[2].set(0, 1);
                    break;
                case 5:
                    vectors[0].set(-1, 0);
                    vectors[1].set(1, 1);
                    vectors[2].set(0, 1);
                    break;
                case 6:
                    vectors[0].set(1, 0);
                    vectors[1].set(-1, 0);
                    vectors[2].set(0, 1);
                    break;

                case 7:
                    vectors[0].set(1, 0);
                    vectors[1].set(0, 1);
                    vectors[2].set(-1, 1);
                    break;
                }
            
           // vectors[0].set()
        }
        void rotate90()
        {
            int n;
            for (int i = 0; i < 3; i++)
            {
                n = vectors[i].y;
                vectors[i].y = -vectors[i].x;
                vectors[i].x = n;
            }
        }
        void rotate270()
        {
            int n;
            for (int i = 0; i < 3; i++)
            {
                n = vectors[i].x;
                vectors[i].x = -vectors[i].y;
                vectors[i].y = n;
            }
        }
};

class game
{
public:
    int move = 0;
    bool gameison = true;
    int score = 0;
    figure& active_figure = *(new figure);
    game()
    {
        map = new bool* [10];
        for (int i = 0; i < 10; i++)
        {
            map[i] = new bool[20];
        }
        for (int i = 0; i < 10; i++)
        {
            for (int g = 0; g < 20; g++)
            {
                map[i][g] = 0;
            }
        }
    }

    bool step_right()
    {
        if (active_figure.mainpos.x + 1 > 9)
        {
            active_figure.mainpos.x -= 10;
        }
         if (map[active_figure.mainpos.x + 1][active_figure.mainpos.y] == 1)
        {
            return 0;
        }

        for (int i = 0; i < 3; i++)
        {
            if (active_figure.mainpos.x + active_figure.vectors[i].x + 1 > 9)
            {
                active_figure.vectors[i].x -= 10;
            }
            else if (active_figure.mainpos.x + active_figure.vectors[i].x + 1 < 0)
            {
                active_figure.vectors[i].x += 10;
            }
            if (map[active_figure.mainpos.x + active_figure.vectors[i].x + 1][active_figure.mainpos.y - active_figure.vectors[i].y] == 1)
            {
                return 0;
            }
 

        }
        active_figure.mainpos.x += 1;

        return 1;
    
    }

    bool step_left()
    {
        if (active_figure.mainpos.x - 1 < 0)
        {
            active_figure.mainpos.x += 10;
        }
        if (map[active_figure.mainpos.x - 1][active_figure.mainpos.y] == 1)
        {
            return 0;
        }

        for (int i = 0; i < 3; i++)
        {
            if (active_figure.mainpos.x + active_figure.vectors[i].x - 1 < 0)
            {
                active_figure.vectors[i].x += 10;
            }
            if (active_figure.mainpos.x + active_figure.vectors[i].x - 1 > 9)
            {
                active_figure.vectors[i].x -= 10;
            }
            else if (map[active_figure.mainpos.x + active_figure.vectors[i].x- 1][active_figure.mainpos.y - active_figure.vectors[i].y] == 1)
            {
                return 0;
            }


        }
        active_figure.mainpos.x -= 1;

        return 1;

    }

    bool checkforlose()
    {
            for (int g = 0; g < 10; g++)
            {
                if (map[g][1] == 1)
                {
                    return  0;
                }
            }
        
        return 1;
    }

    void output()
    {
        if (gameison)
        {
            int out[10][20];
            for (int i = 0; i < 10; i++)
            {
                for (int g = 0; g < 20; g++)
                {
                    out[i][g] = map[i][g];
                }
            }
            system("cls");
            out[active_figure.mainpos.x][active_figure.mainpos.y] = 1;
            for (int i = 0; i < 3; i++)
            {
                out[active_figure.mainpos.x + active_figure.vectors[i].x][active_figure.mainpos.y - active_figure.vectors[i].y] = 1;
            }
            for (int i = 2; i < 20; i++)
            {
                for (int g = 0; g < 10; g++)
                {
                    cout << out[g][i] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cout << endl;
            cout << " Your score: " << score << endl;
            /*   for (int i = 0; i < 3; i++)
               {
                   cout << " OUT" << active_figure.vectors[i].x << " " << active_figure.vectors[i].y << endl;
               }
               cout << active_figure.mainpos.y;*/
        }
    }
    bool check()
    {
     /*   for (int i = 0; i < 3; i++)
        {
            cout << active_figure.vectors[i].x << " " << active_figure.vectors[i].y << endl;
        }*/
        if (map[active_figure.mainpos.x][active_figure.mainpos.y + 1] == 1)
        {
            return 0;
        }
        else if(active_figure.mainpos.y + 1 > 19)
        {
            return 0;
        }
        for (int i = 0; i < 3; i++)
        {
            if (map[active_figure.mainpos.x + active_figure.vectors[i].x][active_figure.mainpos.y - active_figure.vectors[i].y + 1] == 1)
            {
                return 0;
            }
            if (active_figure.mainpos.y - active_figure.vectors[i].y + 1 > 19)
            {
                return 0;
            
            }

        }
        active_figure.mainpos.y += 1;

            return 1;
    }
    void new_figure()
    {
        map[active_figure.mainpos.x][active_figure.mainpos.y] = 1;
        for (int i = 0; i < 3; i++)
        {
           
            map[active_figure.mainpos.x + active_figure.vectors[i].x][active_figure.mainpos.y -active_figure.vectors[i].y] = 1;
        }


        active_figure = *(new figure);
        move++;
    }

    void rotate()
    {
        active_figure.rotate90();
        if (map[active_figure.mainpos.x][active_figure.mainpos.y] == 1)
        {
            active_figure.rotate270();
        }
        else if (active_figure.mainpos.y > 19)
        {
            active_figure.rotate270();
        }
        for (int i = 0; i < 3; i++)
        {
            if (map[active_figure.mainpos.x + active_figure.vectors[i].x][active_figure.mainpos.y - active_figure.vectors[i].y ] == 1)
            {
                active_figure.rotate270();
            }
            if (active_figure.mainpos.y - active_figure.vectors[i].y > 19)
            {
                active_figure.rotate270();

            }

        }
    }

    void getdown(int from)
    {
        for (int i = from; i > 2; i--)
        {
            for (int g = 0; g < 10; g++)
            {
                map[g][i] = map[g][i - 1];
            }
        }
    }

    void givemescore()
    {
        bool buf = true;
        for (int i = 2; i < 20; i++)
        {
            for (int g = 0; g < 10; g++)
            {
                if (map[g][i] == 0)
                {
                    buf = false;
                }
            }
            if (buf)
            {
                score += move;
                getdown(i);

            }
            buf = true;
        }
    }

    void dotick()
    {
        if (!checkforlose())
        {
            gameison = false;
            system("cls");
            cout << "YOU LOSE! (LOSER)" << endl;
        }
        else
        {
            if (!check())
            {
                new_figure();
            }
            givemescore();
        }
       
    }



private:
    bool** map;
    
   
};


class BetterTimer {
public:

    BetterTimer(game* games)
    {
        thread main([&]() {BetterThreadTimer(games); });
        main.detach();
    }

    void BetterThreadTimer(game* games)
    {
        while (true)
        {
            Sleep(1000 - games->move);
            games->dotick();
        }
    }

};



void input(game* main)
{
   int a;
   while (true)
   {
       a = _getch();
       if (a == 97 || a == 75)
       {

           if (!main->step_left())
           {
            //   main->new_figure();
           }
         
       }
       else if (a == 100 || a == 77)
       {
           if (!main->step_right())
           {
            //   main->new_figure();
           }
       }
       else if(a == 32)
        {
           main->rotate();
        }
       else if (a == 115 || a == 80)
       {
           if (!main->check())
           {
               main->new_figure();
           }
       }
   }
}

void out(game* main)
{
    while (true)
    {
        if (main->gameison)
        {
            main->output();
        }
    }
}

int main()
{   
   srand(time(0));

    game main;
    thread nes(input, &main);
    thread outp(out, &main);
    nes.detach();
    BetterTimer timer(&main);

    int a= 0 ;
  /*      while (true)
        {
            a = getch();
            cout << a<<endl;
            switch (a)
            {
                case 
            }
       */
    for (;;)
    {

    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

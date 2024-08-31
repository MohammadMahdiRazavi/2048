#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;
struct GameHistory
{
    int size; //size of square
    string name; //name of palyer
    int ScoreMatch; //score of the match
};
void dispmenu( GameHistory leaderboard[100] , int **Game); //menu
void print(int** Game , int size); //cout the square
void NewGame(int **Game , GameHistory leaderboard[100] , int size);
void Up(int** Game , int size); // up moving
void UpSort(int** Game , int size); // sort before up move
void Down(int** Game , int size); // down move
void DownSort(int** Game , int size); // sort before down move
void Right(int** Game , int size); // right move
void RightSort(int** Game , int size);  //sort before right move
void Left(int** Game , int size); // left move
void LeftSort(int** Game , int size);  // sort before left move
bool winCheck(int** Game , GameHistory leaderboard[100] , int size);
bool loseCheck(int** Game , GameHistory leaderboard[100] , int size);
int RandomNumber();
void leaderboardSort(GameHistory leaderboard[100]);
void leaderboardsave(GameHistory leaderboard[100]);
void SortArray(GameHistory leaderboard[100] , int counter);
void leaderboardprint(GameHistory leaderboard[100]);
int number_of_match = 0;
int score = 0;
typedef enum // set text color
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8,
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12,
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground) // set text color
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}
int main()
{
    int** Game; // square of game
    GameHistory leaderboard[100];
    for(int counter = 0; counter < 100 ; counter++) // clean leaderboard
    {
        leaderboard[counter].name = "";
        leaderboard[counter].ScoreMatch = 0;
        leaderboard[counter].size = 0;
    }
    dispmenu(leaderboard , Game); // menu
}
void dispmenu(GameHistory leaderboard[100] , int** Game) //menu
{
    while(true)
    {
        int section;
        int size; // size of square
        setTextColor(BLUE);
        cout << "please select the section" << endl;
        cout << "1 - NewGame" << endl;
        cout << "2 - Leaderboard" << endl;
        cout << "3 - Exit" << endl;
        cin >> section;
        if(section == 1) // newgame
        {
            system("cls");
            cout << "please enter your name : ";
            cin >> leaderboard[number_of_match].name;
            setTextColor(YELLOW);
            system("cls");
            cout << "please enter the size :";
            cin >> size;
            leaderboard[number_of_match].size = size;
            int** Game = new int * [size];
            for(int i = 0; i < size ; i++)
            {
                *(Game + i) = new int [size];
            }
            for(int counter1 = 0; counter1 < size; counter1++)
            {
                for(int counter2 = 0; counter2 < size; counter2++)
                {
                    *(*(Game + counter1) + counter2) = 0;
                }
            }

            int Rand_Num_1 = rand()%size;
            int Rand_Num_2 = rand()%size;
            int Rand_Num_3 = rand()%size;
            int Rand_Num_4 = rand()%size;
            *(*(Game + Rand_Num_1) + Rand_Num_2) = RandomNumber();
            *(*(Game + Rand_Num_3) + Rand_Num_4) = RandomNumber();
            NewGame(Game , leaderboard , size);
        }
        else if(section == 2) // leaderboard
        {
            leaderboardSort(leaderboard);
            leaderboardprint(leaderboard);
        }
        else if(section == 3) // exit the game
        {
            system("cls");
            cout << "Are you sure you want to quit 2048" << endl;
            cout << "1 - Yes! quit now" << endl;
            cout << "2 - NO" << endl;
            int quit;
            cin >> quit;
            if(quit == 1)
            {
                delete [] Game; // delete pointer
                system("cls");
                break;
            }
            else{
                continue;
            }
        }

    }
}
void SortArray(GameHistory leaderboard[100] , int counter)
{
    // Sort the leaderboard
    for(int counter1 = 0 ; counter1 < counter - 1 ; counter1++)
    {
        for(int counter2 = 0 ; counter2 < counter - 1 - counter1 ; counter2++)
        {
            if(leaderboard[counter2].ScoreMatch < leaderboard[counter2 + 1].ScoreMatch)
            {
                swap(leaderboard[counter2] , leaderboard[counter2 + 1]);
            }
        }
    }
}
void leaderboardSort(GameHistory leaderboard[100])
{
    ifstream file("Leaderboard.txt"); // add data
    int counter = number_of_match;
    if(file.is_open())
    {
        while(file >> leaderboard[counter].name >> leaderboard[counter].size >> leaderboard[counter].ScoreMatch)
        {
            counter++;
        }
        file.close();
    }
    SortArray(leaderboard , counter);
}
void leaderboardprint(GameHistory leaderboard[100])
{
    system("cls");
    setTextColor(YELLOW);
    int count = 0;
    while(leaderboard[count].ScoreMatch > 0)
    {
        cout << "name : " << leaderboard[count].name << " - size : " << leaderboard[count].size << " - score : " << leaderboard[count].ScoreMatch << "\n";
        count++;
    }
}
void leaderboardsave(GameHistory leaderboard[100])
{
    ofstream file("LeaderBoard.txt", ios::trunc); //save data
    if(file.is_open())
    {
        for(int counter = 0 ; leaderboard[counter].ScoreMatch > 0 ; counter++)
        {
            file << leaderboard[counter].name << " " << leaderboard[counter].size << " " << leaderboard[counter].ScoreMatch << "\n";
        }
        file.close();
        if(leaderboard[0].ScoreMatch == 0)
        {
            cout << "the game has not been played yet!" << endl;
        }
        else
        {
            cout << "file saved!" << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Unable to open the file" << endl;;
    }
}
bool winCheck(int** Game , GameHistory leaderboard[100] , int size) // check win
{
    bool flag_2048 = false;
    for(int counter1 = 0 ; counter1 < size ; counter1++)
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == 2048)
            {
                flag_2048 = true;
                break;
            }
        }
    }
    if(flag_2048 == true)
    {
        leaderboard[number_of_match].ScoreMatch = score;
        score = 0;
        number_of_match++; // save data
        leaderboardsave(leaderboard);
    }
    return flag_2048;
}
bool loseCheck(int** Game , GameHistory leaderboard[100] , int size) // check lose
{
    bool flag_1 = false;
    bool flag_2 = false;
    for(int counter1 = 0 ; counter1 < size ; counter1++) // found zero
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                flag_1 = true;
                flag_2 = true;
            }
        }
    }
    if(flag_1 == false)
    {
        for(int counter1 = 0 ; counter1 < size - 1 ; counter1++) // found two equal values
        {
            for(int counter2 = 0 ; counter2 < size - 1 ; counter2++)
            {
                if(*(*(Game + counter1) + counter2) == *(*(Game + counter1 + 1) + counter2) || *(*(Game + counter1) + counter2) == *(*(Game + counter1) + counter2 + 1))
                {
                    flag_2 = true;
                }
            }
        }
    }
    if(flag_1 == false)
    {
        for(int counter1 = size - 1 ; counter1 >= 1 ; counter1--) // found two equal values
        {
            for(int counter2 = size - 1 ; counter2 >= 1 ; counter2--)
            {
                if(*(*(Game + counter1) + counter2) == *(*(Game + counter1 - 1) + counter2) || *(*(Game + counter1) + counter2) == *(*(Game + counter1) + counter2 - 1))
                {
                    flag_2 = true;
                }
            }
        }
    }
    if(flag_2 == false)
    {
        leaderboard[number_of_match].ScoreMatch = score;
        score = 0;
        number_of_match++; // save data
        leaderboardsave(leaderboard);
    }
    return flag_2;
}
void print(int** Game , int size) // print the square and score
{
    setTextColor(RED);
    cout << "Score : ";
    setTextColor(BLUE);
    cout << score <<endl;
    for(int counter1 = 0 ; counter1 < size ; counter1++)
    {
        int counter3 = size;
        while(counter3--)
        {
            setTextColor(GREEN);
            cout << "\u250C" << "\u2508"  << "\u2508"  << "\u2508" << "\u2508" <<  "\u2510" ;
        }
        cout << "\n";
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) >= 1000)
            {
                setTextColor(YELLOW);
                cout << "\u250A" << *(*(Game + counter1) + counter2) << "\u250A";
            }
            else if(*(*(Game + counter1) + counter2) >= 100 && *(*(Game + counter1) + counter2) < 1000)
            {
                setTextColor(RED);
                cout << "\u250A" << *(*(Game + counter1) + counter2) << " " << "\u250A";
            }
            else if(*(*(Game + counter1) + counter2) >= 10 && *(*(Game + counter1) + counter2) < 100)
            {
                setTextColor(BLUE);
                cout << "\u250A" << " " << *(*(Game + counter1) + counter2) << " " << "\u250A";
            }
            else if(*(*(Game + counter1) + counter2) >= 1 && *(*(Game + counter1) + counter2) < 10)
            {
                setTextColor(GREEN);
                cout << "\u250A" << " " << *(*(Game + counter1) + counter2) << "  " << "\u250A";
            }
            else if(*(*(Game + counter1) + counter2) == 0)
            {
                setTextColor(PURPLE);
                cout << "\u250A" << "    " << "\u250A";
            }
        }
        cout << "\n";
        int counter4 = size;
        while(counter4--)
        {
            setTextColor(AQUA);
            cout << "\u2514" << "\u2508"<< "\u2508"  << "\u2508" << "\u2508" <<  "\u2518" ;
        }
        cout << "\n";
    }
}
void NewGame(int** Game , GameHistory leaderboard[100] , int size)
{
    while(true)
    {
        system("cls");
        print(Game , size);
        if(winCheck(Game , leaderboard , size) == true)
        {
            setTextColor(RED);
            cout << "congratulations , you won!" << endl;
            cout << "rate us in Google paly" << endl;
            break;
        }
        if(loseCheck(Game , leaderboard , size) == false)
        {
            setTextColor(BLUE);
            cout << "Game over" << endl << "Thanks for playing." <<endl << "rate us in Google paly" << endl;
            break;
        }
        setTextColor(GREEN);
        cout << "Enter a move (W/A/S/D/Q{to exit the game}) : " << endl; // get the character to move
        char UserInprt = getch();
        if(UserInprt == 'W'){
            Up(Game , size);
        }
        else if(UserInprt == 'S')
        {
            Down(Game , size);
        }
        else if(UserInprt == 'D')
        {
            Right(Game , size);
        }
        else if(UserInprt == 'A')
        {
            Left(Game , size);
        }
        else if(UserInprt == 'Q') // quit the game
        {
            leaderboard[number_of_match].ScoreMatch = score;
            score = 0;
            leaderboardsave(leaderboard);
            number_of_match++; // save data
            break;
        }
    }
}
int RandomNumber() //prodution pf number 2 or 4
{
    int radom_num = rand() % 4;
    if(radom_num == 3)
    {
        return 4;
    }
    else{
        return 2;
    }
}
void UpSort(int** Game , int size) // sort before up move
{
    for(int counter1 = 0 ; counter1 < size - 1 ; counter1++)
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = *(*(Game + counter1 + 1) + counter2);
                *(*(Game + counter1 + 1) + counter2) = 0;
            }
        }
    }
}
void Up(int** Game , int size) // up move
{
    bool flag_null = false;
    int size_sort = size - 1;
    while(size_sort--)
    {
        UpSort(Game , size);
    }
    for(int counter1 = 0 ; counter1 < size - 1 ; counter1++)
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == *(*(Game + counter1 + 1) + counter2))
            {
                score += *(*(Game + counter1) + counter2);
                *(*(Game + counter1) + counter2) *= 2;
                *(*(Game + counter1 + 1) + counter2) = 0;
            }
        }
    }
    size_sort = size - 1;
    while(size_sort--)
    {
        UpSort(Game , size);
    }
    for(int counter1 = size - 1 ; counter1 >= 0 ; counter1--) // random number
    {
        if(flag_null == true)
        {
            break;
        }
        for(int counter2 = size - 1 ; counter2 >= 0 ; counter2--)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = RandomNumber();
                flag_null = true;
                break;
            }
        }
    }
}
void DownSort(int** Game , int size) // sort before down move
{
    for(int counter1 = size -1  ; counter1 > 0 ; counter1--)
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = *(*(Game + counter1 - 1) + counter2);
                *(*(Game + counter1 - 1) + counter2) = 0;
            }
        }
    }
}
void Down(int** Game , int size) // down move
{
    bool flag_null = false;
    int size_sort = size - 1;
    while(size_sort--)
    {
        DownSort(Game , size);
    }
    for(int counter1 = size - 1 ; counter1 > 0 ; counter1 --)
    {
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == *(*(Game + counter1 - 1) + counter2))
            {
                score += *(*(Game + counter1) + counter2);
                *(*(Game + counter1) + counter2) *= 2;
                *(*(Game + counter1 - 1) + counter2) = 0;
            }
        }
    }
    size_sort = size - 1;
    while(size_sort--)
    {
        DownSort(Game , size);
    }
    for(int counter1 = 0 ; counter1 < size  ; counter1++)
    {
        if(flag_null == true)
        {
            break;
        }
        for(int counter2 = 0 ; counter2 < size ; counter2++) // random number
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = RandomNumber();
                flag_null = true;
                break;
            }
        }
    }
}
void RightSort(int** Game , int size) // sort before and after rifgt move
{
    for(int counter2 = size - 1 ; counter2 > 0 ; counter2--)
    {
        for(int counter1 = 0 ; counter1 < size ; counter1++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = *(*(Game + counter1) + counter2 - 1);
                *(*(Game + counter1) + counter2 - 1) = 0;
            }
        }
    }
}
void Right(int** Game , int size) // right move
{
    bool flag_null = false;
    int size_sort = size -1;
    while(size_sort--)
    {
        RightSort(Game , size);
    }
    for(int counter2 = size - 1 ; counter2 > 0 ; counter2--)
    {
        for(int counter1 = 0 ; counter1 < size ;counter1++)
        {
            if(*(*(Game + counter1) + counter2) == *(*(Game + counter1) + counter2 - 1))
            {
                score += *(*(Game + counter1) + counter2);
                *(*(Game + counter1) + counter2) *= 2;
                *(*(Game + counter1) + counter2 - 1) = 0;
            }
        }
    }
    size_sort = size -1;
    while(size_sort--)
    {
        RightSort(Game , size);
    }
    for(int counter1 = 0 ; counter1 < size ; counter1++)
    {
        if(flag_null == true)
        {
            break;
        }
        for(int counter2 = size - 1 ; counter2 >= 0 ; counter2--)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = RandomNumber();
                flag_null = true;
                break;
            }
        }
    }
}
void LeftSort(int** Game , int size) // sort before and after left move
{
    for(int counter2 = 0 ; counter2 < size - 1 ; counter2++)
    {
        for(int counter1 = 0 ; counter1 < size ; counter1++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = *(*(Game + counter1) + counter2 + 1);
                *(*(Game + counter1) + counter2 + 1) = 0;
            }
        }
    }
}
void Left(int** Game , int size) // left move
{
    bool flag_null = false;
    int size_sort = size - 1;
    while(size_sort--)
    {
        LeftSort(Game , size);
    }
    for(int counter2 = 0 ; counter2 < size - 1 ; counter2++)
    {
        for(int counter1 = 0 ; counter1 < size ; counter1++)
        {
            if(Game[counter1][counter2] == Game[counter1][counter2 + 1])
            {
                score += *(*(Game + counter1) + counter2);
                *(*(Game + counter1) + counter2) *= 2;
                *(*(Game + counter1) + counter2 + 1) = 0;
            }
        }
    }
    size_sort = size - 1;
    while(size_sort--)
    {
        LeftSort(Game , size);
    }
    for(int counter1 = size - 1 ; counter1 >= 0 ; counter1--)
    {
        if(flag_null == true)
        {
            break;
        }
        for(int counter2 = 0 ; counter2 < size ; counter2++)
        {
            if(*(*(Game + counter1) + counter2) == 0)
            {
                *(*(Game + counter1) + counter2) = RandomNumber();
                flag_null = true;
                break;
            }
        }
    }
}
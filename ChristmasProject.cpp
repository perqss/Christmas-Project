#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

void Print(string arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < arr[i].size(); j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
}

void Tree(int width, string arr[], int length, int size)
{
    int n = 0;
    int counter = 1;
    for(int i = 0; i < length + 1; i++)
    {
        for(int j = 0; j < length + counter; j++)
        {
            if(j > length - counter) arr[n] += '.';
            else arr[n] += ' ';
        }
        counter++;
        n++;
    }
    for(int i = n; i < size - 1; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == width / 2) arr[n] += '|';
            else arr[n] += ' ';
        }
        n++;
    }
    for(int i = 0; i < width; i++)
    {
        if(i >= width / 3 && i < width - (width / 3)) arr[n] += 'Z';
        else arr[n] += ' ';
    }
    Print(arr, size);
}

void Baubles(string arr[], int n, mt19937& gen, int size)
{
    uniform_int_distribution<> row(0, n);
    int randomRow = row(gen);
    int firstDotPos = 0;
    int lastDotPos = 0;
    int randomColumn;
    int isThereADot = 0;
    for(int i = 0; i < arr[randomRow].size(); i++)
    {
        if(arr[randomRow][i] == '.')
        {
            firstDotPos = i;
            while(arr[randomRow][i] == '.') i++;
            lastDotPos = i - 1;
            i--;
            isThereADot = 1;
        }
    }
    if(isThereADot == 1)
    {
        uniform_int_distribution<> column(firstDotPos, lastDotPos);
        randomColumn = column(gen);
        arr[randomRow][randomColumn] = 'O';
        Print(arr, size);
        cout << endl;
    }
    else
    {
        Print(arr, size);
        cout << endl;
    }
}

int DidYouWin(string arr[], int length)
{
    int result;
    int dotsCounter = 0;
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < arr[i].size(); j++)
        {   
            if(arr[i][j] == '.') dotsCounter++;
        }
    }
    if(dotsCounter == 0) result = 1;
    else result = 0;
    return result;
}

void BaubleMoving(string arr[], int length, int pos, int size, int* counter, int* fail)
{
    char move;
    int row = 0;
    int column = pos;
    char sign;
    int firstSignPos = 0;
    if(arr[row][column] == '.') sign = '.';
    else if(arr[row][column] == 'O')
    {
        sign = 'O';
        *fail = 1;
        return;
    }
    arr[0][pos] = '0';
    Print(arr, size);
    while(1)
    {
        cin >> move;
        *counter = *counter + 1;
        if(cin.fail())
        {
            cout << "Please enter w, a, s or d" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if(move == 'w')
        {  
            for(int i = 0; i < arr[row].size(); i++)
            {
                if(arr[row][i] == '.' || arr[row][i] == 'O' || arr[row][i] == '0')
                {
                    firstSignPos = i;
                    break;
                }
            }
            if(row > 0)
            {
                if(column < arr[row].size() - 1 && column > firstSignPos)
                {
                    cout << arr[row].size() << endl;
                    arr[row][column] = sign;
                    if(arr[row - 1][column] == '.') sign = '.';
                    else if(arr[row - 1][column] == '0') sign = 'O';
                    else if(arr[row - 1][column] == 'O')
                    {
                        sign = 'O';
                        *fail = 1;
                        break;
                    }
                    arr[row - 1][column] = '0';
                    row--;
                    Print(arr, size);
                }
                else cout <<"You cannot go in that direction!" << endl;
            }
            else cout <<"You cannot go in that direction!" << endl;
        }
        else if(move == 's')
        {
            if(row < length)
            {
                arr[row][column] = sign;
                if(arr[row + 1][column] == '.') sign = '.';
                else if(arr[row + 1][column] == '0') sign = 'O';
                else if(arr[row + 1][column] == 'O')
                {
                    sign = 'O';
                    *fail = 1;
                    break;
                }
                arr[row + 1][column] = '0';
                row++;
                Print(arr, size);
            }
            else cout <<"You cannot go in that direction!" << endl;
        }
        else if(move == 'd')
        {
            if(column + 1 < arr[row].size())
            {
                arr[row][column] = sign;
                if(arr[row][column + 1] == '.') sign = '.';
                else if(arr[row][column + 1] == '0') sign = 'O';
                else if(arr[row][column + 1] == 'O')
                {
                    sign = 'O';
                    *fail = 1;
                    break;
                }
                arr[row][column + 1] = '0';
                column++;
                Print(arr, size);
            }
            else cout <<"You cannot go in that direction!" << endl;
        }
        else if(move == 'a')
        {
            if(row == length)
            {
                if(column - 1 >= 0)
                {
                    arr[row][column] = sign;
                    if(arr[row][column - 1] == '.') sign = '.';
                    else if(arr[row][column - 1] == '0') sign = 'O';
                    else if(arr[row][column - 1] == 'O')
                    {
                        sign = 'O';
                        *fail = 1;
                        break;
                    }
                    arr[row][column - 1] = '0';
                    column--;
                    Print(arr, size);
                }
                else cout <<"You cannot go in that direction!" << endl;
            }
            else
            {
                if(arr[row][column - 1] != ' ')
                {
                    arr[row][column] = sign;
                    if(arr[row][column - 1] == '.') sign = '.';
                    else if(arr[row][column - 1] == '0') sign = 'O';
                    else if(arr[row][column - 1] == 'O')
                    {
                        sign = 'O';
                        *fail = 1;
                        break;
                    }
                    arr[row][column - 1] = '0';
                    column--;
                    Print(arr, size);
                }
                else cout <<"You cannot go in that direction!" << endl;
            }
        }
        else if(move == 'e')
        {
            arr[row][column] = 'O';
            cout << "NEW SESSION" << endl;
            cout << endl;
            break;
        }
    }
}

void Sort(string name, int* bestScore)
{
    ifstream in(name);
    ifstream in1(name);
    int n = 0;
    int i = 0;
    int score;
    while(in >> score) n++;
    int* leaderboard = new int[n];
    while(in1 >> score)
    {
        leaderboard[i] = score;
        i++;
    }
    sort(leaderboard, leaderboard + n);
    ofstream out(name);
    cout << endl;
    i = 0;
    while(i < n)
    {
        out << leaderboard[i] << endl;
        i++;
    }
    *bestScore = leaderboard[0];
    in.close();
    in1.close();
    out.close();
    delete[] leaderboard;
}

int main()
{
    int width; // width has to be an odd number bigger than 1
    int length;
    int choice;
    int size;
    int firstDotPos = 0;
    char whatever;
    int counter = 0;
    int bestScore = 0;
    int fail = 0;
    string fileNameGame2;
    string fileNameGame1;
    mt19937 gen(time(0));
    cout << "Enter the width of the tree" << endl;
    cin >> width;
    fileNameGame2 = to_string(width);
    fileNameGame1 = fileNameGame2 + "_1.txt";
    fileNameGame2 += "_2.txt";
    if(width % 2 == 0) width++;
    length = width / 2;
    size = length + 1 + width / 3;
    string* arr = new string[size];
    Tree(width, arr, length, size);
    cout << "Choose how to decorate your tree" << endl;
    cout << "1) baubles generated in random places on a tree" << endl << "2) a minigame where you need to palce all baubles on a christmas tree to win" << endl;
    cin >> choice;
    if(choice == 1)
    {
        while(1)
        {
            Baubles(arr, width / 2, gen, size);
            counter++;
            if(DidYouWin(arr, length + 1) == 1)
            {
                cout << "Congratulations, you've won! It took " << counter << " draws" << endl;
                ofstream out1;
                out1.open(fileNameGame1, ios_base::app);
                out1 << counter << endl;
                Sort(fileNameGame1, &bestScore);
                if(counter <= bestScore)
                {
                    cout << "You have the best score so far" << endl;
                }
                else if(counter > bestScore)
                {
                    cout << "Your score isn't the best so far" << endl;
                }
                out1.close();
                break;
            }
        }
    }
    else if(choice == 2)
    {
        for(int i = 0; i < arr[0].size(); i++)
        {
            if(arr[0][i] == '.') firstDotPos = i;
        }
        //Instructions();
        while(1)
        {
            BaubleMoving(arr, length, firstDotPos, size, &counter, &fail);
            if(fail == 1)
            {
                cout << "You've lost. Try again." << endl;
                break;
            }
            if(DidYouWin(arr, length + 1) == 1)
            {
                cout << "Congratulations, you've won! It took you " << counter << " moves" << endl;
                ofstream out2;
                out2.open(fileNameGame2, ios_base::app);
                out2 << counter << endl;
                Sort(fileNameGame2, &bestScore);
                if(counter <= bestScore)
                {
                    cout << "You have the best score so far" << endl;
                }
                else if(counter > bestScore)
                {
                    cout << "Your score isn't the best so far" << endl;
                }
                out2.close();
                break;
            }
        }
    }
    delete[] arr;
    cout << "Press any key to leave the application." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    return 0;
}
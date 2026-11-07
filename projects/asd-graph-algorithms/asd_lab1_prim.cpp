#include <iostream>
using namespace std;

int main()
{
    unsigned int Array[6][6] = { {0, 5, 0, 1, 3, 0}, {5, 0, 1, 0, 7, 0}, {0, 1, 0, 0, 5, 4}, {1, 0, 0, 0, 2, 0}, {3, 7, 5, 2, 0, 10}, {0, 0, 4, 0, 10, 0} };

    for (unsigned int i = 0; i < 6; i++)
    {
        for (unsigned int j = 0; j < 6; j++)
        {
            cout << Array[i][j] << "\t";
        }
        cout << "\n";
    }

    bool BoolArray[6] = { true, false, false, false, false, false };
    unsigned int wayArray[5][3] = { {0} };

    unsigned int min;

    for (unsigned int iter = 0; iter < 5; iter++)
    {
        min = 0xffffffff;
        for (unsigned int i = 0; i < 6; i++)
        {
            if (BoolArray[i])
            {
                for (unsigned int j = 0; j < 6; j++)
                {
                    if (!BoolArray[j] && Array[i][j] < min && Array[i][j] != 0)
                    {
                        min = Array[i][j];
                        wayArray[iter][0] = i;
                        wayArray[iter][1] = j;
                    }
                }
            }
        }

        BoolArray[wayArray[iter][1]] = true;
        wayArray[iter][2] = min;
    }
    unsigned int weight = 0;
    cout << "Number\t from\t where\t weight\n";
    for (unsigned int i = 0; i < 5; i++)
    {
        cout << i + 1 << " \t " << wayArray[i][0] + 1 << "\t " << wayArray[i][1] + 1 << "\t " << wayArray[i][2] << " \n";
        weight += wayArray[i][2];
    }
    cout << "Weight: " << weight << "\n";
}
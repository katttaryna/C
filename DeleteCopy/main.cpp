#include <iostream>

using namespace std;

void inputMassive(string* massive,int size)
{
    cout << "Enter words without spaces:\n";
    for (int i = 0; i < size; i++) {
        string word;
        cin >> word;
        cin.clear();
        massive[i] = word;
    }
}

void deleteCopy(string* massive, const string word,int size) {
    bool flag = true;
    string* helpMassive = new string[size];
    int counter=0;
    for (int i = 0; i < size; i++)
    {
        if (massive[i] == word)
        {
            if (flag)
            {
                helpMassive[counter] = massive[i];
                ++counter;
                flag = false;
            }
        }
        else
        {
            helpMassive[counter] = massive[i];
            ++counter;
        }
    }
    if (!flag)
    {
        for(int i=0;i<size;i++)
            massive[i].clear();
        for (int i = 0; i < counter; i++)
            massive[i] = helpMassive[i];
    }
    else
        cout << "The " << word << " in this massive is not repeated.\n";
    delete[] helpMassive;
}

void print(const string* massive, int size)
{
    int i = 0;
    for(int i=0;i<size;i++)
    {
        if (massive[i] == "")
            break;
        else
            cout << massive[i] << " ";
    }
    cout << "\n";
}


template <typename T>
int countMatch(const T* massive, int size, const T* sequence, int seqSize) {
    int counter = 0;
    T st = sequence[seqSize - 1];
    for(int i=seqSize-1;i<size;i++)
        if (st == massive[i])
        {
            bool flag = true;
            for(int j=i,k=seqSize-1;k>=0;k--,j--)
                if (massive[j] != sequence[k])
                {
                    flag = false;
                    break;
                }
            if (flag)
                ++counter;
        }
    return counter;
}

template <typename T>
void inputMassive(T* massive, const int size) {
    cout << "Enter values:";
    for (int i = 0; i < size; i++) {
        T element;
        cin >> element;
        massive[i] = element;
    }
}


int menu(){
    cout << "\nEnter the number of operation :\n"
            "1. letters\n"
            "2. numbers\n"
            "0. exit\n";
    int num;
    cin >> num;
    return num;
}
int main() {
    const int size = 5;
    while(1) {

        switch (menu()) {
            case 1 :
                //string
            {
                string words[size];
                inputMassive(words, size);
                cout << "Enter word without spaces:\n";
                string word;
                cin >> word;
                cin.clear();
                deleteCopy(words, word, size);
                cout << "Result massive:";
                print(words, size);
                break;
            }
            case 2 : {
                //number
                int massive[size];
                inputMassive(massive, size);
                cout << "Enter sequence size.";
                int seqSize;
                cin >> seqSize;
                int *sequence = new int[seqSize];
                inputMassive(sequence, seqSize);
                int counter = countMatch(massive, size, sequence, seqSize);
                cout << "There are " << counter << " same subsequences";
                delete[] sequence;
                break;
            }
            case 0 :
                return 0;

        }
    }
    return 0;
}

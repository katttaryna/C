
#include <iostream>
#include <limits>
#include <string>
#include <utility>

using namespace std;

#define N 2
class ExceptionClass{
    string error;
public:
    explicit ExceptionClass(string message) : error(move(message)){};
    ~ExceptionClass() = default;
    void wrongValue();
    void problem();
};

class Matrix {
    int matrix[N][N];
public:
    Matrix();
    explicit Matrix(int array[N][N]);
    ~Matrix();
    void output();
    void input();
    void search();
    void init(Matrix &array);
};

void myTerm();
void myUn();



void ExceptionClass::problem() {
    cout << error << endl;
}

void ExceptionClass::wrongValue() {
    cin.clear();
    cin.ignore(100, '\n');
}

Matrix::Matrix() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = 0;
        }
    }
}
Matrix::Matrix(int array[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = array[i][j];
        }
    }
}
Matrix::~Matrix() {}

void Matrix::output(){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "\t" << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Matrix::input() {
    cout << "Enter matrix" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
            if(cin.fail()){
                throw ExceptionClass("Incorrect input");
            }
        }
    }
}

void Matrix::search() {
    cout << "Enter number:";
    int numb;
    int flag = 0;
    cin >> numb;
    if (cin.fail())
        throw ExceptionClass("Incorrect input");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (numb == matrix[i][j]) {
                cout << "matrix[" << i << "][" << i << "]= " << numb << endl;
                flag = 1;
            }
        }
    }
    if(flag == 0){
        cout << "This number is not in the matrix" << endl;
    }
}

void Matrix::init(Matrix& array) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = array.matrix[i][j];
        }
    }
}

void myTerm(){
    cout << "terminate" << endl;
    exit(1000);
}

void myUn(){
    cout <<"unexpected" << endl;
    throw;
}


int main() {
    set_terminate(myTerm);
    set_unexpected(myUn);

    int matrix[N][N] = {{1, 2}, {1, 3}};
    Matrix mt(matrix), mt1, mt2;
    while (true){
        try {
            mt1.input();
            break;
        } catch (ExceptionClass &ex) {
            ex.problem();
            ex.wrongValue();
        }
    }
    mt2.init(mt1);

    mt.output();
    cout << endl;
    mt1.output();
    cout << endl;
    mt2.output();
    cout << endl;

    while (true){
        try {
            mt2.search();
            break;
        } catch (ExceptionClass &ex) {
            ex.problem();
            ex.wrongValue();
        }
    }
    return 0;
}
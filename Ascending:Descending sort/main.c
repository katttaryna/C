#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void DisplayOnTheScreen(int n, int m, int*** matrix, int n1);
void SortInAscendingOrder(int** matrix, int n, int j);
void SortInDescendingOrder(int** matrix, int n, int j);
int GetIntegerValue();
int main()
{
    int n1, m, n;
    int*** matrix;

    printf("Enter a number of matrix: \n");
    n1 = GetIntegerValue();
    printf("Enter a number of columns: \n");
    m = GetIntegerValue();
    printf("Enter a number of strings: \n");
    n = GetIntegerValue();

    matrix = (int***)calloc(n1, sizeof(int**));
    for (int k = 0; k < n1; k++)
    {

        printf("Number of matrix is: %d\n", (k + 1));
        matrix[k] = (int**)calloc(n, sizeof(int*));
        printf("Enter values: \n");
        for (int i = 0; i < n; i++)
        {
            matrix[k][i] = (int*)calloc(m, sizeof(int));
            for (int j = 0; j < m; j++)
            {
                matrix[k][i][j] = GetIntegerValue();
                rewind(stdin);
            }
        }
    }
    DisplayOnTheScreen(n, m, matrix, n1);

    for (int k = 0; k < n1; k++)
    {

        for (int i = 0; i < n; i++)
        {

            for (int j = 0; j < m; j++)
            {
                if (j % 2 != 0)
                {


                    void(*function)(int**, int, int);
                    function = SortInDescendingOrder;
                    function(matrix[k], n, j);

                }
                else
                {

                    void(*function)(int**, int, int);
                    function = SortInAscendingOrder;
                    function(matrix[k], n, j);
                }


            }
        }
    }

    printf("New matrixs are: \n");
    DisplayOnTheScreen(n, m, matrix, n1);

    for (int k = 0; k < n1; k++)
    {
        for (int i = 0; i < n; i++)
        {
            free(matrix[k][i]);
        }
    }
    for (int k = 0; k < n1; k++)
    {
        free(matrix[k]);
    }
    free(matrix);
}

int GetIntegerValue()
{
    char c;
    int n;
    while ((scanf("%d%c", &n, &c) != 2 || c != '\n'))
    {
        printf("You entered incorrect value. Please try again: \n");
        rewind(stdin);
    }

    return n;
}
void DisplayOnTheScreen(int n, int m, int*** matrix, int n1)
{
    for (int k = 0; k < n1; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%5d", matrix[k][i][j]);
            }

            printf("\n");

        }
        printf("\n\n");
    }
}

void  SortInAscendingOrder(int** matrix, int n, int j)
{
    int temp = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int l = 0; l < n - i - 1; l++)
        {
            if (matrix[l][j] > matrix[l + 1][j])
            {
                temp = matrix[l][j];
                matrix[l][j] = matrix[l + 1][j];
                matrix[l + 1][j] = temp;
            }

        }

    }

}

void SortInDescendingOrder(int** matrix, int n, int j)
{
    int temp = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int l = 0; l < n - i - 1; l++)
        {

            if (matrix[l][j] < matrix[l + 1][j])
            {
                temp = matrix[l][j];
                matrix[l][j] = matrix[l + 1][j];
                matrix[l + 1][j] = temp;
            }

        }
    }
}
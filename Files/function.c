#include "header.h"
#include <stdio.h>
#include <string.h>


void actionsWithATextFile(char *str){
    strcat(str, ".txt");
    FILE *file = fopen(str,"w+");
    int choose;
    int flg = 0;
    if (file) {
        do {
            if (flg == 0) {
                inputFile(str);
                flg++;
                continue;
            } else {
                printf("1. Output\n"
                       "2. Search min word\n"
                       "3. Replace first and second words(enter twice)\n"
                       "0. Exit\n");
                choose = inputSave(0, 3);
            }
            if (choose == 0) {
                fclose(file);
                break ;
            }
            switch (choose) {
                case 1:
                    outputFile(str);
                    break;
                case 2:
                    findMinWordFile(str);
                    break;
                case 3:
                    outputFile(str);
                    replaceFirstAndSecondWords(str);
                    break;
                default:;
            }
        }while (1);
    }
    else {
        printf("No access to the file\n");
    }
    fclose(file);
}

void inputFile(char *str) {

    FILE* file = fopen(str , "w");
    confirmInput();
    int input=inputSave(1,2);
    switch(input) {
        case 1:
            break;
        case 2 :
            return ;
        default:
            printf("Error. Incorrect value!\n");
    }
    printf("Input string into file\n");
    char letter;
    int ind = 0;

    while (ind<3)
    {
        scanf("%c", &letter);
        if(letter=='\n') ind++;
        fprintf(file, "%c", letter);
    }
    fclose(file);
}
int inputSave(int floor, int ceil) {
    int number;
    int ind;
    int flg = 0;
    do {
        if (flg > 0) {
            printf("Incorrect number\n");
        }
        ind = 0;
        scanf("%d", &number);
        scanf("%*[^\n]%n", &ind);
        flg++;
    }while (ind > 0 || number < floor || number > ceil);
    return number;
}

void outputFile (char *str) {
    FILE* file = fopen(str, "r");
    rewind(file);
    char letter;
    while (!feof(file))
    {
        fscanf(file, "%c", &letter);
        printf("%c", letter);
    }
    fclose(file);
}

void findMinWordFile(char *str) {
    FILE *file = fopen(str, "r");
    rewind(file);
    fpos_t startPositionMinWord;
    fpos_t startPositionForMinimal;
    int min = 666;
    int counter=0;
    char letter;
    while (!feof(file))
    {
       fscanf(file, "%c", &letter);
        if((letter != ' ') && (letter != '\n'))
        {
            if(counter==0){
            fgetpos(file, &startPositionMinWord);
           }
            counter++;

        } else{
            if (counter < min && counter !=0) {
                min = counter;
                counter = 0;
                startPositionForMinimal = startPositionMinWord;

            }
        }
    }
    printf("Min word in text: \n");
    fseek(file,startPositionForMinimal-1 ,SEEK_SET  );
    letter =0;
    while((letter  != ' ') && (letter  != '\n'))
    {
        fscanf(file, "%c", &letter);
        printf("%c", letter);
    }
    printf("\n");
    fclose(file);
}

void reverse(char *str,int left, int right ){
    FILE *file = fopen(str, "r+");
    char a,b;
   // char *str;
    fpos_t n, k;
    rewind(file);
    while (left < right){
        fsetpos(file, &left);
        fscanf(file, "%c", &a);
        fsetpos(file, &k);
        fscanf(file, "%c", &b);
        fsetpos(file, &n);
        fprintf(file, "&c", b);
        fsetpos(file, &k);
        fprintf(file, "%c", a);
        n++;k--;

//        fseek(file, left, SEEK_SET);
//        a = (char)fgetc(file);
//        fseek(file, right-1, SEEK_SET);
//        b = (char)fgetc(file);
//        fseek(file, right-1, SEEK_SET);
//        fputc(a, file);
//        fseek(file, left, SEEK_SET);
//        fputc(b, file);
//        left++;
//        right--;
    }
    fclose(file);

}
void replaceFirstAndSecondWords(char *str) {
    FILE *file = fopen(str, "r+");
    rewind(file);
    //printf("dodik1");
    int l1, l3, kol = 0;
	char s;
    fpos_t n1, k1,n2, k2 ;
	l1 = 1;
	l3= 2 ;
//    printf("dodik2");
	//scanf("%d%d", &l1, &l3);
	while (1)                                  // бесконечный цикл
	{
		while (!feof(file))                       // цикл пока на конец файла
		{                                      // пропуск пробелов в файле                   // позиция считываемого символа
           // printf("pos of first symbol:\n");
		    fscanf(file, "%c", &s);
			if (s != ' ') break;               // выход из цикла если не пробел
		}
		if (feof(file)) break;                    // выход из бесконечного цикла если доcтигли EOF
		kol++;                                 // найдено новое слово
		if (kol == l1) fgetpos(file, &n1);      // найдено начало первого слова
		else if (kol == l3) fgetpos(file, &n2); // найдено начало второго слова
		while (!feof(file) && (s != ' ') && (s != '\n')) // движение по буквам текущего слова в файле
	       fscanf(file, "%c", &s);
		if (kol == l1) fgetpos(file, &k1);      // найден конец первого слова
		else if (kol == l3) fgetpos(file, &k2); // найден конец второго слова
	}
    //printf("dodik3");
	n1--; k1-=2;          // корректировка начала и конца первого слова
	n2--;                 //  ........................... второго слова
	if (kol== l3 ) k2-=1; // второе слово последнее в строке и за EOF УТПФ не перемещается                              второго
	else k2 -= 2;
   // printf("dodik4");
    reverse(str, n1,n2);
//
//    reverse(file, n1, k1);
//    reverse(file, n2, k2);
//    reverse(file,n1 , k2);
//    printf("\nIf you want to see the result click OUTPUT\n");
    fclose(file);
}

void actionsWithABinFile( char *str){
    strcat(str, ".bin");
    FILE *file=fopen(str, "wb+");
    int choose;
    int flg = 0;
    if (file) {
        do {
            if (flg == 0) {
                inputBinFile(file,str);
                flg++;
                continue;
            } else {
                printf("1. Output\n"
                       "2. Number of negative numbers\n"
                       "3. Replace \n"
                       "0. Exit\n");
                choose = inputSave(0, 3);
            }
            if (choose == 0) {
                fclose(file);
                break ;
            }
            switch (choose) {
                case 1:
                    outputBinFile(file,str);
                    break;
                case 2:
                    numberOfNegativeNumbers(file,str);
                    break;
                case 3:
                    //заменить отрицательные элементы значением максимального элемента
                    replace(file, str);
                    break;
                default:;
            }
        }while (1);
    }
    else {
        printf("No access to the file\n");
    }
    fclose(file);
}

void inputBinFile(FILE *file, char *str) {
    fopen(str, "w+b");
    int numb,n;
    confirmInput();
    int input=inputSave(1,2);
    switch(input) {
        case 1:
            break;
        case 2 :
            return ;
        default:
            printf("Error. Incorrect value!\n");
    }
    printf("How many numbers do you want to enter:\n");
    scanf("%d", &n);
    printf("Enter numbers:\n");
    for (int i = 0; i < n; i++)
    {
        while (!scanf("%d", &numb))
        {
            rewind(stdin);
            printf("Incorrect value. Try again... ");
        }
        fwrite(&numb, sizeof(int), 1, file);
    }
    printf("\n");
    fclose(file);
}

void outputBinFile(FILE *file, char *str)
{
    fopen(str, "rb");
    int numb;
    do
    {
        fread(&numb, sizeof(int), 1, file);
        if (feof(file))  break;
        printf("%4d", numb);
    }while (1);
    printf("\n");
    fclose(file);
}

void numberOfNegativeNumbers(FILE *file, char *str){
    fopen(str, "rb");
    int numb;
    int count = 0;
    while(!feof(file)){
        fread(&numb, sizeof(int), 1, file);
        if(numb < 0){
            count++;
            continue;
        }
    }
    printf("%d", count);
    printf("\n\n");
    fclose(file);
}
void replace(FILE *file, char *str){
    fopen(str, "rb");
    int max , numb = 0;
    int min = 0 ;
    for (int i = 0; i < numb; i++)
    {
        fread(&numb, sizeof(int), 1, file);
        if (i == 0){
        max = numb;
        min= numb;
        continue;
        }
        if (min> numb)
            min = numb;
        if( max < numb)
            max = numb;
    }
    int temp ;


    fclose(file);
}

void confirmInput(){
    printf("Do you want to make an input?\n"
           "1. Yes\n"
           "2. No\n");
}
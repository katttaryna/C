void reverse (char*, int, int);
int main () {

    char* string;
    int length;

    printf("Enter length\n");
    scanf("%d", &length);

    string = (char*)malloc((length + 1) * sizeof(char));

    printf("Enter your string\n");
    rewind(stdin);
    fgets(string, length, stdin);
    printf("Your string\n");
    int firstSimbol, endSimbol;
    int i = 0;
    while (string[i]) {
        while (string[i] == ' ') { // проход каждых пробелов с строке. После этого цикла индекс стоит на символе отличен от проблеа (первый символ слова)
            i++;
        }
        firstSimbol = i;
        while (string[i] != ' ' && string[i] != '\0') { // проход по слову. После цикла индекс стоит на пробеле
            i++;
        }
        endSimbol = i - 1;
        reverse(string, firstSimbol, endSimbol); // после каждого прохода слова вызываю функцию
    }
    puts(string);

    return 0;
}
void reverse (char* string, int first, int end){
    int c;
    if (first > end) {
        return ;
    }
    c = string[first];
    string[first] = string[end];
    string[end] = c;
    first++;
    end--;
    reverse(string, first, end);
}
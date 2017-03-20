#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct one_string {
    int str_length;
    char * str;
} one_string;

typedef struct array_of_strings {
    int number;
    one_string * item;
} array_of_strings;

char* getstr() //ввод строки
{
    char *ptr = (char*)malloc(sizeof(char));
    *ptr = '\0';
    char buf[81];
    int n, len = 0;
    do
    {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            free(ptr);
            ptr = NULL;
            continue;
        } else
        if(n == 0)
            scanf("%*c");
        else
        {
            len += strlen(buf);
            ptr = (char*)realloc(ptr,len + 1);
            strcat(ptr, buf);
        }
    } while(n > 0);
    return ptr;
}

void create_list (array_of_strings *arr, char *s, int n) { //создание списка со строками
    arr->number = n;
    char *temp;
    if (n == 1) {
            arr->item = (one_string *)malloc(sizeof(one_string));
    } else {
            arr->item = (one_string *)realloc(arr->item, n*sizeof(one_string));
    }
    (arr->item + n - 1)->str_length = strlen(s);
    temp = (char *)malloc(strlen(s)*sizeof(char));
    (arr->item + n - 1)->str = temp;
    strcpy(temp, s);
}

void edit_list (array_of_strings *arr) { //обработка списка
    int i, count_even, count_numbers, new_len;
    char * temp;
    char * newstr;
    for (i = 0; i < arr->number; i++) {
        temp = (arr->item + i)->str;
        newstr = (char*)malloc(sizeof(char));
        *newstr = '\0';
        new_len = 0;
        while (*temp != '\0') {
            while ((*temp == ' ') || (*temp == '\t')) temp++;
            if (*temp == '\n') continue;
            count_even = 0, count_numbers = 0, new_len = 0;
            while ((*temp != ' ') && (*temp != '\t') && (*temp != '\0')) {
                count_numbers++;
                if ((*temp) % 2 == 0) count_even++;
                temp++;
            }
            if (count_even == count_numbers) {
                temp -= count_even;
                new_len += count_even;
                newstr = (char *) realloc(newstr, new_len + 2);
                strncat(newstr, temp, sizeof(char) * count_even);
                strcat(newstr, " ");
                temp += count_even;
            }
        }
        *(newstr + strlen(newstr) - 1) = '\0';
        if (*newstr == '\0') newstr = "Dannaya stroka ne soderzhit nuzhnyh chisel!\n";
        (arr->item + i)->str = newstr;
        (arr->item + i)->str_length = strlen(newstr);
    }
}

void erase(array_of_strings * arr) { //очистка пам€ти
    for (int i = 0; i < arr->number; i++) {
        if ((arr->item + i)->str) free((arr->item + i)->str);
    }
    free(arr->item);
}

void print(array_of_strings * arr) { //вывод списка на экран
    int i;
    char * temp;
    for (i = 0; i < arr->number; i++) {
        temp = (arr->item + i)->str;
        printf("Stroka #%d: %s\n", i + 1, temp);
    }
}

int main()
{
    array_of_strings arr;
    char *s = NULL;
    int n = 0;
    printf("Vvedite stroki:\n");
    while ((s = getstr())) {
        create_list(&arr, s, ++n);
        free(s);
    }
    if (n == 0) {
        printf("Programma zavershena bez vvoda strok!\n");
        return 0;
    }
    printf("Ishodnye stroki:\n");
    print(&arr);
    printf("\nStroki posle preobrazovaniy:\n");
    edit_list(&arr);
    print(&arr);
    erase(&arr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct array_of_strings { //структура списка
    char character;
    struct array_of_strings * next;
} array_of_strings;

void delete_list(array_of_strings *); //образ функции (так как она используется в функции создания, но описывается позже)

array_of_strings * create_list() { //создание списка
    //создрается массив символов произвольной длины (в данном случае 81)
    //пока scanf возвращает положительное число (т.е. символы, кроме \n вводятся), вносим посимвольно из буфера в список символы
    //в случае n<0 (ошибка ввода) происходит очистка списка
    //если встречается \n (перенос строки) (т.е. n=0), то происходит его ввод без записи в память
    char buf[81], *str;
    array_of_strings *last = (array_of_strings *)malloc(sizeof(array_of_strings));
    array_of_strings *head;
    head = last;
    int n;
    printf("Vvedite simvoly cherez probel ili Tab:\n");
    printf("(V konce vvoda nazhmite ENTER)\n");
    do {
        n = scanf("%80[^\n]", buf);
        if (n > 0) {
            for (str = buf; *str != '\0'; ++str) {
                last->character = *str;
                last->next = (array_of_strings *)malloc(sizeof(array_of_strings));
                last = last->next;
            }
            last->character = '\n';
            last->next = NULL;
            continue;
        }
        if (n < 0) {
            delete_list(head);
            head->next = NULL;
        }
        else scanf("%*c");
    } while (n > 0);

    last = head;
    return last;
}


void edit_list (array_of_strings *arr) { //обработка списка
    //из непрерывной последовательности символов выделяются строки, которые являются числами
    //для каждого числа считается общее кол-во цифр и кол-во чётных цифр
    //если эти значения не совпадает, ставим в начало числа символ n (или любой произв. буквенный) для удобства вывода
    //иначе оставляем число без изменений
    int count_even, count_numbers;
    array_of_strings * p;
    p = arr;
    do {
        while (p->character == ' ' || p->character == '\t' || p->character == '\n') {
            if (p->next != NULL) p = p->next;
        }
        count_even = 0;
        count_numbers = 0;
        array_of_strings *x = p;
        while (p->character != ' ' && p->character != '\t' && p->character != '\n') {
            if (p->character % 2 == 0) {
                count_even++;
            }
            count_numbers++;
            p = p->next;
        }
        array_of_strings *y = p;
        if (count_numbers != count_even) {
            p = x;
            p->character = 'n';
            p = y;
        }
    } while (p != NULL && p->next != NULL);
}

void delete_list(array_of_strings * head){ //удаление списка
  if (head != NULL){
    delete_list(head->next);
    free(head);
  }
}

void print_list_as_char_sequence (array_of_strings * arr, int flag) { //вывод списка на экран в виде последовательности символов
    array_of_strings *p = arr;
    if (!flag) {
        for (p = arr; p != NULL; p = p->next) {
            printf("%c", p->character);
        }
        printf("\n");
    } else {
        int x = 1;
        do {
            if (p->character == 'n') {
                x = 0;
            }
            if (x == 1) {
                printf("%c", p->character);
            }
            if (p->character == ' ' || p->character == '\t' || p->character == '\n') {
                x = 1;
            }
            p = p->next;
        } while (p != NULL);
    }
}

/*void print_list(array_of_strings * arr) { //вывод списка на экран
    //из непрерывной последовательности символов выделяются строки, которые являются числами
    //если встречаем в начале числа букву n (или любую другую, которую мы добавили в предыдущей функции), то выводим, что число не подходит
    //иначе выводим число
    array_of_strings * p;
    p = arr;
    int i = 0;
    int x;
    do {
        while (p->character == ' ' || p->character == '\t' || p->character == '\n') {
            if (p->next != NULL) p = p->next;
        }
        x = 0;
        if (p->character == 'n') {
            //printf("Dannaya stroka ne sootvetstvuet usloviyu!");
            x = 1;
        }
        i++;
        if (!x) printf("Stroka #%d: ", i);
        while (p->character != ' ' && p->character != '\t' && p->character != '\n') {
                if (!x) printf("%c", p->character);
                p = p->next;
            }
        if (!x) printf("\n");
    } while (p != NULL && p->next != NULL);
}*/

int main()
{
    array_of_strings * head;
    array_of_strings * arr;
    while ((arr = create_list())) {
        head = arr;
        printf("\nIshodnye stroki:\n");
        print_list_as_char_sequence(arr, 0);
        printf("\nStroki posle preobrazovaniy:\n");
        edit_list(arr);
        arr = head;
        print_list_as_char_sequence(arr, 1);
        printf("\n\n");
        delete_list(arr);
    }
    return 0;
}

// Лабораторная работа №4
// Выполнили студенты группы м3о-219Бк-20 Бокарев, Катвалян
// 22/11/21

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef int Priority;
typedef struct Node Node;

struct Node {
    Priority data;
    Node* next;
};

void print(Node* list);
void push(Node** plist, Priority d);
int is_empty(Node* list);
Priority pop(Node** list);
Priority deleteLastNode(Node** plist);
int* searchByKey(Node* list, int key);
void deleteFirstByKey(Node** plist, int key);
void insertNodeAtMiddle(Node** plist, int data, int position);
void insertNodeAtEnd(Node** plist, int data);

int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");
    
    Node* list = NULL;
    push(&list, 0); // добавит элемент в начало
    Priority test[] = { 1, 2, 5, 10, 30, 40, 80 };

    Node* p;
    Priority d;
    int x = 0;
    int value = 0;
    int index = 0;
    int priority = 0;
    int maxpriority = 0;
    
    int* Arr;
    do
    {
        printf("1. Инициализация очереди 9 элементами\n");
        printf("2. Добавление в конец очереди\n");
        printf("3. Добавление в очередь по убывающему приоритету\n");
        printf("4. Удаление из начала очереди\n");
        printf("5. Удаление из очереди по заданному приоритету\n");
        printf("6. Очистка очереди\n");
        printf("7. Вывод на экран элементов очереди с их приоритетами и индексами\n");
        printf("8. Удалить элемент с первым максимальным приоритетом\n");
        printf("0. Выйти\n");
        printf("\nНомер операции > "); scanf_s("%d", &x);
        switch (x)
        {
        case 1: // инициализация очереди
            for (size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)//инициализация списка
            {
                insertNodeAtEnd(&list, test[i]); // добавит элемент в конец очереди

            }
            
            print(list);
            break;
        case 2: //Добавление в конец очереди
            printf("Значение > "); scanf_s("%d", &value);
            insertNodeAtEnd(&list, value); // добавит элемент в конец очереди
            print(list);
            break;
        case 3: //Добавление в очередь по убывающему приоритету
            index = 0;
            printf("Значение приоритета > "); scanf_s("%d", &value);
            priority = value;
            p = list;
            value = p->data;
            
            while(p != NULL && p->data < priority) {
                index++;
                p = p->next;
            }
            if (value > priority)
                push(&list, priority);
            else 
                insertNodeAtMiddle(&list, priority, ++index);
            print(list);
            break;

        case 4: // Удаление из очереди из начала списка
            if (!is_empty(list)) {
                Priority d = pop(&list);
                printf("Удален элемент с приоритетом %d\n", d);
            }
            print(list);
            break;
        case 5: // Удаление из очереди по заданному приоритету
            printf("Значение > "); scanf_s("%d", &value);
            // Удаление первого вхождения элемента по ключу
            deleteFirstByKey(&list, value);

            break;
        case 6: // Очистка очереди
            while (!is_empty(list)) {
                Priority d = pop(&list);
                printf("Удален элемент с приоритетом %d\n", d);
            }
            printf("Очередь пуста: %s\n", is_empty(list) ? " Да" : " Нет");
            break;
        
        case 7: // Вывод на экран элементов очереди с их приоритетами и индексами
            print(list);
            break;
        case 8: // Удалить элемент с первым максимальным приоритетом
            p = list;
            maxpriority = p->data;
            
            index = 0;
            while(p != NULL && maxpriority != 0) {
                
                if (p->data < maxpriority)
                    maxpriority = p->data;
                p = p->next;
               
                index++;
            }
            printf("%d - max priority ", maxpriority);
            printf("\n");
            // Удаление первого вхождения элемента по ключу
            deleteFirstByKey(&list, maxpriority);
            print(list);
            break;
        }
    } while (x != 0);

    printf("\n");
    return 0;
}


void insertNodeAtEnd(Node** pList, int data) // Добавить элемент в конец очереди
{
    Node* newNode, * temp;

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {} //Не удалось выделить память
    else
    {
        newNode->data = data; // значение приоритета
        newNode->next = NULL;
        //head списка
        temp = *pList;

        // Traverse to the last node
        while (temp != NULL && temp->next != NULL)
            temp = temp->next;

        temp->next = newNode; // Link address part

        //printf("DATA INSERTED SUCCESSFULLY\n");
    }
}

void insertNodeAtMiddle(Node** plist, int data, int position) // Вставка приоритета по убывающему списку
{
    int i;
    Node* newNode, * temp;

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {} // Не удалось выделить память
    else
    {
        newNode->data = data; 
        newNode->next = NULL;

        // получить указатель на голову списка Node
        temp = *plist;

        for (i = 2; i <= position - 1; i++) // Поставить указатель до n - 1 позиции
        {
            temp = temp->next;

            if (temp == NULL)
                break;
        }

        if (temp != NULL)
        {
            
            newNode->next = temp->next; // Адрес нового узла

            temp->next = newNode; // Адрес узла n-1-ого
            //Вставка приоритета успешна
            
        }
        else {} // Не удалось вставить приоритет
    }
}
Priority pop(Node** plist) { // удаляет первый элемент

    Node* p = *plist;
    Priority res = p->data;
    *plist = p->next;
    free(p);

    return res;
}

Priority deleteLastNode(Node** plist) //7.  Удаление элемента из конца списка
{
    Node* toDelete, * secondLastNode;
    if (plist == NULL)
    {
        printf("List is already empty.");
        return 0;
    }
    else
    {
        toDelete = *plist;
        secondLastNode = *plist;

        /* меняем указатель до тех пор, пока не дойдем до конца */
        while (toDelete->next != NULL)
        {
            secondLastNode = toDelete;
            toDelete = toDelete->next;
        }

        if (toDelete == *plist)
        {
            *plist = NULL;
        }
        else
        {
            /* разрываем связь предпоследнего элемента с последним*/
            secondLastNode->next = NULL;
        }
        Priority res = toDelete->data;
        /* освобождаем память */
        free(toDelete);
        return res;
    }
}
int is_empty(Node* list) { // проверка на пустоту списка
    return list == NULL;
}
void print(Node* list) { // вывести на экран
    int index = 0;
    for (Node* p = list; p != NULL; p = p->next) {
        printf("[%d] = %d\n", index, p->data);
        index++;
    }

    printf("\n");
}
int* searchByKey(Node* list, int key) { // найти индекс элемента
    int overlap = 0;
    for (Node* p = list; p != NULL; p = p->next) {
        if (p->data == key) {
            overlap++;

        }
    }
    printf("\n");
    int index = -1;
    int count = 0;
    int query = 0;
    int* Arr = new int[overlap];
    for (Node* p = list; p != NULL; p = p->next) {
        if (p->data == key) {

            index = query;
            count++;
            Arr[count] = index;
            printf("Ключ %d поиска найден. Индекс равен %d\n", key, index);
        }
        query++;
    }
    if (index == -1) {
        printf("Ключ %d поиска не найден\n", key);
    }
    return Arr;
}
void push(Node** plist, Priority d) { // положить элемент в начало
    Node* p = (struct Node*)malloc(sizeof(Node));
    p->data = d;
    p->next = *plist;
    *plist = p;
}

void deleteFirstByKey(Node** plist, int key) // Удалить первое вхождение элемента по ключу в односвязанном списке
{
    struct Node* prev, * cur;

    while (*plist != NULL && (*plist)->data == key) // Проверка если голова списка Node содержит ключ удаления
    {
        // получить указатель на голову списка Node
        prev = *plist;

        // связь головного элемента с указателем начала и следующего за ним
        *plist = (*plist)->next;

        // Удаление предыдущей версии, так как она содержит ссылку на предыдущий узел
        free(prev);


        return;
    }

    prev = NULL;
    cur = *plist;

    while (cur != NULL) // Перебор всех узлов в очереди
    {
        // Текущий узел содержит ключ
        if (cur->data == key)
        {
            // Настройка ссылок для предыдущего узла
            if (prev != NULL)
                prev->next = cur->next;

            // Удалить текущий узел
            free(cur);

            return;
        }

        prev = cur;
        cur = cur->next;
    }
}
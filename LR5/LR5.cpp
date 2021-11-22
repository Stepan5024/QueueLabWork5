// Лабораторная работа №5
// Выполнили студенты группы м3о-219Бк-20 Бокарев, Катвалян
// 22/11/21

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef int Priority;
typedef struct Node Node;
const int CAPACITY = 25; // Максимальный размер очереди

struct Node {
    Priority data;
    Node* next;
};

void print(Node* queue);
void push(Node** pQueue, Priority d);
int is_empty(Node* queue);
Priority deleteFirstFromQueue(Node** queue);
void deleteFirstByPriority(Node** pQueue, int key);
void insertForPriority(Node** pQueue, int data, int position);
void insertAtEnd(Node** pQueue, int data);

unsigned int size = 0; // текущий размер очереди

int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");
    
    Node* queue = NULL;
    
    
    
    Node* p;
    Priority d;
    int x = 0; // очередной пункт меню
    int value = 0;
    int index = 0;
    int priority = 0;
    int maxpriority = 0;
    Priority test[] = { 1, 2, 5, 10, 30, 40, 80 };
    push(&queue, 0); // добавит элемент в начало

    do
    {
        printf("1. Инициализация очереди 9-ью элементами\n");
        printf("2. Добавление в очередь по убывающему приоритету\n");
        printf("3. Удаление из начала очереди\n");
        printf("4. Удаление из очереди по заданному приоритету\n");
        printf("5. Очистка очереди\n");
        printf("6. Вывод на экран элементов очереди с их приоритетами и индексами\n");
        printf("0. Выйти\n");
        printf("\nНомер операции > "); scanf_s("%d", &x);
        switch (x)
        {
        case 1: // инициализация очереди
            
            for (size_t i = 0; i < sizeof(test) / sizeof(test[0]); i++)//инициализация списка
            {
                insertAtEnd(&queue, test[i]); // добавит элемент в конец очереди
            }
            
            print(queue);
            break;
       
        case 2: //Добавление в очередь по убывающему приоритету
            index = 0;
            printf("Значение приоритета > "); scanf_s("%d", &value);
            priority = value;
            
            p = queue;
            value = p->data;

            while(p != NULL && p->data < priority) {
                index++;
                p = p->next;
            }
            if (value > priority)
                push(&queue, priority);
            else 
                insertForPriority(&queue, priority, ++index);
            print(queue);
            break;

        case 3: // Удаление из очереди из начала очереди
            if (!is_empty(queue)) {
                Priority d = deleteFirstFromQueue(&queue);
                printf("Удален элемент с приоритетом %d\n", d);
            }
            print(queue);
            break;
        case 4: // Удаление из очереди по заданному приоритету
            printf("Значение > "); scanf_s("%d", &value);
            // Удаление первого вхождения элемента по ключу
            deleteFirstByPriority(&queue, value);
            print(queue);

            break;
        case 5: // Очистка очереди
            while (!is_empty(queue)) {
                Priority d = deleteFirstFromQueue(&queue);
                printf("Удален элемент с приоритетом %d\n", d);
            }
            printf("Очередь пуста: %s\n", is_empty(queue) ? " Да" : " Нет");
            break;
        
        case 6: // Вывод на экран элементов очереди с их приоритетами и индексами
            print(queue);
            break;
        
        }
    } while (x != 0);

    printf("\n");
    return 0;
}


void insertAtEnd(Node** pQueue, int priority) // Добавить элемент в конец очереди
{
    if (size < CAPACITY) {
        Node* newNode, * temp;

        newNode = (Node*)malloc(sizeof(Node));

        if (newNode == NULL) {} // Не удалось выделить память
        else
        {
            newNode->data = priority; // значение приоритета
            newNode->next = NULL; // потому что в конец вставка
            
            temp = *pQueue; // head очереди

            // Переход к поледнему приоритету
            while (temp != NULL && temp->next != NULL)
                temp = temp->next;

            temp->next = newNode; // адрес

            size++;
        }
    }
    else {
        printf("В очереди максимальное кол-во элементов\n");
    }
}

void insertForPriority(Node** pQueue, int priority, int position) // Вставка приоритета по убывающему списку
{
    if (size < CAPACITY) {

        Node* newNode, * temp;
        newNode = (Node*)malloc(sizeof(Node));

        if (newNode == NULL) {} // Не удалось выделить память
        else
        {
            newNode->data = priority;
            newNode->next = NULL;

            // получить указатель на голову списка Node
            temp = *pQueue;

            for (int i = 2; i <= position - 1; i++) // Поставить указатель до n - 1 позиции
            {
                temp = temp->next;

                if (temp == NULL)
                    break;
            }

            if (temp != NULL)
            {

                newNode->next = temp->next; // Адрес  n + 1- ого узла

                temp->next = newNode; // Адрес узла n-1-ого
                //Вставка приоритета успешна

            }
            else {} // Не удалось вставить приоритет
        }
    }
    else {
        printf("В очереди максимальное кол-во элементов\n");
    }
}
Priority deleteFirstFromQueue(Node** pQueue) { // удаляет первый элемент

    Node* p = *pQueue;
    Priority res = p->data;
    *pQueue = p->next;
    free(p);
    size--;
    return res;
}

int is_empty(Node* queue) { // проверка на пустоту списка
    return queue == NULL;
}
void print(Node* queue) { // вывести на экран
    int index = 0;
    for (Node* p = queue; p != NULL; p = p->next) {
        printf("[%d] = %d\n", index, p->data);
        index++;
    }

    printf("\n");
}

void push(Node** pQueue, Priority d) { // положить элемент в начало
    Node* p = (struct Node*)malloc(sizeof(Node));
    p->data = d;
    p->next = *pQueue;
    *pQueue = p;
    size++;
}

void deleteFirstByPriority(Node** pQueue, int priority) // Удалить первое вхождение элемента по приоритету в односвязанном списке
{
    Node* prev, * cur;

    while (*pQueue != NULL && (*pQueue)->data == priority) // Проверка если голова очереди содержит ключ удаления
    {
        // получить указатель на голову списка Node
        prev = *pQueue;

        // связь головного элемента с указателем начала и следующего за ним
        *pQueue = (*pQueue)->next;

        // Удаление предыдущей версии, так как она содержит ссылку на предыдущий узел
        free(prev);
        size--;

        return;
    }

    prev = NULL;
    cur = *pQueue;

    while (cur != NULL) // Перебор всех узлов в очереди
    {
        // Текущий узел содержит ключ
        if (cur->data == priority)
        {            
            if (prev != NULL) // Настройка ссылок для предыдущего узла
                prev->next = cur->next;
            free(cur); // Удалить текущий узел
            size--;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
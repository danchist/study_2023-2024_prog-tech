#include <iostream>

struct node {
    int num;
    double val;
    std::string name;
    node* next;
};

void list_print(node* currNode) {

    // Если ноуд один, то выводим его сразу, а если нет, то идём до конца выводя каждый нод,
    // также не забываем про последний ноуд


    std::cout << "Displaying list... \n \n";

    if (currNode->next == NULL) {
        std::cout << "Node: " << currNode->name << "\n";
        std::cout << "  - ID: " << currNode->num << "\n" << "  - Value: " << currNode->val << "\n";
        return;
    }

    while (currNode->next != NULL) {
        std::cout << "Node: " << currNode->name << "\n";
        std::cout << "  - ID: " << currNode->num << "\n" << "  - Value: " << currNode->val << "\n \n";
        currNode = currNode->next;
    }

    std::cout << "Node: " << currNode->name << "\n";
    std::cout << "  - ID: " << currNode->num << "\n" << "  - Value: " << currNode->val << "\n";
}

void add_to_end(node* currNode) {
    // Заводим Переменные
    std::string nehmen;
    double valya;

    // Считываем имя и значение
    std::cout << "Enter the name of the node \n";
    std::cin >> nehmen;

    std::cout << "\n Enter the value of the node \n";
    std::cin >> valya;

    // Создаём новый ноуд.
    node* new_node = new node;
    new_node->name = nehmen;
    new_node->val = valya;
    new_node->next = NULL;

    // Если у нас только один ноуд, то сразу к нему добавляем новый с порядковым ID
    // Если же нет, то просто идём до конца, после чего обновляем последнюю ссылку на новый ноуд
    // А также повышаем ID нового ноуда на 1

    if (currNode->next == NULL) {
        new_node->num = currNode->num + 1;
        currNode->next = new_node;
        return;
    }
    else {
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        new_node->num = currNode->num + 1;

        currNode->next = new_node;
    }

    std::cout<<"Node added successfully \n \n";


}

void add_to_beg(node* currNode) {
    // Заводим Переменные
    std::string nehmen;
    double valya;

    // Считываем имя и значение
    std::cout << "Enter the name of the node \n";
    std::cin >> nehmen;

    std::cout << "\n Enter the value of the node \n";
    std::cin >> valya;



    // Создаём новый ноуд. Запоминаем ссылку на второй ноуд как отдельную переменную
    node* new_node = new node;
    node* ptr = currNode->next;

    // В новый ноуд переносим данные из первого, а ссылку переносим из переменной
    new_node->name = currNode->name;
    new_node->val = currNode->val;
    new_node->num = currNode->num;
    new_node->next = ptr;

    // Обновляем текущий (первый) ноуд считанными значениями
    currNode->name = nehmen;
    currNode->val = valya;
    currNode->num = 1;
    currNode->next = new_node;

    // Переходим на новый второй ноуд, затем проходимся по всем ноудам и обновляем их ID
    currNode = currNode->next;

    while (currNode->next != NULL) {
        currNode->num += 1;
        currNode = currNode->next;
    }
    currNode->num += 1;

    std::cout<<"Node added successfully \n \n";


}

void add_by_ID(node* currNode, int ID) {
    // Проверка на корректный ID, если он такой не встретит. То пишем попробовать снова!
    node* checkpoint = currNode;
    while (checkpoint->next != NULL) {
        if (checkpoint->num == ID) {
            break;
        }
        checkpoint = checkpoint->next;
    }
    if (checkpoint->num != ID) {
        std::cout<<"\n No such ID in the list. Try again! \n";
    }
    // Заводим Переменные
    std::string nehmen;
    double valya;
    // Считываем имя и значение
    std::cout << "Enter the name of the node \n";
    std::cin >> nehmen;

    std::cout << "\n Enter the value of the node \n";
    std::cin >> valya;

    // Создаём новый ноуд.
    node* new_node = new node;
    new_node->name = nehmen;
    new_node->val = valya;

    // спрашиваем командным образом, до ID добавить или после
    std::string comm;
    std::cout<< "\n Before " << ID << " or After? \n";
    std::cin>> comm;
    if (comm == "After" or comm == "after") {
        // Если добавляем после: проходимся до того момента, пока ID не совпадёт.
        // Защита от ошибки имплементирована была в самом начале функции

        while (currNode->num != ID) {
            currNode = currNode->next;
        }
        // запоминаем ссылку на след следующий нод как переменную
        // затем добавляем прицепляем новый нод к текущему, а сохранённую ссылку, к новому
        // Также повышаем ID нового нода, т.к. мы решили добавить после
        node* ptr = currNode->next;
        currNode->next = new_node;
        new_node->next = ptr;
        new_node->num = ID + 1;

        // Заходим в новый нод (он теперь текущий) Обновляем индексы всех последующих нодов
        currNode = currNode->next;
        while (currNode->next != NULL) {
            currNode = currNode->next;
            currNode->num += 1;
        }
    }
    else if (comm == "Before" or comm == "before") {
        // Если добавляем до: идём до нода, который стоит перед нужным ID

        while (currNode->num != ID - 1) {
            currNode = currNode->next;
        }
        // Запоминаем ссылку на следующий нод в отдельной переменной
        // Заменяем данные текущего на данные нового, и ссылку следующего тоже присваиываем новому ноду
        // Делаем индекс нового: ID - 1, т.к. мы решили поставить его до ID
        node* ptr = currNode->next;
        currNode->next = new_node;
        new_node->next = ptr;
        new_node->num = ID - 1;

        // Переходим в слеующий ноуд - новый, повышаем ID всех последующих нодов, и того, который в самом конце
        currNode = currNode->next;
        while (currNode->next != NULL) {
            currNode->num += 1;
            currNode = currNode->next;
        }
        currNode->num += 1;
    }
    // если неправильно ввели команду, просим попробовать снова
    else {
        std::cout<<"\n Wrong command! Try again! \n;";
    }


}

void rm_by_name(node* currNode) {

    // Делаем защиту от удаления одной единственной ноды.

    if (currNode->next == NULL) {
        std::cout<<"\n Seems like there's only one node. You can't delete the only available node.\n";
        return;
    }

    // спрашиваем название желаемой ноуды
    std::string nehmen;
    std::cout<<"\n Enter the name which you want to delete \n";
    std::cin>>nehmen;


    // создаём ноду для случая, когда хотим удалить последнюю ноду
    node* checkpoint = currNode;

    // идём по нодам, если встретили ноду с таким же именем, то заменяем данные текущей ноды, на
    // данные следующей. В начале запомнили ссылку на след следующеую ноду, удаляем следующую ноду
    // а ссылкой текущей ноды присваиваем значени ссылки на след следующую.
    // Также после этого пройдёмся по оставшимся нодам и убавим их индексы
    while (currNode->next != NULL) {
        if (currNode->name == nehmen) {
            node* ptr = currNode->next->next;
            currNode->name = currNode->next->name;
            currNode->num = currNode->next->num - 1;
            currNode->val = currNode->next->val;
            delete currNode->next;
            currNode->next = ptr;


            while (currNode->next != NULL) {
                currNode = currNode->next;
                currNode->num -= 1;
            }

            std::cout<<"\n Node deleted succsessfully! \n";
            return;
        }
        currNode = currNode->next;
    }

    // если так и не встретили такой ноды, то пишем "ОШИБКА"
    if (currNode->name != nehmen) {
        std::cout<<"\n No node with such name. Try again! \n";
        return;
    }

    // не горжусь этим решением. ещё раз проходим по всем нодам, но в этот раз останавливаемся,
    // когда след следующая - последняя нода. В таком случае просто делаем конечной текущую ноду,
    // на которой остановились, перед этим удалив следующую ноду
    while (checkpoint->next->next != NULL) {
        checkpoint = checkpoint->next;
    }
    delete checkpoint->next;
    checkpoint->next = NULL;
    std::cout<<"\n Node deleted succsessfully! \n";





}

// ----- Список команд ------
// help - вывести список команд
// addEnd - добавить в конец
// addBeg - добавить в начало
// addID - добавить по индексу (Потом спросят до индекса (before) или после (after))
// rm - удалить
// print - вывести текущий список
// ---------------------------


int main() {
    node start = {1, 64, "Start", NULL};

    list_print(&start);

    std::string command = "";

    while (command != "exit") {
        std::cout<<"********************************************* \n";
        std::cout<< "Enter command  \n";
        std::cin>> command;
        std::cout<< "\n";

        if (command == "addEnd") {
            add_to_end(&start);
        }
        else if (command == "addBeg") {
            add_to_beg(&start);
        }
        else if (command == "print") {
            list_print(&start);
        }
        else if (command == "help") {
            std::cout<<"\n addEnd, addBeg, addID, print, rm \n";
        }
        else if (command == "addID") {
            std::cout << "\n Enter ID: \n";
            int ID;
            std::cin >> ID;
            add_by_ID(&start, ID);
        }
        else if (command == "rm") {
            rm_by_name(&start);
        }
        else {
            std::cout<<"Invalid command \n";
        }

    }

}
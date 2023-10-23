#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Program Restoran Margamedon

// Admin
string admUsn = "admin";
string admPin = "123123";

struct menu { // Struct Menu 
    int idMenu;
    string namaMenu, jenisMenu, hargaMenu;

    menu *next = NULL;
    menu *prev = NULL;
};

menu *newMenu() {
    menu *menuBaru = new menu;
    cout << "-----------------------------------------------------" << endl;
    cout << "        ||          CREATE NEW MENU          ||      " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Masukkan ID Menu    : "; cin >> menuBaru->idMenu; cin.ignore();
    cout << "Masukkan Nama Menu  : "; getline(cin, menuBaru->namaMenu);
    cout << "Masukkan Jenis Menu : "; getline(cin, menuBaru->jenisMenu);
    cout << "Masukkan Harga Menu : "; getline(cin, menuBaru->hargaMenu);
    cout << "_____________________________________________________" << endl;
    return menuBaru;
}

struct order { // Struct Order for Customer
    int idOrder;
    string namaMenuOrder, hargaMenuOrder, jumlahOrder;

    order *next = NULL;
    order *prev = NULL;
};

order *newOrder() {
    order *orderBaru = new order;
    cout << "\n-----------------------------------------------------" << endl;
    cout << "        ||          CREATE NEW MENU          ||      " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Masukkan ID Order    : "; cin >> orderBaru->idOrder; cin.ignore();
    cout << "Masukkan Nama Order  : "; getline(cin, orderBaru->namaMenuOrder);
    cout << "Masukkan Jenis Order : "; getline(cin, orderBaru->hargaMenuOrder);
    cout << "Masukkan Harga Order : "; getline(cin, orderBaru->jumlahOrder);
    cout << "_____________________________________________________" << endl;
    return orderBaru;
}

// ====================================== ADD ======================================

void addFirst_MENU(menu **head, menu **tail) {
    menu *menuBaru = newMenu();
    if (isEmpty(*head, *tail)) {
        *head = menuBaru;
        *tail = menuBaru;
    } 
    else {
        (*head)->prev = menuBaru;
        menuBaru->next = *head;
        *head = menuBaru;
    }
}

void addLast_MENU(menu **head, menu **tail) {
    menu *temp = *head;
    if (isEmpty(*head, *tail)) {
        addFirst_MENU(head, tail);
    }
    else {
        menu *menuBaru = newMenu();
        (*tail)->next = menuBaru;
        menuBaru->prev = *tail;
        *tail = menuBaru;
    }
}

void addMiddle_MENU(menu *head, menu **tail, int idx) {
    if (isEmpty(*head, *tail)) {
        addFirst_MENU(head, tail);
    } else {
        menu *menuBaru  = newMenu();
        menu *temp = head;
        for (int i = 0; i < idx - 1; i++) {
            temp = temp->next;
        }
        menuBaru->next = temp;
        menuBaru->prev = temp->prev;
        temp->prev->next = menuBaru;
        temp->prev = menuBaru;
    }
}

// ====================================== DISPLAY ======================================

void displayHead_MENU(menu *head, menu *tail) {
    if (isEmpty(head, tail)) {
        cout << " Empty Menu " << endl;
    } 
    else {
        cout << "\n-----------------------------------------------------" << endl;
        cout << "      ||           MENU MARGAMEDON            ||     " << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "----------------------------------------------------------------\n";
        cout << "|    ID    |    Nama Menu  |   Jenis Menu    |   Harga Menu    |\n";
        cout << "----------------------------------------------------------------\n";

        menu *temp = head;
        while (temp != NULL) {
            cout << "|    " << temp->idMenu << "    |     " << temp->namaMenu << "      |     " << temp->jenisMenu << "      |     " << temp->hargaMenu << "      |\n";
            cout << "----------------------------------------------------------------\n";
            temp = temp->next;
        }
    }
}

void displayTail_MENU(menu *head, menu *tail) {
    if (isEmpty(head, tail)) {
        cout << " Empty Menu " << endl;
    } 
    else {
        cout << "\n-----------------------------------------------------" << endl;
        cout << "      ||           MENU MARGAMEDON            ||     " << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "----------------------------------------------------------------\n";
        cout << "|    ID    |    Nama Menu  |   Jenis Menu    |   Harga Menu    |\n";
        cout << "----------------------------------------------------------------\n";

        menu *temp = tail;
        while (temp != NULL) {
            cout << "|    " << temp->idMenu << "    |     " << temp->namaMenu << "      |     " << temp->jenisMenu << "      |     " << temp->hargaMenu << "      |\n";
            cout << "----------------------------------------------------------------\n";
            temp = temp->prev;
        }
    }
}

// ====================================== UPDATE ======================================

void updateMenu(menu *head, int idx) {
    menu *temp = head;
    for (int i = 1; i < idx; i++) {
        temp = temp->next;
    }
    cout << "Masukkan ID enu baru: "; cin >> temp->idMenu; cin.ignore();
    cout << "Masukkan nama menu baru: "; fflush(stdin); getline(cin, temp->namaMenu);
    cout << "Masukkan jenis menu baru: "; fflush(stdin); getline(cin, temp->jenisMenu);
    cout << "Masukkan harga menu baru: "; fflush(stdin); getline(cin, temp->hargaMenu);
}

// ====================================== DELETE ======================================

void delFirst_MENU(menu **head, menu **tail) {
    if (isEmpty(*head, *tail)) {
        cout << " Empty menu " << endl;
    }
    else {
        delete *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
}

void delLast_MENU(menu **head, menu **tail) {
    if ((*head)->next == NULL) {
        delFirst_MENU(head, tail);
    } 
    else {
        delete *tail;
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
}

void delMiddle_MENU(menu *head, int idx) {
    menu *temp = head;

    for (int i = 1; i < idx - 1; i++) {
        temp = temp->next;
    }
    menu *Delete = temp->next;
    temp->next = Delete->next;
    temp->prev = Delete->prev;
    delete Delete;
}

// ====================================== SORTING ======================================
// == ID ASCENDING ==
menu *SortedMergeID_asc(menu *a, menu *b);
void FrontBackSplitID_asc(menu *source, menu **frontRef, menu **backRef);
void MergeSortID_asc(menu **headRef) {
    menu *head = *headRef;
    menu *a;
    menu *b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    FrontBackSplitID_asc(head, &a, &b);
    MergeSortID_asc(&a);
    MergeSortID_asc(&b);
    *headRef = SortedMergeID_asc(a, b);
}

menu *SortedMergeID_asc(menu *a, menu *b) {
    menu *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->idMenu <= b->idMenu) {
        result = a;
        result->next = SortedMergeID_asc(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMergeID_asc(a, b->next);
    }
    return (result);
}

void FrontBackSplitID_asc(menu *source, menu **frontRef, menu **backRef) {
    menu *fast;
    menu *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// == ID DESCENDING ==
menu *SortedMergeID_desc(menu *a, menu *b);
void FrontBackSplitID_desc(menu *source, menu **frontRef, menu **backRef);
void MergeSortID_desc(menu **headRef) {
    menu *head = *headRef;
    menu *a;
    menu *b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    FrontBackSplitID_desc(head, &a, &b);
    MergeSortID_desc(&a);
    MergeSortID_desc(&b);
    *headRef = SortedMergeID_desc(a, b);
}

menu *SortedMergeID_desc(menu *a, menu *b) {
    menu *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->idMenu >= b->idMenu) {
        result = a;
        result->next = SortedMergeID_desc(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMergeID_desc(a, b->next);
    }
    return (result);
}

void FrontBackSplitID_desc(menu *source, menu **frontRef, menu **backRef) {
    menu *fast;
    menu *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// ====================================== SEARCHING ======================================
// == Jump Search == berdasarkan ID 
menu *findMenu(menu *head, int idx) {
    menu *temp = head;
    for (int i = 0; i < idx; i++)
    {
        temp = temp->next;
    }
    return temp;
}

int jumpSearch(menu *head, int x, int n)
{
    int step = sqrt(n);
    int prev = 0;

    int idx = min(step, n) - 1;
    while (findMenu(head, idx)->idMenu < x)
    {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n)
        {
            return -1;
        }
    }
    while (findMenu(head, prev)->idMenu < x)
    {
        prev++;
    }
    cout << endl;
    if (findMenu(head, prev)->idMenu == x)
    {
        return prev;
    }
    return -1;
}

// ====================================== PER BOOL-AN ======================================

bool isNum(string str) { // Mengecek inputan numerik
    bool numeric = false;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            numeric = true;
            continue;
        }
        numeric = false;
        break;
    }
    return numeric;
}

bool isEmpty (menu *head, menu *tail) { // Mengecek apakah data menu null atau tidak
    if(head == NULL and tail == NULL) {
        return true;
    }
    return false;
}

bool isEmpty (order *head, order *tail) { // Mengecek apakah data order null atau tidak, ini perlu ga si?
    if(head == NULL and tail == NULL) {
        return true;
    }
    return false;
}

// ====================================== FIX PREV ======================================

void fixPrev (menu **head, menu **tail) {
    (*head)->prev = NULL;
    menu *cur = *head;
    while(cur->next != NULL) {
        menu *temp = cur->next;
        temp->prev = cur;
        cur = cur->next;
    }
    *tail = cur;
    (*tail)->next = NULL;
}

// ====================================== MENU ADMIN ======================================

void menuAdmin() { // Tampilan Menu Admin
    int listMenuAdm;
    while (true) {
        cout << "\n-------------------------------" << endl;
        cout << "|         DAFTAR MENU         |" << endl;
        cout << "-------------------------------" << endl;
        cout << "| 1. | Add Menu               |" << endl;
        cout << "| 2. | Display Menu           |" << endl;
        cout << "| 3. | Update Menu            |" << endl;
        cout << "| 4. | Delete Menu            |" << endl;
        cout << "| 5. | Sorting Menu           |" << endl;
        cout << "| 6. | Searching Menu         |" << endl;
        cout << "| 0. | Log Out                |" << endl;
        cout << "|_____________________________|" << endl;
        cout << "Pilih Menu: "; cin >> listMenuAdm; cin.ignore();
        if (listMenuAdm == 1) {
            int add;
            cout << "\n-------------------------------" << endl;
            cout << "|          ADD MENU           |" << endl;
            cout << "-------------------------------" << endl;
            cout << "| 1. | Add First              |" << endl;
            cout << "| 2. | Add Last               |" << endl;
            cout << "| 3. | Add Middle             |" << endl;
            cout << "| 0. | Back to List Menu      |" << endl;
            cout << "|_____________________________|" << endl;
            cout << "Pilih Menu: "; cin >> add; cin.ignore();
            if (add == 1) {
                addFirst_MENU(&head, &tail);
            }
            else if (add == 2) {
                addLast_MENU(&head, &tail);
            }
            else if (add == 3) {
                addMiddle_MENU(&head, &tail);
            }
            else if (add == 0) {
                menuAdmin();
            } 
            else {
                break;
            }
        }
        else if (listMenuAdm == 2) {
            int display;
            cout << "\n-------------------------------" << endl;
            cout << "|         DISPLAY MENU         |" << endl;
            cout << "-------------------------------" << endl;
            cout << "| 1. | Display Head            |" << endl;
            cout << "| 2. | Display Tail            |" << endl;
            cout << "| 0. | Back to List Menu       |" << endl;
            cout << "|______________________________|" << endl;
            cout << "Pilih Menu: "; cin >> display; cin.ignore();
            if (display == 1) {
                displayHead_MENU(head, tail);
            }
            else if (display == 2) {
                displayTail_MENU(head, tail);
            }
            else if (display == 0) {
                menuAdmin();
            }
            else {
                break;
            }
        }
        else if (listMenuAdm == 3) {
            cout << "| Mau Update di data berapa? "; cin >> idx; cin.ignore();
            updateMenu(head, idx);
        }
        else if (listMenuAdm == 4) {
            int deleteMenu;
            cout << "\n-------------------------------" << endl;
            cout << "|         DELETE MENU         |" << endl;
            cout << "-------------------------------" << endl;
            cout << "| 1. | Delete First           |" << endl;
            cout << "| 2. | Delete Last            |" << endl;
            cout << "| 3. | Delete Middle          |" << endl;
            cout << "| 0. | Back to List Menu      |" << endl;
            cout << "|_____________________________|" << endl;
            cout << "Pilih Menu: "; cin >> deleteMenu; cin.ignore();
            if (deleteMenu == 1) {
                delFirst_MENU(&head, &tail);
            }
            else if (deleteMenu == 2) {
                delLast_MENU(&head, &tail);
            }
            else if (deleteMenu == 3) {
                delMiddle_MENU(head, idx);
            }
            else if (deleteMenu == 0) {
                menuAdmin();
            }
            else {
                break;
            }
        }
        else if (listMenuAdm == 5) {
            int sort;
            cout << "\n--------------------------------" << endl;
            cout << "|         SORTING MENU         |" << endl;
            cout << "--------------------------------" << endl;
            cout << "| 1. | ID Menu                 |" << endl;
            cout << "| 2. | Nama Menu               |" << endl;
            cout << "| 3. | Jenis Menu              |" << endl;
            cout << "| 4. | Harga Menu              |" << endl;
            cout << "| 0. | Back to List Menu       |" << endl;
            cout << "|______________________________|" << endl;
            cout << "Pilih Menu: "; cin >> sort; cin.ignore();
            if (sort == 1){
                int asc_desc;
                cout << "\n--------------------------------" << endl;
                cout << "|         SORTING MENU         |" << endl;
                cout << "--------------------------------" << endl;
                cout << "| 1. | Ascending               |" << endl;
                cout << "| 2. | Descending              |" << endl;
                cout << "| 0. | Back to List Menu       |" << endl;
                cout << "|______________________________|" << endl;
                cout << "Pilih Menu: "; cin >> asc_desc; cin.ignore();
                if (asc_desc == 1) {
                    // mergesortID_asc;
                    fixPrev(&head, &tail);
                }
                else if (asc_desc == 2) {
                    // mergesortID_desc;
                    fixPrev(&head, &tail);
                }
                else if(asc_desc == 0) {
                    menuAdmin();
                }
                else {
                    cout << " Masukkan inputan yang benar " << endl;
                }
            }
            else if (sort == 2){
                int asc_desc;
                cout << "\n--------------------------------" << endl;
                cout << "|         SORTING MENU         |" << endl;
                cout << "--------------------------------" << endl;
                cout << "| 1. | Ascending               |" << endl;
                cout << "| 2. | Descending              |" << endl;
                cout << "| 0. | Back to List Menu       |" << endl;
                cout << "|______________________________|" << endl;
                cout << "Pilih Menu: "; cin >> asc_desc; cin.ignore();
                if (asc_desc == 1) {
                    // mergesortNama_asc;
                    fixPrev(&head, &tail);
                }
                else if (asc_desc == 2) {
                    // mergesortNama_desc;
                    fixPrev(&head, &tail);
                }
                else if(asc_desc == 0) {
                    menuAdmin();
                }
                else {
                    cout << " Masukkan inputan yang benar " << endl;
                }
            }
            else if (sort == 3){
                int asc_desc;
                cout << "\n--------------------------------" << endl;
                cout << "|         SORTING MENU         |" << endl;
                cout << "--------------------------------" << endl;
                cout << "| 1. | Ascending               |" << endl;
                cout << "| 2. | Descending              |" << endl;
                cout << "| 0. | Back to List Menu       |" << endl;
                cout << "|______________________________|" << endl;
                cout << "Pilih Menu: "; cin >> asc_desc; cin.ignore();
                if (asc_desc == 1) {
                    // mergesortJenis_asc;
                    fixPrev(&head, &tail);
                }
                else if (asc_desc == 2) {
                    // mergesortJenis_desc;
                    fixPrev(&head, &tail);
                }
                else if(asc_desc == 0) {
                    menuAdmin();
                }
                else {
                    cout << " Masukkan inputan yang benar " << endl;
                }
            }
            else if (sort == 4){
                int asc_desc;
                cout << "\n--------------------------------" << endl;
                cout << "|         SORTING MENU         |" << endl;
                cout << "--------------------------------" << endl;
                cout << "| 1. | Ascending               |" << endl;
                cout << "| 2. | Descending              |" << endl;
                cout << "| 0. | Back to List Menu       |" << endl;
                cout << "|______________________________|" << endl;
                cout << "Pilih Menu: "; cin >> asc_desc; cin.ignore();
                if (asc_desc == 1) {
                    // mergesortHarga_asc;
                    fixPrev(&head, &tail);
                }
                else if (asc_desc == 2) {
                    // mergesortHarga_desc;
                    fixPrev(&head, &tail);
                }
                else if(asc_desc == 0) {
                    menuAdmin();
                }
                else {
                    cout << " Masukkan inputan yang benar " << endl;
                }
            }
            else if (sort == 0){
                menuAdmin();
            }
            else {
                cout << " Masukkan Inputan yang Benar " << endl;
            }
        } 
        else if (listMenuAdm == 6) {
            int search;
            cout << "\n--------------------------------" << endl;
            cout << "|        SEARCHING MENU        |" << endl;
            cout << "--------------------------------" << endl;
            cout << "| 1. | ID Menu                 |" << endl;
            cout << "| 2. | Nama Menu               |" << endl;
            cout << "| 3. | Jenis Menu              |" << endl;
            cout << "| 4. | Harga Menu              |" << endl;
            cout << "| 0. | Back to List Menu       |" << endl;
            cout << "|______________________________|" << endl;
            cout << "Pilih Menu: "; cin >> search; cin.ignore();
            if (search == 1) {
                // jumpsearch_ID;
            }
            else if (search == 2) {
                // jumpsearch_Nama;
            }
            else if (search == 3) {
                // jumpsearch_Jenis;
            }
            else if (search == 4) {
                // jumpSearch_Harga;
            }
            else if (search == 0) {
                menuAdmin();
            }
            else {
                cout << " Opsi Tidak Ada " << endl;
            }
        }
        else if (listMenuAdm == 0) {
            break;
        }
    }
}

// ====================================== MENU CUSTOMER ======================================

void menuCust() { // Tampilan Menu Customer
    int listMenuCust;
    while (true) {
        cout << "\n-------------------------------" << endl;
        cout << "|    Welcome to Margamedon    |" << endl;
        cout << "-------------------------------" << endl;
        cout << "| 1. | Display Menu           |" << endl;
        cout << "| 2. | Order Menu             |" << endl;
        cout << "| 0. | Log Out                |" << endl;
        cout << "|_____________________________|" << endl;
        cout << "Pilih Menu: "; cin >> listMenuCust; cin.ignore();
        if (listMenuCust == 1) {
            int select;
            cout << "\n-------------------------------" << endl;
            cout << "|         Select Menu         |" << endl;
            cout << "-------------------------------" << endl;
            cout << "| 1. | Makanan Berat          |" << endl;
            cout << "| 2. | Snack                  |" << endl;
            cout << "| 3. | Minuman                |" << endl;
            cout << "| 0. | Back                   |" << endl;
            cout << "|--------------------------------|" << endl;
            cout << "|  Mau pilih menu apa? "; cin >> select;
            cout << "|--------------------------------|" << endl;
            if (select == 1) {
                cout << "\n|------------------------------|" << endl;
                cout << "| ---  List Makanan Berat  --- |" << endl;
                cout << "|------------------------------|\n" << endl;
                cout << "------------------------------------------------------------------------------------\n";
                cout << "|            Nama Menu              |                  Harga Menu                  |\n";
                cout << "------------------------------------------------------------------------------------\n";

                menu *temp = head;
                while (temp != NULL) {
                    cout << "|     " << temp->namaMenu << "         |           " << temp->hargaMenu << "      |\n";
                }
            }
            else if (select == 2) {
                cout << "\n|------------------------------|" << endl;
                cout << "| ---      List Snack      --- |" << endl;
                cout << "|------------------------------|\n" << endl;
                cout << "------------------------------------------------------------------------------------\n";
                cout << "|            Nama Menu              |                  Harga Menu                  |\n";
                cout << "------------------------------------------------------------------------------------\n";

                menu *temp = head;
                while (temp != NULL) {
                    cout << "|     " << temp->namaMenu << "         |           " << temp->hargaMenu << "      |\n";
                }
            }
            else if (select == 3) {
                cout << "\n|-------------------------------|" << endl;
                cout << "| ---      List Minuman     --- |" << endl;
                cout << "|-------------------------------|\n" << endl;
                cout << "------------------------------------------------------------------------------------\n";
                cout << "|            Nama Menu              |                  Harga Menu                  |\n";
                cout << "------------------------------------------------------------------------------------\n";

                menu *temp = head;
                while (temp != NULL) {
                    cout << "|     " << temp->namaMenu << "         |           " << temp->hargaMenu << "      |\n";
                }
            }
        }
        else if (listMenuCust == 2) {
            // apa yach;
        }
    }
}

void login() {
    int loginAttempt = 1;

    bool isNum(string str);
    string inputUsn;
    string inputPin;
    bool login;

    while (true) {
        system("CLS");
        cout << "\nLOGIN PAGE\n" << endl;
        cout << "Username: "; getline(cin, inputUsn);
        cout << "PIN: "; getline(cin, inputPin);
        if (!isNum(inputPin) || inputPin.length() != 6) {
            login = false;
            break;
        }
        else {
            login = true;
            break;
        }
    }
}

int main() {
    // isi apa juga yach ini;
}
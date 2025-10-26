#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Node {
    string name;
    string phone;
    Node* next;
};

void initTable(Node* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

int hashFunction(const string& name) {
    int sum = 0;
    for (char c : name) {
        sum += c;
    }
    return sum % SIZE;
}

void insert(Node* table[], const string& name, const string& phone) {
    int index = hashFunction(name);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->name == name) {
            cur->phone = phone; 
            return;
        }
        cur = cur->next;
    }

    Node* baru = new Node;
    baru->name = name;
    baru->phone = phone;
    baru->next = table[index];
    table[index] = baru;
}

Node* search(Node* table[], const string& name) {
    int index = hashFunction(name);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->name == name) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void removeKey(Node* table[], const string& name) {
    int index = hashFunction(name);
    Node* cur = table[index];
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->name == name) {
            if (prev == nullptr)
                table[index] = cur->next;
            else
                prev->next = cur->next;

            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void display(Node* table[]) {
    cout << "\nDaftar Kontak Teman:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";
        Node* tmp = table[i];
        while (tmp != nullptr) {
            cout << "(" << tmp->name << ", " << tmp->phone << ") -> ";
            tmp = tmp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    Node* table[SIZE];
    initTable(table);

    insert(table, "Chalisa", "081234567890");
    insert(table, "Deta", "082345678901");
    insert(table, "Preisi", "083456789012");
    insert(table, "Manda", "084567890123");
    insert(table, "Nanda", "085678901234"); 

    display(table);

    string cari = "Deta";
    Node* hasil = search(table, cari);
    if (hasil != nullptr)
        cout << "\nKontak " << cari << " ditemukan dengan nomor: " << hasil->phone << endl;
    else
        cout << "\nKontak " << cari << " tidak ditemukan\n";

    removeKey(table, "Deta");
    cout << "\nSetelah menghapus kontak Deta:\n";
    display(table);

    return 0;
}

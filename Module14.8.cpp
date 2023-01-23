#include <iostream>
#include <string>
#include "TrieNode.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    string keys[] = { "hell", "help", "hello", "helps", "helping", "dog", "dot", "dove", "cat", "call"};
    int n = sizeof(keys) / sizeof(keys[0]);
    struct TrieNode* root = getNewNode();
   
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    char prefix[ALPHABET_SIZE];
    string res = "";
 
    int i = 0;
    do {
        cout << "Введите слово: " << endl;
        cin >> res;
        int comp = printAddition(root, res);
        if (comp == 0)
            cout << "Слово с этим префиксом не найдено" << endl;
        if (comp == -1)
            i = 0;
        cout << "Для продолжения работы нажмите 0, а для завершения работы напишите 1 " << endl;
        cin >> i;
    } while (i != 1); 
   
    cout << " ___________________________________END___________________________________" << endl;
    return 0;
}

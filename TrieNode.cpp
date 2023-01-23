#include "TrieNode.h"
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

//----------------------------------------
// Function...... insert
// Description... Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
// Note.......... 
// Parameters:
//  I root - дерево
//  I key - ключ
// Return: void
// Change History:
//----------------------------------------
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}
//----------------------------------------
// Function...... search
// Description... Возврашает true если ключ есть в дереве, 
// иначе false 
// Note.......... 
// Parameters:
//  I root - дерево
//  I key - ключ
// Return: bool
// Change History:
//---------------------------------------- 
bool search(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}
//----------------------------------------
// Function...... isEmpty
// Description... Возвращает true если root имеет лист, 
// иначе false 
// Note.......... 
// Parameters:
//  I root - дерево
// Return: bool
// Change History:
//---------------------------------------- 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}
//----------------------------------------
// Function...... remove
// Description... Рекурсивная функция удаления ключа из дерева 
// Note.......... 
// Parameters:
//  I root - дерево
//  I key - ключ
//  I depth - индекс
// Return: bool
// Change History:
//----------------------------------------  
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // Если дерево пустое 
    if (!root)
        return nullptr;

    // если дошли до конца ключа 
    if (depth == key.size()) {

        // Этот узел больше не конец слова 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
    return root;
}
//----------------------------------------
// Function...... friends
// Description... вычисление частоты ключа
// Note.......... 
// Parameters:
//  I root - дерево
// Return: bool
// Change History:
//----------------------------------------  
int friends(TrieNode* node)
{

    if (isEmpty(node))
        return 1;

    int f = 0;

    if (node->isEndOfWord)
        f = 1;

    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (node->children[j])
            f += friends(node->children[j]);
    }

    return f;
}
//----------------------------------------
// Function...... findMinPrefixes
// Description... поиск минимального префикса слова
// Note.......... 
// Parameters:
//  I root - дерево
//  I buf - буфер
//  I ind - индекс
//  I res - результат
// Return: bool
// Change History:
//----------------------------------------  
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    //если узел нулевой
    if (root == nullptr)
        return;

    ////скольким словам принадлежит узел
    //int fr = friends(root);

    ////если только одному слову
    //if (fr == 1)
    //{
    //    //заносим слово в строку вывода
    //    buf[ind] = '\0';
    //    res += buf;
    //    res = res + " ";
    //    return;
    //}

    //если префикс уже есть слово, которое входит в другое слово
    if (root->isEndOfWord)
    {

        buf[ind] = '\0';
        res += buf;
        res += " ";
        cout << res << endl;
    }
    //движение вниз по дереву
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (root->children[j]) {
            buf[ind] = 'a' + j;
            //рекурсивный вызов функции для потомков               
            findMinPrefixes(root->children[j], buf, ind, res);
        }
            
    }
}
//----------------------------------------
// Function...... addition
// Description... рекурсивная функция для печати 
// автоматических предложений для данного узла
// Note.......... 
// Parameters:
//  I root - дерево
//  I currPrefix - текущий префикс
// Return: bool
// Change History:
//----------------------------------------  
void addition(struct TrieNode* root, string currPrefix)
{
    if (isEmpty(root))
    {
        cout << currPrefix << endl;
        return;
    }
    //если префикс уже есть слово, которое входит в другое слово
    if (root->isEndOfWord)
    {
   
        cout << currPrefix << endl;
    }
   
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // добавить текущий символ в строку
            currPrefix.push_back(97 + i);
            
            addition(root->children[i], currPrefix);
            currPrefix.pop_back();
        }      
    }
}
//----------------------------------------
// Function...... printAddition
// Description... вывод предложений для заданного 
// префикса запроса
// Note.......... 
// Parameters:
//  I root - дерево
//  I query - текущий префикс
// Return: bool
// Change History:
//----------------------------------------  
int printAddition(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    char buf[ALPHABET_SIZE];
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }


    bool isWord = (pCrawl->isEndOfWord == true);


    bool isLast = isEmpty(pCrawl);


    if (isWord && isLast)
    {
        //cout << query << endl;
        return -1;
    }

    if (!isLast)
    {
        string prefix = query;
        addition(pCrawl, prefix);
        return 1;
    }
}
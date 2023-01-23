#include "TrieNode.h"
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

//----------------------------------------
// Function...... insert
// Description... ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
// Note.......... 
// Parameters:
//  I root - ������
//  I key - ����
// Return: void
// Change History:
//----------------------------------------
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � ������ ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� �������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ����� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}
//----------------------------------------
// Function...... search
// Description... ���������� true ���� ���� ���� � ������, 
// ����� false 
// Note.......... 
// Parameters:
//  I root - ������
//  I key - ����
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
// Description... ���������� true ���� root ����� ����, 
// ����� false 
// Note.......... 
// Parameters:
//  I root - ������
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
// Description... ����������� ������� �������� ����� �� ������ 
// Note.......... 
// Parameters:
//  I root - ������
//  I key - ����
//  I depth - ������
// Return: bool
// Change History:
//----------------------------------------  
TrieNode* remove(TrieNode* root, string key, int depth)
{
    // ���� ������ ������ 
    if (!root)
        return nullptr;

    // ���� ����� �� ����� ����� 
    if (depth == key.size()) {

        // ���� ���� ������ �� ����� ����� 
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // ���� ���� �� �������� ���������, ������� ���
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // ���� �� ����� �� ����� �����, ���������� �������� ��� ������� 
    // ���������������� ������� 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // ���� � ����� ��� ��������� ����� 
    // (������ ������ ���� ��� �������� �������), 
    // � �� �� ������������� ������ ������. 
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }

    // ���������� ����� ������
    return root;
}
//----------------------------------------
// Function...... friends
// Description... ���������� ������� �����
// Note.......... 
// Parameters:
//  I root - ������
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
// Description... ����� ������������ �������� �����
// Note.......... 
// Parameters:
//  I root - ������
//  I buf - �����
//  I ind - ������
//  I res - ���������
// Return: bool
// Change History:
//----------------------------------------  
void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
    //���� ���� �������
    if (root == nullptr)
        return;

    ////�������� ������ ����������� ����
    //int fr = friends(root);

    ////���� ������ ������ �����
    //if (fr == 1)
    //{
    //    //������� ����� � ������ ������
    //    buf[ind] = '\0';
    //    res += buf;
    //    res = res + " ";
    //    return;
    //}

    //���� ������� ��� ���� �����, ������� ������ � ������ �����
    if (root->isEndOfWord)
    {

        buf[ind] = '\0';
        res += buf;
        res += " ";
        cout << res << endl;
    }
    //�������� ���� �� ������
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (root->children[j]) {
            buf[ind] = 'a' + j;
            //����������� ����� ������� ��� ��������               
            findMinPrefixes(root->children[j], buf, ind, res);
        }
            
    }
}
//----------------------------------------
// Function...... addition
// Description... ����������� ������� ��� ������ 
// �������������� ����������� ��� ������� ����
// Note.......... 
// Parameters:
//  I root - ������
//  I currPrefix - ������� �������
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
    //���� ������� ��� ���� �����, ������� ������ � ������ �����
    if (root->isEndOfWord)
    {
   
        cout << currPrefix << endl;
    }
   
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // �������� ������� ������ � ������
            currPrefix.push_back(97 + i);
            
            addition(root->children[i], currPrefix);
            currPrefix.pop_back();
        }      
    }
}
//----------------------------------------
// Function...... printAddition
// Description... ����� ����������� ��� ��������� 
// �������� �������
// Note.......... 
// Parameters:
//  I root - ������
//  I query - ������� �������
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
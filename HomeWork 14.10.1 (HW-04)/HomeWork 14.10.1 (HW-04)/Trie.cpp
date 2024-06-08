#include "Trie.h"

Trie::Trie()
{
    _root = new Node();
}

Trie::~Trie()
{
    delete _root;
}


void Trie::insert(const std::string& key)
{
    if (search(key)) 
        return;

    Node* node = _root;
    for (unsigned char i = 0; i < key.length(); ++i) 
    {
       
        unsigned char index = key[i] - alphabetStart;
        node = node->goDeepByIndex(index); 
    }
 
    node->setEndOfWord();
}


void Trie::remove(const std::string& key)
{
    if (search(key) == false) 
        return;

    Node* node = _root;
    unsigned char depth = 0;
    for (unsigned char i = 0; i < key.length(); ++i) 
    {
        unsigned char index = key[i] - alphabetStart;
        node = node->lookDeepByIndex(index);   
        if (!node->isVisitedOnce())             
            node->decreaseVisitsCounter();     
        else                                   
            break;                              
        ++depth;                               
    }

    if (depth == key.length())                 
    {                                          
        node->resetEndOfWord();                 
    }
    else
    {
        node = _root;                           
        for (unsigned char i = 0; i < depth; ++i)
        {
            unsigned char index = key[i] - alphabetStart;
            node = node->lookDeepByIndex(index);
        }
        unsigned char index = key[depth] - alphabetStart;

        node->deleteChild(index);              
    }
}

bool Trie::search(const std::string& key) const
{
    Node* node = _root;

    for (unsigned char i = 0; i < key.length(); ++i)
    {
       
        unsigned char index = key[i] - alphabetStart;
        node = node->lookDeepByIndex(index);
       
        if (node == nullptr)
            return false;
    }

    return (node != nullptr && node->isEndOfWord()); 
}

std::string Trie::findMinPrefixes() const
{
    unsigned char buf[biggestWordLength];
    unsigned char ind = 0;
    std::string retVal;
    findMinPrefixes(_root, buf, ind, retVal);
    return retVal;
}

std::string Trie::tryToAutoComplete(const std::string& key) const
{
    if ((key.compare("") == 0) || (this == nullptr) || (_root->isEmpty())) 
        return "";

    Node* node = _root;
    std::string retVal;

    for (unsigned char i = 0; i < key.length(); ++i)
    {
        unsigned char index = key[i] - alphabetStart;
        node = node->lookDeepByIndex(index);
        if (node == nullptr)
            return "";
    }

    if (node != nullptr && !(node->isEndOfWord()) && node->isVisitedOnce())
    {
        while (!node->isEmpty())
        {
            for (unsigned char i = 0; i < alphabetSize; ++i)
                if (node->childExists(i))
                {
                    retVal += (alphabetStart + i);
                    node = node->lookDeepByIndex(i);
                    break;
                }
        }
    }
    if (node != nullptr && !(node->isVisitedOnce())) 
        return "\a";

    return retVal;
}

bool Trie::T9(const std::string& key) const
{
    std::string autoCompleted;
    autoCompleted = tryToAutoComplete(key);

    if (autoCompleted == "")
    {
        std::cout << "T9: " << key << " - не найдено!" << std::endl;
        return true;
    }
    else
        if (autoCompleted == "\a")
            std::cout << "T9: " << key << " - несколько вариантов!" << std::endl;
        else
        {
            std::cout << "T9: " << key << "_" << autoCompleted << std::endl;
            return true;
        }
    return false;
}

void Trie::print() const
{
    Node* node = _root;
    print(node, "");
    std::cout << std::endl;
}

Trie* operator>>(std::ifstream& fileId, Trie* trie)
{
    const unsigned char wordMinLength = 3;
    std::string newWord;
    bool wordIsOk;
    if (fileId.is_open())
    {
        while (std::getline(fileId, newWord)) 
        {
            wordIsOk = newWord.length() > wordMinLength;
            for (unsigned char i = 0; i < newWord.length(); ++i)
                if ((newWord[i] < alphabetStart) || (newWord[i] > alphabetEnd)) 
                {
                    wordIsOk = false;
                    break;
                }
            if (wordIsOk)
                trie->insert(newWord);
        }
        fileId.close();
    }
    return trie;
}


bool Trie::loadVocabulary(const std::string& fileName)
{
    std::ifstream fileId(fileName);
    if (fileId.is_open())
    {
        fileId >> this;
        fileId.close();
        return true;
    }
    return false;
}

void Trie::print(Node* node, const std::string& fullWord) const
{
    if (node->isEndOfWord()) 
    {
        std::cout << fullWord << std::endl;
        if (node->isEmpty())
            return;
    }

    for (unsigned char i = 0; i < alphabetSize; ++i)
        if (node->childExists(i))
            print(node->lookDeepByIndex(i), fullWord + (char)(alphabetStart + i)); 
}

void Trie::findMinPrefixes(Node* root, unsigned char buf[], unsigned char ind, std::string& res) const
{
    if (root == nullptr)
        return;

    if (ind > biggestWordLength - 1)
        return;

    if (root->isVisitedOnce())
    {
        for (unsigned char i = 0; i < ind; ++i)
            res += buf[i];
        res += " ";
        return;
    }

    for (unsigned char i = 0; i < alphabetSize; ++i)
    {
        Node* node = root->lookDeepByIndex(i);
        if (node != nullptr)
        {
            buf[ind] = i + alphabetStart;
            findMinPrefixes(node, buf, ind + 1, res);
        }
    }
}
#include "Node.h"

Node::Node() : _isEndOfWord(false), _visitedTimes(0)
{
    _children = new Node * [alphabetSize];
    for (unsigned char i = 0; i < alphabetSize; ++i)
        _children[i] = nullptr;
}


Node::~Node()
{
    for (unsigned char i = 0; i < alphabetSize; ++i)
        if (_children[i] != nullptr)
            delete _children[i];
    delete[] _children;
}


void Node::addChild(const unsigned char& index)
{
    _children[index] = new Node();
}


void Node::deleteChild(const unsigned char& index)
{
    Node* node = lookDeepByIndex(index);
    if (node != nullptr)
        delete node; 
    _children[index] = nullptr;
}


bool Node::isEmpty() const
{
    for (unsigned char i = 0; i < alphabetSize; ++i)
        if ((this->_children[i]) != nullptr)
            return false;
    return true;
}


bool Node::childExists(const unsigned char& index) const
{
    return (_children[index] != nullptr);
}


Node* Node::goDeepByIndex(const unsigned char& index)
{
    Node* node = this;


    if (!node->childExists(index))
        node->addChild(index);

    node = node->_children[index];
    node->increaseVisitsCounter(); 

    return node;
}

Node* Node::lookDeepByIndex(const unsigned char& index)
{
    if ((this == nullptr) || (this->_children == nullptr))
        return nullptr;
    return _children[index];
}

void Node::setEndOfWord()
{
    _isEndOfWord = true;
}

void Node::resetEndOfWord()
{
    _isEndOfWord = false;
}

bool Node::isEndOfWord() const
{
    return _isEndOfWord;
}

void Node::increaseVisitsCounter()
{
    ++_visitedTimes;
}

void Node::decreaseVisitsCounter()
{
    if (_visitedTimes > 0)
        --_visitedTimes;
}

bool Node::isVisitedOnce() const
{
    return (_visitedTimes == 1);
}
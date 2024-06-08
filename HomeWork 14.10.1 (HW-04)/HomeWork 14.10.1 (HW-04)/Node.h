#pragma once
#include <iostream>

using visitedTimesType = int16_t; 
constexpr char alphabetStart = 'a';
constexpr char alphabetEnd = 'z';

constexpr char alphabetSize = alphabetEnd - alphabetStart + 1;


// ===================================== //
// ==  Класс узла префиксного дерева  == //
// ===================================== //
class Node
{
public:
	Node();
	~Node();

	void addChild(const unsigned char& index);			
	void deleteChild(const unsigned char& index);		

	bool isEmpty() const;								
	bool childExists(const unsigned char& index) const;	

	Node* goDeepByIndex(const unsigned char& index);	
														

	Node* lookDeepByIndex(const unsigned char& index);	

	void setEndOfWord();								
	void resetEndOfWord();								
	bool isEndOfWord() const;							

	void increaseVisitsCounter();						
	void decreaseVisitsCounter();						
	bool isVisitedOnce() const;							

private:
	Node** _children;									
	bool _isEndOfWord;									
	visitedTimesType _visitedTimes;						
};
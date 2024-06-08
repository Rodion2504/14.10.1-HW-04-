#pragma once
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iostream>

constexpr char biggestWordLength = 35;

// ================================ //
// ==  Класс префиксного дерева  == //
// ================================ //

class Trie
{
public:
	Trie();
	~Trie();

	void insert(const std::string& key);							
	void remove(const std::string& key);							
	bool search(const std::string& key) const;						
	std::string findMinPrefixes() const;							
																	

	std::string tryToAutoComplete(const std::string& key) const;	
	bool T9(const std::string& key) const;							

	void print() const;												
	friend Trie* operator>>(std::ifstream& fileId, Trie* trie);		
	bool loadVocabulary(const std::string& fileName);				

private:
	Node* _root;												

	void print(Node* node, const std::string& prefix) const;		
	void findMinPrefixes(Node* root, unsigned char buf[],		 
		unsigned char ind, std::string& res) const;					

};
#include <iostream>
#include <string>
#include "Trie.h"

int main()
{
	setlocale(LC_ALL, "");

	Trie* trie = new Trie();							

	std::string vocabularyFileName = "english-words.95";// Имя файла словаря (взят из http://wordlist.aspell.net/)

	trie->loadVocabulary(vocabularyFileName);		
	//std::ifstream fileId(vocabularyFileName);
	//fileId >> trie;								

	
	/*
	std::cout << trie->search("errorful") << std::endl;	
	trie->remove("errorful");							
	std::cout << trie->search("errorful") << std::endl;	
	*/
	//trie->print();										
	//std::cout << trie->findMinPrefixes();				


	std::cout << std::endl << "Автодополнение: пожалуйста, введите префикс или \'exit\' остановиться" << std::endl;
	std::string prefix;
	do
	{
		std::cin >> prefix;
		trie->T9(prefix);								
														
	} while (prefix.compare("exit") != 0);

	delete trie;

	return 0;
}
/**
* @class Dic_reader
*
* @brief Classe principal da API de importacao de dicionario, onde estao presentes as funcoes de leitura do dicionario, tem como datamembers sets de Word e Rule, sendo que e tambem responsavel por fazer a ligacao entre os 2, conjugando as palavras com as respectivas regras, e onde reside a funcao de Auto-Complete propriamente dita.
* @author Jorge Silva - ei09016
* @author Tiago Mota - ei09068
*
* $Header $
*/

#ifndef DIC_READER_H_
#define DIC_READER_H_

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rule.h"
#include "word.h"

using namespace std;

class Dic_reader {
private:
	string dic_path;
	string aff_path;
	set<Word> palavras;
	set<Rule> regras;
public:
	Dic_reader();
	string toLower(string s);
	Dic_reader(string dic_path , string aff_path);
	virtual ~Dic_reader();
	void read();
	void readAff();
	void readDic();
	vector<string> conjuga (string word);
	vector<string> conjuga (set<Word>::iterator itw);
	bool validCompletation (string fragment, string word);
	vector<string> autoComplete (string s);
};

#endif /* DIC_READER_H_ */

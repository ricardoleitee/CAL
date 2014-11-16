/**
* @class Rule
*
* @brief Identificada por um tipo (char), e responsavel por ter agrupadas todas as alineas de uma dada transformacao, seja ela mudanca de numero, genero, tempo.
* @author Jorge Silva - ei09016
* @author Tiago Mota - ei09068
*
* $Header $
*/

#ifndef RULE_H_
#define RULE_H_

#include <string>
#include <iostream>
#include "alinea.h"

using namespace std;

class Rule {
private:
	char tipo;
	vector<Alinea> alineas;

public:
	Rule(char tipo);
	virtual ~Rule();
	void addAlinea(string Line);
	vector<string> getCombinacoes(const string word) const;
    char getTipo() const;
    void setTipo(char tipo);
    bool operator == (const Rule &r2) const;
    bool operator < (const Rule &r2) const;
    bool operator > (const Rule &r2) const;
};

#endif /* RULE_H_ */

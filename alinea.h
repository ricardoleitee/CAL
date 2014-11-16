/**
* @class Alinea
*
* @brief Classe responsavel por conter a informacao de uma alinea de uma dada regra, contem a sucessao de caracteres necessarios para aplicar uma transformacao a uma dada palavra valida, e capaz de processar texto do mesmo genero que o contido no ficheiro aff, criando toda a estrutura logica necessaria para aplicar a dada transformacao.
* @author Jorge Silva - ei09016
* @author Tiago Mota - ei09068
*
* $Header $
*/

#ifndef ALINEA_H_
#define ALINEA_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct t{
	string letras;
	bool isConjunto;
	bool necessario;
};
typedef struct t Terminacao;

class Alinea {
private:
	vector<Terminacao> regras;
	string remocao;
	string adicao;
	int n_chars_terminacao;
public:
	Alinea(string line);
	virtual ~Alinea();
	void novaTerminacao(string line);
	bool obedeceTerminacao(string word) const;
	string conjuga(string word) const;
};

#endif /* ALINEA_H_ */

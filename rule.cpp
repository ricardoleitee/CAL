#include "rule.h"

/**
 * construtor da classe Rule
 * @param tipo tipo de regra
 */
Rule::Rule(char tipo) {
	this->tipo=tipo;
}

Rule::~Rule() {
	// TODO Auto-generated destructor stub
}

/**
 * adiciona uma alinea apartir duma linha do ficheiro .aff
 * @param line linha extraida do ficheiro .aff
 */
void Rule::addAlinea(string line)
{
	alineas.push_back(Alinea(line));
}

char Rule::getTipo() const
{
    return tipo;
}

void Rule::setTipo(char tipo)
{
    this->tipo = tipo;
}

/**
 * gera todas as combinacoes de uma dada palavra, conjugando-a com todas as alineas
 * @param word palavra a conjugar
 * @return vector de strings com todas as conjugacoes da dada palavra
 */
vector<string> Rule::getCombinacoes( const string word) const
{
	vector<string> v;
	for(size_t i=0;i<alineas.size();i++)
	{
		string tmp = alineas[i].conjuga(word);
		if(tmp!="")
			v.push_back(tmp);
	}
	return v;
}

bool Rule::operator ==(const Rule &r2) const
{
	return (tipo==r2.getTipo());
}

bool Rule::operator <(const Rule &r2) const
{
	return (tipo < r2.getTipo());
}

bool Rule::operator >(const Rule &r2) const
{
	return (tipo > r2.getTipo());
}

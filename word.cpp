#include "Word.h"

/**
 * construtor para a classe Word
 * @param line string com a palavra da Word a criar
 * @param b booleano que deve conter true caso a string recebida seja uma linha de importacao do ficheiro .dic
 */
Word::Word(string line,bool b) {
	if(b)
		{
		size_t i=0;
		while(line[i]!='/' && line[i]!= '	')
			i++;

		word = line.substr(0,i);
		if(line[i]=='/')
		{
			size_t j=i+1;
			while(line[j]!= '	')
				j++;
			rules = line.substr(i+1,j-i-1);
		}
	}
	else
		word= line;
}

string Word::getRules() const
{
    return rules;
}

string Word::getWord() const
{
    return word;
}

void Word::setRules(string rules)
{
    this->rules = rules;
}

void Word::setWord(string word)
{
    this->word = word;
}

bool Word::operator ==(const Word &p2) const
{
	return (p2.getWord()==word);
}

bool Word::operator <(const Word &p2) const
{
	return (word < p2.getWord());
}

bool Word::operator >(const Word &p2) const
{
	return (word > p2.getWord());
}

/**
 * verifica se um dado fragmento de palavra é "parecido" com a palavra guardada pela instancia de Word
 *
 * para isto sao comparadas as duas strings, sendo que sao consideradas parecidas quando 2/3 da palavra inicial é igual
 *
 * @param s fragmento a verificar
 *
 * @return true caso fragmento valido
 */
bool Word::beginLooksLike (string s) const
{
	//considerada que é parecida se s corresponder a 2/3 da palavra
	size_t limit = (size_t) 2*(word.size()/3);
	for(size_t i=0; i < limit && i< s.size(); i++)
		if(tolower(word[i])!=tolower(s[i]))
			return false;
	return true;
}



Word::~Word() {
}

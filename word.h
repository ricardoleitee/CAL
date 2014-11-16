/**
* @class Word
*
* @brief Contem uma palavra e um identificador de todas as regras que podem nela ser aplicadas.
* @author Jorge Silva - ei09016
* @author Tiago Mota - ei09068
*
* $Header $
*/

#ifndef WORD_H_
#define WORD_H_
#define TAB 9

#include <string>
#include <iostream>

using namespace std;

class Word {
private:
	string word;
	string rules;
public:
	Word(string line,bool b);
	virtual ~Word();
    string getRules() const;
    string getWord() const;
    void setRules(string rules);
    void setWord(string word);
    bool beginLooksLike (string s) const;
    bool operator ==(const Word &p2) const;
    bool operator <(const Word &p2) const;
    bool operator >(const Word &p2) const;
};

#endif /* WORD_H_ */

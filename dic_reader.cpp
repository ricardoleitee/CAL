#include "dic_reader.h"

/**
 * construtor por defeito da classe dic_reader, inicia o dicionario default como pt-PT
 */
Dic_reader::Dic_reader(){
	this->dic_path="pt-PT.dic";
	this->aff_path= "pt-PT.aff";
}

/**
 * passa uma string a minusculas e devolve-a
 * @param s string a processar
 * @retun string processada
 */
string Dic_reader::toLower(string s)
{
	for(size_t i=0; i<s.size(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

/**
 * construtor classe dic_reader
 * @param dic_path path do ficheiro *.dic
 * @param aff_path path do ficheiro *.aff
 */
Dic_reader::Dic_reader(string dic_path , string aff_path)
{
	this->dic_path=dic_path;
	this->aff_path=aff_path;
}
/**
 * destrutor por defeito da class dic_reader
 */
Dic_reader::~Dic_reader() {
}

/**
 * funcao responsavel pela importacao do ficheiro .aff
 */
void Dic_reader::readAff()
{
	string line;
	ifstream aff_file (aff_path.c_str());
	if (aff_file.is_open())
	{
		while ( aff_file.good() )
		{
			getline (aff_file,line);
			//	      cout << line << endl;
			if(line[0]=='S' && line[1]=='F' && line[2]=='X')
			{
				int n_alineas = atoi(line.substr(8,line.length()).c_str());
				Rule regra (line[4]);
				//cout << line  << "    "<<n_alineas<< endl;
				for(int i=0;i< n_alineas;i++)
				{
					getline (aff_file,line);
					regra.addAlinea(line);
				}
				regras.insert(regra);
			}
		}
		aff_file.close();
	}

	else
	{
		cout << "Unable to open .aff file" << endl;
	}
}

/**
 * funcao responsavel pela importacao do ficheiro .dic
 */
void Dic_reader::readDic()
{
	string line;
	ifstream dic_file (dic_path.c_str());
	if (dic_file.is_open())
	{
		getline (dic_file,line);
		int n_lines =atoi(line.c_str());
		for(int i=0; i<n_lines;i++)
		{
			getline (dic_file,line);
			palavras.insert(Word(line,true));
			//palavras.insert(Word(line));
		}
		dic_file.close();
	}

	else
	{
		cout << "Unable to open .dic file" << endl;
	}
}

/**
 * 	devolve todas as conjugacoes de uma dada palavra
 * 	@param word palavra a conjugar
 * 	@return vector com todas as conjugacoes da palavra dada
 */
vector<string> Dic_reader::conjuga (string word)
{
	vector<string> vs;
	set<Word>::iterator itw;
	itw = palavras.find(Word(word,false));
	if(itw!=palavras.end())
	{
		string regras_to_use =(*itw).getRules();
		for(size_t i=0; i < regras_to_use.length() ; i++)
		{
			set<Rule>::iterator itr;
			itr=regras.find(regras_to_use[i]);
			if(itr!=regras.end())
			{
				vector<string> tmp;
				string s =(*itw).getWord();
				tmp = (*itr).getCombinacoes(s);
				for(size_t k=0; k < tmp.size(); k++)
					vs.push_back(tmp[k]);
			}
		}
	}
	return vs;
}


/**
 * 	devolve todas as conjugacoes de uma palavra de um dado iterador do set palavras
 * 	@param itw iterador com a palavra a conjugar
 * 	@return vector com todas as conjugacoes da palavra pretendida
 */
vector<string> Dic_reader::conjuga (set<Word>::iterator itw)
{
	vector<string> vs;
	if(itw!=palavras.end())
	{
		string regras_to_use =(*itw).getRules();
		for(size_t i=0; i < regras_to_use.length() ; i++)
		{
			set<Rule>::iterator itr;
			itr=regras.find(regras_to_use[i]);
			if(itr!=regras.end())
			{
				vector<string> tmp;
				string s =(*itw).getWord();
				tmp = (*itr).getCombinacoes(s);
				for(size_t k=0; k < tmp.size(); k++)
					vs.push_back(tmp[k]);
			}
		}
	}
	return vs;
}



/**
 * 	devolve todas as possiveis palavras que completem a string recebida
 * 	@param s fragmento de palavra a completar
 * 	@return vector com todas as palavras que completam a string recebida
 */
vector<string> Dic_reader::autoComplete (string s)
{
	vector<string> vs;
	set<Word>::iterator it;
	for (it=palavras.begin(); it!=palavras.end(); it++)
	{
		if((*it).beginLooksLike(s))
		{
			if(validCompletation(s,it->getWord()))
				vs.push_back(it->getWord());
			vector<string> tmp = conjuga (it);
			for(size_t i=0; i < tmp.size();i++)
				if(validCompletation(s,tmp[i]))
					vs.push_back(tmp[i]);
		}
	}
	return vs;
}

/**
 * 	verifica se uma palavra completa um fragmento dado
 * 	@param fragment fragmento de palavra a completar
 * 	@param word sugestao de palavra para completar o fragmento
 * 	@return true se palavra sugerida e valida
 */
bool Dic_reader::validCompletation (string fragment, string word)
{
	for(size_t i=0; i< fragment.size(); i++)
		if(tolower(fragment[i])!=tolower(word[i]))
			return false;
	return true;
}

/**
 * 	funcao responsavel pela chamada das funcoes que efectuam a importacao dos ficheiros do dicionario
 */
void Dic_reader::read()
{
	readAff();
	readDic();
}

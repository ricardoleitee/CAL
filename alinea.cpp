#include "Alinea.h"

/**
 * construtor para a classe Alinea
 * @param line linha do ficheiro aff a processar
 */
Alinea::Alinea(string line) {
	n_chars_terminacao=0;
	line =line.substr(8,line.length());//cortar parte inicial desnecessaria
	int i=1;
	while(line[i]!= ' ')
		i++;
	remocao = line.substr(0,i);
	if(remocao=="0")
		remocao="";
	while(line[i]== ' ')
			i++;
	line =line.substr(i,line.length());//cortar parte inicial desnecessaria
	i=0;
	while(line[i]!= ' ')
			i++;
	adicao = line.substr(0,i);

	while(line[i]== ' ')
				i++;
	line =line.substr(i,line.length());//cortar parte inicial desnecessaria

	i=0;
	while(line[i]!= ' ')
			i++;
	//cout<< line.substr(0,i) << endl;
	novaTerminacao(line.substr(0,i));
}

/**
 * gera uma nova terminacao apartir da string recebida
 * @param line string com a informacao sobre a terminacao a criar
 */
void Alinea::novaTerminacao(string line)
{
	int found;
	while(!line.empty())
	{
		Terminacao t;
		found = line.find('[');
		if(found!=0)
		{
			if(found==-1)
				t.letras= line;//.substr(0,line.length());
			else
				t.letras= line.substr(0,found);
			//cout << t.letras << endl;
			n_chars_terminacao+=t.letras.length();

			t.necessario=true;
			t.isConjunto=true;
			regras.push_back(t);
			if(found==-1)
				break;
			line= line.substr(0,found);
			//line= line.substr(found,line.length());

		}
		else
		{
			int found_end= line.find(']');
			t.letras= line.substr(found,found_end+1);
			t.necessario = t.letras[1]!='^';
			t.isConjunto=false;
			if(!t.necessario)
				t.letras.erase(t.letras.begin()+1); //caso necessario remover ^ da string
			t.letras.erase(t.letras.begin()); //remover [ da string
			t.letras.erase(t.letras.end()-1); //remover ] da string
			line= line.substr(found_end+1,line.length()-found_end-1); //apagar desde o inicio da string até ao ]
			n_chars_terminacao++;
			regras.push_back(t);
		}
		//cout << "letras: " << t.letras << " necessario: " << t.necessario << " conjunto: " <<t.isConjunto << endl;
	}
}

/**
 * verifica se uma dada palavra obedece as terminacoes pre carregadas
 * @param word palavra a verificar
 * @return true se palavra valida
 */
bool Alinea::obedeceTerminacao(string word) const
{
	if((int)word.length()<n_chars_terminacao)
		return false;

	string validacao = word.substr(word.length()-n_chars_terminacao,word.length());
	for(size_t i=0; i<regras.size(); i++)
	{
		if(regras[i].isConjunto)
		{
			string tmp= validacao.substr(validacao.length()-regras[i].letras.length(),validacao.length());
			if(regras[i].necessario && tmp != regras[i].letras)
				return false;
			else
				if(!regras[i].necessario && tmp == regras[i].letras)
					return false;
		}
		else
		{
			char tmp = validacao[0];
			validacao = validacao.substr(1,validacao.length());
			if(regras[i].necessario)
			{
				if((int)regras[i].letras.find(tmp) == -1) //se uma letra for necessaria e a palavra n a tiver nao e valida
					return false;
			}
			else
			{
				if((int)regras[i].letras.find(tmp) != -1) //se uma letra for proibida e a palavra a tiver nao e valida
					return false;
			}
		}
	}
	return true;
}

/**
 * conjuga uma determindada palavra conforme as regras impostas
 * @param word palavra a conjugar
 * @return palavra conjugada ou string nula caso palavra nao obedeca a terminacao imposta pela alinea
 */
string Alinea::conjuga(string word) const
{
	if(!obedeceTerminacao(word))
	{
		return "";
	}
	if(remocao!="");
		word = word.substr(0,word.length()-remocao.length());
	word += adicao;
	return word;
}

Alinea::~Alinea() {
	// TODO Auto-generated destructor stub
}

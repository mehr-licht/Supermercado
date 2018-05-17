/*
 * matcher.cpp
 *
 *  Created on: 13/05/2018
 *      Author: luis
 */

#include "matcher.h"

using namespace std;

#define MIN(x,y) ((x) < (y) ? (x) : (y))

bool findStringNaive(string pattern, string text) {
	unsigned int j = 0;

	for (unsigned int i = 0; i < text.size(); i++) {
		if (pattern[j] != text[i])
			j = 0;
		else {
			if (j == pattern.size() - 1)
				return true;
			j++;
		}
	}

	return false;
}

void computePrefixFunction(string toSearch, int pi[]) {
	int m = toSearch.length();
	pi[0] = 0;
	int k = 0;

	for (int q = 1; q < m; q++) {
		while (k > 0 && toSearch[k] != toSearch[q])
			k = pi[k];
		if (toSearch[k] == toSearch[q])
			k++;
		pi[q] = k;

	}

	return;
}

void a2pre_kmp(string pattern, vector<int> & prefix) {
	int m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q])
			k = k + 1;
		prefix[q] = k;
	}
}

void a3preKMP(string pattern, int f[]) {
	int m = pattern.size(), k;
	f[0] = -1;
	for (int i = 1; i < m; i++) {
		k = f[i - 1];
		while (k >= 0) {
			if (pattern[k] == pattern[i - 1])
				break;
			else
				k = f[k];
		}
		f[i] = k + 1;
	}
}

int b1kmpMatcher(string text, string pattern) {
	int num = 0;
	int m = pattern.length();
	vector<int> prefix(m);
	a2pre_kmp(pattern, prefix);

	int n = text.length();

	int q = -1;
	for (int i = 0; i < n; i++) {
		while (q > -1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i])
			q++;
		if (q == m - 1) {
			//cout <<"pattern occurs with shift" << i-m+1 << endl;
			num++;
			q = prefix[q];
		}
	}
	return num;
}

bool kmpMatcher(string text, string pattern) {
	int m = pattern.size();
	int n = text.size();
	int f[m];

	a3preKMP(pattern, f);

	int i = 0;
	int k = 0;
	while (i < n) {
		if (k == -1) {
			i++;
			k = 0;
		} else if (text[i] == pattern[k]) {
			i++;
			k++;
			if (k == m)
				return true;
		} else
			k = f[k];
	}
	return false;
}
/*
 int numStringMatching(string filename, string toSearch) {
 ifstream inputFile;
 inputFile.open(filename.c_str());

 int counter = 0;

 while (!inputFile.eof()) {
 string input;
 getline(inputFile, input);

 int n = input.length();
 int m = toSearch.length();
 int pi[toSearch.length()];
 computePrefixFunction(toSearch, pi);
 int q = 0;

 for (int i = 0; i < n; i++) {
 while (q > 0 && toSearch[q] != input[i])
 q = pi[q - 1];

 if (input[i] == toSearch[q])
 q++;

 if (q == m) {
 cout << "Pattern occurs with shift " << i - m + 1 << endl;
 q = pi[q - 1];
 counter++;
 }
 }
 }

 inputFile.close();
 return counter;
 }
 */
vector<int> numStringMatching(string filename, string toSearch) {

	ifstream file(filename.c_str());
	if (!file) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;
	}

	string line;
	vector<int> ids;

	if (!file) {
		cout < "Erro a abrir ficheiro de leitura\n";
		return ids;
	}
	int i = 1;

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;

		getline(linestream, s, ';');
		getline(linestream, s, ';');
		if (kmpMatcher(s, toSearch) == 1) {
			ids.push_back(i);
		}
		getline(linestream, s, ';');
		getline(linestream, s, ';');
		getline(linestream, s, ';');
		i++;
	}
	file.close();
	return ids;
}

vector<int> numStringMatchingRoad(string filename, string toSearch) {

	ifstream file(filename.c_str());
	if (!file) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;
	}

	string line;
	vector<int> ids;

	if (!file) {
		cout < "Erro a abrir ficheiro de leitura\n";
		return ids;
	}
	int i = 1;

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;

		getline(linestream, s, ';');
		getline(linestream, s, ';');
		if (kmpMatcher(s, toSearch) == 1) {
			ids.push_back(i);
		}
		getline(linestream, s, ';');

		i++;
	}
	file.close();
	return ids;
}


vector<int> numStringMatchingFreg(string filename, string toSearch) {

	ifstream file(filename.c_str());
	if (!file) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;
	}

	string line;
	vector<int> ids;

	if (!file) {
		cout < "Erro a abrir ficheiro de leitura\n";
		return ids;
	}
	int i = 1;

	while (getline(file, line)) {
		stringstream linestream(line);
		string s;

		getline(linestream, s, ';');
		getline(linestream, s, ';');

		getline(linestream, s, ';');
		getline(linestream, s, ';');
		if (kmpMatcher(s, toSearch) == 1) {
					ids.push_back(i);
				}
		getline(linestream, s, ';');
		i++;
	}
	file.close();
	return ids;
}



int editDistance(string pattern, string text) {
	int n = text.length();
	int m = pattern.length();
	int old, neww;
	vector<int> d(n + 1);

	for (int j = 0; j <= n; j++)
		d[j] = j;

	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == text[j - 1])
				neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}
/*
 float numApproximateStringMatching(string filename, string toSearch) {
 // TODO
 return 0;
 }
 */
vector<float> numApproximateStringMatching(string filename, string toSearch) {

	ifstream fich(filename.c_str());
	vector<float> values;
	if (!fich) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;

	}
	string line, word1;
	int num = 0, nwords = 0;

	while (getline(fich, line)) {

		num = 0;
		nwords = 0;
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		getline(linestream, s, ';');

		stringstream s1(s);
		while (!s1.eof()) {

			s1 >> word1;
			num += editDistance(toSearch, word1);
			nwords++;
		}

		float res = (float) num / nwords;//num=distancia de edição; res=distancia na pesquisa por numero de palavras no texto
		values.push_back(res);
	}

	fich.close();

	return values;
}

vector<float> numApproximateStringMatchingRoad(string filename, string toSearch) {

	ifstream fich(filename.c_str());
	vector<float> values;
	if (!fich) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;

	}
	string line, word1;
	int num = 0, nwords = 0;

	while (getline(fich, line)) {

		num = 0;
		nwords = 0;
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		getline(linestream, s, ';');

		stringstream s1(s);
		while (!s1.eof()) {

			s1 >> word1;
			num += editDistance(toSearch, word1);
			nwords++;
		}

		float res = (float) num / nwords;
		values.push_back(res);
	}

	fich.close();

	return values;
}


vector<float> numApproximateStringMatchingFreg(string filename, string toSearch) {

	ifstream fich(filename.c_str());
	vector<float> values;
	if (!fich) {
		cout << "ficheiro " << filename << " nao encontrado " << endl;

	}
	string line, word1;
	int num = 0, nwords = 0;

	while (getline(fich, line)) {

		num = 0;
		nwords = 0;
		stringstream linestream(line);
		string s;
		getline(linestream, s, ';');
		getline(linestream, s, ';');
		getline(linestream, s, ';');
				getline(linestream, s, ';');
		stringstream s1(s);
		while (!s1.eof()) {

			s1 >> word1;
			num += editDistance(toSearch, word1);
			nwords++;
		}

		float res = (float) num / nwords;
		values.push_back(res);
	}

	fich.close();

	return values;
}

vector<string> splitter(string original) {
	vector<string> result;
	stringstream temp(original);
	string token;
	while (temp >> token)
		result.push_back(token);
	return result;
}

bool notStretName(string text) {
	return text != "Rua" && text != "rua" && text != "Estrada"
			&& text != "estrada" && text != "Avenida" && text != "avenida"
			&& text != "Alameda" && text != "alameda" && text != "Praça"
			&& text != "praça" && text != "Praca" && text != "praca"
			&& text != "Praceta" && text != "praceta" && text != "Largo"
			&& text != "largo" && text != "Ruela" && text != "ruela"
			&& text != "Travessa" && text != "travessa" && text != "de"
			&& text != "De" && text != "da" && text != "Da" && text != "do"
			&& text != "Do" && text != "dos" && text != "Dos" && text != "das"
			&& text != "Das" && text != "Via" && text != "via"
			&& text != "Viaduto" && text != "viaduto";
}

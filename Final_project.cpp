//============================================================================
// Name        : Final_project.cpp
// Author      : Paul Narup
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>//check for number input
using namespace std;

vector<string> english_words;//total possible different words to translate;
vector<string> minion_words;//minion translations
vector<string> all_words;//words from user's file
vector<string> translated_words;//translated results


string toLower(string str){//changes string to lowercase
	for(int i = 0; i<str.length();i++){
		if(isupper(str[i])){
			str[i] = tolower(str[i]);
		}
	}
	return str;
}

/*
 * puts english words into one vector
 * puts minion words into another vector
 * index of english word and minion translation are equal
 */
void get_trans(char * file_name){
	string line, tempword1,tempword2="";
	int pos;
	ifstream transIn;
	transIn.open(file_name);
	if(!transIn.is_open()){
		cout<<"The translation file could not be opened, check location\n";
	}else{
		while(getline(transIn,line)){
			tempword1 ="";
			tempword2 ="";
			pos = line.find('=');
			for(int i = 0; i<line.length();i++){
				if(i<pos){
					tempword1 += line[i];
				}else if(i>pos){
					tempword2 += line[i];
				}
			}
			minion_words.push_back(toLower(tempword1));
			english_words.push_back(toLower(tempword2));
		}
	}
}
/*
 * reads lines in file
 * separates words in line by spaces and punctuation
 * adds words to all_words
 */
void read_file(){
	ifstream test_file;
	string file_name, line, tempword,spaces,temp_upper;

	cout<<"What file would you like to translate?"<<endl;
	cin>>file_name;
	test_file.open(file_name.c_str());
	if(test_file.is_open()){
		while(getline(test_file,line)){
			for(int i =0;i<line.length();i++){
				if(line[i]=='.'||line[i]=='!'|| line[i]=='?'){
					temp_upper = tempword;
					all_words.push_back(temp_upper);//pushes tempword once punc. or space is reached
					tempword ="";
					spaces = line[i];//location of punc. or space
					all_words.push_back(spaces);
				}else{
					tempword +=line[i];
				}
			}
			all_words.push_back("\n");
		}
	}else{
		cout<<"The file could not be opened, check location\n";
		read_file();
	}


}




/*
 * compares words from file with the english words
 * if word is found pushes translated version of word
 * else pushed the word from original file
 */
bool add_translated_words(){
	string temp,original, matchCase, phrase;
	int startpos, endpos, length;
	cout<<"\n";
	for(int i =0; i<all_words.size();i++){//loops all words
		matchCase = all_words[i];
		phrase = toLower(all_words[i]);
		for(int k =0; k<english_words.size();k++){//loops english words finding if all_words contains them
			if(phrase.find(english_words[k])!= string::npos){//if found erase english and insert minion
				startpos = phrase.find(english_words[k]);
				endpos = startpos + english_words[k].length();
				length = endpos - startpos;
				phrase.erase(startpos, length);
				phrase.insert(startpos, minion_words[k]);
				if(isupper(matchCase[0])||isupper(matchCase[1])){//first letter of sentence capitalization
					if(phrase[0]==' '){//checks for space after punctuation
						phrase[1] = toupper(phrase[1]);
					}else{
						phrase[0] = toupper(phrase[0]);
					}
				}

			}
		}
		translated_words.push_back(phrase);
	}



	return false;
}

void write_to_file(){
	ofstream outfile;
	int temp;

	cout<<"Would you like a new file or include translation in the old file to compare?"<<endl;
	cout<<"Press 1 for new file. Press 2 for compare file."<<endl;
	while(!(cin >> temp)|| (temp!=1 && temp!=2)){//check for numerical input and value
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Press 1 for new file. Press 2 for compare file."<<endl;
	}
	if(temp ==1){
		outfile.open("translation.txt");
		for(int j=0;j<translated_words.size();j++){
			outfile<<translated_words[j];
		}
		outfile.close();
	}else{
		outfile.open("comparision.txt");
		for(int i=0;i<all_words.size();i++){
			outfile<<all_words[i];
		}
		outfile<<"\n";
		for(int j=0;j<translated_words.size();j++){
			outfile<<translated_words[j];
		}
		outfile.close();
	}




}

int main() {
	char type;
	get_trans("minion_to_english.txt");
	read_file();
	add_translated_words();
	write_to_file();

	do
	{
	    cout << "Would you like the translation written to the console? [y/n]" << endl;
	    cin >> type;
	}
	while( !cin.fail() && type!='y' && type!='n' );
	if(type == 'y'){
		for(int i = 0; i<translated_words.size(); i++){
			cout<<translated_words[i];
		}

	}
	return 0;
}

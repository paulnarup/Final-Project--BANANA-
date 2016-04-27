//============================================================================
// Name        : Final_project.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> english_words;//total possible different words to translate;
vector<string> minion_words;
vector<string> all_words;
vector<string> translated_words;
vector<string> temp_vec;

string toLower(string str){
	for(int i = 0; i<str.length();i++){
		if(isupper(str[i])){
			str[i] = tolower(str[i]);
		}
	}
	return str;
}

/*
 * reads file with translations seperated by '='
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
void read_file(char * file_name){
	ifstream test_file;
	string line, tempword,spaces,temp_upper;
	int j=0;
	test_file.open(file_name);
	if(!test_file.is_open()){
		cout<<"The file could not be opened, check location\n";
	}else{
		while(getline(test_file,line)){
			for(int i =0;i<line.length();i++){
				if(line[i]==' '||line[i]==','||line[i]=='.'|| line[i]=='-'|| line[i]=='!'|| line[i]=='?'){
					temp_upper = tempword;
					all_words.push_back(temp_upper);//pushes tempword once punc. or space is reached
					tempword ="";
					spaces = line[i];//location of punc. or space
					all_words.push_back(spaces);
				}else{
					tempword +=line[i];
				}
			}
		}
	}
	for(int i = 0;i<all_words.size();i++){
		cout<<all_words[i];
	}
}

/*
 * searches for word in vector
 * returns true if found
 */
bool find_word(string word,vector <string> vec){

	if(find(vec.begin(),vec.end(),word) != vec.end()){
		return true;
	}else{
		return false;
	}
}

/*
 * compares words from file with the english words
 * if word is found pushes translated version of word
 * else pushed the word from original file
 */
bool add_translated_words(){
	string temp,original, matchCase;
	cout<<"\n";
	for(int i =0; i<all_words.size();i++){//loops all words
		original = all_words[i];
		if(find_word(toLower(all_words[i]),english_words)){//finds word in english translations
			temp = toLower(all_words[i]);
			for(int j = 0;j<english_words.size();j++){//finds index in english words to find translation
				if(temp == english_words[j]){
					if(isupper(original[0])){//fixes capitalization problem at beginning of sentences
						matchCase = minion_words[j];
						matchCase[0]= toupper(matchCase[0]);
						translated_words.push_back(matchCase);
					}else{
						translated_words.push_back(minion_words[j]);
					}
				}
			}
		}else{
			translated_words.push_back(all_words[i]);//if no translation found, pushes original word
		}
	}

	for(int i = 0;i<translated_words.size();i++){
		cout<<translated_words[i];
	}
	return false;
}

int main() {


	get_trans("minion_to_english.txt");

	read_file("test2.txt");
	//for(int i = 0; i<all_words.size();i++){
		//cout<<all_words[i]<<endl;
	//}
	add_translated_words();
	return 0;
}

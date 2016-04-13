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
#include<string>
#include<algorithm>
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

void read_file(char * file_name){
	ifstream test_file;
	string line, tempword,spaces,temp_upper;
	int j=0;
	test_file.open(file_name);
	if(!test_file.is_open()){
		cout<<"The file could not be opened, check location\n";
	}else{
		line = "This article is about the 1961 film. For the 2008 Hindi film, see One Two Three (2008 film).";
		while(getline(test_file,line)){
			for(int i =0;i<line.length();i++){
				if(line[i]==' '||line[i]==','||line[i]=='.'|| line[i]=='-'){
					temp_upper = tempword;
					all_words.push_back(temp_upper);
					tempword ="";
					spaces = line[i];
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
bool find_word(string word,vector <string> vec){
	string temp;

	if(find(vec.begin(),vec.end(),word) != vec.end()){
		return true;
	}else{
		return false;
	}
}

bool add_translated_words(){
	string temp;
	cout<<"\n";
	for(int i =0; i<all_words.size();i++){
		if(find_word(all_words[i],english_words)){
			temp = all_words[i];
			for(int j = 0;j<english_words.size();j++){
				if(english_words[j]==temp){
					translated_words.push_back(minion_words[j]);
				}
			}
		}else{
			translated_words.push_back(all_words[i]);
		}
	}

	for(int i = 0;i<translated_words.size();i++){
		cout<<translated_words[i];
	}
	return false;
}

int main() {

	get_trans("minion_to_english.txt");
	read_file("test_file.txt");
	add_translated_words();
	return 0;
}

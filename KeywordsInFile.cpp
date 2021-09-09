#include "KeywordsInFile.h"

KeywordsInFile::KeywordsInFile(const std::string& keywords, const std::string& text){
	//This is creating an unordered_set of keywords read from the text file
	std::string line, temp = "";
	std::ifstream keyfile(keywords);
	while(std::getline(keyfile,line)){
		for(int i =0; i<line.size();i++){
			//Should loop to the end of the word
			if(std::isalpha(line[i])){
				temp+=line[i];
			}
			//Checks if it is the end of the line and the temp is empty
			else if((line[i]=='\n')&&(temp!="")){
				keywordset.insert(temp);
				temp="";
			}
			else if(temp.length()>0){
				//Inserts the keyword into the keyword set
				keywordset.insert(temp);
				temp="";
			}
		}
		if(temp!=""){
			keywordset.insert(temp);
			temp="";
		}
		//Clears the line
		line="";
	}
	//Finds total length of the text file
	line="";
	std::ifstream firsttextfileread(text);
	int totallines=0;
	while(std::getline(firsttextfileread,line)){
		totallines++;	
	}
	//****************************Works
	//std::cout << "The total number of lines is " << totallines << std::endl;
	//Constructs the map totalwordperline with vectors initialized to the number of lines with all values 0
	//Also makes totalword with all values 0
	for(auto i =keywordset.begin();i!=keywordset.end();i++){
		totalwordperline.insert(make_pair(*i,std::vector<int>(totallines,0)));
		totalword.insert(make_pair(*i,0));
		//std::cout << *i << std::endl;
	}
	//****************************
	line,temp = "";
	int linenum = 0;
	std::ifstream textfile(text);
	while(std::getline(textfile,line)){
		for(int i =0; i<line.size();i++){
			//Checks if the character at i is a non-alphabetic character, which denotes the end of a word
			if(std::isalpha(line[i])){
				temp+=line[i];
			}
			//Checks if the last word of the line goes through
			else if((line[i]=='\n'&&temp!="")&&temp.length()!=0){
				//Checks if the word is found inside the set of keywords
				if((keywordset.find(temp)!=keywordset.end())&&temp.length()!=0){
					auto x = totalword.find(temp);
					x->second++;
					auto y = totalwordperline.find(temp);
					y->second[linenum]++;
					temp="";
				}
			}
			//Checks the words before the end of the line
			else if((keywordset.find(temp)!=keywordset.end())&&temp.length()!=0){
				auto x = totalword.find(temp);
				x->second++;
				auto y = totalwordperline.find(temp);
				y->second[linenum]++;
				temp="";
			}
			//All other cases are omitted, as they are not keywords
			else{
				temp="";
			}
		}
		if((temp!="")&&temp.length()!=0){
			if(keywordset.find(temp)!=keywordset.end()){
				auto x = totalword.find(temp);
				x->second++;
				auto y = totalwordperline.find(temp);
				y->second[linenum]++;
				temp="";
			}
		}
		/*
		for(auto i=totalwordperline.begin();i!=totalwordperline.end();i++){
			std::cout << i->first << i->second[linenum]<< std::endl;
			std::cout << "----" << std::endl;
		}
		std::cout << "-------------------------------" << std::endl; 
		*/
		linenum++;
		line="";
	}
	/*
	std::cout << "This is used to check the values inside the totalword map" << std::endl;
	for(auto i=totalword.begin();i!=totalword.end();i++){
		std::cout << i->first << "->" << i->second << std::endl; 
	}
	std::cout << "--------------------------------------" << std::endl;
	
	int total = 0;
	for(auto i =totalwordperline.begin();i!=totalwordperline.end();i++){
		total = 0;
		for(int j = 0; j < i->second.size();j++){
			total+=i->second[j];
			std::cout << total << std::endl;
		}
		//std::cout << i->first << "-" << total << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
	*/
}
bool KeywordsInFile::KeywordFound(const std::string& keyword) const{
	if(totalword.find(keyword)!=totalword.end()){
		return true;
	}
	return false;
}
int KeywordsInFile::KeywordInLine(const std::string& keyword,const int& line_num) const{
	int total=0;
	auto i = totalwordperline.find(keyword);
	total = i->second[line_num-1];
	return total;
}
int KeywordsInFile::TotalOccurrences(const std::string& keyword) const{
	auto it= totalword.find(keyword);
	return it->second;
}
std::ostream&operator <<(std::ostream& x, const KeywordsInFile& key){
	for(auto i=key.totalword.begin();i!=key.totalword.end();i++){
		x << i->first<< " " << i->second<< std::endl;
	}
	return x;
}
#include <iostream>
#include<unordered_map>
#include<unordered_set>
#include<fstream>
#include<string>
#include<vector>
#include<set>

class KeywordsInFile{
	private:
		std::unordered_set<std::string> keywordset;
		std::unordered_map<std::string, int> totalword;
		std::unordered_map<std::string,std::vector<int>> totalwordperline;
	public:
		KeywordsInFile(const std::string& keywords, const std::string& text);
		KeywordsInFile()= delete;
		bool KeywordFound(const std::string& keyword) const;
		int KeywordInLine(const std::string& keyword,const int& line_num) const;
		int TotalOccurrences(const std::string& keyword) const;
		friend std::ostream& operator<<(std::ostream& x, const KeywordsInFile& key);
};
#include <iostream>
#include <fstream>
#include "KeywordsInFile.h"

int main()
{	
    KeywordsInFile x = KeywordsInFile("keyword.txt", "test.txt");

    std::cout << x << std::endl;
    
    std::cout << x.KeywordInLine("rat", 3) << std::endl;
    std::cout << x.KeywordFound("cat") << std::endl;
    std::cout << x.KeywordFound("Mattias") << std::endl;
    
    return 0;
}
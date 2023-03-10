#include <iostream>
#include <string>
#include <vector>
#include "any.hpp"

using namespace any;

int main()
{
    std::string str1 = "Hello string x1";
    std::string str2 = "Hello string x2";
    std::vector<int> vint1 = {0,1,2,3,4};
    std::vector<int> vint2 = {5,6,7,8,9};

    std::vector<Any> cont = {str1,str2,vint1,vint2};

    std::cout << cont[0].cast<std::string>() << std::endl;
    std::cout << cont[1].cast<std::string>() << std::endl;
    std::cout << cont[2].cast<std::vector<int>>()[0] << std::endl;
    std::cout << cont[3].cast<std::vector<int>>()[0] << std::endl;
    return 0;
}

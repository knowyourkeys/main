#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using std::string;

string found_in_dic(string pass)
{
    std::ifstream dictionnary;
    string line;
    unsigned int cpt = 0;
    dictionnary.open("key.txt");

    if(dictionnary.is_open()){

        while( getline(dictionnary,line) )
        {
            if(pass.find(line)!=string::npos)
            {

                return line;

            }
            cpt++;
        }

        dictionnary.close();
    }
    return "";
}
bool close_to_dic(string pass){

    string found = found_in_dic(pass);
    if (found.size())
    {
        std::cout << "To close to dictionary word: " << found << "\n";
        return false;
    }
    else return true;
}
bool isspecial(string pass){
    string const special = {".!@&%?$_"};
    if(pass.find_first_of(special)!=string::npos)
        return false;
    else
    return true;
}
string how_strong(string pass,bool special)
{
    bool dic = close_to_dic(pass);
    if(!dic)
        return "To close to dictionary";
    if(pass.size() < 10)
        return "Too short";
    if(std::none_of(pass.begin(),pass.end(),&::islower))
        return "No lower characters";
    if(std::none_of(pass.begin(),pass.end(),&::isupper))
        return "No upper characters";
    if(std::none_of(pass.begin(),pass.end(),&::isdigit))
        return "No digits";
    if(isspecial(pass) && special)
        return "No Special";
    else return "OK";
}

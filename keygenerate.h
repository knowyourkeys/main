#ifndef KEYGENERATE_H
#define KEYGENERATE_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using std::cout;
using std::string;

int rand_pb()
{
    int pb(0);
    pb = rand()%16;
    return pb;
};

int type_return(bool special)
{
    int pb = rand_pb();
    if(pb<=4)
        return 1;
    if(pb<=8 && pb > 4)
        return 2;
    if(pb<=12 && pb > 8)
        return 3;
    else if(special)
        return 4;
    else return 1;

}
string rand_low()
{
    int pb = rand()%25;
    char tab[25]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','z'};
    string key;
    key = tab[pb];
    //cout << "Low adding: " << key <<"\n";
    return key;

}
string rand_up()
{
    int pb = rand()%25;
    char tab[25]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','Z'};
    string key;
    key = tab[pb];
    //cout << "Up adding: " << key <<"\n";
    return key;

}
string rand_int()
{
    int pb = rand()%10;
    char tab[10]= {'0','1','2','3','4','5','6','7','8','9'};
    string key;
    key = tab[pb];
    //cout << "Int adding: " << key <<"\n";
    return key;

}

string rand_special()
{
    int pb = rand()%7;
    char tab[7]= {'!','?','$','%','&','@','_'};
    string key;
    key = tab[pb];
    //cout << "Special adding: " << key <<"\n";
    return key;

}
string key_gener(size_t size_key,bool special)
{
    string key;
    int key_int(special);
    for(unsigned int i = 0; i < size_key; i++)
    {
        key_int=type_return(special);
        if(key_int == 1)
            key += rand_low();
        if(key_int == 2)
            key += rand_up();
        if(key_int == 3)
            key += rand_int();
        if(key_int == 4)
            key += rand_special();
    }
    //cout << key <<std::endl;
    return key;
}

#endif // KEYGENERATE_H

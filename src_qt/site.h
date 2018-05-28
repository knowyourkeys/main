#ifndef SITE_H
#define SITE_H

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//#include "ret_rand.h"
//#include "dic_test.h"


class Site
{
private:
    std::string _username;
    std::string _password;
    std::string _site_name;
public:

    Site(std::string username, std::string password, std::string site_name) :_username(username), _password(password), _site_name(site_name) {}
    std::string getSiteName() { return _site_name; }
    std::string getPassword() { return _password; }
    std::string getUsername() { return _username; }
    void changeUsername(const std::string &changed) { _username = changed; }
    void changeSiteName(const std::string &changed) { _site_name = changed; }
    void changePassword(const std::string &changed) { _password = changed; }
    void print() {
        std::cout << _site_name << " " << _username << " " << _password << "\n";
    }
    std::string format() {
        std::string formated;
        formated = "Site name: " + _site_name + " Username: " + _username + " Password: " + _password + "\n";
        return formated;
    }
    /*void random_replace(size_t  x, bool i) {
        std::string pass;
        while (how_strong(pass, i) != "OK") {
            pass = key_gener(x, i);
        }
        _password = pass;
    }*/

    ~Site() {}

};

int get_file_lines(std::string file_name);
void vector_to_temp_output(std::vector<Site> &vect);
std::vector<Site> output_temp_to_vector();
void clear_file();

#endif // SITE_H

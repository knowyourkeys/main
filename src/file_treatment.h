#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "encryption.h"
#include "Site.h"



int get_file_lines(std::string file_name) {
	unsigned int i = 0;
	std::string line;
	std::ifstream file;
	file.open(file_name);
	while (std::getline(file, line)) {
		i++;
	}
	file.close();
	return i;
}

void vector_to_temp_output(std::vector<Site> &vect) {
	std::ofstream output_f;
	output_f.open("output.txt");
	for (unsigned int i = 0; i < vect.size(); i++) {
		output_f << vect[i].getUsername() <<" "<<vect[i].getPassword() <<" "<<vect[i].getSiteName() <<"\n";
		
	}
	output_f.close();
}
std::vector<Site> output_temp_to_vector() {
	std::ifstream output_f;
	std::string temp_f = "output.txt";
	output_f.open("output.txt");
	std::vector<Site> vect;
	std::string temp_u, temp_p, temp_sn;
	
	//unsigned int size = get_file_lines(output_f);
	for (unsigned int i = 0; i < get_file_lines(temp_f); i++) {
		output_f >> temp_u >> temp_p >> temp_sn;
		//getline(output_f, temp_u);
		Site temp(temp_u, temp_p, temp_sn);
		vect.push_back(temp);

	}
	output_f.close();
	return vect;
}
void clear_file() {

	unsigned int size = get_file_lines("output.txt");
	std::ofstream output_file;
	output_file.open("output.txt");
	unsigned k = 0;
	while (k < 50)
	{
		for (unsigned int i = 0; i < size; i++) {
			output_file <<"0";
		}
		k++;
	}

	output_file.close();
}
bool vector_to_file(std::vector<Site> &vect, const std::string &pass) {
	std::ofstream us_k;
	us_k.open("us_k.txt");
	std::ofstream us_v;
	us_v.open("us_v.txt");
	std::ofstream us_c;
	us_c.open("us_c.txt");

	std::ofstream p_k;
	p_k.open("p_k.txt");
	std::ofstream p_v;
	p_v.open("p_v.txt");
	std::ofstream p_c;
	p_c.open("p_c.txt");

	std::ofstream s_k;
	s_k.open("s_k.txt");
	std::ofstream s_v;
	s_v.open("s_v.txt");
	std::ofstream s_c;
	s_c.open("s_c.txt");

	std::ofstream ivs;
	ivs.open("iv.txt");

	for (auto i = vect.begin(); i != vect.end(); ++i) {
		encrypt_key(pass, i->getUsername(), us_k, us_v, us_c, ivs);

		encrypt_key(pass, i->getPassword(), p_k, p_v, p_c, ivs);

		encrypt_key(pass, i->getSiteName(), s_k, s_v, s_c, ivs);

	}
	us_k.close();
	us_v.close();
	us_c.close();

	p_k.close();
	p_v.close();
	p_c.close();

	s_k.close();
	s_v.close();
	s_c.close();

	ivs.close();

	return 1;
}
std::vector<std::string> return_from_path(const std::string &path) {
	std::vector<std::string> to_return;
	std::ifstream file;
	unsigned int file_size = 0;
	std::string line;

	file.open(path);
	while (std::getline(file, line)) {
		to_return.push_back(line);
	}
	file.close();
	return to_return;
}
unsigned int min(unsigned int a, unsigned int b, unsigned int c) {

	unsigned int min = 0;
	for (unsigned int i = 0; i < 3; i++) {
		if (a < b)
		{
			min = a;
			b = c;
		}
		else {
			min = b;
			a = c;
		}
	}

	return min;
}
std::vector<Site> file_to_vector(const std::string &password) {
	std::vector<Site> vector;
	std::vector<std::string> user_ciphers, user_keys, user_ivs;
	std::vector<std::string> pass_ciphers, pass_keys, pass_ivs;
	std::vector<std::string> sname_ciphers, sname_keys, sname_ivs;
	std::vector<std::string> ivs;
	std::string pass, username, sname;
	user_ciphers = return_from_path("us_c.txt");
	user_keys = return_from_path("us_k.txt");
	user_ivs = return_from_path("us_v.txt");

	pass_ciphers = return_from_path("p_c.txt");
	pass_keys = return_from_path("p_k.txt");
	pass_ivs = return_from_path("p_v.txt");

	sname_ciphers = return_from_path("s_c.txt");
	sname_keys = return_from_path("s_k.txt");
	sname_ivs = return_from_path("s_v.txt");

	ivs = return_from_path("iv.txt");

	if (user_ciphers.size() == pass_ciphers.size() && pass_ciphers.size() == sname_ciphers.size()) {
		unsigned int x = 0, y = 1, z = 2;
		for (unsigned int i = 0; i < user_ciphers.size(); ++i) {
			username = decrypt_key(user_ciphers[i], user_keys[i], user_ivs[i], password, ivs[x]);
			pass = decrypt_key(pass_ciphers[i], pass_keys[i], pass_ivs[i], password, ivs[y]);
			sname = decrypt_key(sname_ciphers[i], sname_keys[i], sname_ivs[i], password, ivs[z]);

			//cout << username << " " << pass << " " << sname << "\n";
			Site a(username, pass, sname);
			vector.push_back(a);
			x += 3;
			y += 3;
			z += 3;
		}

		return vector;
	}
	else
	{
		// error pop-out 
		unsigned int x = 0, y = 1, z = 2;
		unsigned int min_size = min(user_ciphers.size(), pass_ciphers.size(), sname_ciphers.size());
		for (unsigned int i = 0; i < min_size; ++i) {
			username = decrypt_key(user_ciphers[i], user_keys[i], user_ivs[i], password, ivs[x]);
			pass = decrypt_key(pass_ciphers[i], pass_keys[i], pass_ivs[i], password, ivs[y]);
			sname = decrypt_key(sname_ciphers[i], sname_keys[i], sname_ivs[i], password, ivs[z]);

			//cout << username << " " << pass << " " << sname << "\n";
			Site a(username, pass, sname);
			vector.push_back(a);
			x += 3;
			y += 3;
			z += 3;
		}

		return vector;

	}
}
/*bool fist_run() {
	std::ifstream us_k;
	us_k.open("us_k.txt");
	if (get_file_lines(us_k))
		return false;
	else
		return true;
}*/
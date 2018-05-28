    #include "site.h"

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
        if(temp_u == "ERROR_PASS")
        {
            Site temp(temp_u, temp_p, temp_sn);
            vect.push_back(temp);
            return vect;
        }
        //getline(output_f, temp_u);
        else{
		Site temp(temp_u, temp_p, temp_sn);
		vect.push_back(temp);
    }
	}
	output_f.close();
	return vect;
}

void clear_file() {

    unsigned int size = get_file_lines("output.txt");
    std::ofstream output_file;
    output_file.open("output.txt",std::ios::trunc);
    output_file.close();
}

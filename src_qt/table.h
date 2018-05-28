#ifndef TABLE_H
#define TABLE_H

std::string smash(std::string table)
{
    std::string smashed;
    size_t pos_initial = table.find(":");
    //cout << pos_initial << "\n";
    size_t pos_final = table.find(";");
    smashed = table.substr(pos_initial+1, pos_final-1);
    return smashed;
}

std::string get_table(std::string table,std::string smashed)
{
    table.erase(0, smashed.size()+2);

    return table;
}

/*std::string add_mdp(std::string mdp, std::string temp.s)
{
    mdp = ":Usename: Admin - Site: " + temp + mdp + ";";
    return mdp;
}*/

std::string create_table(std::string mdp,std::string table)
{
    table += mdp;
    return table;
}

#endif // TABLE_H

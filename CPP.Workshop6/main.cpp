#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter)
{
    int i, prev = 0;
    std::string str1 = "";
    std::vector<std::string> a;
    for (i=0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            a.push_back(str.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    a.push_back(str.substr(prev, i - prev));
    return a;
}

std::string join(const std::vector<std::string>& tokens, char delimiter)
{
    int i = 1;
    std::string str = "";
    if (tokens.size() != 0)
    {
        str = tokens.at(0);
    }
    for (i=1; i<tokens.size(); i++)
    {
        str += delimiter;
        str += tokens.at(i);
    }
    return str;
}

// Input sample (MAC styled): ./main.out train.csv output.csv 0 1 2
int main (int argc, char *argv[]) {
    std::ifstream infile(argv[1]);
    std::ofstream outfile(argv[2]);
    std::vector<std::string> columns;
    std::vector<std::string> vec;
    std::string line;
    for (int i = 3; i<argc; i++)
    {
        columns.push_back(argv[i]);
    }
    while (!infile.eof() && infile.good()) {
        std::getline(infile, line);
        std::vector<std::string> finalVec;
        vec = split(line, ',');
        for (int k = 0; k<argc - 3; k++)
        {
            int wow;
            std::stringstream ss;
            ss << columns[k];
            ss >> wow;
            finalVec.push_back(vec[wow]);
        }
        outfile << join(finalVec, ',') << std::endl;
        finalVec.push_back("\n");
    }

}
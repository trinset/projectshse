#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

typedef std::map<std::string, int> Frequencies;
typedef std::map<int, std::string> Freq;

//Prints final answer to the problem
void printSwappedMap (const Frequencies &frequencies)
{
    std::map<int, std::string> freq;

    for (const std::pair<std::string, int> &item : frequencies)
    {
        freq[item.second] = item.first;
    }
    for (Freq::reverse_iterator it = freq.rbegin (); it != freq.rend (); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

//Parses column
Frequencies parseColumn (const std::string &fileName, const size_t &column_number)
{
    std::ifstream in(fileName);
    std::string line;
    Frequencies frequencies;

    while (!in.eof() && in.good()) {
        std::getline(in, line);
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;

        while (!ss.eof() && ss.good()) {
            std::getline(ss, token, ',');
            tokens.push_back(token);
        }

        if (column_number >= tokens.size())
            continue;

        if (frequencies.find(tokens[column_number]) != frequencies.end())
        {
            frequencies[tokens[column_number]] += 1;
        }
        else
        {
            frequencies[tokens[column_number]] = 0;
        }
    }
    return frequencies;
}

//Receives arguments fileName and column_number
//Input sample (MAC styled): ./main.out input.csv 2
int main (int argc, char **argv) {
    if (argc != 3) {
        return 0;
    }
    Frequencies frequencies;
    std::string fileName = argv[1];
    size_t column_number = static_cast<size_t> (atoi (argv[2]));
    frequencies = parseColumn(fileName, column_number);
    printSwappedMap(frequencies);
}

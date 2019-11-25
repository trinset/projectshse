#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <map>


//Counts the number of countries and prints it out
void howManyCountries(const std::vector<std::vector<std::string> > &worldCities)
{
    int countriesNum = 0;
    int countryColNum = 4;
    for (size_t i=1; i<worldCities.size(); i++)
    {
        if (!worldCities[i][countryColNum].empty())
        {
            countriesNum++;
        }
    }
    std::cout << countriesNum << std::endl;
}

//Prints countries and their capitals
//Sample: Russia - Moscow
void printCountryAndCapital(const std::vector<std::vector<std::string> > &worldCities)
{
    int countryColNum = 4;
    int capitalColNum = 8;
    int cityColNum = 1;
    for (size_t i=1; i<worldCities.size(); i++)
    {
        if (worldCities[i][capitalColNum] == "primary")
        {
            std::cout << worldCities[i][countryColNum] << " - " << worldCities[i][cityColNum] << std::endl;
        }
    }

}

//Prints longitudes, where there are no cities
void uninhabitedLongitude(const std::vector<std::vector<std::string> > &worldCities)
{
    std::set<int> longitudeNum;
    int longitudeColNum = 3;
    int longNum;
    double uselessDouble;
    for (size_t i=1; i<worldCities.size(); i++)
    {
        std::stringstream ss(worldCities[i][longitudeColNum]);
        ss >> uselessDouble;
        longNum = uselessDouble;
        longitudeNum.insert(longNum);
    }
    for (int i=-180; i<=180; i++)
    {
        if (!longitudeNum.count(i))
        {
            std::cout << i << std::endl;
        }
    }
}

//Outputs City:Population by country in file population.txt
void populationByCountryAndCity(const std::vector<std::vector<std::string> > &worldCities)
{
    std::ofstream file;
    file.open ("population.txt");
    int popColNum = 9;
    int cityColNum = 1;
    int countryColNum = 4;
    int pop1 = 0;
    double pop2 = 0;
    std::map<std::string, std::map<std::string, int> > cityPopulation;
    std::map<std::string, int> countryPopulation;
    for (int i=1; i<worldCities.size(); i++)
    {
        if (worldCities[i][popColNum].empty())
        {
            pop1 = 0;
        }
        else
        {
            std::stringstream ss(worldCities[i][popColNum]);
            ss >> pop2;
            pop1 = pop2;
        }
        if (countryPopulation.find(worldCities[i][countryColNum]) != countryPopulation.end())
        {
            countryPopulation[worldCities[i][countryColNum]] += pop1;
        }
        else
        {
            countryPopulation[worldCities[i][countryColNum]] = pop1;
        }
        cityPopulation[worldCities[i][countryColNum]][worldCities[i][cityColNum]] = pop1;
    }
    std::string str1;
    std::string str2;
    for (std::map<std::string, int>::iterator it = countryPopulation.begin(); it!=countryPopulation.end(); it++)
    {
        file << it->first << " : " << it->second << std::endl;
        for (std::map<std::string, int>::iterator it1 = cityPopulation[it->first].begin(); it1 != cityPopulation[it->first].end(); it1++)
        {
            if (it1->second == 0)
            {
                file << it1->first << " : " << '?' << " / " << it->second << std::endl;
            }
            else {
                file << it1->first << " : " << it1->second << " / " << it->second << std::endl;
            }
        }
    }
}

int main()
{
    std::ifstream file;
    file.open("worldcities.csv");
    std::vector<std::vector<std::string> > worldCities;
    std::string str;
    while (!file.eof() && file.good()) {
        std::getline(file, str);
        if (str.empty())                                    //Some mistakes occur without this statement
        {
            break;
        }
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (!ss.eof() && ss.good()) {
            std::getline(ss, token, ',');
            if (token.empty())
            {
            }
            tokens.push_back(token.substr(1, token.length() - 2));
        }
        worldCities.push_back(tokens);
    }
    howManyCountries(worldCities);
    printCountryAndCapital(worldCities);
    uninhabitedLongitude(worldCities);
    populationByCountryAndCity(worldCities);
}

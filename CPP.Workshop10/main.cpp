#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

typedef std::map<std::string, std::map<std::string, double> > ComplexRegionAndPop;
typedef std::map<std::string, double> RegionAndPop;

enum worldcities_data_columns
{
    city_ascii = 1,
    lat = 2,
    lng = 3,
    country = 4,
    iso2 = 5,
    iso3 = 6,
    admin_name = 7,
    capital = 8,
    population = 9,
    id = 10,
    total_columns = 11
};

std::string no_quotes (const std::string &input)
{
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
    return result;
}

struct city_data
{
    city_data()
    {}

    city_data (const std::vector <std::string> &tokens) :
            lat (std::stod (no_quotes (tokens[worldcities_data_columns::lat]))),
            lng (std::stod (no_quotes (tokens[worldcities_data_columns::lng]))),
            country (no_quotes (tokens[worldcities_data_columns::country])),
            is_capital (no_quotes (tokens[worldcities_data_columns::capital]) == "primary"),
            iso2 (no_quotes (tokens[worldcities_data_columns::iso2])),
            iso3 (no_quotes (tokens[worldcities_data_columns::iso3])),
            admin_name (no_quotes (tokens[worldcities_data_columns::admin_name])),
            id (no_quotes (tokens[worldcities_data_columns::id]))
    {
        std::string population_string = no_quotes (tokens[worldcities_data_columns::population]);
        if (population_string.empty ())
        {
            has_population = false;
        }
        else
        {
            has_population = true;
            population = std::stod (population_string);
        }
    }
    double lat;
    double lng;
    std::string country;
    bool is_capital;
    std::string iso2;
    std::string iso3;
    std::string admin_name;
    std::string id;
    double population;
    bool has_population;
};

typedef std::pair<const std::string, city_data> CityAndData;

std::unordered_map<std::string, city_data> worldCities ()
{
    std::ifstream in ("worldcities.csv");
    std::string line;

    std::unordered_map<std::string, city_data> result;

    std::getline (in, line);
    while (!in.eof() && in.good ())
    {
        std::getline (in, line);

        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (!ss.eof () && ss.good ())
        {
            std::getline (ss, token, ',');

            if (!tokens.empty () &&
                !tokens[tokens.size () - 1].empty () &&

                tokens[tokens.size () - 1].front () == '"'
                &&
                (tokens[tokens.size () - 1].back () != '"' ||
                 tokens[tokens.size () - 1].size () == 1))
            {
                tokens[tokens.size () - 1] += "," + token;
            }
            else
            {
                tokens.push_back (token);
            }
        }

        if (tokens.size () == total_columns)
            result[no_quotes(tokens[worldcities_data_columns::city_ascii])] = city_data (tokens);
        else
            assert (ss.eof () || !ss.good ());
    }
    return result;
}


void printCountryAndCapital(const std::unordered_map<std::string, city_data> &world_cities)
{
    for (const CityAndData &elem : world_cities)
    {
        if (elem.second.is_capital)
        {
            std::cout << elem.second.country << " - " << elem.first << std::endl;
        }
    }

}

//Prints longitudes, where there are no cities
void uninhabitedLongitude(const std::unordered_map<std::string, city_data> &world_cities)
{
    std::set<int> longitudeNum;
    for (const CityAndData &elem : world_cities)
    {
        longitudeNum.insert((int) elem.second.lng);
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
void populationByCountryAndCity(const std::unordered_map<std::string, city_data> &world_cities)
{
    std::ofstream file;
    file.open ("population.txt");
    int pop1 = 0;
    double pop2 = 0;
    ComplexRegionAndPop cityPopulation;
    RegionAndPop countryPopulation;
    for (const CityAndData &elem : world_cities)
    {
        if (countryPopulation.find(elem.second.country) != countryPopulation.end())
        {
            countryPopulation[elem.second.country] += elem.second.population;
        }
        else
        {
            countryPopulation[elem.second.country] = elem.second.population;
        }
        cityPopulation[elem.second.country][elem.first] = elem.second.population;
    }
    for (RegionAndPop::iterator it = countryPopulation.begin(); it!=countryPopulation.end(); it++)
    {
        file << it->first << " : " << (int) it->second << std::endl;
        for (RegionAndPop::iterator it1 = cityPopulation[it->first].begin(); it1 != cityPopulation[it->first].end(); it1++)
        {
            if (it1->second == 0)
            {
                file << it1->first << " : " << '?' << " / " << (int) it->second << std::endl;
            }
            else {
                file << it1->first << " : " << (int) it1->second << " / " << (int) it->second << std::endl;
            }
        }
    }
}

size_t howManyCountries (const std::unordered_map<std::string, city_data> &world_cities)
{
    std::unordered_set<std::string> countries;
    for (const std::pair<const std::string, city_data> &data : world_cities)
    {
        countries.insert (data.second.country);
    }
    return countries.size ();
}


int main ()
{
    std::unordered_map<std::string, city_data> world_cities = worldCities ();
    size_t number_of_countries = howManyCountries (world_cities);
    std::cout << number_of_countries << std::endl;
    printCountryAndCapital (world_cities);
    uninhabitedLongitude (world_cities);
    populationByCountryAndCity (world_cities);
    return 0;
}
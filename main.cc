/**
 * This file is the solution to the reddit challenge #257. Given
 * a csv file of presidential information such as <Name, birth date, birth place, death date, location of death>
 * find the year(s) in which the most presidents (future, present, or previous) were alive.
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <map>
int current_year = 2016;        // present year
int max_alive = 0;              // keeps track of the maximum number of presidents alive at any one year
static const int MONTH = 0;
static const int DAY = 1;
static const int YEAR = 2;
static const int NAME = 0;
static const int BIRTH_DATE = 1;
static const int BIRTH_PLACE = 2;
static const int DEATH_DATE = 3;
static const int DEATH_PLACE = 4;

// representation of a president's information
struct President
{
    std::string name;
    std::string birth_date;
    std::string birth_place;
    std::string death_date;
    std::string location_of_death;

    int getBirthYear()
    {
        // birth date string follow the form: <month> <day> <year>
        // we only care about the year
        char* current_word;
        char* birth_date_cstring = (char*)birth_date.c_str();
        current_word = strtok(birth_date_cstring, " "); 
        int i = 0;
        while (current_word != NULL)
        {
            switch(i)
            {
                case MONTH:
                    break;
                case DAY:
                    break;
                case YEAR:
                    return atoi(current_word);
                    break;
                default:
                    // nothing
                    break;
            }
            current_word = strtok(NULL, " ");
            i++;
        }
    }

    int getDeathYear()
    {
        // death date string follow the form: <month> <day> <year>
        // we only care about the year
        char* current_word;
        char* death_date_cstring = (char*)death_date.c_str();
        current_word = strtok(death_date_cstring, " ");      // month
        int i = 0;
        while (current_word != NULL)
        {
            switch(i)
            {
                case MONTH:
                    break;
                case DAY:
                    break;
                case YEAR:
                    return atoi(current_word);
                    break;
                default:
                    // nothing
                    break;
            }
            current_word = strtok(NULL, " ");
            i++;
        }
    }
};

/**
 * function: updateAlivePerYearTable
 * This method takes in a president's birth and death year and increment
 * the count of how many presidents are alive between those years.
 */
int
updateAlivePerYearTable(std::map<int, int> & alive_per_year_table, const int & birth_year, const int & death_year)
{
    int years_between_death = death_year - birth_year;
    if (years_between_death < 0)
    {
        // note: a current alive president has death year of 0
        years_between_death = current_year - birth_year;
    }

    int greatest_amount_alive_between_death = 0;
    for (int years_after_birth = 0; years_after_birth < years_between_death; years_after_birth++)
    {
        if(alive_per_year_table.find(birth_year + years_after_birth) == alive_per_year_table.end())
        {
            // year is not in table yet; add it
            alive_per_year_table[birth_year + years_after_birth] = 1;
        }
        else
        {
            alive_per_year_table[birth_year + years_after_birth]++;
        }
        if (alive_per_year_table[birth_year + years_after_birth] > greatest_amount_alive_between_death)
        {
            greatest_amount_alive_between_death = alive_per_year_table[birth_year + years_after_birth];
        }
    }

    return greatest_amount_alive_between_death;
}


/**
 * function: parseCvs
 * This method takes in a path to a cvs file and parse though it at the same time
 * keeping count of which years has the most presidents alive.
 */
void
parseCvs(char* cvs_file_full_path, std::vector<President*> & list_of_presidents, std::map<int, int> & alive_per_year_table)
{
    std::string line;
    std::fstream cvs_file(cvs_file_full_path);
    int max_alive_between_president_death;
    if (cvs_file.is_open())
    {
        while (getline(cvs_file, line))
        {
            std::string current_word;
            std::istringstream iss(line);
            President* president = new President();
            for (int i = 0; i < 5; i++)
            {
                std::getline(iss, current_word, ',');
                switch (i)
                {
                    case NAME:
                        president->name = current_word;
                        break;
                    case BIRTH_DATE:
                        president->birth_date = current_word;
                        break;
                    case BIRTH_PLACE:
                         president->birth_place = current_word;
                         break;
                    case DEATH_DATE:
                         president->death_date = current_word;
                         break;
                    case DEATH_PLACE:
                         president->location_of_death = current_word;
                         break;
                    default:
                        // do nothing
                        break;
                }
            } 
            
            list_of_presidents.push_back(president);
            max_alive_between_president_death = updateAlivePerYearTable(alive_per_year_table, president->getBirthYear(), president->getDeathYear());
            if (max_alive < max_alive_between_president_death)
            {
                max_alive = max_alive_between_president_death;
            }
        }
    }
    else
    {
        std::cout << "Cannot open cvs file." << std::endl;
    }
}

/**
 * function: clearVector
 * This method deletes each allocated item in a given vector.
 */
template <class T>
void
clearVector(std::vector<T> & v)
{
    for (int i = 0; i < v.size(); i++)
    {
        delete v[i];
    }
}

/**
 * function: outputYearsWithMostAlive
 * This method prints out the years in which the most number of president was alive.
 */
void
outputYearsWithMostAlive(std::map<int, int> & alive_per_year_table, const int & max_alive)
{
    std::cout << "The following year(s) has " << max_alive << " presidents alive:\n"; 
    for (std::map<int, int>::iterator it = alive_per_year_table.begin(); it != alive_per_year_table.end(); it++)
    {
        if (it->second == max_alive)
        {
            std::cout << it->first << ", ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<President*> list_of_presidents;
    std::map<int, int> alive_per_year_table;

    parseCvs(argv[1], list_of_presidents, alive_per_year_table);
    outputYearsWithMostAlive(alive_per_year_table, max_alive);
    clearVector(list_of_presidents);
    return 0;
}

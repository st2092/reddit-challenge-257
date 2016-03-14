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
int min_year = 0;               // the year of the earliest president on the provided cvs file
int current_year = 2016;        // present year
int max_alive = 0;              // keeps track of the maximum number of presidents alive at any one year

// representation of a president information
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
        current_word = strtok(birth_date_cstring, " ");      // month
        int i = 0;
        while (current_word != NULL)
        {
            switch(i)
            {
                case 0: // month
                    break;
                case 1: // day
                    break;
                case 2: // year
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
                case 0: // month
                    break;
                case 1: // day
                    break;
                case 2: // year
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
 * function: parseCvs
 * This method takes in a path to a cvs file and parse though it at the same time
 * keeping count of which years has the most presidents alive.
 */
void
parseCvs(char* cvs_file_path, std::vector<President*> & list_of_presidents)
{
    std::string line;
    std::fstream cvs_file(cvs_file_path);
    if (cvs_file.is_open())
    {
        // read line by line
        while (getline(cvs_file, line))
        {
            // split line up by ',' 
            std::string current_word;
            std::istringstream iss(line);       // string stream version of line
            President* president = new President();
            for (int i = 0; i < 5; i++)
            {
                std::getline(iss, current_word, ',');
                switch (i)
                {
                    case 0:     // name
                        president->name = current_word;
                        break;
                    case 1:     // birth date
                        president->birth_date = current_word;
                        break;
                    case 2:     // birth place
                         president->birth_place = current_word;
                         break;
                    case 3:     // death date
                         president->death_date = current_word;
                         break;
                    case 4:     // location of death
                         president->location_of_death = current_word;
                         break;
                    default:
                        // do nothing
                        break;
                }
            } 
          //  std::cout << president->name << ", " << president->birth_date << ", "
          //            << president->birth_place << ", " << president->death_date << ", "
          //            << president->location_of_death << std::endl;
          //  std::cout << " Name: " << president->name << ", Birth year: " << president->getBirthYear()
          //            << ", Death year: " << president->getDeathYear() << std::endl;
            // update list of president and how many president is alive on year of this president
            list_of_presidents.push_back(president);
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
 * @param v     the vector to free up
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

int main(int argc, char** argv)
{
    std::vector<President*> list_of_presidents;
    //parseCvs(argv[1], list_of_presidents);
    std::map<int, int> m;
   // m[1920] = 2;


    //m[1920]++;
    /*for (std::map<int, int>::iterator i = m.begin(); i != m.end(); i++)
    {
        std::cout << i->first << ":" << i->second << std::endl;
    }
*/
    clearVector(list_of_presidents);
    return 0;
}

#pragma once
#ifndef __STRINGHELPER__H
#define __STRINGHELPER__H

#include <algorithm> 
#include <cctype>
#include <locale>
#include <stdexcept>
#include <sstream>

namespace Geometry
{
    class FileNotFoundError : public std::logic_error
    {
    public:
        FileNotFoundError(string msg) : std::logic_error(msg) { };
    };

    class StringHelper
    {
    public:
        // trim from start (in place)
        static inline void ltrim(std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
                }));
        }

        // trim from end (in place)
        static inline void rtrim(std::string& s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
                }).base(), s.end());
        }

        // trim from both ends (in place)
        static inline void trim(std::string& s) {
            ltrim(s);
            rtrim(s);
        }

        // trim from start (copying)
        static inline std::string ltrim_copy(std::string s) {
            ltrim(s);
            return s;
        }

        // trim from end (copying)
        static inline std::string rtrim_copy(std::string s) {
            rtrim(s);
            return s;
        }

        // trim from both ends (copying)
        static inline std::string trim_copy(std::string s) {
            trim(s);
            return s;
        }

        static const std::vector<std::string> splitString(const std::string& s, const char& c)
        {
            std::string buff{ "" };
            std::vector<std::string> v;

            for (auto n : s)
            {
                if (n != c) buff += n; else
                    if (n == c && buff != "") { v.push_back(buff); buff = ""; }
            }
            if (buff != "") v.push_back(buff);

            return v;
        }

        static const std::string extractString(std::string str, std::string start, std::string end)
        {
            unsigned first = str.find(start);
            unsigned last = str.find(end);
            return str.substr(first+1, last - first-1);
        }

        static double toDouble(std::string s)
        {
            std::string::size_type sz;     // alias of size_t
            return std::stod(s, &sz);
        }

        static bool readStringsFromFile(const string& fileName, std::vector<string> &stringList)
        {
            std::ifstream in(fileName);

            std::string str;

            if (in.is_open())
            { 
                while (getline(in, str))
                { //read data from file object and put it into string.
                    stringList.push_back(str);
                }
                in.close();
                return true;
            }
            else
            {
                return false;
            }
            
        }

        static bool writeStringsToFile(const string &fileName, const std::vector<string> &stringList)
        {
            std::ofstream out(fileName);

            if (!out.is_open())
                return false;

            for (auto i = 0; i < stringList.size(); i++)
            {
                out << stringList[i] << std::endl;
            }
            
            out.close();
            return true;
        }

        static bool is_number(const std::string& s)
        {
            long double ld;
            return((std::istringstream(s) >> ld >> std::ws).eof());
        }

    };
}
#endif
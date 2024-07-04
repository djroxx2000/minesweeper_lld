#ifndef Utility_hpp
#define Utility_hpp

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <type_traits>

using namespace std;

class Utility
{
public:
  static vector<string> splitStrOn(string input, char delimiter)
  {
    stringstream ss;
    ss << input;
    vector<string> splitResult;
    while (!ss.eof())
    {
      string temp;
      getline(ss, temp, ',');
      splitResult.push_back(temp);
    }
    return splitResult;
  }

  static bool isNumeric(string val)
  {
    for (char ch : val)
    {
      if (ch < '0' || ch > '9')
      {
        return false;
      }
    }
    return true;
  }

  static pair<int, int> getRowCol(vector<string> splitStr)
  {
    if (splitStr.size() != 2)
    {
      throw invalid_argument(
          "Input for grid size is invalid format. Please enter input in the format <row>,<col> and then press enter. Eg: 3,4");
    }
    if (!isNumeric(splitStr[0]) || !isNumeric(splitStr[1]))
    {
      throw invalid_argument(
          "Input for grid size is invalid format. Please enter numeric values for row and col fields.");
    }
    return make_pair(
        stoi(splitStr[0]),
        stoi(splitStr[1]));
  }

  static void validateMines(int numberOfMines, int rows, int cols)
  {
    if (numberOfMines >= rows * cols)
    {
      throw invalid_argument("Cannot add more mines than available spots in the grid.");
    }
  }

  static string getCharSeries(char ch, int times)
  {
    string series = "";
    while (times--)
    {
      series += ch;
    }
    return series;
  }

  template<typename T>
  static vector<vector<T>> readCsvFromStdin(char lineDelimiter, char dataDelimiter)
  {
    vector<vector<T>> csvOut;
    stringstream ss;
    ifstream inputStream("./inputGrid.txt");
    if (!inputStream)
    {
      cerr << "Unable to read grid from file. Switching to user input...";
      return csvOut;
    }
    string curLine;
    while (getline(inputStream, curLine, lineDelimiter))
    {
      ss << curLine;
      string dataString;
      csvOut.push_back(vector<T>());
      while (getline(ss, dataString, dataDelimiter))
      {
        T dataPoint;
        if constexpr (is_integral_v<T>) {
          dataPoint = stoi(dataString);
        } else if (is_floating_point_v<T>) {
          dataPoint = stof(dataString);
        } else {
          dataPoint = static_cast<T>(dataString);
        }
        csvOut[csvOut.size() - 1].push_back(dataPoint);
      }
    }
    return csvOut;
  }
};

#endif /* Utility_hpp */
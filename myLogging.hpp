//
//  myLogging.hpp
//  circular_logging_ece
//
//  Created by Ece Guler on 4.07.2022.
//

#ifndef myLogging_hpp
#define myLogging_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <time.h> // time, time_t, ctime
#include <filesystem>

using namespace std;

/*
 logging type, num of files, frequency ---> json format
 */

class myLogging{
    
public:
    myLogging();
    ~myLogging(); //called when object gets destroyed
    void setSecond(int);
    void setMinute(int);
    void setHour(int);
    void setDay(int);
    
    int getSecond();
    int getMinute();
    int getHour();
    int getDay();
    
    void setMaxFileNum(int);
    void setFreq(int);
    
    int getFreq();
    int getMaxFileNum();
    
    string UTC_Date();
    void CreatingLogFile(int, string , int , int );
    void LogCheck(int , string , int , int);
    void fullCheck(int);
    vector<string> storing;
    void deleteFile(string,int);
    
private:
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int max_file_num;
    int fileFrequency;
};


#endif /* myLogging_hpp */

//
//  main.cpp
//  circular_logging_ece
//
//  Created by Ece Guler on 5.07.2022.
//

#include <iostream>

#include <stdio.h> //printf etc.
//#include <unistd.h>
#include <time.h>


#include "myLogging.hpp"

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>


#include <fstream>
#include <string>



using namespace std;
int main() {
    
    time_t now = time(NULL);
    
    struct tm *UTC_time = gmtime(&now);
        
    int cur_year = 1900 + UTC_time->tm_year;
    
    char *other_string = asctime(UTC_time);

    char s[100];
    //string full_date=
    //strftime(s,100,"%H %M %S %A %B %Y ", UTC_time);
    //printf("%s\n", s);
    strftime(s,100,"%a_%b_%d_%X_%Y ", UTC_time);
    //printf("%s\n", s);
    
    myLogging myLog;
    
    string jsonFile;
    cout<<"Please enter json file name in .json format : ";
    cin>>jsonFile;
    
    //I created fileInfo.json as an example of my use in my code
    
    ifstream inFile(jsonFile);
    
    Json::Reader heading;
    Json::Value val;
    
    reader.parse( inFile, val);
    
    int max_log_file;
    //cout<<"Please select maximum number of log files: ";
    //cin>> max_log_file;
    max_log_file = val["numOfFiles"].asInt();
    
    myLog.setMaxFileNum(max_log_file);
    
    int frequency;
    //cout<<"Frequency of occurrence of log files: ";
    //cin>>frequency;
    frequency = val["frequency"].asInt();
    myLog.setFreq(frequency);
    
    //int type;
    //cout<<"Please choose a log type (1-second, 2-minute, 3-hourly, 4-daily): ";
    //cin>>type;
    string Ltype = val["logType"].asString();
    string fileName;
    fileName = myLog.UTC_Date();
    
    int type;
    if(Ltype=="second"){
        type=1;
    }
    else if(Ltype=="minute"){
        type=2;
    }
    else if(Ltype=="hourly"){
        type=3;
    }
    else if(Ltype=="daily"){
        type=4;
    }
    
    myLog.LogCheck(type, fileName, myLog.getMaxFileNum(), myLog.getFreq());
    
    return 0;
}

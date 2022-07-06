//
//  myLogging.cpp
//  circular_logging_ece
//
//  Created by Ece Guler on 5.07.2022.
//

#include "myLogging.hpp"

//#include "myLogging.h"
#include <iostream>
#include <vector>

#include <cstdlib>

#include <unistd.h>
#include <time.h>
using namespace std;


int second;
int minute;
int hour;
int day;
int month;
int year;
int max_file_num;
int fileFrequency;

myLogging::myLogging(){
    //cout<<"myLogging class constructor runned"<<endl;
    cout<<"Constructed myLogging!"<<endl;
}

myLogging::~myLogging(){
    //cout<<"Destroyed entity!"<<endl;
    cout<<"Destructed myLogging!"<<endl;
}


string myLogging::UTC_Date(){
    
    time_t now = time(NULL);
    struct tm *UTC_time = gmtime(&now);
    
    int UTC_second=  UTC_time->tm_sec;
    int UTC_minute= UTC_time->tm_min;
    int UTC_hour = UTC_time->tm_hour;
    int UTC_day = UTC_time->tm_mday;
      
    int UTC_month = UTC_time->tm_mon;
      
    int UTC_year = UTC_time->tm_year;
      
    UTC_year = 1900 + UTC_year;
    
    
    char *other_string = asctime(UTC_time);
    char s[100];
    //string full_date=
    //strftime(s,100,"%H %M %S %A %B %Y ", UTC_time);
    //printf("%s\n", s);
    strftime(s,100,"%a_%b_%d_%X_%Y ", UTC_time);
    //return other_string;
    return s;
    
}

void myLogging::setSecond(int UTC_second){
    second=UTC_second;
}
void myLogging::setMinute(int UTC_minute){
    minute=UTC_minute;
}
void myLogging::setHour(int UTC_hour){
    hour =UTC_hour;
}
void myLogging::setDay(int UTC_day){
    day =UTC_day;
}


int myLogging::getSecond(){
    return second;
}
int myLogging::getMinute(){
    return minute;
}
int myLogging::getHour(){
    return hour;
}
int myLogging::getDay(){
    return day;
}


void myLogging::setFreq(int frequency){
    fileFrequency = frequency;
}

void myLogging::setMaxFileNum(int max_num){
    max_file_num = max_num;
}


int myLogging::getFreq(){
    return fileFrequency;
}

int myLogging::getMaxFileNum(){
    return max_file_num;
}

void myLogging::CreatingLogFile(int type, string fileName, int maxNum, int frequency){
    string fileNameInJson = fileName+".json";
    
    ofstream outfile;
    outfile.open(fileNameInJson.c_str());
    
    string log_type= "";
    int freqNum=0; //used as second - everything converted to second (hour, minute, day)
    if (type==1){
        log_type = "second";
        freqNum=1;
    }
    else if(type==2){
        log_type = "minute";
        freqNum=60;
    }
    else if(type==3){
        log_type = "hourly";
        freqNum=3600;
    }
    else if(type==4){
        log_type = "daily";
        freqNum=86400;
    }
   
    cout<<"Writing to the file "<< fileNameInJson<<endl;
    //writing in json format
    //brackets for json format
    outfile<<"{"<<endl<<"\t"<<"\"file name\":"<<"\""<<fileNameInJson<<"\","<<endl;
    outfile<<"\t"<<"\"logging type\":"<<"\""<<log_type<<"\","<<endl;
    outfile<<"\t"<<"\"frequency\":"<<"\""<<frequency<<"\","<<endl;
    outfile<<"\t"<<"\"maxFileSize\":"<<"\""<<maxNum<<"\","<<endl<<"}"<<endl;
    
    outfile.close();
    cout << "Logging has ended. Closing the file " << fileNameInJson<< endl;
    cout<< "Will sleep for "<< freqNum*frequency <<" seconds."<<endl;
    sleep(freqNum*frequency);
}

void myLogging::fullCheck(int maxNum){
    for(int i=0; i<myLogging::storing.size();i++){
        if(maxNum<myLogging::storing.size()){
            string delFile=myLogging::storing[0];
            string delJsonFile = delFile+".json";
            cout<< "deleting "<<delJsonFile<<endl;
            myLogging::storing.erase(myLogging::storing.begin());
            deleteFile(delFile,maxNum);
        }
    }
    cout<<"storing contains: ";
    for(int j=0; j<myLogging::storing.size(); j++){
        cout<< " "<< myLogging::storing[j]<<" ";
    }
}

void myLogging::deleteFile(string fileName,int maxNum){
    int control;
    string delFileName =fileName+".json";
    control = remove(delFileName.c_str());
    if(control==0){
        cout<<"\nFile deleted successfully!"<<endl;
    }
    else{
        cout<<"\nError!"<<endl;
    }
}

void myLogging::LogCheck(int type, string fileName, int maxNum, int frequency){
    
    //string fileNameConv= fileName + ".json";
    CreatingLogFile(type, fileName,  maxNum, frequency);
    myLogging::storing.push_back(fileName);
    fullCheck(maxNum);
    cout<<endl;
}

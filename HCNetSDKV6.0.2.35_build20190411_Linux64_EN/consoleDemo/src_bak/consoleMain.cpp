#ifndef __APPLE__

#include <stdio.h>
#include <iostream>
#include "GetStream.h"
#include "public.h"
#include "ConfigParams.h"
#include "Alarm.h"
#include "CapPicture.h"
#include "playback.h"
#include "Voice.h"
#include "tool.h"
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
   char* uname;
   char* pass;
   int port;
   char* ip;
   std::cout << "Usage: sdkTest:: Username | Password | IP | Port" << "\n";
   // Check the number of parameters
    if (argc < 1) {
       uname = "admin";
       pass  = "admin12345";
       port     = 8000;
       ip    = "192.168.1.121";

    }else{

       uname = argv[1];
       pass  = argv[2];
       ip    = argv[3];
       port  = argv[4];



}
        // Print the user's name:
    std::cout <<  "UserName::, " << uname << "!\n" << std::endl;
    std::cout <<  "Password::, " << pass << "!\n" << std::endl;
    std::cout <<  "IP::, " << ip << "!\n" << std::endl;
    std::cout <<  "Port::, " << port << "!\n" << std::endl;
    std::cout << "here is end of old\n";













    NET_DVR_Init();
    Demo_SDK_Version();
    //Login device
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;
    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, ip , NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, uname, NAME_LEN);
    memcpy(struLoginInfo.sPassword, pass, NAME_LEN);
    int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    Demo_Capture();
    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();
    return 0;
}

#endif

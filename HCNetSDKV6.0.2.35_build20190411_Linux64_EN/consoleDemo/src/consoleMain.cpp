#ifndef __APPLE__

#include <stdio.h>
#include <iostream>
#include "GetStream.h"
#include "public.h"
#include "ConfigParams.h"
#include "CapPicture.h"
#include "tool.h"
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
   char* uname;
   char* pass;
   char* ip;
   char* dir;
   //std::cout << "Usage: sdkTest:: Username | Password | IP | Dir" << "\n";
   // Check the number of parameters
    if (argc < 4) {
       uname = "admin";
       pass  = "admin12345";
       ip    = "192.168.1.122";
       dir   = "IMG/"; 

    }else{

       uname = argv[1];
       pass  = argv[2];
       ip    = argv[3];
       dir   = argv[4];
    }
    // Print the user's name:
    // std::cout <<  "UserName::, " << uname << "!\n" << std::endl;
    // std::cout <<  "Password::, " << pass << "!\n" << std::endl;
    // std::cout <<  "IP::, " << ip << "!\n" << std::endl;
    // std::cout <<  "Port::, " << "8000" << "!\n" << std::endl;
    // std::cout <<  "Dir::, " << dir << "!\n" << std::endl; 
    // std::cout << "here is end of old\n";
    NET_DVR_Init();
    //Demo_SDK_Version();
    //NET_DVR_SetLogToFile(3, "./sdkLog");
    //char cUserChoose = 'r';

    //Login device

    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, ip, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, uname, NAME_LEN);
    memcpy(struLoginInfo.sPassword, pass, NAME_LEN);

    int lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    //if (lUserID < 0)
    //{
    //    printf("pyd---Login error, %d\n", NET_DVR_GetLastError());
    //    printf("Press any key to quit...\n");
    //    cin>>cUserChoose;

    //    NET_DVR_Cleanup();
    //    return HPR_ERROR;
    //}
    //NET_DVR_JPEGPARA strPicPara = {0};
    //strPicPara.wPicQuality = 2;
    //strPicPara.wPicSize = 0;
    //int iRet;
    //  iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, "./ssss.jpeg");
    //if (!iRet)
    //{
      //  printf("pyd1---NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
       // return HPR_ERROR;
    // }
    Demo_Capture(uname,pass,ip,dir);
    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return 0;
}

#endif

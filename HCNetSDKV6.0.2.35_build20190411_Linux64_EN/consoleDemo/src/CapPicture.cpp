#include "public.h"
#include "CapPicture.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
/*    -------------    */
#include <ctime>
#include <sstream>
#include <stdio.h>

using namespace std;

/*******************************************************************
      Function:   Demo_Capture
   Description:   Capture picture.
     Parameter:   (IN)   none 
        Return:   0--success��-1--fail.   
**********************************************************************/
int Demo_Capture(char* uname, char* pass, char* ip, char* dir)
{
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;
    //cout << uname << "::  Uname\n" << endl; 
    //cout << pass << "::  pass\n" << endl; 
    //cout << ip << "::  IP\n" << endl; 
    //cout << dir << "::  DIR\n" << endl; 
    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, ip, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, uname, NAME_LEN);
    memcpy(struLoginInfo.sPassword, pass, NAME_LEN);
    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 0;
    int iRet;
     time_t current_time;
     time(&current_time);
     //cout << current_time << "\n";
     //std::cout << typeid(current_time).name() << '\n';
     char strLong[1024];
     sprintf(strLong, "%ld", current_time);
     char *ext = ".jpeg";
     char result[100];   // array to hold the result.
     strcpy(result,strLong);
     strcat(result,ext);
     cout << result << endl;
     char rs[100];
     strcpy(rs,dir);
     strcat(rs,result);
     //cout << rs << "\n" << endl; 
    iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, rs);//result);
    //if (!iRet)
    //{
    //    printf("pyd1---NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
    //    return HPR_ERROR;
    //}
    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}

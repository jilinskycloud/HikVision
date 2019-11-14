#include "public.h"
#include "CapPicture.h"
#include <stdio.h>
#include <string.h>

/*    -------------    */
#include <ctime>
#include <sstream>



/*******************************************************************
      Function:   Demo_Capture
   Description:   Capture picture.
     Parameter:   (IN)   none 
        Return:   0--success��-1--fail.   
**********************************************************************/
int Demo_Capture()
{
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.1.121", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "admin12345", NAME_LEN);

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    //
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 0;
    int iRet;





time_t current_time;
// Stores time in current_time
time(&current_time);
//cout << current_time << "\n";
//std::cout << typeid(current_time).name() << '\n';
char strLong[1024];
sprintf(strLong, "%ld", current_time);
//printf("%s\n",strLong);
//std::cout << typeid(strLong).name() << '\n';


char *ext = ".jpeg";

char result[100];   // array to hold the result.
strcpy(result,strLong);
strcat(result,ext);
//std::cout << typeid(result).name() << '\n';
//cout << result << "this is the f*\n";






//std::cout << typeid(strLong).name() << '\n';




















    iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, result);

    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}

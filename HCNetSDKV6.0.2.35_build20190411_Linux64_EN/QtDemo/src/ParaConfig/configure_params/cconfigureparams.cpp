/*
 * Copyright(C) 2010,Hikvision Digital Technology Co., Ltd 
 * 
 * �ļ����ƣ�cconfigureparams.cpp
 * ��    ����
 * ��ǰ�汾��1.0
 * ��    �ߣ����Ƕ�
 * �������ڣ�2010��2��1��
 * �޸ļ�¼��
 */

#include "cconfigureparams.h"
#include "ui_cconfigureparams.h"
#include <QPushButton>
#include <new>
#include "DemoPublic.h"
#include <stdio.h>

/*******************************************************************
      Function:   CConfigureParams::CConfigureParams
   Description:   ���캯��
     Parameter:   (IN)   QWidget *parent ������ 
        Return:   0--�ɹ���-1--ʧ�ܡ�   
**********************************************************************/
CConfigureParams::CConfigureParams(QWidget *parent): QWidget(parent), ui(new Ui::CConfigureParams)
{
    ui->setupUi(this);
    m_lUserID = -1;

    m_pRemoteparams = NULL; 
    m_pIPParams = NULL;
    m_pCurrentWidget = NULL;
    m_pHardDiskParams = NULL;

   connect(ui->btnRemoteParams, SIGNAL(clicked()), this, SLOT(loadRemoteParams()));
   connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(GetDVRUserID()));
   connect(ui->btnLogout, SIGNAL(clicked()), qApp, SLOT(quit()));

   ui->btnLogin->hide();
   ui->btnLogout->hide();
   ui->btnLocalParams->hide();
}

/*******************************************************************
      Function:   CConfigureParams::~CConfigureParams
   Description:   ��������
     Parameter:   (IN)   �޲���  
        Return:   ��
**********************************************************************/
CConfigureParams::~CConfigureParams()
{
    if(m_pRemoteparams != NULL)
    {
        delete m_pRemoteparams;
    }
    if(m_pIPParams != NULL)
    {
    	delete m_pIPParams;
    }
    delete m_pHardDiskParams;   //ɾ��Ӳ������

    delete ui;
}

/*******************************************************************
      Function:   CConfigureParams::loadRemoteParams
   Description:   load the remot params form!
     Parameter:   (IN)   �޲���  
        Return:   0--�ɹ���-1--ʧ�ܡ�   
**********************************************************************/
void CConfigureParams::loadRemoteParams()
{
	if(NULL == m_pRemoteparams)
	{
		m_pRemoteparams = new(std::nothrow) CRemoteParams;
		if(NULL == m_pRemoteparams)
		{
	    	m_MessageBox.setText("addWidget error!");
	    	m_MessageBox.exec();
	    	return ;
		}
	}

	if(m_pCurrentWidget != NULL) //���ص�ǰ����
	{
		m_pCurrentWidget->hide();
	}
	m_pCurrentWidget = m_pRemoteparams;
	m_pRemoteparams->setUserID(m_lUserID);
	ui->vLayParamForm->addWidget(m_pCurrentWidget);
	m_pCurrentWidget->show();
}

/*******************************************************************
      Function:   CConfigureParams::on_btnIPParams_clicked
   Description:   ip��������
     Parameter:   (IN)   �޲���  
        Return:   0--�ɹ���-1--ʧ�ܡ�   
**********************************************************************/
void CConfigureParams::on_btnIPParams_clicked()
{
	if(NULL == m_pIPParams)
	{
		m_pIPParams = new(std::nothrow) CIPParams;
		if(NULL == m_pIPParams)
		{
	    	m_MessageBox.setText("addWidget error!");
	    	m_MessageBox.exec();
	    	return ;
		}
	}
	//���ص�ǰ����
	if(m_pCurrentWidget != NULL)
	{
		m_pCurrentWidget->hide();
	}
	m_pIPParams->setUserID(m_lUserID);
	m_pCurrentWidget = m_pIPParams;
	ui->vLayParamForm->addWidget(m_pCurrentWidget);
    m_pCurrentWidget->show();
}

/*******************************************************************
      Function:   CConfigureParams::on_btnHardDiskParams_clicked
   Description:   Ӳ������
     Parameter:   (IN)   �޲���  
        Return:   0--�ɹ���-1--ʧ�ܡ�   
**********************************************************************/
void CConfigureParams::on_btnHardDiskParams_clicked()
{
	if(NULL == m_pHardDiskParams)
	{
		m_pHardDiskParams = new(std::nothrow) CHardDiskParams;
		if(NULL == m_pHardDiskParams)
		{
	    	m_MessageBox.setText("addWidget error!");
	    	m_MessageBox.exec();
	    	return ;
		}
	}
	//���ص�ǰ����
	if(m_pCurrentWidget != NULL)
	{
		m_pCurrentWidget->hide();
	}
	m_pHardDiskParams->setUserID(m_lUserID);
	m_pCurrentWidget = m_pHardDiskParams;
	ui->vLayParamForm->addWidget(m_pCurrentWidget);
    m_pCurrentWidget->show();
}

/*******************************************************************
      Function:   CConfigureParams::GetDVRUserID
   Description:   Get the user ID.
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void CConfigureParams::GetDVRUserID()
{
    //1.m_lUserID =lUerID;

    //2.login the divice
    int iRet;
    int iError;
    iRet = NET_DVR_Init();
    iError = NET_DVR_GetLastError();

    //m_lUserID = NET_DVR_Login(m_serverIP, 8000, "admin", "091103", &m_devInfo);
        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
        struLoginInfo.bUseAsynLogin = false;

        struLoginInfo.wPort = 8000;
        memcpy(struLoginInfo.sDeviceAddress, "10.8.98.80", NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
        memcpy(struLoginInfo.sPassword, "hik12345", NAME_LEN);

        m_lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);



     if(m_lUserID < 0)
     {
         iError = NET_DVR_GetLastError();
        printf( "Login DVR failed ... LastError[%d]\n", NET_DVR_GetLastError());
        QMessageBox::information(this, tr("Login failed"), tr("\"%1\" is return value of NET_DVR_Login_V40.").arg(m_lUserID));
        NET_DVR_Cleanup();
        return ;
     }
     else
     {
         ui->btnLogin->setEnabled(FALSE);
     }

}

/*******************************************************************
      Function:   CConfigureParams::SetDVRUserID
   Description:   Set User ID to this class.
     Parameter:   (IN)   long lUserID  
        Return:   none   
**********************************************************************/
void CConfigureParams::SetDVRUserID(long lUserID)
{
	if(lUserID >= 0)
	{
		m_lUserID = lUserID;
	}
}

/*******************************************************************
      Function:   CConfigureParams::showEvent
   Description:   show event
     Parameter:   (IN)   QShowEvent * event  
        Return:   bone   
**********************************************************************/
void CConfigureParams::showEvent ( QShowEvent * event )
{
	if(m_lUserID < 0)
	{
		return;
	}

	//QMessageBox::information(this, tr("Login failed"), tr(" is return value of NET_DVR_Login_V40."));
	if(NULL != m_pRemoteparams)
	{
		m_pRemoteparams->setUserID(m_lUserID);
	}

	if(NULL != m_pIPParams)
	{
		m_pIPParams->setUserID(m_lUserID);
	}

	if(NULL != m_pHardDiskParams)
	{
		m_pHardDiskParams->setUserID(m_lUserID);
	}
}

/*******************************************************************
      Function:   CConfigureParams::showLoginBtn
   Description:   Show buttons.
     Parameter:   (IN)   �޲���  
        Return:   none   
**********************************************************************/
void CConfigureParams::showLoginBtn()
{
	ui->btnLogin->show();
	ui->btnLogout->show();
}




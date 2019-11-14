/**  @file qtclientdemo.cpp
 *   @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved. 
 *   @brief 
 *   
 *   @author wanggongpu 
 *   @modify by panyadong
 *   @date 2012-5-22
 *   
 *   @note 
 */

#include "qtclientdemo.h"
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <Qt>
#include <QDir>
#include <QTableWidgetItem>
#include "treeitem.h"
extern QtClientDemo* gqtclinetdemo;

//each start or exit mainwindow need read or write file path
#define DEVICE_TREE_FILE_PATH "device_tree.txt" 


/*******************************************************************
      Function:   MessCallBack_V30
   Description:   �����ص�����
     Parameter:   (IN)   int lCommand  �¼����� 
                  (IN)   NET_DVR_ALARMER *pAlarmer  �澯����
                  (IN)   char *pAlarmInfo  �澯��Ϣ
                  (IN)   unsigned int dwBufLen  ���ݳ���
                  (IN)   void* pUser  �û�����
        Return:   ��   
**********************************************************************/
void __stdcall MessCallBack_V30(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
    qDebug("len:%d, user data:%p", dwBufLen, pUser);

   	if(lCommand < EXCEPTION_EXCHANGE)
	{         
		fprintf(stderr, "lCommand[%x]\n",lCommand);
	}

	switch (lCommand)
	{
		case COMM_ALARM:
			if ((gqtclinetdemo != NULL)&&(gqtclinetdemo->m_alarmtable != NULL))
			{
				QString currenttime = QDateTime::currentDateTime().toString(
				" yyyy/MM/dd hh:mm:ss");
				QTableWidgetItem *currtime = new QTableWidgetItem(currenttime);
				QString alarminformation;
				switch (((LPNET_DVR_ALARMINFO)pAlarmInfo)->dwAlarmType)
				{ 
					case 0:
						alarminformation.append("�ź�������");
						break;
					case 1:
						alarminformation.append("Ӳ����");
						break;
					case 2:
						alarminformation.append("�źŶ�ʧ");
						break;
					case 3:
						alarminformation.append("�ƶ�����");
						break;
					case 4:
						alarminformation.append("Ӳ�̸�ʽ��");
						break;
						
					case 5:
						alarminformation.append("��дӲ�̳���");
						break;
					case 6:
						alarminformation.append("�ڵ�����");
						break;
					case 7:
						alarminformation.append("��ʽ��ƥ��");
						break;
					case 8:
						alarminformation.append("�Ƿ�����");
						break;
					default:
						alarminformation.append("δ֪�澯");
						break;
				}
				QTableWidgetItem *alarminfo = new QTableWidgetItem(alarminformation);	
				QString deviceip(pAlarmer->sDeviceIP);
				deviceip.append("_");
				deviceip.append(pAlarmer->sDeviceName);
				QTableWidgetItem *devinfo = new QTableWidgetItem(deviceip);	
				int row = gqtclinetdemo->m_alarmtable->ui.tableWidget->rowCount();
				gqtclinetdemo->m_alarmtable->ui.tableWidget->insertRow(row);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 0, currtime);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 1, alarminfo);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 2, devinfo);
			}		
			break;
		//case COMM_ALARM_RULE:
			
			//break;
			
		case COMM_TRADEINFO:
			break;
		
		case COMM_ALARM_V30:
			if ((gqtclinetdemo != NULL)&&(gqtclinetdemo->m_alarmtable != NULL))
			{
				QString currenttime = QDateTime::currentDateTime().toString(
				" yyyy/MM/dd hh:mm:ss");
				QTableWidgetItem *currtime = new QTableWidgetItem(currenttime);
				QString alarminformation;
				switch (((LPNET_DVR_ALARMINFO_V30)pAlarmInfo)->dwAlarmType)
				{ 
					case 0:
						alarminformation.append("�ź�������");
						break;
					case 1:
						alarminformation.append("Ӳ����");
						break;
					case 2:
						alarminformation.append("�źŶ�ʧ");
						break;
					case 3:
						alarminformation.append("�ƶ�����");
						break;
					case 4:
						alarminformation.append("Ӳ�̸�ʽ��");
						break;
						
					case 5:
						alarminformation.append("��дӲ�̳���");
						break;
					case 6:
						alarminformation.append("�ڵ�����");
						break;
					case 7:
						alarminformation.append("��ʽ��ƥ��");
						break;
					case 8:
						alarminformation.append("�Ƿ�����");
						break;
					case 9:
						alarminformation.append("��Ƶ�ź��쳣");
						break;
					case 10:
						alarminformation.append("¼���쳣");
						break;
					default:
						alarminformation.append("δ֪����");
						break;
				}
				QTableWidgetItem *alarminfo = new QTableWidgetItem(alarminformation);	
				QString deviceip(pAlarmer->sDeviceIP);
				deviceip.append("_");
				deviceip.append(pAlarmer->sDeviceName);
				QTableWidgetItem *devinfo = new QTableWidgetItem(deviceip);	
				int row = gqtclinetdemo->m_alarmtable->ui.tableWidget->rowCount();
				gqtclinetdemo->m_alarmtable->ui.tableWidget->insertRow(row);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 0, currtime);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 1, alarminfo);
				gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 2, devinfo);
			}
			break;
		case COMM_IPCCFG :
				break;
			
		//case COMM_IPCCFG_V31:
			//break;
		default :
			break;
	}
}

/*******************************************************************
      Function:   MessCallBack
   Description:   �쳣�¼��ص�����
     Parameter:   (IN)   int lCommand  �¼�����
                  (IN)   char *sDVRIP  �澯����
                  (IN)   char *pBuf  �쳣��Ϣ
                  (IN)   unsigned int dwBufLen  ���ݳ���
        Return:   0��ʾʧ�ܣ�1��ʾ�ɹ�
**********************************************************************/
unsigned int __stdcall MessCallBack(int lCommand, char *sDVRIP, char *pBuf, unsigned int dwBufLen)
{
    qDebug("MessCallBack len:%d", dwBufLen);

	int lIndex = -1;

   	if(lCommand < EXCEPTION_EXCHANGE)
	{         
		//fprintf(stderr, "lCommand[%x], sDVRIP[%s], pBuf[%s], dwBufLen[%d]\n",
		//		lCommand, sDVRIP, pBuf, dwBufLen);
	
		switch (lCommand)
		{
			case COMM_ALARM:
				if ((gqtclinetdemo != NULL)&&(gqtclinetdemo->m_alarmtable != NULL))
				{
					QString currenttime = QDateTime::currentDateTime().toString(
					" yyyy/MM/dd hh:mm:ss");
					QTableWidgetItem *currtime = new QTableWidgetItem(currenttime);
					QString alarminformation;
					switch (((LPNET_DVR_ALARMINFO)pBuf)->dwAlarmType)
					{ 
						case 0:
							alarminformation.append("�ź�������");
							break;
						case 1:
							alarminformation.append("Ӳ����");
							break;
						case 2:
							alarminformation.append("�źŶ�ʧ");
							break;
						case 3:
							alarminformation.append("�ƶ�����");
							break;
						case 4:
							alarminformation.append("Ӳ�̸�ʽ��");
							break;
							
						case 5:
							alarminformation.append("��дӲ�̳���");
							break;
						case 6:
							alarminformation.append("�ڵ�����");
							break;
						case 7:
							alarminformation.append("��ʽ��ƥ��");
							break;
						case 8:
							alarminformation.append("�Ƿ�����");
							break;
						default:
							alarminformation.append("δ֪�澯");
							break;
					}
					QTableWidgetItem *alarminfo = new QTableWidgetItem(alarminformation);	
					QString deviceip(sDVRIP);
					QTableWidgetItem *devinfo = new QTableWidgetItem(deviceip);	
					int row = gqtclinetdemo->m_alarmtable->ui.tableWidget->rowCount();
					gqtclinetdemo->m_alarmtable->ui.tableWidget->insertRow(row);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 0, currtime);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 1, alarminfo);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 2, devinfo);
				}		
				break;
			//case COMM_ALARM_RULE:
				
				//break;
				
			case COMM_TRADEINFO:
				break;
			
			case COMM_ALARM_V30:
				if ((gqtclinetdemo != NULL)&&(gqtclinetdemo->m_alarmtable != NULL))
				{
					QString currenttime = QDateTime::currentDateTime().toString(
					" yyyy/MM/dd hh:mm:ss");
					QTableWidgetItem *currtime = new QTableWidgetItem(currenttime);
					QString alarminformation;
					switch (((LPNET_DVR_ALARMINFO_V30)pBuf)->dwAlarmType)
					{ 
						case 0:
							alarminformation.append("�ź�������");
							break;
						case 1:
							alarminformation.append("Ӳ����");
							break;
						case 2:
							alarminformation.append("�źŶ�ʧ");
							break;
						case 3:
							alarminformation.append("�ƶ�����");
							break;
						case 4:
							alarminformation.append("Ӳ�̸�ʽ��");
							break;
							
						case 5:
							alarminformation.append("��дӲ�̳���");
							break;
						case 6:
							alarminformation.append("�ڵ�����");
							break;
						case 7:
							alarminformation.append("��ʽ��ƥ��");
							break;
						case 8:
							alarminformation.append("�Ƿ�����");
							break;
						case 9:
							alarminformation.append("��Ƶ�ź��쳣");
							break;
						case 10:
							alarminformation.append("¼���쳣");
							break;
						default:
							alarminformation.append("δ֪����");
							break;
					}
					QTableWidgetItem *alarminfo = new QTableWidgetItem(alarminformation);	
					QString deviceip(sDVRIP);
					QTableWidgetItem *devinfo = new QTableWidgetItem(deviceip);	
					int row = gqtclinetdemo->m_alarmtable->ui.tableWidget->rowCount();
					gqtclinetdemo->m_alarmtable->ui.tableWidget->insertRow(row);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 0, currtime);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 1, alarminfo);
					gqtclinetdemo->m_alarmtable->ui.tableWidget->setItem(row, 2, devinfo);
				}
				break;
			case COMM_IPCCFG :
					break;
				
			//case COMM_IPCCFG_V31:
				//break;
			default :
				break;
		}

		

	}
	else
	{	
		QString exception;
		QString devip(sDVRIP);
		lIndex = *((int *)pBuf);
		switch (lCommand)  
		{
			case EXCEPTION_EXCHANGE:
				exception.append("network exception");
				break;
			case EXCEPTION_AUDIOEXCHANGE:
				exception.append(" audioexchange exception");
				exception.append("_");
				exception.append(QString::number(lIndex));
				break;
			case EXCEPTION_ALARM:
				
				exception.append(" alarm exception");
				exception.append("_");
				exception.append(QString::number(lIndex));
				break;
			case EXCEPTION_PREVIEW:
				exception.append(" preview exception");
				exception.append("_");
				exception.append(QString::number(lIndex));
				break;
			case EXCEPTION_SERIAL:
				exception.append(" serial exception");
				exception.append("_");
				exception.append(QString::number(lIndex));
				break;	
			default:
				break;
		}
		if ((gqtclinetdemo != NULL)&&(gqtclinetdemo->m_logtable != NULL))
		{
			gqtclinetdemo->m_logtable->addLogAlarmInfo(0, exception, 
				devip, exception);
		}
	}      
    return 1;
}

/**  @fn  void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
 *   @brief Process exception.
 *   @param (IN) DWORD dwType  
 *   @param (IN) LONG lUserID  
 *   @param (IN) LONG lHandle  
 *   @param (IN) void *pUser  
 *   @return none.  
 */
#if defined(_WIN32)
void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
#else
void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
#endif
{
    qDebug("ExceptionCallBack lUserID:%d, handle:%d, user data:%p", lUserID, lHandle, pUser);

	char tempbuf[256];
	memset(tempbuf, 0, 256);
	switch(dwType)
	{
	case EXCEPTION_AUDIOEXCHANGE:		//Audio exchange exception
	    sprintf(tempbuf,"Audio exchange exception!");
	    gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
		//TODO: close audio exchange
		break;

    //Alarm//
	case EXCEPTION_ALARM:			            //Alarm exception
		sprintf(tempbuf,"Alarm exception!");
		gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
		//TODO: close alarm update
		break;
    case EXCEPTION_ALARMRECONNECT:  //Alarm reconnect
        sprintf(tempbuf,"Alarm reconnect.");
        gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
        break;
    case ALARM_RECONNECTSUCCESS:      //Alarm reconnect success
        sprintf(tempbuf,"Alarm reconnect success.");
        gqtclinetdemo->m_logtable->addLogAlarmInfo(1, "", "", QString(tempbuf));
        break;

	case EXCEPTION_SERIAL:			           //Serial exception
		sprintf(tempbuf,"Serial exception!");
		gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
		//TODO: close exception
		break;

    //Preview//
    case EXCEPTION_PREVIEW:			     //Preview exception
        sprintf(tempbuf,"Preview exception!");
        gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
        //TODO: close preview
        break;
	case EXCEPTION_RECONNECT:			 //preview reconnect
		sprintf(tempbuf,"preview reconnecting.");
		gqtclinetdemo->m_logtable->addLogAlarmInfo(0, "", "", QString(tempbuf));
		break;
    case PREVIEW_RECONNECTSUCCESS: //Preview reconnect success
        sprintf(tempbuf,"Preview reconncet success.");
        gqtclinetdemo->m_logtable->addLogAlarmInfo(1, "", "", QString(tempbuf));
        break;
	default:
		break;
	}
}

/*******************************************************************
      Function:   QMainWindow
   Description:   �������๹�캯��
     Parameter:   (IN)   parent  ����
        Return:   ��   
**********************************************************************/
QtClientDemo::QtClientDemo(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);

    //show date and time right upper corner
    m_qtimer = new QTimer;   
    m_qtimer->start( 1000 );
    connect (m_qtimer, SIGNAL(timeout()), this, SLOT(updateTime()));

	m_gmodel =NULL;
	
    //show tree left side
    m_addnewdevice = NULL;    
    m_qtreemenu = NULL;
    m_deviceattr = NULL;
    m_channelattr = NULL;
    m_iposttreelevel = -1;

	m_logtable = NULL;  
	m_alarmtable = NULL;  
	m_loghasallocated = 0;
	m_alarmhasallocated = 0;
	show();

	ui.DVRsets_treeView->setMouseTracking(1);
    //mouse right clicked and left single responsing
    ui.DVRsets_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.DVRsets_treeView, SIGNAL(customContextMenuRequested(const QPoint &)), 
		this, SLOT(showTreeContextMenu(const QPoint &)));

	connect(ui.DVRsets_treeView, SIGNAL(pressed(const QModelIndex &)), 
		this, SLOT(pressedTreeView(const QModelIndex &)));
	connect(ui.DVRsets_treeView, SIGNAL(viewportEntered()), 
		this, SLOT(enterview()));
	m_gblanklabel = 0;	
    connect(ui.DVRsets_treeView, SIGNAL(doubleClicked(const QModelIndex &)), \
        this, SLOT(OnDoubleClickTree(const QModelIndex &)));

    //read file and fill tree widget
    QFile treefile(DEVICE_TREE_FILE_PATH);
    if (!treefile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::information(this,tr("file error"),\
            tr("open device tree file error"));
    }
    QByteArray treedata =treefile.readAll();
    treefile.close();
    m_qlistdevicedata = getListFromArray(treedata);
    QString treedatastring;
    treedatastring =getStringFromList(m_qlistdevicedata);
    showDeviceTree(treedatastring);

    //����ȫ����־table
	m_logtable = new LogTable;
	m_loghasallocated = 1;
	m_alarmtable = new AlarmTable;
	m_alarmhasallocated = 1;
    ui.vboxLayout->addWidget(m_logtable);
	ui.vboxLayout->addWidget(m_alarmtable);

	on_radioButton_locallog_pressed ();
	ui.radioButton_locallog->setChecked(1);
	
	//AT last need init SDK 
    if (!NET_DVR_Init())
    {
        QMessageBox::information(this,tr("SDK INITIAL ERROR"), \
            tr("SDK_LAST_ERROR=%1").arg(NET_DVR_GetLastError()));
		if (m_logtable != NULL)
		{
			m_logtable->addLogAlarmInfo(0, QString("NET_DVR_Init"), 
				NULL, QString::number(NET_DVR_GetLastError()));
		}
		
    }
	else
	{
		//WRITE LOG OF NET_DVR INTERFACE CALLED
		if (m_logtable != NULL)
		{
			m_logtable->addLogAlarmInfo(1, QString("NET_DVR_Init"), 
				NULL, NULL);
		}

	}
	BOOL bRet = NET_DVR_SetLogToFile(3, "./sdkLog", false);
        NET_DVR_SetLogPrint(true);
	printf("NET_DVR_SetLogToFile %d\n", bRet);
	NET_DVR_SetConnectTime(10000, 1);
    NET_DVR_SetExceptionCallBack_V30(0, NULL, ExceptionCallBack, NULL);
	
    //for draw area 
    show();
	m_gcurrentuserid =-1;
	m_guseridbackup =m_gcurrentuserid;
    m_gcurrentchannelnum =1;
	m_gchannelnumbackup =1;
    m_gcurrentchannellinkmode =0x0;

	
    //drawarea initial and new realplay
    m_realplay =new RealPlay(&m_gmodel, &m_qtreemodelindex, &m_qlistdevicedata, &m_gcurrentuserid,&m_gcurrentdeviceinfo,\
        &m_gcurrentchannelnum, &m_gcurrentchannellinkmode, m_logtable);
	
    ui.gridLayout->addWidget(m_realplay);
	
	m_realplay->DrawAreaInit();

    m_currentpagenum = 1;  


    m_playback =NULL;
	
    //manage module
    m_qmenumanage =NULL;
    m_timing=NULL;
    m_update=NULL;
    m_format=NULL;
    m_reboot=NULL;
    m_shutdown=NULL;
    m_searchlog=NULL;
    m_state=NULL;
    m_reset=NULL;

    //other module
    m_qmenuother =NULL;
    m_deploy=NULL;
    m_devicepan=NULL;
    m_import=NULL;
    m_serial=NULL;
    m_audiobroadcast=NULL;
    m_audiointercom=NULL;
    m_audiotransfer=NULL;

    //exit module
    m_exitdemo = NULL;
	
	//DBG("QtClientDemo", 377);
	m_iparaconfhasclicked =0;


    //Display verison
    SetSDKVersionToLabel();

	//NET_DVR_SetDVRMessageCallBack_V30(MessCallBack_V30,(void*)0);	
     NET_DVR_SetDVRMessageCallBack_V51(0, MessCallBack_V30, NULL);
	//NET_DVR_SetDVRMessCallBack(MessCallBack);
	m_glistenhandle = NET_DVR_StartListen_V30(NULL, 7200, MessCallBack_V30, (void*)0 );
	if( m_glistenhandle < 0 )
	{
	    printf("StartListen failed ... LastError[%d]\n", NET_DVR_GetLastError());
	}

	ui.pushButton_logaramsave->hide();
	ui.pushButton_logaramlistconf->hide();
	ui.pushButton_logaramtest->hide();
}

/*******************************************************************
      Function:   QtClientDemo::~QtClientDemo
   Description:   �������๹�캯��
     Parameter:   (IN)   �޲���  
        Return:   �� 
**********************************************************************/
QtClientDemo::~QtClientDemo()
{ 
	if (m_glistenhandle >= 0)
	{
	    NET_DVR_StopListen_V30(m_glistenhandle);
	}
//QMessageBox::information(this,tr("~QtClientDemo"),tr("528"));
	if (m_realplay != NULL)
	{
		delete m_realplay;
		m_realplay = NULL;
	}
//QMessageBox::information(this,tr("~QtClientDemo"),tr("534"));	
	if (m_playback!= NULL)
	{
		delete m_playback;
		m_playback = NULL;
	}
	
    if (m_exitdemo != NULL)
    {
        delete m_exitdemo;
        m_exitdemo = NULL;
    }
	if (m_addnewdevice != NULL)
    {
        m_addnewdevice->close();
        delete m_addnewdevice;
        m_addnewdevice = NULL;
    }
	
	if (NULL != m_qtimer)
	{	
		delete m_qtimer;
		m_qtimer = NULL;
	}

//QMessageBox::information(this,tr("~QtClientDemo"),tr("560"));
	
	//save current config to file
    QFile treefile(DEVICE_TREE_FILE_PATH);
    if (!treefile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this,tr("file error"),\
        tr("open device tree file error"));
    }

    QTextStream stream( &treefile );
    QString lines =getStringFromList(m_qlistdevicedata);
    stream << lines;

    treefile.close();

//QMessageBox::information(this,tr("~QtClientDemo"),tr("576"));
	
    //releas real play resource
     if (NULL != m_timing )
    {
        delete m_timing;
        m_timing= NULL;
    }
    if (NULL != m_update)
    {
        delete m_update;
        m_update= NULL;
    }

    if (NULL != m_format)
    {
        delete m_format;
        m_format= NULL;
    }
    if (NULL != m_reboot)
    {
        delete m_reboot;
        m_reboot= NULL;
    }
    if (NULL != m_shutdown)
    {
        delete m_shutdown;
        m_shutdown= NULL;
    }
    if (NULL != m_searchlog)
    {
        delete m_searchlog;
        m_searchlog= NULL;
    }
    if (NULL != m_state)
    {
        delete m_state;
        m_state= NULL;
    }
    if (NULL != m_reset)
    {
        delete m_reset;
        m_reset= NULL;
    }

    if (NULL != m_deploy)
    {
        delete m_deploy;
        m_deploy = NULL;
    }
    if (NULL != m_devicepan)
    {
        delete m_devicepan;
        m_devicepan= NULL;
    }
    if (NULL != m_import)
    {
        delete m_import;
        m_import= NULL;        
    }
    if (NULL != m_serial)
    {
        delete m_serial;
        m_serial= NULL;        
    }
    if (NULL != m_audiobroadcast)
    {
        delete m_audiobroadcast;
        m_audiobroadcast= NULL;        
    }
    if (NULL != m_audiointercom)
    {
        delete m_audiointercom;
        m_audiointercom= NULL;        
    }
    if (NULL != m_audiotransfer)
    {
        delete m_audiotransfer;
        m_audiotransfer= NULL;        
    }

//QMessageBox::information(this,tr("~QtClientDemo"),tr("646"));
    //manage and other menu
    if (m_qmenumanage !=NULL)
    {
        delete m_qmenumanage;
        m_qmenumanage =NULL;
    }
    if (m_qmenuother !=NULL)
    {
        delete m_qmenuother;
        m_qmenuother =NULL;
    }

//QMessageBox::information(this,tr("~QtClientDemo"),tr("659"));	
	
	NET_DVR_Cleanup();
//QMessageBox::information(this,tr("~QtClientDemo"),tr("662"));	
}

/*******************************************************************
      Function:   QtClientDemo::updateTime
   Description:   ����ʱ����Ϣ
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::updateTime()
{
    QString currentdatetime = QDateTime::currentDateTime().toString(\
								" yyyy-MM-dd \n dddd \n hh:mm:ss");
    ui.CurrDataTime_label->setText(currentdatetime);
    return;
}

/*******************************************************************
      Function:   QtClientDemo::pressedTreeView
   Description:   �������ڵ�
     Parameter:   (IN)   const QModelIndex &index  ���ڵ�����
        Return:   ��   
**********************************************************************/
void QtClientDemo::pressedTreeView(const QModelIndex &index )
{
	//Ŀ�������õ�ǰ��Ч���豸��ͨ����Ϣ�����������������豸�����豸����ͨ��
	//Ȼ��ͨ��index��parent()��row()ֵ����λ��qlistdevice�е�λ�ú�ʵ������
    //QMessageBox::information(this,tr("pressedTreeView"),tr("row=%1 column=%2 data=%3").arg(index.row()
    //).arg(index.column()).arg(index.data().toString().toLatin1().data()));
	int level = 0;
	QModelIndex tmpindex = index;
	while (tmpindex.parent().isValid()==1)
	{
		level ++ ;
		tmpindex = tmpindex.parent();		
	}
	//QMessageBox::information(this,tr("pressedTreeView"),tr("level=%1").arg(level));
	//ˮƽ������
	ui.DVRsets_treeView->resizeColumnToContents(index.column());
	

	//the top of tree to add new device node
    if (level == 0)
    {
         m_iposttreelevel= 0;
		 //���ı䵱ǰ��Ч�豸��ͨ�����ݣ�ֱ�ӷ���
		 return;
    }
    else if (level == 1)
    {
    	//��ǰ��������һ̨�豸
    	m_qtreemodelindex = index;
		m_iposttreelevel = 1;
    }
    else if(level == 2)
    {   
    	m_qtreemodelindex = index;
        m_iposttreelevel = 2;
    }
	m_gblanklabel = 0;	
}

/*******************************************************************
      Function:   QtClientDemo::enterview
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::enterview()
{
	//QMessageBox::information(this,tr("enterview"),tr("enterview"));
	//m_gblanklabel = 1;	
}

/*******************************************************************
      Function:   QtClientDemo::treeBeenClicked
   Description:   ˫�����ڵ㣺��ǰ���豸��ͨ���ᱻ�ı�
     Parameter:   (IN)   const QModelIndex & index  ���ڵ�����
        Return:   ��   
**********************************************************************/
void QtClientDemo::OnDoubleClickTree(const QModelIndex & index)
{   
	int level = 0;
	QModelIndex tmpindex = index;
	while (tmpindex.parent().isValid()==1)
	{
		level ++ ;
		tmpindex = tmpindex.parent();		
	}
	if (level == 0)
    {
        m_iposttreelevel= 0;
    }
    else if (level == 1)
    {
		m_qtreemodelindex = index;
		m_iposttreelevel = 1;
    }
    else if (level == 2)
    {
       	m_qtreemodelindex = index;
        m_iposttreelevel = 2;	
    }

	//˫�����Ǹ��ڵ�
    if (m_iposttreelevel == 0)
    {
		return;
	}
	//��ǰ��������һ̨�豸
    else if (m_iposttreelevel == 1)
    {
    	int devicerow = index.row();
        int i=0;
        QList<DeviceData>::iterator it;
        for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end();++it)
        {
            if (i == devicerow)
            {
                break;//������������Ϊ�ؼ��֣�������ͬ�豸��
            }
			i++;
        }

		m_gcurrentuserid =(*it).getUsrID();

 //QMessageBox::information(this,tr("treeBeenClicked"),tr("device"));
 
		//�������������豸��û�е�¼
        if (m_gcurrentuserid < 0) 
        {   
            //Login
            int i = -1;
            // i=NET_DVR_Login_V30((*it).getIP().toLatin1().data(), \
            //     (*it).getPort(), \
            //     (*it).getUsrName().toLatin1().data(), \
            //     (*it).getPasswd().toLatin1().data(), \
            //     &(*it).m_deviceinfo);
       
        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
        struLoginInfo.bUseAsynLogin = false;

        struLoginInfo.wPort = (*it).getPort();
        memcpy(struLoginInfo.sDeviceAddress, (*it).getIP().toLatin1().data(), NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, (*it).getUsrName().toLatin1().data(), NAME_LEN);
        memcpy(struLoginInfo.sPassword, (*it).getPasswd().toLatin1().data(), NAME_LEN);

        i = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
        memcpy(&(*it).m_deviceinfo, &struDeviceInfoV40.struDeviceV30, sizeof(NET_DVR_DEVICEINFO_V30));


            if (-1 == i )
            {
                QMessageBox::information(this,tr("NET_DVR_Login_V40"),tr("SDK_LAST_ERROR=%1").arg(NET_DVR_GetLastError()));
				ui.DVRsets_treeView->setExpanded(index, 1);
                return;
            }
            else
            {
                m_gcurrentuserid = i;
                (*it).setUsrID(i);
				
				QStandardItem *item = m_gmodel->itemFromIndex(index);
				item->setIcon(QIcon(":/images/login.bmp"));
						
            }
        }
 //QMessageBox::information(this,tr("treeBeenClicked"),tr("816"));
        m_gcurrentchannelnum =0;
        memcpy(&m_gcurrentdeviceinfo, &(*it).m_deviceinfo,sizeof(NET_DVR_DEVICEINFO_V30));
// QMessageBox::information(this,tr("treeBeenClicked"),tr("819"));

		//preview
		if (m_currentpagenum == 1)
        {              
       	 	//������Ƶ
       	 	if ((m_realplay->m_rpstartstopflag == 1)&&(m_guseridbackup != m_gcurrentuserid))
       	 	{
				m_realplay->on_pushButton_realplay_clicked();
			}
        	m_realplay->on_pushButton_realplay_clicked(); 
		}
 
        //Change the user id of parameters configuring.
		m_guseridbackup = m_gcurrentuserid;
		m_ConfigureParams.SetDVRUserID(m_gcurrentuserid);
		m_ConfigureParams.loadRemoteParams();
		m_gchannelnumbackup =0;
		ui.DVRsets_treeView->setExpanded(index,0);
		return;
    }


	//��ǰ��������һ��ͨ��
    else if (m_iposttreelevel == 2)
    {   

// QMessageBox::information(this,tr("treeBeenClicked"),tr("channel"));
		int deviceindex = index.parent().row();
		int channelindex = index.row();
		
        //need first find device then channel then set the channel num
        QList<DeviceData>::iterator it;
        QList<ChannelData>::iterator it_channel;

		int i=0;
        for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
        {
            if (i ==deviceindex)
            {
                break;
            }
			i++;
        }
		m_gcurrentuserid =(*it).getUsrID();
	    //�����豸û�е�¼�ȵ�¼
        if (m_gcurrentuserid < 0) 
        {   
            int ret=-1;
            // ret=NET_DVR_Login_V30((*it).getIP().toLatin1().data(), (*it).getPort(), 
            //         (*it).getUsrName().toLatin1().data(),
            //         (*it).getPasswd().toLatin1().data(), &(*it).m_deviceinfo) ;

            NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
            NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
            struLoginInfo.bUseAsynLogin = false;

            struLoginInfo.wPort = (*it).getPort();
            memcpy(struLoginInfo.sDeviceAddress, (*it).getIP().toLatin1().data(), NET_DVR_DEV_ADDRESS_MAX_LEN);
            memcpy(struLoginInfo.sUserName, (*it).getUsrName().toLatin1().data(), NAME_LEN);
            memcpy(struLoginInfo.sPassword, (*it).getPasswd().toLatin1().data(), NAME_LEN);

            ret = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
            memcpy(&(*it).m_deviceinfo, &struDeviceInfoV40.struDeviceV30, sizeof(NET_DVR_DEVICEINFO_V30));


			addInterfaceCalledInfoToLog(0, ret, "NET_DVR_Login_V40", 
				(*it).getIP().toLatin1().data(), 
				QString::number(NET_DVR_GetLastError()).toLatin1().data());
            if (-1 == ret )
            {
                QMessageBox::information(this,tr("NET_DVR_Login_V40"),tr(\
                    "SDK_LAST_ERROR=%1").arg(NET_DVR_GetLastError()));
                return;
            }
            else
            {
                m_gcurrentuserid = ret;
                (*it).setUsrID(ret);
				QStandardItem *item = m_gmodel->itemFromIndex(index.parent());
				item->setIcon(QIcon(":/images/login.bmp"));
            }
        }
		m_ConfigureParams.SetDVRUserID(m_gcurrentuserid);
		m_ConfigureParams.loadRemoteParams();
        //Ŀǰ�豸�Ѿ���½�ɹ�����ʼѰ�ҵ�����ͨ��
        memcpy(&m_gcurrentdeviceinfo, &(*it).m_deviceinfo,sizeof(NET_DVR_DEVICEINFO_V30));
		i=0;
        for (it_channel = (*it).m_qlistchanneldata.begin(); it_channel !=    
        			(*it).m_qlistchanneldata.end();++it_channel)
        {
            if (i == channelindex)
            {
            	//�ҵ���ͨ�� ���ϴε������豸���бȽϣ������᲻��ͬ
				if (m_guseridbackup != m_gcurrentuserid)
				{
		        	if (m_currentpagenum == 1)
		        	{ 
			            //�����ڲ���״̬�ȹر�֮ǰ��Ԥ��
			            if (m_realplay->m_rpstartstopflag == 1)
			            {
			                m_realplay->on_pushButton_realplay_clicked(); 
			            }
						m_realplay->on_pushButton_realplay_clicked(); 
		        	}
					
				}
				else
				{
					//ͬһ̨�豸��ͨ����������������
					if (m_currentpagenum ==1)
	    			{
	    				if (m_gchannelnumbackup != (*it_channel).getChannelNum())
                    	{
                    		if ((m_gchannelnumbackup != 0)&&(m_realplay->m_rpstartstopflag ==1))
                    		{
								m_realplay->on_pushButton_realplay_clicked(); 
							}
							
	    				}

	                   	m_realplay->on_pushButton_realplay_clicked();
						
					}
				}
				 
				m_gchannelnumbackup = (*it_channel).getChannelNum();
				m_gcurrentchannelnum = (*it_channel).getChannelNum();
				m_guseridbackup = m_gcurrentuserid;

                break;  
            }
			i++;
        }

 		return;
	}
}

/*******************************************************************
      Function:   QtClientDemo::showTreeContextMenu
   Description:   ��ʾ�˵����˵���������m_iposttreelevel������
                  ��m_iposttreelevel��ֵ��preessed�¼�����ʱ�������á�
     Parameter:   (IN)   const QPoint &pos  ��������λ�õ�����
        Return:   ��
**********************************************************************/
void QtClientDemo::showTreeContextMenu(const QPoint &pos)
{   
	if (m_gblanklabel == 1)
	{
		//return;
	}
    QPoint posChannel = pos;
    if (m_qtreemenu != NULL)
    {
        delete m_qtreemenu;
        m_qtreemenu = NULL;
    }

    m_qtreemenu= new QMenu(ui.DVRsets_treeView);
    //���������豸
    if (m_iposttreelevel == 0)
    {
    	//the top of tree to add new device node
		if (m_addnewdevice != NULL)
		{
			delete m_addnewdevice;
			m_addnewdevice = NULL;
		}
		m_addnewdevice = new AddNode;
		connect(m_addnewdevice->ui.sure_pushButton,SIGNAL(clicked()),this, SLOT(addDeviceSureClicked()));
		connect(m_addnewdevice->ui.sure_pushButton,SIGNAL(clicked()),this, SLOT(addDeviceCancelClicked()));
		m_addnewdevice->exec();

		//չ��
		//ui.DVRsets_treeView->setExpanded(m_gmodel->index(0,0).child(0,0), 1);
		ui.DVRsets_treeView->setExpanded(m_gmodel->index(0,0), 1);
    }
    if (m_iposttreelevel == 1)
    {   
        QAction *loginAction = m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"login", \
            0, QApplication::UnicodeUTF8));
        QAction *logoutAction = m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"logout", \
            0, QApplication::UnicodeUTF8));
        QAction *exitAction = m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"delete", \
            0, QApplication::UnicodeUTF8));
        QAction *attrAction = m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"property", \
            0, QApplication::UnicodeUTF8));
        
        connect(loginAction, SIGNAL(triggered(bool)), this, SLOT(loginDevice()));
        connect(logoutAction, SIGNAL(triggered(bool)), this, SLOT(logoutDevice()));
        connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(deleteDevice()));
        connect(attrAction, SIGNAL(triggered(bool)), this, SLOT(showDevAttrDial()));
        
        m_qtreemenu->exec(QCursor::pos());
    }
    else if (m_iposttreelevel ==2)
    {
        QAction *JPEGAction = m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"\346\212\223\345\233\276", \
            0, QApplication::UnicodeUTF8));
        QAction *attrAction =m_qtreemenu->addAction(\
            QApplication::translate("translateClass", 
			"\345\261\236\346\200\247", \
            0, QApplication::UnicodeUTF8));
        connect(JPEGAction, SIGNAL(triggered(bool)), this, SLOT(getJPEGpic()));
        connect(attrAction, SIGNAL(triggered(bool)), this, SLOT(showChannAttrDial()));

        m_qtreemenu->exec(QCursor::pos());
    }
}

/*******************************************************************
      Function:   QtClientDemo::getListFromArray
   Description:   �ı�QByteArray��д�� QList<DeviceData>
     Parameter:   (IN)   QByteArray& data  �ַ���
        Return:   �豸�б���Ϣ   
**********************************************************************/
QList<DeviceData> QtClientDemo::getListFromArray(QByteArray& data)
{
    QStringList lines;
    QString dataInString;
    dataInString = (QString)data;
    lines = dataInString.split(QString("\n"));
    
    QList<DeviceData>  deviceList;
    QString deviceBegin("<device>");
    QString deviceEnd("</device>");
    QString channelBegin("<channel>");
    QString channelEnd("</channel>");

    //in all for{} is valid, have a expe write incorrectly position
    DeviceData * newDevice =NULL;
    ChannelData* newChannel =NULL;
    for ( QStringList::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        if (*it == deviceBegin)
        {   
            QString str;
            newDevice = new DeviceData;
            str = *(it+1);
            newDevice->setDeviceName(str);
            str = *(it+2);
            newDevice->setIP(str);
            str = *(it+3);
            newDevice->setPort(str.toInt());
            str = *(it+4);
            newDevice->setUsrName(str);
            str = *(it+5);
            newDevice->setPasswd(str);
        }
        else if (*it == deviceEnd)
        {   
            deviceList.append(*newDevice);
            delete newDevice;
            newDevice =NULL;
        }
        else if (*it == channelBegin)
        {   
            QString str;
            newChannel = new ChannelData;
            str = *(it+1);
            newChannel->setChannelName(str);
            str = *(it+2);
            newChannel->setChannelNum(str.toInt());
            str = *(it+3);
            newChannel->setProtocolType((PROTOCOL)str.toInt());
            str = *(it+4);
            newChannel->setStreamType((STREAMTYPE)str.toInt());
    
        }
        else if (*it == channelEnd)
        {   
            newDevice->m_qlistchanneldata.append(*newChannel);
            delete newChannel;
            newChannel =NULL;
        }
    }
    m_qlistdevicedata= deviceList;
    return m_qlistdevicedata;
}

/*******************************************************************
      Function:   QtClientDemo::getStringFromList
   Description:   ���豸�б��л�ȡ�豸�ַ���
     Parameter:   (IN)   QList<DeviceData> & data  �豸�б�
        Return:   �豸��Ϣ   
**********************************************************************/
QString QtClientDemo::getStringFromList(QList<DeviceData> & data)
{
    QString dataInString;
    QStringList lines;

    QString deviceBegin("<device>");
    QString deviceEnd("</device>");
    QString channelBegin("<channel>");
    QString channelEnd("</channel>");

    DeviceData device;
    ChannelData chann;
    QString port;
    QString channum;
    for ( QList<DeviceData>::iterator it = data.begin(); it != data.end(); 
	++it)
    {
        lines << deviceBegin;
        device =(*it);
        lines << device.getDeviceName();
        lines << device.getIP();
        lines << port.number(device.getPort());
        lines << device.getUsrName();
        lines << device.getPasswd();

        for ( QList<ChannelData>::iterator it_Chann = 
		device.m_qlistchanneldata.begin(); \
            it_Chann !=  device.m_qlistchanneldata.end(); ++it_Chann)
        {
            lines << channelBegin;
            chann = (*it_Chann);
            lines << chann.getChannelName();
            lines << channum.number(chann.getChannelNum());
            lines << chann.getProtocolTypeQstring();
            lines << chann.getStreamTypeQstring();
            lines << channelEnd;
        }
        lines << deviceEnd;
    }
    for (QStringList::iterator it_string = lines.begin();\
        it_string != lines.end(); ++it_string)
    {
        dataInString.append(*it_string);
        dataInString.append("\n");
    }
    return dataInString;
}

/*******************************************************************
Function:   QtClientDemo::setDeviceMultiCast
Description:   ���豸�б��л�ȡ�豸�ַ���
Parameter:   (IN)   QList<DeviceData> & data  �豸�б�
Return:   �豸��Ϣ   
**********************************************************************/
bool QtClientDemo::setDeviceMultiCast(int iUserID, QString sMultiCast)
{
	if (iUserID < 0)
	{
		return false;
	}

	DeviceData device;

	for ( QList<DeviceData>::iterator it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); 
		++it)
	{
		if ((*it).getUsrID() == iUserID)
		{
			(*it).setMultiCast(sMultiCast);
			return true;
		}
	}
	return false;
}

//Get SDK verison and Set to the label.
void QtClientDemo::SetSDKVersionToLabel()
{
    DWORD dwVersion = NET_DVR_GetSDKBuildVersion();
    QString strHCNetSDK;
    strHCNetSDK.sprintf("HCNetSDK V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
        (0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));
    ui.m_labelNetSDKVersion->setText(strHCNetSDK);

    dwVersion = PlayM4_GetSdkVersion();
    QString strPlaySDKVersion;
    strPlaySDKVersion.sprintf("PlayCtrl V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
                        (0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));
    ui.m_labelPlayerSDKVersion->setText(strPlaySDKVersion);
}

/*******************************************************************
      Function:   QtClientDemo::showDeviceTree
   Description:   ��ʾ�豸��
     Parameter:   (IN)   const QString &nodedata �豸����Ϣ  
        Return:   ��   
**********************************************************************/
void QtClientDemo::showDeviceTree(const QString &nodedata)
{
	if (m_gmodel != NULL)
	{
		delete m_gmodel;
		m_gmodel = NULL;
		ui.DVRsets_treeView->clearSelection();
		QMessageBox::information(this,tr("system message"),tr("add or delete device success"));
	}	

	m_gmodel = new TreeModel(nodedata);
	ui.DVRsets_treeView->header()->hide();
	ui.DVRsets_treeView->setModel(m_gmodel);

	//ui.DVRsets_treeView->setUpdatesEnabled (TRUE);
	//ui.DVRsets_treeView->update();
	//ui.DVRsets_treeView->repaint();	
	
	//setUpdatesEnabled (TRUE);
	//update();
	//repaint();

	ui.DVRsets_treeView->expand(m_gmodel->index(0,0));
	ui.DVRsets_treeView->setExpanded(m_gmodel->index(0,0), 1);

	//�����豸״̬��ͨ��״̬ �����豸���ڵ�Ȼ���ݹ�
	QModelIndex tmpindex = m_gmodel->index(0,0);
	if (tmpindex.isValid()==1)
	{
		ui.DVRsets_treeView->setExpanded(tmpindex, 1);
	}
	
	QModelIndex devicetreeindex = tmpindex;
	QModelIndex deviceindex = tmpindex.child(0,0);

	
	QList<DeviceData>::iterator it;
    QList<ChannelData>::iterator it_channel;
	int i=0;
	it = m_qlistdevicedata.begin();
	while((deviceindex.isValid()==1)&&(it != m_qlistdevicedata.end()))
	{	
		if (it->getUsrID()!=-1)
		{
			
			QStandardItem *item = m_gmodel->itemFromIndex(deviceindex);
			item->setIcon(QIcon(":/images/login.bmp"));
			ui.DVRsets_treeView->expand(deviceindex);
			ui.DVRsets_treeView->setExpanded(deviceindex, 1);
		}
		QModelIndex channelindex = deviceindex.child(0,0);
		it_channel = (*it).m_qlistchanneldata.begin();
		int j=0;
		while((channelindex.isValid()==1)&&(it_channel != (*it).m_qlistchanneldata.end()))
		{
			if (it_channel->getRealhandle()!=-1)
			{
				//�������߱���ͼƬ��չ��ͨ��
				QStandardItem *item = m_gmodel->itemFromIndex(channelindex);
				item->setIcon(QIcon(":/images/play.bmp"));
				ui.DVRsets_treeView->expand(channelindex);
				ui.DVRsets_treeView->setExpanded(channelindex, 1);
			}
			j++;
			++it_channel;
			channelindex = deviceindex.child(j,0);
			
		}
		i++;
		++it;
		deviceindex = tmpindex.child(i,0);
	}
}

/*******************************************************************
      Function:   QtClientDemo::addInterfaceCalledInfoToLog
   Description:   ����־table�ؼ��м�������
     Parameter:   (IN)   int isbool  
                  (IN)   int returnvalue  
                  (IN)   char* interfacename  
                  (IN)   char* deviceip  
                  (IN)   char* errorinfo  
        Return:   ��   
**********************************************************************/
void QtClientDemo::addInterfaceCalledInfoToLog(int isbool, int returnvalue, char* interfacename, char* deviceip, char* errorinfo)
{
	if (m_logtable != NULL)
	{
		if (((isbool==1)&&(returnvalue ==0))||((isbool==0)&&(returnvalue ==-1)))
		{
			//ʧ��
			m_logtable->addLogAlarmInfo(0, QString(interfacename), 
							QString(deviceip), QString(errorinfo));
		}
		else
		{
			//�ɹ�
			m_logtable->addLogAlarmInfo(1, QString(interfacename), 
							QString(deviceip), NULL);
		}
	}
	return;
}

/*******************************************************************
      Function:   QtClientDemo::loginDevice
   Description:   ��½�豸
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::loginDevice()
{

    int deviceindex = m_qtreemodelindex.row();
	int i = 0;

	QList<DeviceData>::iterator it;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i == deviceindex)
        {
            break;
        }
		i++;
    }

    if ((*it).getUsrID()>= 0)
    {
        m_gcurrentuserid =(*it).m_iuserid;
        QMessageBox::information(this,tr("login"),tr("already login!"));
		return;
    }
    else
    {
        // (*it).m_iuserid = NET_DVR_Login_V30((*it).getIP().toLatin1().data(), (*it).getPort(), 
        //             (*it).getUsrName().toLatin1().data(), \
        //             (*it).getPasswd().toLatin1().data(), &(*it).m_deviceinfo);

        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
        struLoginInfo.bUseAsynLogin = false;

        struLoginInfo.wPort = (*it).getPort();
        memcpy(struLoginInfo.sDeviceAddress, (*it).getIP().toLatin1().data(), NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, (*it).getUsrName().toLatin1().data(), NAME_LEN);
        memcpy(struLoginInfo.sPassword, (*it).getPasswd().toLatin1().data(), NAME_LEN);

        (*it).m_iuserid = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

        memcpy(&(*it).m_deviceinfo, &struDeviceInfoV40.struDeviceV30, sizeof(NET_DVR_DEVICEINFO_V30));


		addInterfaceCalledInfoToLog(0,int((*it).m_iuserid),"NET_DVR_Login_V40",
			(*it).getIP().toLatin1().data(), QString::number(NET_DVR_GetLastError()).toLatin1().data());
		
        if ((*it).m_iuserid < 0)
        {
            QMessageBox::information(this, tr("NET_DVR_Login_V40"),
                tr("��½�豸ʧ�ܣ������� = %1").arg(NET_DVR_GetLastError()));
			return;
	    }
		
        m_gcurrentuserid =(*it).m_iuserid;
        m_gcurrentdeviceinfo =(*it).m_deviceinfo;
		
		//�������߱���ͼƬ��չ��ͨ��
		QStandardItem *item = m_gmodel->itemFromIndex(m_qtreemodelindex);
		item->setIcon(QIcon(":/images/login.bmp"));
		ui.DVRsets_treeView->setExpanded(m_qtreemodelindex, 1);
		m_gcurrentuserid =(*it).getUsrID();
		return;
    }
}

/*******************************************************************
      Function:   QtClientDemo::logoutDevice
   Description:   �ǳ��豸
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::logoutDevice()
{
	int deviceindex = m_qtreemodelindex.row();
	int i=0;
	QList<DeviceData>::iterator it;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i== deviceindex)
        {
            break;
        }
		i++;
    }
    if ((*it).getUsrID() < 0)
    {
        QMessageBox::information(this,tr("have no login yet"),tr("not login"));
    }
    else
    {
		if ((*it).getRealPlayLabel()==1)
		{

			QMessageBox::information(this,tr("logout error"),tr("preview not stopped"));
			return;
		}
  		int ret = NET_DVR_Logout_V30((*it).m_iuserid);
		addInterfaceCalledInfoToLog(1, ret, "NET_DVR_Logout_V30", 
			(*it).getIP().toLatin1().data(), QString::number(NET_DVR_GetLastError()).toLatin1().data());
        (*it).setUsrID(-1);
		m_gcurrentuserid = -1;
		
		//�������߱���ͼƬ������ͨ��
		QStandardItem *item = m_gmodel->itemFromIndex(m_qtreemodelindex);
		item->setIcon(QIcon(":/images/logout.bmp"));
		ui.DVRsets_treeView->setExpanded(m_qtreemodelindex,0);
        QMessageBox::information(this,tr("NET_DVR_Logout_V30"),tr("login success"));
		return;
    }
}

/*******************************************************************
      Function:   QtClientDemo::deleteDevice
   Description:   �ӽڵ�����ɾ���豸
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::deleteDevice()
{

	int devicerow = m_qtreemodelindex.row();

    QList<DeviceData>::iterator it;
    int i=0;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i == devicerow)
        {
            break;
        }
		i++;
    }
    if ((*it).getRealPlayLabel() == 1)
    {
        QMessageBox::information(this,tr("DeleteError!"),\
            tr("There are channel RealPlay"));
        return;
    }

    m_qlistdevicedata.removeAt(devicerow);

    QString treedatastring;
    treedatastring =getStringFromList(m_qlistdevicedata);
    showDeviceTree(treedatastring);
	if (m_gcurrentuserid >= 0)
	{
		for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
	    {
	        if (m_gcurrentuserid == it->getUsrID())
	        {
	            break;
	        }
	    }
		if (it == m_qlistdevicedata.end())
		{
			m_gcurrentuserid =-1;
		}
	}

}

/*******************************************************************
      Function:   QtClientDemo::showDevAttrDial
   Description:   ��ʾ�豸������Ϣ
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::showDevAttrDial()
{
	int isdeletenode=0;//��֤��ǰ�ڵ㲻�Ǹոձ�ɾ���Ľڵ�
    QList<DeviceData>::iterator it;
	int i = 0;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {	
        if (i == m_qtreemodelindex.row())
        { 
        	isdeletenode =1 ;
            break;
        }
		i++;
    }
	if (isdeletenode ==0)
	{
		QMessageBox::information(this,tr("error"),tr("this device is not in the device list"));
		return ;
	}
	if (m_deviceattr !=	NULL)
	{
		delete m_deviceattr;
		m_deviceattr =NULL;
	}
	
	m_deviceattr=new DeviceAttr;
    m_deviceattr->show();
	
    connect(m_deviceattr->ui.sure_pushButton,SIGNAL(clicked()),
        this,SLOT(modfDevAttrSureClicked()));
	connect(m_deviceattr->ui.cancel_pushButton,SIGNAL(clicked()),
        this,SLOT(modfDevAttrCancelClicked()));
	
    QString port;
    port.setNum((*it).m_qiport);

    m_deviceattr->ui.nodename_lineEdit->setText(m_qtreemodelindex.data().toString().toLatin1().data());

    m_deviceattr->ui.ip_lineEdit->setText((*it).m_qip);

    m_deviceattr->ui.port_lineEdit->setText(port);

    m_deviceattr->ui.usrname_lineEdit->setText((*it).m_qusername);

    m_deviceattr->ui.passwd_lineEdit->setText((*it).m_qpassword);

    QString num;
    //m_deviceattr->ui.McastIP_lineEdit->setText((*it).m_deviceinfo);
                      
	m_deviceattr->ui.channelNum_lineEdit->setText(num.setNum(int(\
    (*it).m_deviceinfo.byChanNum),10));

    
	m_deviceattr->ui.devType_lineEdit->setText(num.setNum(int(\
    (*it).m_deviceinfo.byDVRType),10));

    m_deviceattr->ui.SID_lineEdit->setText((const char *)(*it).m_deviceinfo.sSerialNumber);

}

/*******************************************************************
      Function:   QtClientDemo::getJPEGpic
   Description:   scrash picture interface
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::getJPEGpic()
{
	if (m_currentpagenum ==1)
    {
   		 m_realplay->on_pushButton_scrashPic_clicked();
	}
}

/*******************************************************************
      Function:   QtClientDemo::showChannAttrDial
   Description:   show edit channel attribute dialogue
     Parameter:   (IN)   �޲���  
        Return:   �ޡ�   
**********************************************************************/
void QtClientDemo::showChannAttrDial()
{
	if (m_channelattr != NULL)
	{
		delete m_channelattr;
		m_channelattr = NULL;
	}
    m_channelattr=new ChannelAttr;

    QList<DeviceData>::iterator it;
	int i=0;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i == m_qtreemodelindex.parent().row())
        { 
            break;
        }
		i++;
    }
    m_channelattr->ui.devName_lineEdit->setText((*it).getDeviceName());
    m_channelattr->ui.devAddr_lineEdit->setText((*it).getIP()); 

    QList<ChannelData>::iterator channel_it;
	int j = 0;
    for ( channel_it = (*it).m_qlistchanneldata.begin(); 
			channel_it != (*it).m_qlistchanneldata.end(); ++channel_it)
    {
        if (j == m_qtreemodelindex.row())
        { 
            break;
        }
		j++;
    }
    
    m_channelattr->ui.channName_lineEdit->setText((*channel_it).getChannelName());
    QString channelnumber;
    channelnumber.setNum((*channel_it).getChannelNum());
    m_channelattr->ui.channNum_lineEdit->setText(channelnumber);
    
	m_channelattr->ui.transProtocol_comboBox->setCurrentIndex(\
    int((*channel_it).m_eprotocoltype));
    
	m_channelattr->ui.streamType_comboBox->setCurrentIndex(\
    int((*channel_it).m_estreamtype));  
      

    m_channelattr->show();
    connect(m_channelattr->ui.sure_pushButton,SIGNAL(clicked()),\
        this,SLOT(modfChanAttrSureClicked()));
    connect(m_channelattr->ui.cancel_pushButton,SIGNAL(clicked()),\
        this,SLOT(modfChanAttrCancelClicked()));
}

/*******************************************************************
      Function:   QtClientDemo::addDeviceSureClicked
   Description:   add Device Surebutton been Clicked
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::addDeviceSureClicked()
{	
    DeviceData * newDNode = new DeviceData;
    QString treedatastring;
	if (m_addnewdevice->ui.nodename_lineEdit->text().isEmpty())
	{
		newDNode->m_qdevicename = m_addnewdevice->ui.ip_lineEdit->text();
	}
	else
	{
 		newDNode->m_qdevicename = m_addnewdevice->ui.nodename_lineEdit->text();
	}
    newDNode->m_qip = m_addnewdevice->ui.ip_lineEdit->text();
    newDNode->m_qiport = m_addnewdevice->ui.port_lineEdit->text().toInt();
    newDNode->m_qusername = m_addnewdevice->ui.usrname_lineEdit->text();
    newDNode->m_qpassword = m_addnewdevice->ui.passwd_lineEdit->text();
    
    //��Ҫ���Ե�½�豸,��½�ɹ����ܼ��뵽�����У�Ȼ����Ҫ�ж�ͨ������
    // newDNode->m_iuserid = NET_DVR_Login_V30(newDNode->getIP().toLatin1().data(), 
    // 						newDNode->getPort(), 
    //             			newDNode->getUsrName().toLatin1().data(),
    //             			newDNode->getPasswd().toLatin1().data(), 
	// 						&newDNode->m_deviceinfo);
        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
        struLoginInfo.bUseAsynLogin = false;

        struLoginInfo.wPort = newDNode->getPort();
        memcpy(struLoginInfo.sDeviceAddress, newDNode->getIP().toLatin1().data(), NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, newDNode->getUsrName().toLatin1().data(), NAME_LEN);
        memcpy(struLoginInfo.sPassword, newDNode->getPasswd().toLatin1().data(), NAME_LEN);

        newDNode->m_iuserid = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

        memcpy(&newDNode->m_deviceinfo, &struDeviceInfoV40.struDeviceV30, sizeof(NET_DVR_DEVICEINFO_V30));  



    //��¼ʧ��ֱ�ӷ��أ����޸ĵ�ǰm_qlistdevicedata
    if (newDNode->m_iuserid < 0)
    {   
		QMessageBox::information(this, tr("login fail"),
		   tr("error code=%1").arg(NET_DVR_GetLastError()));
		delete m_addnewdevice;
		m_addnewdevice = NULL;
	    m_addnewdevice = new AddNode;
	    m_addnewdevice->show();

		m_addnewdevice->ui.nodename_lineEdit->setText(newDNode->m_qdevicename);
		m_addnewdevice->ui.ip_lineEdit->setText(newDNode->m_qip);
		m_addnewdevice->ui.port_lineEdit->setText(QString::number(newDNode->m_qiport));
		m_addnewdevice->ui.usrname_lineEdit->setText(newDNode->m_qusername);
		m_addnewdevice->ui.passwd_lineEdit->setText(newDNode->m_qpassword);
		
	    connect(m_addnewdevice->ui.sure_pushButton,SIGNAL(clicked()),this,
	        SLOT(addDeviceSureClicked()));
	    connect(m_addnewdevice->ui.sure_pushButton,SIGNAL(clicked()),this,
	        SLOT(addDeviceCancelClicked()));

		
  		delete newDNode;
		newDNode =NULL;
       	return ;
    }
	else
	{
		//QMessageBox::information(this,tr("�����豸"),tr("�����豸�ɹ�"));
	    //����ͨ����Ϣ������ͨ������
	    NET_DVR_IPPARACFG ipcfg;
	    DWORD Bytesreturned;
	    //��½�ɹ���ȡ��ͨ��������Ϣ�����ļ��Ա�������ʾ
	    if (!NET_DVR_GetDVRConfig(newDNode->m_iuserid, NET_DVR_GET_IPPARACFG,0, 
				&ipcfg, sizeof(NET_DVR_IPPARACFG),&Bytesreturned)) 
	    {
	        //8000 devices begin
	        NET_DVR_DEVICECFG devicecfg;
	        DWORD Bytesreturned;
	        if (!NET_DVR_GetDVRConfig(newDNode->m_iuserid, 
			NET_DVR_GET_DEVICECFG,0, &devicecfg, sizeof(NET_DVR_DEVICECFG),&Bytesreturned)) 
	        {
	            QMessageBox::information(this, tr("NET_DVR_GetDVRConfig"),
	                tr("SDK_LAST_ERROR=%1").arg(NET_DVR_GetLastError()));
	            
	            delete newDNode;
	            newDNode =NULL;
	            m_addnewdevice->close();
	            delete m_addnewdevice;
	            m_addnewdevice = NULL;
	            return;
	        }

	        for (int i=devicecfg.byStartChan;i<=devicecfg.byChanNum ;i++)
	        {
	            ChannelData *newChannel = new ChannelData;
	            QString name="Cameral";
	            QString num = QString::number(i, 10) ;
	            name.append(num);
	            //����ͨ����ʼ��������,��ʼ��ΪTCP+������
	            newChannel->setChannelName(name);
	            newChannel->setChannelNum(i);
	            newChannel->setProtocolType(TCP);
	            newChannel->setStreamType(MAINSTREAM);
	            //���ӽ��豸�ڵ�
	            newDNode->m_qlistchanneldata.append(*newChannel);
	            delete newChannel;
	            newChannel =NULL;
	            
	        }
			NET_DVR_Logout_V30(newDNode->m_iuserid);
			newDNode->m_iuserid = -1;
	        m_qlistdevicedata.append(*newDNode);
	        delete newDNode;        
	        newDNode =NULL;
	        treedatastring =getStringFromList(m_qlistdevicedata);
	        showDeviceTree(treedatastring);
	        m_addnewdevice->close();
	        delete m_addnewdevice;
	        m_addnewdevice = NULL;
	        return;
	        //8000 devices end
	    }

	    for (int i=0;i< MAX_ANALOG_CHANNUM;i++)
	    {
	        if (1== ipcfg.byAnalogChanEnable[i])
	        {
	            ChannelData *newChannel = new ChannelData;
	            QString name="Cameral";
	            QString num = QString::number(i+1, 10) ;
	            name.append(num);
	            //����ͨ����ʼ��������,��ʼ��ΪTCP+������
	            newChannel->setChannelName(name);
	            newChannel->setChannelNum(i+1);
	            newChannel->setProtocolType(TCP);
	            newChannel->setStreamType(MAINSTREAM);

	            //���ӽ��豸�ڵ�
	            newDNode->m_qlistchanneldata.append(*newChannel);
	            delete newChannel;
	            newChannel =NULL;
	        }
	    }

	    for (int i=0;i< MAX_IP_CHANNEL;i++)
	    {
//QMessageBox::information(this,tr("ipcfg"), tr("ipcfg.struIPChanInfo[%1].byIPID=%2").arg(i).arg(ipcfg.struIPChanInfo[i].byIPID));
		
	        if (0 != ipcfg.struIPChanInfo[i].byIPID)
	        {
	            ChannelData *newChannel = new ChannelData;
	            QString name="IPCameral";
	            QString num = QString::number(ipcfg.struIPChanInfo[i].byIPID, 10) ;
	            name.append(num);
	            //����ͨ����ʼ��������,��ʼ��ΪTCP+������
	            newChannel->setChannelName(name);
	            newChannel->setChannelNum(32+ipcfg.struIPChanInfo[i].byIPID);
	            newChannel->setProtocolType(TCP);
	            newChannel->setStreamType(MAINSTREAM);
	            //���ӽ��豸�ڵ�
	            newDNode->m_qlistchanneldata.append(*newChannel);
	            delete newChannel;
	            newChannel =NULL;
	        }
	    }
		
	    NET_DVR_Logout_V30(newDNode->m_iuserid);
		newDNode->m_iuserid = -1;
	    m_qlistdevicedata.append(*newDNode);
	    delete newDNode;
	    treedatastring =getStringFromList(m_qlistdevicedata);
	    showDeviceTree(treedatastring);
	    m_addnewdevice->close();
	    delete m_addnewdevice;
	    m_addnewdevice = NULL;
	    return;
	}
    
}

/*******************************************************************
      Function:   QtClientDemo::addDeviceCancelClicked
   Description:   cancel device add dialogue
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::addDeviceCancelClicked()
{
    m_addnewdevice->close();
    delete m_addnewdevice;
    m_addnewdevice = NULL; 
    return;
}

/*******************************************************************
      Function:   QtClientDemo::modfDevAttrSureClicked
   Description:   sure modify device attr 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::modfDevAttrSureClicked()
{
    QList<DeviceData>::iterator it;
    int i=0;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i == m_qtreemodelindex.row())
        { 
            break;
        }
		i++;
    }

	if (m_deviceattr->ui.nodename_lineEdit->text().isEmpty())
	{
		(*it).m_qdevicename =m_deviceattr->ui.ip_lineEdit->text();
	}
	else
	{
 		(*it).m_qdevicename = m_deviceattr->ui.nodename_lineEdit->text();
	}
	
	
    (*it).m_qip = m_deviceattr->ui.ip_lineEdit->text();
    (*it).m_qiport = m_deviceattr->ui.port_lineEdit->text().toInt();
    (*it).m_qusername = m_deviceattr->ui.usrname_lineEdit->text();
    (*it).m_qpassword = m_deviceattr->ui.passwd_lineEdit->text();

	QStandardItem *item = m_gmodel->itemFromIndex(m_qtreemodelindex);
	item->setText((*it).m_qdevicename);
	
    delete m_deviceattr;
    m_deviceattr = NULL; 
}

/*******************************************************************
      Function:   QtClientDemo::modfDevAttrCancelClicked
   Description:   cancel device attr modify
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::modfDevAttrCancelClicked()
{
    m_deviceattr->close();
    delete m_deviceattr;
    m_deviceattr = NULL;
}

/*******************************************************************
      Function:   QtClientDemo::modfChanAttrSureClicked
   Description:   sure channel attr
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::modfChanAttrSureClicked()
{
    QList<DeviceData>::iterator it;
	int i=0;
    for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end(); ++it)
    {
        if (i == m_qtreemodelindex.parent().row())
        { 
            break;
        }
		i++;
    }

    QList<ChannelData>::iterator channel_it;
   
	int j=0;
	for ( channel_it = (*it).m_qlistchanneldata.begin(); 
        channel_it != (*it).m_qlistchanneldata.end(); ++channel_it)
    {
        if (j == m_qtreemodelindex.row())
        {
            break;
        }
		j++;
    } 
	int k=0;
    k = (*channel_it).getChannelNum();
    
    ChannelData channel;
    channel.setChannelName(m_channelattr->ui.channName_lineEdit->text());
    channel.setChannelNum(k);
        
	channel.setProtocolType(
    (PROTOCOL)m_channelattr->ui.transProtocol_comboBox->currentIndex());
    
	channel.setStreamType(
    (STREAMTYPE)m_channelattr->ui.streamType_comboBox->currentIndex());

	if (m_currentpagenum == 1)
    {
	    //�����ڲ��ţ��ȹغ���
	    if (m_realplay->m_rpstartstopflag ==1)
	    {   
	        m_realplay->on_pushButton_realplay_clicked();   
	        m_gcurrentchannellinkmode =channel.getLinkMode();
	        m_realplay->on_pushButton_realplay_clicked();
	    }
	}
    i = (*it).modifyChannelDataChild(&channel);
    if (i<0)
    {
        QMessageBox::information(this,tr("modify channel attr error"),
            tr("modify channel attr error"));
    }
    
	QStandardItem *item = m_gmodel->itemFromIndex(m_qtreemodelindex);
	item->setText(m_channelattr->ui.channName_lineEdit->text());

	
    delete m_channelattr;
    m_channelattr = NULL;
}

/*******************************************************************
      Function:   QtClientDemo::modfChanAttrCancelClicked
   Description:   cancel channel attr dialogue window
     Parameter:   (IN)   �޲���  
        Return:   �ޡ�   
**********************************************************************/
void QtClientDemo::modfChanAttrCancelClicked()
{
    m_channelattr->close();
    delete m_channelattr;
    m_channelattr = NULL;
}

/*******************************************************************
      Function:   QtClientDemo::on_Configure_pushButton_clicked
   Description:   configure button clicked responding
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_Configure_pushButton_clicked()
{
	if (m_currentpagenum == 1)
    {   
    	if (m_realplay->m_rpstartstopflag == 1)
		{
			m_realplay->stopRealPlay();
		}
    	
        m_realplay->hide();
		delete m_realplay;
		m_realplay =NULL;
    }
    else if (m_currentpagenum == 2)
    {   
        m_playback->hide();
		delete m_playback;
		m_playback =NULL;
    }   
	if (m_iparaconfhasclicked ==1)
	{
		m_currentpagenum = 0;
		m_iparaconfhasclicked =1;
		m_ConfigureParams.SetDVRUserID(m_gcurrentuserid);
		m_ConfigureParams.show();
		return ;
	}
	
	m_currentpagenum = 0;
	m_ConfigureParams.SetDVRUserID(m_gcurrentuserid);
	m_ConfigureParams.loadRemoteParams(); 
	//��δ�������ش���
	ui.gridLayout->addWidget(&m_ConfigureParams);
	
	
	m_iparaconfhasclicked =1;
}

/*******************************************************************
      Function:   QtClientDemo::on_Preview_pushButton_clicked
   Description:   show preview widget
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_Preview_pushButton_clicked()
{
    if (m_currentpagenum == 0)
    {
        //�ȹر���������ģ������ʾ
        //m_paraconf->hide();
        m_ConfigureParams.hide();
    }
    else if (m_currentpagenum == 2)
    {   
        m_playback->hide();
		delete m_playback;
		m_playback =NULL;
    }   
    else if (m_currentpagenum ==1)
    { 
      	m_realplay->show();
    	m_irealplayhasclicked =1;
    	m_currentpagenum = 1;
    	return;
    }
 	//drawarea initial and new realplay
    m_realplay =new RealPlay(&m_gmodel, &m_qtreemodelindex, &m_qlistdevicedata, &m_gcurrentuserid, &m_gcurrentdeviceinfo,\
        &m_gcurrentchannelnum, &m_gcurrentchannellinkmode, m_logtable);

	ui.gridLayout->addWidget(m_realplay);
	m_currentpagenum = 1;
}

/************************************************************************
 *        Function            :  on_PlayBack_pushButton_clicked
 *        Description         :  show playback window
 *        Input               :  none
 *        Output              :  none
 *        Return              :  none
*************************************************************************/
void QtClientDemo::on_PlayBack_pushButton_clicked()
{
    //�ȹر���������ģ������ʾ
    if (m_currentpagenum == 0)
    {	 
    	m_ConfigureParams.hide();
        //m_paraconf->hide();
        
    }
    else if (m_currentpagenum == 1)
    {   
    	if (m_realplay->m_rpstartstopflag == 1)
		{
			m_realplay->stopRealPlay();
		}
        m_realplay->hide();
		delete m_realplay;
		m_realplay =NULL;
    }   
    else if (m_currentpagenum == 2 )
    {   
        m_playback->show();
        m_currentpagenum = 2;
        return;
    }
	//QMessageBox::information(this,tr("on_PlayBack_pushButton_clicked"),tr("line=%1").arg(1661));
    m_playback =new PlayBack(&m_qlistdevicedata, &m_gcurrentuserid, &m_gcurrentdeviceinfo,\
                &m_gcurrentchannelnum, m_logtable);
	//QMessageBox::information(this,tr("on_PlayBack_pushButton_clicked"),tr("line=%1").arg(1663));
   
    ui.gridLayout->addWidget(m_playback);
    m_playback->DrawAreaInit();
	//QMessageBox::information(this,tr("on_PlayBack_pushButton_clicked"),tr("line=%1").arg(1667));
   
    m_ipalybackhasclicked =1;
    m_currentpagenum = 2;
 
    return;

}

/*******************************************************************
      Function:   QtClientDemo::on_Manage_pushButton_clicked
   Description:   manage modle show menu
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_Manage_pushButton_clicked()
{
    if (m_qmenumanage != NULL)
    {
        delete m_qmenumanage;
        m_qmenumanage = NULL;
    }
    m_qmenumanage =new QMenu(ui.Manage_pushButton);

    QAction *timingAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
			"check time", \
            0, QApplication::UnicodeUTF8));
    QAction *updateAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
			"upgrade", \
            0, QApplication::UnicodeUTF8));
    QAction *formatAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
			"format", \
            0, QApplication::UnicodeUTF8));
    QAction *rebootAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
			"restart", \
            0, QApplication::UnicodeUTF8));
    QAction *shutdownAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
			"shut down", \
            0, QApplication::UnicodeUTF8));
    QAction *logSearchAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
            "query log", \
            0, QApplication::UnicodeUTF8));
    QAction *deviceStateAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", 
            "device state", \
            0, QApplication::UnicodeUTF8));
    QAction *defaultConfigAction = m_qmenumanage->addAction(\
            QApplication::translate("translateClass", "restore default", \
            0, QApplication::UnicodeUTF8));
    connect(timingAction, SIGNAL(triggered(bool)), this, 
	SLOT(timingDevice()));
    connect(updateAction, SIGNAL(triggered(bool)), this, 
	SLOT(updateDevice()));
    connect(formatAction, SIGNAL(triggered(bool)), this, SLOT(formatDisk()));
    connect(rebootAction, SIGNAL(triggered(bool)), this, 
	SLOT(rebootDevice()));
    connect(shutdownAction, SIGNAL(triggered(bool)), this, 
	SLOT(shutdownDevice()));
    connect(logSearchAction, SIGNAL(triggered(bool)), this, 
	SLOT(searchlogOnDevice()));
    connect(deviceStateAction, SIGNAL(triggered(bool)), this, 
	SLOT(deviceState()));
    connect(defaultConfigAction, SIGNAL(triggered(bool)), this, 
    SLOT(setDeviceDefaultConfig()));
    m_qmenumanage->exec(QCursor::pos());

    return;
}    

/*******************************************************************
      Function:   QtClientDemo::timingDevice
   Description:   show timingDevice window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::timingDevice()
{
    if (NULL!=m_timing)
    {
        delete m_timing;
    }
    m_timing = new Timing(m_gcurrentchannelnum,&m_qlistdevicedata);
    m_timing->exec();
}

/*******************************************************************
      Function:   QtClientDemo::updateDevice
   Description:   show updateDevice window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::updateDevice()
{
    if (NULL!=m_update)
    {
        delete m_update;
    }
    m_update = new RemoteUpdate(&m_gcurrentuserid);
    m_update->exec();
}

/*******************************************************************
      Function:   QtClientDemo::formatDisk
   Description:   show formatDisk window 
     Parameter:   (IN)   �޲���  
        Return:   �ޡ�   
**********************************************************************/
void QtClientDemo::formatDisk()
{
    if (NULL!=m_format)
    {
        delete m_format;
    }
    m_format = new FormatDisk(&m_gcurrentuserid);
    m_format->exec();
}

/*******************************************************************
      Function:   QtClientDemo::rebootDevice
   Description:   show rebootDevice window 
     Parameter:   (IN)   �޲���  
        Return:   �ޡ�   
**********************************************************************/
void QtClientDemo::rebootDevice()
{
    if (NULL!=m_reboot)
    {
        delete m_reboot;
    }
    m_reboot = new RebootDevice(&m_gcurrentuserid);
    m_reboot->exec();
}

/*******************************************************************
      Function:   QtClientDemo::shutdownDevice
   Description:   show shutdownDevice window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::shutdownDevice()
{
    if (NULL!=m_shutdown)
    {
        delete m_shutdown;
    }
    m_shutdown = new ShutdownDevice(&m_gcurrentuserid);
    m_shutdown->exec();
}

/*******************************************************************
      Function:   QtClientDemo::searchlogOnDevice
   Description:   show searchlogOnDevice window
     Parameter:   (IN)   �޲���  
        Return:   �ޡ�   
**********************************************************************/
void QtClientDemo::searchlogOnDevice()
{
    if (NULL!=m_searchlog)
    {
        delete m_searchlog;
    }
    m_searchlog = new LogSearch(&m_qlistdevicedata, &m_gcurrentuserid);
    m_searchlog->exec();
}

/*******************************************************************
      Function:   QtClientDemo::deviceState
   Description:   show deviceState window 
     Parameter:   (IN)   �޲���  
        Return:   HPR_OK--�ɹ���HPR_ERROR--ʧ�ܡ�   
**********************************************************************/
void QtClientDemo::deviceState()
{
    if (NULL!=m_state)
    {
        delete m_state;
    }
    m_state = new DeviceState(&m_qlistdevicedata, &m_gcurrentuserid);
    m_state->exec();

}

/*******************************************************************
      Function:   QtClientDemo::setDeviceDefaultConfig
   Description:   show setDeviceDefaultConfig window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::setDeviceDefaultConfig()
{
    if (NULL!=m_reset)
    {
        delete m_reset;
    }
    m_reset = new ResetDevice(&m_gcurrentuserid);
    m_reset->exec();
}

/*******************************************************************
      Function:   QtClientDemo::on_Other_pushButton_clicked
   Description:   show other module menu
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_Other_pushButton_clicked()
{   
    if (m_qmenuother != NULL)
    {
        delete m_qmenuother;
        m_qmenuother = NULL;
    }
    m_qmenuother =new QMenu(ui.Other_pushButton);

    QAction *deploymentAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Guard/Unguard", \
            0, QApplication::UnicodeUTF8));
    QAction *manualSaveAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Manual record", \
            0, QApplication::UnicodeUTF8));
    QAction *serialTransferAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Serial port forward", \
            0, QApplication::UnicodeUTF8));
    QAction *devicePanelAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Device panel", \
            0, QApplication::UnicodeUTF8));
    QAction *importConfigAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Config file", \
            0, QApplication::UnicodeUTF8));
/*
	QAction *audioIntercomAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "\350\257\255\351\237\263\345\257\271\350\256\262", \
            0, QApplication::UnicodeUTF8));
    QAction *audioBroadcastAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "\350\257\255\351\237\263\345\271\277\346\222\255", \
            0, QApplication::UnicodeUTF8));
*/	
    QAction *audioTransferAction = m_qmenuother->addAction(\
            QApplication::translate("translateClass", 
            "Audio forward", \
            0, QApplication::UnicodeUTF8));

    connect(deploymentAction, SIGNAL(triggered(bool)), this, 
		SLOT(deploymentOrNotDevice()));
    connect(manualSaveAction, SIGNAL(triggered(bool)), this, 
		SLOT(manualSaveFile()));
    connect(serialTransferAction, SIGNAL(triggered(bool)), this, 
		SLOT(serialTransfer()));
    connect(devicePanelAction, SIGNAL(triggered(bool)), this, 
		SLOT(devicePanelSimulation()));
    connect(importConfigAction, SIGNAL(triggered(bool)), this, 
		SLOT(importExortConfig()));
/*
  	connect(audioIntercomAction, SIGNAL(triggered(bool)), this, 
		SLOT(auidoIntercom()));
    connect(audioBroadcastAction, SIGNAL(triggered(bool)), this, 
		SLOT(audioBroadcast()));
 */ 
  	connect(audioTransferAction, SIGNAL(triggered(bool)), this, 
		SLOT(audioTransfer()));

    m_qmenuother->exec(QCursor::pos());
    return;
}

/*******************************************************************
      Function:   QtClientDemo::deploymentOrNotDevice
   Description:   show deploymentOrNotDevice window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::deploymentOrNotDevice()
{	
    if (NULL!=m_deploy)
    {
        delete m_deploy;
    }
    m_deploy = new Deploy(&m_qlistdevicedata);

    m_deploy->exec();
	
}

/*******************************************************************
      Function:   QtClientDemo::manualSaveFile
   Description:   show manualSaveFile window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::manualSaveFile()
{	
	if (m_gcurrentchannelnum ==0)
	{
		if (!NET_DVR_StartDVRRecord(m_gcurrentuserid,0xffff,0))
		{
			QMessageBox::information(this,tr("Manual record fail"),\
			    tr("SDK_LASTERROR=[%1]").arg(NET_DVR_GetLastError()));
		}
		else
		{
			QMessageBox::information(this,tr("NET_DVR_StartDVRRecord SUCC"),\
			    tr("Manual record success"));
		}
		
		return;
	}
    if (! NET_DVR_StartDVRRecord(m_gcurrentuserid,m_gcurrentchannelnum,0))
    {
		if (m_logtable != NULL)
		{
			QList<DeviceData>::iterator it;
	        for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end();++it)
	        {
	            if ((*it).getUsrID() == m_gcurrentuserid)
	            {
	                break;//������������Ϊ�ؼ��֣�������ͬ�豸��
	            }
	        }
			m_logtable->addLogAlarmInfo(0, QString("NET_DVR_StartDVRRecord"), 
				(*it).getIP().toLatin1().data(), QString::number(NET_DVR_GetLastError()));
		}
        QMessageBox::information(this,tr("NET_DVR_StartDVRRecord Error"),\
            tr("SDK_LASTERROR=[%1]").arg(NET_DVR_GetLastError()));
	}  
	else
	{
		if (m_logtable != NULL)
		{
			QList<DeviceData>::iterator it;
	        for ( it = m_qlistdevicedata.begin(); it != m_qlistdevicedata.end();++it)
	        {
	            if ((*it).getUsrID() == m_gcurrentuserid)
	            {
	                break;//������������Ϊ�ؼ��֣�������ͬ�豸��
	            }
	        }
			m_logtable->addLogAlarmInfo(1, QString("NET_DVR_StartDVRRecord"), 
				(*it).getIP().toLatin1().data(), NULL);
		}
		QMessageBox::information(this,tr("NET_DVR_StartDVRRecord SUCC"),\
            tr("Manual record success"));
	}
	return;
}

/*******************************************************************
      Function:   QtClientDemo::serialTransfer
   Description:   show serialTransfer window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::serialTransfer()
{
	
    if (NULL!=m_serial)
    {
        delete m_serial;
    }
    
    m_serial = new SerialTransfer(&m_qlistdevicedata, &m_gcurrentuserid);
    m_serial->exec();
	
}

/*******************************************************************
      Function:   QtClientDemo::devicePanelSimulation
   Description:   show devicePanelSimulation window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::devicePanelSimulation()
{
    if (NULL!=m_devicepan)
    {
        delete m_devicepan;
    }
    m_devicepan =new DevicePan(&m_gcurrentuserid);
    m_devicepan->exec();
}

/*******************************************************************
      Function:   QtClientDemo::importExortConfig
   Description:   show importExortConfig window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::importExortConfig()
{
    if (NULL!=m_import)
    {
        delete m_import;
    }
    m_import = new ImportConfig(&m_qlistdevicedata);
    m_import->exec();
}

/*******************************************************************
      Function:   QtClientDemo::auidoIntercom
   Description:   show auidoIntercom window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::auidoIntercom()
{
    if (NULL!=m_audiointercom)
    {
        delete m_audiointercom;
    }
    m_audiointercom = new AudioIntercom;
    m_audiointercom->show();
}

/*******************************************************************
      Function:   QtClientDemo::audioBroadcast
   Description:   show audioBroadcast window 
     Parameter:   (IN)   �޲���  
        Return:   ��  
**********************************************************************/
void QtClientDemo::audioBroadcast()
{
    if (NULL!=m_audiobroadcast)
    {
        delete m_audiobroadcast;
    }
    m_audiobroadcast = new AudioBroadcast;
    m_audiobroadcast->show();
}

/*******************************************************************
      Function:   QtClientDemo::audioTransfer
   Description:   show audioTransfer window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::audioTransfer()  
{
    if (NULL!=m_audiotransfer)
    {
        delete m_audiotransfer;
    }
    m_audiotransfer = new AudioTransfer(&m_qlistdevicedata);
    m_audiotransfer->exec();
}

/*******************************************************************
      Function:   QtClientDemo::on_Exit_pushButton_clicked
   Description:   show exit window 
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_Exit_pushButton_clicked()
{
    if (m_exitdemo !=NULL)
    {
        delete m_exitdemo;
        m_exitdemo = NULL;      
    }
    m_exitdemo= new ExitDemo(); 
    m_exitdemo->show();
    connect(m_exitdemo->ui.pushButton_sure, SIGNAL(clicked()), \
        this, SLOT(exitDemoSure()));
    connect(m_exitdemo->ui.pushButton_cancel, SIGNAL(clicked()), \
        this, SLOT(exitDemoCancel()));
}

/*******************************************************************
      Function:   QtClientDemo::exitDemoSure
   Description:   sure responsing function of exit window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::exitDemoSure()
{
    m_exitdemo->close();
	
    if (m_exitdemo != NULL)
    {
        delete m_exitdemo;
        m_exitdemo = NULL;
    }
	
    //clode main window
    close();
	
}

/*******************************************************************
      Function:   QtClientDemo::exitDemoCancel
   Description:   cancel responsing function of exit window
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::exitDemoCancel()
{
    m_exitdemo->close();
    if (m_exitdemo != NULL)
    {
        delete m_exitdemo;
        m_exitdemo = NULL;
    }
    return;
}

/*******************************************************************
      Function:   QtClientDemo::on_radioButton_locallog_pressed
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_radioButton_locallog_pressed ()
{
	if (m_glogoralarm == 0)
	{
		return;
	}
	/*if (m_alarmtable != NULL)
	{
		ui.vboxLayout->removeWidget(m_alarmtable);
		m_alarmtable->hide();
	}*/

	/*if (m_loghasallocated == 0)
	{
		m_logtable = new LogTable;
		m_loghasallocated = 1;
	}*/
		
	//ui.vboxLayout->addWidget(m_logtable);
    m_logtable->show();
	m_alarmtable->hide();
	m_glogoralarm = 0;
}

/*******************************************************************
      Function:   QtClientDemo::on_radioButton_alarminfo_pressed
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_radioButton_alarminfo_pressed ()
{
	if (m_glogoralarm == 1)
	{
		return;
	}
	/*if (m_logtable != NULL)
	{
		ui.vboxLayout->removeWidget(m_logtable);
		m_logtable->hide();
	}*/

	/*if (m_alarmhasallocated == 0)
	{
		m_alarmtable = new AlarmTable;
		m_alarmhasallocated = 1;
	}*/
	m_logtable->hide();
	m_alarmtable->show();
	//ui.vboxLayout->addWidget(m_alarmtable);
	m_glogoralarm = 1;
	
}

/*******************************************************************
      Function:   QtClientDemo::on_pushButton_logaramclear_clicked
   Description:   д��־��Ϣ��table��
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_pushButton_logaramclear_clicked()
{
	if ((m_glogoralarm == 0)&&(m_logtable !=NULL))
	{
	    for (int i=0; i<m_logtable->ui.logtableWidget->rowCount(); i++)
	    {
	        for (int j=0;j<m_logtable->ui.logtableWidget->columnCount();j++ )
	        {
	            delete m_logtable->ui.logtableWidget->takeItem(i, j);
	        }
	        m_logtable->ui.logtableWidget->removeRow(i);
	    }
		m_logtable->ui.logtableWidget->setRowCount(0);
	}

	else if ((m_glogoralarm == 1)&&(m_alarmtable !=NULL))
	{
	    for (int i=0; i<m_alarmtable->ui.tableWidget->rowCount(); i++)
	    {
	        for (int j=0;j<m_alarmtable->ui.tableWidget->columnCount();j++ )
	        {
	            delete m_alarmtable->ui.tableWidget->takeItem(i, j);
	        }
	        m_alarmtable->ui.tableWidget->removeRow(i);
	    }
		m_alarmtable->ui.tableWidget->setRowCount(0);
	}
}

/*******************************************************************
      Function:   QtClientDemo::on_pushButton_logaramsave_clicked
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_pushButton_logaramsave_clicked()
{


}

/*******************************************************************
      Function:   QtClientDemo::on_pushButton_logaramlistconf_clicked
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_pushButton_logaramlistconf_clicked()
{


}

/*******************************************************************
      Function:   QtClientDemo::on_pushButton_logaramtest_clicked
   Description:   
     Parameter:   (IN)   �޲���  
        Return:   ��   
**********************************************************************/
void QtClientDemo::on_pushButton_logaramtest_clicked()
{


}


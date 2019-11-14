/***************************************************************************************
 *      Copyright 2009-2011 Hikvision Digital Technology Co., Ltd.
 *      FileName        :       devicedata.cpp
 *      Description     :       �豸�������ز���
 *      Modification    :
 *      Version         :       V1.0.0
 *      Time            :       2009-10,11
 *      Author          :       wanggp@hikvision.com
 ****************************************************************************************/
#include "devicedata.h"

/************************************************************************
 *        Function            :  DeviceData
 *        Description         :  ���캯��
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
DeviceData::DeviceData()
{
    m_irealplaying =0;
    m_iuserid = -1;
    memset(&m_deviceinfo,0,sizeof(NET_DVR_DEVICEINFO_V30));
    m_qdevicename = "";
    m_qip = "";
    m_qiport = 0;
    m_qusername = "";
    m_qpassword = "";
	m_ideployed = -1;
	m_multiCast = "234.5.6.7";
}

/************************************************************************
 *        Function            :  ~DeviceData
 *        Description         :  ��������
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
DeviceData::~DeviceData()
{

}

/************************************************************************
 *        Function            :  setRealPlayLabel
 *        Description         :  ����������Ԥ������
 *        Input               :  value
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setRealPlayLabel(int value)
{
    m_irealplaying =value;
}

/************************************************************************
 *        Function            :  getRealPlayLabel
 *        Description         :  ��ȡ�Ƿ���ͨ������Ԥ������λֵ
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  m_irealplaying
*************************************************************************/
int DeviceData::getRealPlayLabel()
{
    return m_irealplaying;   
}

/************************************************************************
 *        Function            :  setUsrID
 *        Description         :  �����û�ID
 *        Input               :  id
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setUsrID(int id)
{
    m_iuserid = id;
}

/************************************************************************
 *        Function            :  getUsrID
 *        Description         :  ��ȡ�û�ID
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
int DeviceData::getUsrID()
{
    return m_iuserid;
}

/************************************************************************
 *        Function            :  setDeviceName
 *        Description         :  �����豸����
 *        Input               :  devicename
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setDeviceName(QString devicename)
{
    m_qdevicename = devicename;
}

/************************************************************************
 *        Function            :  getDeviceName
 *        Description         :  ��ȡ�豸����
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  m_qdevicename
*************************************************************************/
QString DeviceData::getDeviceName()
{
    return m_qdevicename;
}

/************************************************************************
 *        Function            :  setIP
 *        Description         :  ����IP
 *        Input               :  ip
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setIP(QString  ip)
{
    m_qip = ip;
}

/************************************************************************
 *        Function            :  getIP
 *        Description         :  ��ȡIP
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  m_qip
*************************************************************************/
QString DeviceData::getIP()
{
    return m_qip;
}

/************************************************************************
 *        Function            :  setPort
 *        Description         :  ���ö˿�ֵ
 *        Input               :  port
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setPort(int port)
{
    m_qiport = port;
}

/************************************************************************
 *        Function            :  getPort
 *        Description         :  ��ȡ�˿�ֵ
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  m_qiport
*************************************************************************/
int DeviceData::getPort()
{
    return m_qiport;
}

/************************************************************************
 *        Function            :  setUsrName
 *        Description         :  �����û���
 *        Input               :  usrname
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setUsrName(QString usrname)
{
    m_qusername = usrname;
}

QString DeviceData::getUsrName()
{
    return m_qusername;
}

/************************************************************************
 *        Function            :  setPasswd
 *        Description         :  ��������
 *        Input               :  passwd
 *        Output              :  ��
 *        Return              :  ��
*************************************************************************/
void DeviceData::setPasswd(QString passwd)
{
    m_qpassword = passwd;
}

/************************************************************************
 *        Function            :  getPasswd
 *        Description         :  ��ȡ����
 *        Input               :  ��
 *        Output              :  ��
 *        Return              :  �ַ���������
*************************************************************************/
QString DeviceData::getPasswd()
{
    return m_qpassword;
}

/************************************************************************
 *        Function            :  modifyChannelDataChild
 *        Description         :  �޸�ͨ������
 *        Input               :  channel
 *        Output              :  ��
 *        Return              :  0�ɹ�-1ʧ��
*************************************************************************/
int DeviceData::modifyChannelDataChild(ChannelData *channel)
{
    for ( QList<ChannelData >::Iterator it = m_qlistchanneldata.begin(); it != 
    m_qlistchanneldata.end(); ++it )
    {
        if ((*it).m_ichannelnum == channel->m_ichannelnum)
        {
            (*it).m_qchannelname = channel->m_qchannelname;
            (*it).m_eprotocoltype = channel->m_eprotocoltype;
            (*it).m_estreamtype = channel->m_estreamtype;
            return 0;
        }
    }
    return -1;
}

NET_DVR_DEVICEINFO_V30 DeviceData::getDeviceInfo()
{

    return m_deviceinfo;
}

void DeviceData::setDeployState(int deployed)
{
	m_ideployed = deployed;
}

int  DeviceData::getDeployState()
{
	return m_ideployed;
}

/************************************************************************
*        Function            :  setMultiCast
*        Description         :  ���öಥ��ַ
*        Input               :  passwd
*        Output              :  ��
*        Return              :  ��
*************************************************************************/
void DeviceData::setMultiCast(QString multiCast)
{
	m_multiCast = multiCast;
}

/************************************************************************
*        Function            :  getMultiCast
*        Description         :  ��ȡ�ಥ��ַ
*        Input               :  ��
*        Output              :  ��
*        Return              :  �ಥ��ַ
*************************************************************************/
QString DeviceData::getMultiCast()
{
	return m_multiCast;
}




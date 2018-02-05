#ifndef __MESSAGE_DEFINE_H__
#define __MESSAGE_DEFINE_H__

#include "typedefine.h"

#define ID_CLEARINGCENTER 0
#define ID_TOLLCENTER 1
#define ID_STATION 2
#define ID_LANE 3

#define STATUS_REQUEST 0
#define STATUS_ANSWER 1

#define TRANTYPE_AUTHORIZE (0x1001)
#define TRANTYPE_IOTOSERVERVARIETY (0x1021)
#define TRANTYPE_IOTOSERVERFIX (0x1022)
#define TRANTYPE_CLIENTTOIO (0x1031)
#define TRANTYPE_IOTOCLIENT (0x1032)
#define TRANTYPE_SERVERTOCLIENTVARIETY (0x1041)
#define TRANTYPE_SERVERTOCLIENTFIX (0x1042)
#define TRANTYPE_ (0x0)

#define RECORDTYPE_DEVICE (0x22)
#define RECORDTYPE_IOTOCLIENT (0x23)//!!!�ݶ�

#define DEVICETYPE_LEDBOARDA (101)
#define DEVICETYPE_LEDBOARDF (102)
#define DEVICETYPE_LEDBOARDXS (103)
#define DEVICETYPE_VEHICLEDETECTOR (110)
#define DEVICETYPE_METEO (120)
#define DEVICETYPE_PM25 (121)
#define DEVICETYPE_CAMERA (130)

#define MESSAGEID_SERVER (1)
#define MESSAGEID_CLIENT (2)
#define MESSAGEID_DEVICE (3)

#define DEVICESTATE_NORMAL (0x0000)
#define DEVICESTATE_DISCONNECTION (0x0001)

#define INSTRUCTIONSTYPE_MODBUSTEXT (1)
#define INSTRUCTIONSTYPE_MODBUSLIMIT (2)

#define ERRORCODE_NOERROR (0)
#define ERRORCODE_COMMANDRESPONSEERROR (1)
#define ERRORCODE_LENGTHERROR (101)
#define ERRORCODE_DEVICEERROR (102)
#define ERRORCODE_COMMANDERROR (103)

#pragma pack (push)
#pragma pack (1)

typedef struct _MessageHead_ {
	UT utVersion;
	UT utStatus;
	US usTranType;
	C utSendID[6];
	C utReceiveID[6];
	UL ulMessageID;
	UT utEncry;
	UT utRepeatFlag;
	UL ulDataLen;
	C  cReserve[2];
	_MessageHead_::_MessageHead_()
	{
		utVersion = 0x64;
		utStatus = 0;
		usTranType = 0;
		memset(utSendID, 0x00, sizeof(utSendID));
		memset(utReceiveID, 0x00, sizeof(utReceiveID));
		ulMessageID = 0;
		utEncry = 0;
		utRepeatFlag = 0;
		ulDataLen = 0;
		memset(cReserve, 0x00, sizeof(cReserve));
	}
	void _MessageHead_::Reset()
	{
		utVersion = 0x64;
		utStatus = 0;
		usTranType = 0;
		memset(utSendID, 0x00, sizeof(utSendID));
		memset(utReceiveID, 0x00, sizeof(utReceiveID));
		ulMessageID = 0;
		utEncry = 0;
		utRepeatFlag = 0;
		ulDataLen = 0;
		memset(cReserve, 0x00, sizeof(cReserve));
	}
	void _MessageHead_::SetStatus(UT Status){utStatus = Status;}
	void _MessageHead_::SetTranType(US TranType){usTranType = TranType;}
	void _MessageHead_::SetSendID(UT IDDefine, US NetworkID, UT ClearingCenterID, UT TollCenterID, US StationID, UT PartID, UT LaneID)
	{
		US m_usTemp;
		switch(IDDefine)
		{
		case ID_CLEARINGCENTER:
			m_usTemp = htons(NetworkID);
			memcpy(utSendID, &m_usTemp, sizeof(m_usTemp));
			utSendID[5] = ClearingCenterID;
			break;
		case ID_TOLLCENTER:
			m_usTemp = htons(NetworkID);
			memcpy(utSendID, &m_usTemp, sizeof(m_usTemp));
			utSendID[5] = TollCenterID;
			break;
		case ID_STATION:
			m_usTemp = htons(NetworkID);
			memcpy(utSendID, &m_usTemp, sizeof(m_usTemp));
			m_usTemp = htons(StationID);
			memcpy(utSendID + 4, &m_usTemp, sizeof(m_usTemp));
			break;
		case ID_LANE:
			m_usTemp = htons(NetworkID);
			memcpy(utSendID, &m_usTemp, sizeof(m_usTemp));
			m_usTemp = htons(StationID);
			memcpy(utSendID + 2, &m_usTemp, sizeof(m_usTemp));
			utSendID[4] = PartID;
			utSendID[5] = LaneID;
			break;
		}
	}
	void _MessageHead_::SetReceiveID(UT IDDefine, US NetworkID, UT ClearingCenterID, UT TollCenterID, US StationID, UT PartID, UT LaneID)
	{
		US m_usTemp;
		switch(IDDefine)
		{
		case ID_CLEARINGCENTER:
			m_usTemp = htons(NetworkID);
			memcpy(utReceiveID, &m_usTemp, sizeof(m_usTemp));
			utReceiveID[5] = ClearingCenterID;
			break;
		case ID_TOLLCENTER:
			m_usTemp = htons(NetworkID);
			memcpy(utReceiveID, &m_usTemp, sizeof(m_usTemp));
			utReceiveID[5] = TollCenterID;
			break;
		case ID_STATION:
			m_usTemp = htons(NetworkID);
			memcpy(utReceiveID, &m_usTemp, sizeof(m_usTemp));
			m_usTemp = htons(StationID);
			memcpy(utReceiveID + 4, &m_usTemp, sizeof(m_usTemp));
			break;
		case ID_LANE:
			m_usTemp = htons(NetworkID);
			memcpy(utReceiveID, &m_usTemp, sizeof(m_usTemp));
			m_usTemp = htons(StationID);
			memcpy(utReceiveID + 2, &m_usTemp, sizeof(m_usTemp));
			utReceiveID[4] = PartID;
			utReceiveID[5] = LaneID;
			break;
		}
	}
	UL _MessageHead_::SetMessageID(UL MessageID){ulMessageID = (MessageID > 10000000 ? 1 : MessageID); return ulMessageID;}
	void _MessageHead_::SetEncry(UT Encry){utEncry = Encry;}
	void _MessageHead_::SetRepeatFlag(UT RepeatFlag){utRepeatFlag = RepeatFlag;}
	void _MessageHead_::SetDataLen(UL DataLen){ulDataLen = DataLen;}
}MessageHead;

typedef struct tagResponseMsg//������Ϣ�ķ�����Ϣ
{
	UT ErrCode;
	L Check;
public:
	tagResponseMsg()
	{
		memset(this, 0, sizeof(tagResponseMsg));	
	}
}ResponseMsg;

typedef struct tagIODeviceBaseMsg
{
	US DeviceType;
	C  DeviceID[6];
	C  Reserve2[6];
	UL DeviceMessageID;
	UL Time;
	C  DeviceData[64];
	US Level;
	US DeviceState;
	C  Reserve3[2];
public:
	tagIODeviceBaseMsg()
	{
		memset(this, 0, sizeof(tagIODeviceBaseMsg));	
	}
}IODeviceBaseMsg;

typedef struct tagIODeviceVarietyMsg//Trantype=0x1021
{
	UT RecordType;
	C  SendID[6];
	C  Reserve1[4];
	IODeviceBaseMsg BaseMsg;
	UL DataLength;
public:
	tagIODeviceVarietyMsg()
	{
		memset(this, 0, sizeof(tagIODeviceVarietyMsg));	
	}
}IODeviceVarietyMsg;

typedef struct tagIODeviceFixMsgHead//Trantype=0x1022
{
	UT RecordType;
	C  SendID[6];
	UL Count;
	C  Reserve1[4];
public:
	tagIODeviceFixMsgHead()
	{
		memset(this, 0, sizeof(tagIODeviceFixMsgHead));	
	}
}IODeviceFixMsgHead;

typedef struct tagClientCommandMsg//Trantype=0x1031
{
	UT RecordType;
	US DeviceType;
	C  DeviceID[6];
	UL InstructionsNo;
	US InstructionsType;
	UL InstructionsLength;
public:
	tagClientCommandMsg()
	{
		memset(this, 0, sizeof(tagClientCommandMsg));	
	}
}ClientCommandMsg;

typedef struct tagIOToClientResponseMsg//Trantype=0x1032
{
	UT RecordType;
	US DeviceType;
	C  DeviceID[6];
	UL InstructionsNo;
	US InstructionsType;
	UL ResponseLength;
public:
	tagIOToClientResponseMsg()
	{
		memset(this, 0, sizeof(tagIOToClientResponseMsg));	
	}
}IOToClientResponseMsg;

typedef struct tagLEDBoardMsg//Trantype=0x1031��1���鱨��ָ��
{
	C Content[150];		        //��������(���������к���ɫ��ת���ַ���ʾ)
	US ContetnLen;				//�������ݳ���
	US UMD;                     //���¶���
	US LMR;                     //���Ҷ���
	US ShowMode;                //���ַ�ʽ
	US FontSize;                //�����С
	US Font;		            //��������
	US FontColor;				//������ɫ
	US Interval;                //���ʱ��
	US Icon;			        //ͼ������
	US IconSize;                //ͼ���С
	C LimitContent[4];          //���ٰ�����
public:
	tagLEDBoardMsg()
	{
		memset(this, 0, sizeof(tagLEDBoardMsg));	
	}
}LEDBoardMsg;

typedef struct tagVehicleDetectorMsg//Trantype=0x1022��1��������
{
	UL Time;                        //����ʱ��
	US VDAreaID;					//�״�����
	US VDDeviceID;					//�״���
	US LaneID;						//������
	US TotalFlow;					//������
	US MultiFactor;					//��������
	US TotalOccupancy;				//��ռ����
	US LongVehicleOccupancy;		//����ռ����
	US AverageSpeed;                //ƽ������
	US UnitTimeFlow;                //��λʱ�䳵����
	US ShortVehicleOccupancy;       //�̳�ռ����
	US UnitTimeLongVehicleFlow;     //��λʱ�䳤������
	US UnitTimeShortVehicleFlow;    //��λʱ��̳�����
	US HeadWay;                     //��ͷʱ��
	US MiddleVehicleOccupancy;      //�г�ռ����
	US LongVehicleAverageSpeed;     //����ƽ���ٶ�
	US MiddleVehicleAverageSpeed;   //�г�ƽ���ٶ�
	US ShortVehicleAverageSpeed;    //�̳�ƽ���ٶ�
	US UnitTimeMiddleVehicleFlow;   //��λʱ���г�����	
public:
	tagVehicleDetectorMsg()
	{
		memset(this, 0, sizeof(tagVehicleDetectorMsg));	
	}
}VehicleDetectorMsg;

typedef struct tagMeteoInstrumentMsg//Trantype=0x1022��2��������
{
	UL Time;
	S AirTempature;        //�¶�
	US AirHumidity;        //ʪ��
	UL AirPressure;        //��ѹ
	US WindSpeed;          //����
	US WindDirection;      //����
	US Precipitation;      //������
	S RoadTempature;       //·���¶�
	S FreezingTempature;   //�����¶�
	US Sault;              //������
	C RoadCondition[20];   //·��״��
	UL Visibility;         //�ܼ���
public:
	tagMeteoInstrumentMsg()
	{
		memset(this, 0, sizeof(tagMeteoInstrumentMsg));
	}
}MeteoMsg;

typedef struct tagPM25Msg//Trantype=0x1022��3��PM2.5
{
	UL Time;	//����ʱ��
	US PM25;	//pm2.5
	US PM10;	//pm10
	US TSP;		//������΢��
public:
	tagPM25Msg()
	{
		memset(this, 0, sizeof(tagPM25Msg));	
	}
}PM25Msg;

//segafan201704�������ٹ�·�����Ŀ������Ƶ��ͼ�Ĺ���
typedef struct tagVideoSnapshot//Trantype=0x1021��1����Ƶ��ͼ
{
	UL Time;			//����ʱ��
	C CameraName[20];	//���������
	US CameraNo;		//��������
	US CameraGroup;		//���������
	US ImageFileType;	//��ͼ��ʽ
	C Reserve[40];		//����
public:
	tagVideoSnapshot()
	{
		memset(this, 0, sizeof(tagVideoSnapshot));	
	}
}VideoSnapshot;

typedef struct tagEventAnalysisMsg
{
	C content[100];   //
public:
	tagEventAnalysisMsg()
	{
		memset(this, 0, sizeof(tagEventAnalysisMsg));	
	}
}EventAnalysisMsg;

typedef struct tagDeviceInfo
{
	C  Name[30];
	BOOL Enable;
	C  IP[20];
	US Port;
	US Type;
	C  ID[6];
	US StationNumber;
	UL Param1;
	UL Param2;
	UL Param3;
	UL Param4;
	UL Param5;
public:
	tagDeviceInfo()
	{
		memset(this, 0, sizeof(tagDeviceInfo));	
	}
}DeviceInfo;

typedef struct tagThreadParam
{
	UL pDlg;
	US nDeviceIndex;
public:
	tagThreadParam()
	{
		memset(this, 0, sizeof(tagThreadParam));	
	}
}ThreadParam;

#pragma pack (pop)

#endif
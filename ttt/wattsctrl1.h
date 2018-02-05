#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CWattsctrl1 包装类

class CWattsctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWattsctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xB68DB243, 0xFD3, 0x11D0, { 0x81, 0x48, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    wLANG_ENGLISH = 0,
    wLANG_FRENCH = 1,
    wLANG_DUTCH = 2,
    wLANG_GERMAN = 3,
    wLANG_ITALIAN = 4,
    wLANG_MAX = 5
}wLanguage;
enum
{
    wdtVIP2 = 0,
    wdtVIP9 = 1,
    wdtSVD = 2,
    wdtVIP3 = 3,
    wdtVIC = 4,
    wdtVIP6 = 5,
    wdtVIP7 = 6,
    wdtCOM3 = 7,
    wdtVIP21 = 8,
    wdtVIP42 = 9,
    wdtVIP22 = 10,
    wdtVIP41 = 11,
    wdtVIP8C = 12,
    wdtVIP23 = 13,
    wdtVICCOM = 14,
    wdtVIP31 = 15,
    wdtVIP32 = 16,
    wdtVIEWCOMUS = 17,
    wdtVIEWCOMEU = 18,
    wdtVIP_P = 19,
    wdtVIP_D = 20,
    wdtVIP_PX = 21,
    wdtVIP_I = 22,
    wdtCOM = 23,
    wdtVIP_D_US = 24,
    wdtVIP_I_US = 25,
    wdtVIP_1X = 26,
    wdtVIP_2X = 27,
    wdtVICCOM_E = 28,
    wdtVIP_DI = 29,
    wdtVIP_DI_US = 30,
    wdtVIP_D2_US = 31,
    wdtTRAFICAM = 32,
    wdtVIP_PD = 33,
    wdtVIP_3D1 = 34,
    wdtVIP_3D2 = 35,
    wdtTRAFICAM_IO = 36,
    wdt4TI = 37,
    wdtVIP_T = 38,
    wdtPCI = 39,
    wdtSIMULATOR = 40,
    wdtCOMSERVER = 41,
    wdtVIEWCOM_E = 42,
    wdt1TI = 43,
    wdtDIB = 44
}wDetectorType;
enum
{
    wqtIMAGE_REQUEST = 1,
    wqtREMOTE_SETUP = 2,
    wqtSEND_OUTPUTS = 3,
    wqtSET_MATRIX = 4,
    wqtPNP_REQUEST = 5,
    wqtFORCE_ALARM = 6,
    wqtWVLT_IMAGE = 7,
    wqtREQ_DET_PARAM = 8,
    wqtSND_DET_PARAM = 9,
    wqtCONNECT_MODEM = 10,
    wqtREMOTE_SETUP_CHANNEL = 11,
    wqtVWCMM_IMAGE = 12,
    wqtREQ_PAR_INFO = 13,
    wqtRELOAD_DATABASE = 14,
    wqtCOMSERVER_SHUTDOWN = 15,
    wqtREQ_MENU_INFO = 16,
    wqtREQ_CONFIG_INFO = 17,
    wqtROUTE_REQUEST = 18,
    wqtSEND_FIRMWARE = 19,
    wqtREQ_COM_PARAM = 20,
    wqtSND_COM_PARAM = 21,
    wqtSET_PROGRAMFLAG = 22,
    wqtSET_STARTPROGRAMMING = 23,
    wqtSEND_VIDEO_BUS = 24,
    wqtSEND_REBOOT = 25,
    wqtREQ_FIRMWARE_VERSION = 26,
    wqtREQ_PARAM_CHECKSUM = 27,
    wqtREQ_ID_LIST = 28,
    wqtSEND_CLOCK = 29,
    wqtSET_SCKOPT = 30,
    wqtSELECT_CONFIG = 31,
    wqtXML = 32,
    wqtLIGHT_CHANGED = 33,
    wqtREQ_COM_PAR_INFO = 34,
    wqtREQ_COM_MENU_INFO = 35,
    wqtREQ_COM_CONFIG_INFO = 36,
    wqtREQ_LOGON = 37,
    wqtREQ_STATE = 38,
    wqtREQ_DET_STATE = 39,
    wqtSEND_FIRMWARE_BIN = 40,
    wqtSND_CHANGE_INHIBITION = 41,
    wqtSND_APPLY_SCENARIO = 42
}wRequestType;
enum
{
    wrtINFO = 0,
    wrtTRAFFIC_ZONE_DATA = 1,
    wrtTRAFFIC_EVENT = 2,
    wrtDET_EVENT = 2,
    wrtIMAGE = 3,
    wrtPNP_INFO = 4,
    wrtWVLT_IMAGE = 5,
    wrtWVLT_IMAGESEQ = 6,
    wrtDET_PARAM = 7,
    wrtVWCMM_IMAGE = 8,
    wrtPAR_INFO = 9,
    wrtMENU_INFO = 10,
    wrtCONFIG_INFO = 11,
    wrtROUTE_REQUEST = 12,
    wrtVERSION = 13,
    wrtPROGRAM_MODE = 14,
    wrtLOGFILE = 15,
    wrtEND_OF_LOGFILE = 16,
    wrtCOM_PARAM = 17,
    wrtPARAM_CHECKSUM = 18,
    wrtDATABASE_LENGTH = 19,
    wrtDATABASE_FORMAT = 20,
    wrtDATABASE_RECORD = 21,
    wrtNUMLINES_CHECK = 22,
    wrtID_LIST = 23,
    wrtJPG_IMAGESEQ = 24,
    wrtLOGON_INFO = 25,
    wrtCOM_EVENT = 26,
    wrtXML_RESPONS = 27,
    wrtXML_INFO = 28,
    wrtCOM_PAR_INFO = 29,
    wrtCOM_MENU_INFO = 30,
    wrtCOM_CONFIG_INFO = 31,
    wrtRES_LOG_INFO = 32,
    wrtRES_INDIVIDUAL_DATA = 33,
    wrtDRAW_EVENT = 34,
    wrtTMS_EVENT = 35,
    wrtVSM_EVENT = 36,
    wrtDET_INFO = 37,
    wrtBIN_PREVIEW = 38,
    wrtDB_EVENT = 39,
    wrtTARGETGROUP_EVENT = 40,
    wrtCONFIRMATION_INFO = 41
}wResponseType;
enum
{
    wetNO_VIDEO = 0,
    wetSPEED_ALARM = 1,
    wetOCCUPANCY_ALARM = 2,
    wetCOMMUNICATION_ERROR = 3,
    wetSTOPPED_VEHICLE = 4,
    wetSPEED_VARIATION = 5,
    wetINVERSE_DIRECTION = 6,
    wetFIRE = 7,
    wetBAD_VIDEO = 8,
    wetDIG_INPUT = 9,
    wetUSER_ALARM = 10,
    wetCONFIG_CHANGED = 11,
    wetZONE_ACTIVE = 12,
    wetOUTPUT_GROUP_ACTIVE = 13,
    wetPHASE_ACTIVE = 14,
    wetINDIV_DATA = 15,
    wetREBOOT_EVENT = 16,
    wetUPGRADED = 17,
    wetRECALL_PRESSED = 18,
    wetSREC_ERROR = 19,
    wetNOREDUNDANTPWR = 20,
    wetPTZ_OUT_OF_HOME = 21,
    wetPEDESTRIAN = 22,
    wetCAMERAMOVED = 23,
    wetFALLENOBJECT = 24,
    wetUNDERSPEED = 25,
    wetOVERSPEED = 26,
    wetLINKERROR = 27,
    wetREDUNDANT_COMM_ERROR = 28,
    wetINHIBITION_CHANGE = 29,
    wetNIGHT_MODE = 30,
    wetEXCESS_LENGTH = 31,
    wetIOEXPANSIONERROR = 32,
    wetTEMPORARYLICENSE = 33,
    wetLICENSEERROR = 34,
    wetOUT_OF_SYNC_ERROR = 35,
    wetSCNENARIO_CHANGED = 36,
    wetPRESENCE = 37,
    wetSNOW = 38,
    wetILL_EVENT = 39
}wEventType;
enum
{
    witDATA_POLL_DONE = 1,
    witMDM_INFO = 2,
    witDATABASE_RELOADED = 3,
    witACK_RECEIVED = 4,
    witDOWNLOAD_STATE = 5,
    witDOWNLOAD_FINISHED = 6,
    witEND_OF_DATA = 7,
    witCONNECT_INFO = 8
}wInfoType;
enum
{
    wltLOGON_OK = 0,
    wltWRONG_PASSWORD = 1,
    wltWRONG_USER = 2,
    wltOTHER_USER_LOGGED_ON = 3,
    wltTIMEOUT = 4
}wLogonType;
enum
{
    wirSTOP = 0,
    wirSINGLE = 1,
    wirSLOW_SCAN = 2,
    wirSTOP_IMMEDIATE = 3
}wImageRequestType;
enum
{
    wrscKBD_UP = 56,
    wrscKBD_DOWN = 50,
    wrscKBD_LEFT = 52,
    wrscKBD_RIGHT = 54,
    wrscKBD_EDIT = 55,
    wrscKBD_MODIFY = 57,
    wrscKBD_OPERATE = 49,
    wrscKBD_CENTER = 53,
    wrscKBD_ENTER = 13,
    wrscKBD_ESC = 27,
    wrscKBD_F1 = 65,
    wrscKBD_F2 = 66,
    wrscKBD_F3 = 67,
    wrscKBD_F4 = 68
}wRemoteSetupCommand;
enum
{
    wttChannel = 0,
    wttNet = 1,
    wttRack = 2,
    wttCamera = 3,
    wttDetector = 4,
    wttZone = 5,
    wttTMSServer = 6,
    wttVSMServer = 7,
    wttTCPConn = 8
}wElementType;
enum
{
    wsoNOEVENT = 1,
    wsoNODATA = 2,
    wsoNOSEQ = 4,
    wsoNOINFO = 8,
    wsoENUMID = -2147483648
}wSockOpt;
enum
{
    wpUNKNOWN = 0,
    wpDISABLED = 0,
    wpBAST = 1,
    wpNEW = 2,
    wpTCP = 3
}wProtocol;


// 操作
public:

// _DWATTS

// Functions
//

	void ClearLastError()
	{
		InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short Connect()
	{
		short result;
		InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	BOOL IsConnected()
	{
		BOOL result;
		InvokeHelper(0x1f6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Disconnect()
	{
		InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short get_zdnVehicles(short classnr)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1f8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, classnr);
		return result;
	}
	short get_zdSpeed(short classnr)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1f9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, classnr);
		return result;
	}
	long get_zdGapTime(short classnr)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1fa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, classnr);
		return result;
	}
	short RemoteSetup(short DetectorId, short Command)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x1fb, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Command);
		return result;
	}
	short ImageRequest(short DetectorId, short Type, short Quality, short Sensitivity, short Resolution)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x1fc, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Type, Quality, Sensitivity, Resolution);
		return result;
	}
	long ImageFile(BSTR * filename)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x1fd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filename);
		return result;
	}
	short RequestPnpInfo(short RackID)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1fe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID);
		return result;
	}
	short SetVideoMatrix(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1ff, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short SetOutputs(short RackID, short Outputs)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x200, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, Outputs);
		return result;
	}
	long get_zdSqGapTime(short classnr)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x201, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, classnr);
		return result;
	}
	long get_zdSqSpeed(short classnr)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x202, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, classnr);
		return result;
	}
	short WaveletImageRequest(short DetectorId, short Type)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x203, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Type);
		return result;
	}
	short RequestParameters(short DetectorId, short ConfigNr, long ParamId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I4 ;
		InvokeHelper(0x204, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, ConfigNr, ParamId);
		return result;
	}
	short SendParameters(short DetectorId, BSTR * Parameters, short ConfigNr, long ParamId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_PBSTR VTS_I2 VTS_I4 ;
		InvokeHelper(0x205, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Parameters, ConfigNr, ParamId);
		return result;
	}
	short ForceUserAlarm(short DetectorId, DATE Timestamp, short EventType, short Zone, long Active, short Level)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_DATE VTS_I2 VTS_I2 VTS_I4 VTS_I2 ;
		InvokeHelper(0x206, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Timestamp, EventType, Zone, Active, Level);
		return result;
	}
	short ModemConnect(short NetID, short bConnect)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x207, DISPATCH_METHOD, VT_I2, (void*)&result, parms, NetID, bConnect);
		return result;
	}
	short get_PnpCardType(short ElementNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x208, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, ElementNr);
		return result;
	}
	CString get_PnpName(short ElementNr)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x209, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ElementNr);
		return result;
	}
	short get_PnpNumChilds(short ElementNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x20a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, ElementNr);
		return result;
	}
	short ViewCommImageRequest(short DetectorId, short Type, short Quality, short Sensitivity, short Resolution)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x20b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Type, Quality, Sensitivity, Resolution);
		return result;
	}
	short RequestParInfo(short DetectorId, short ParamNum)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x20c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, ParamNum);
		return result;
	}
	short ReloadDatabase(short RackID, short ReloadType)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x20d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, ReloadType);
		return result;
	}
	short ComServerShutdown()
	{
		short result;
		InvokeHelper(0x20e, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short RequestMenuInfo(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x20f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short RequestConfigInfo(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x210, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short SendFirmware(BSTR * Record)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x211, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Record);
		return result;
	}
	short SetProgramMode(short RackID, short DetectorId, short Mode)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x212, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, DetectorId, Mode);
		return result;
	}
	short SetStartProgramming(short RackID, short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x213, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, DetectorId);
		return result;
	}
	short RequestDetectorVersion(short RackID, short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x214, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, DetectorId);
		return result;
	}
	short iData(long ByteNr)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x215, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ByteNr);
		return result;
	}
	short EnableEvent(short DetectorId, short EventType, short Active)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x216, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, EventType, Active);
		return result;
	}
	short RequestLogFile(short DetectorId, short EventRowNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x217, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, EventRowNr);
		return result;
	}
	short RequestStatus(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x218, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short SendSelectConfig(short DetectorId, short RackID, short ConfigNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x219, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, RackID, ConfigNr);
		return result;
	}
	short ShowJpegFromString(LPSTR JPegString)
	{
		short result;
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x21a, DISPATCH_METHOD, VT_I2, (void*)&result, parms, JPegString);
		return result;
	}
	short RequestComParameters(short RackID, short ConfigNr, long ParamId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I4 ;
		InvokeHelper(0x21b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, ConfigNr, ParamId);
		return result;
	}
	short SendComParameters(short RackID, BSTR * Parameters)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_PBSTR ;
		InvokeHelper(0x21c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, Parameters);
		return result;
	}
	short RequestParamChecksum(short RackID, short DetectorId, short ConfigNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x21d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, DetectorId, ConfigNr);
		return result;
	}
	short ShowWaveLetFromFile(LPSTR filename)
	{
		short result;
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x21e, DISPATCH_METHOD, VT_I2, (void*)&result, parms, filename);
		return result;
	}
	short SetVideoBus(short DetectorId, short RackID)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x21f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, RackID);
		return result;
	}
	short SendReboot(short RackID, short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x220, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, DetectorId);
		return result;
	}
	short RequestDatabaseLength(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x221, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short RequestDatabaseFormat(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x222, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short RequestDatabaseRecord(short DetectorId, short RecNum)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x223, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, RecNum);
		return result;
	}
	short SendClearDatabase(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x224, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short SendEraseConfig(short DetectorId, short ConfigNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x225, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, ConfigNr);
		return result;
	}
	short SetGraphicsOverlay(short DetectorId, short OnOff)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x226, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, OnOff);
		return result;
	}
	short ForceEventWithID(short DetectorId, short EventID, short Arg)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x227, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, EventID, Arg);
		return result;
	}
	short ForceRecall(short DetectorId, short OnOff)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x228, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, OnOff);
		return result;
	}
	short SendDebugInfo(short DetectorId, long Address, long Value, short Type)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x229, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Address, Value, Type);
		return result;
	}
	short CheckNumLinesSend(short DetectorId, long NumLines)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I4 ;
		InvokeHelper(0x22a, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, NumLines);
		return result;
	}
	short RequestZoneIdList(short ElementType)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x22b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ElementType);
		return result;
	}
	short RequestLogon(short DetectorId, short Type, short UserId, BSTR * Password)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_PBSTR ;
		InvokeHelper(0x22c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, Type, UserId, Password);
		return result;
	}
	short SendRouteRequest(short DetectorId, LPSTR pData, long Length)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_UNKNOWN VTS_I4 ;
		InvokeHelper(0x22d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, pData, Length);
		return result;
	}
	short SendDetectorOutputs(short DetectorId, short OnOff, short OutputNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x22e, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, OnOff, OutputNr);
		return result;
	}
	short SendXML(short DetectorId, BSTR * XML)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_PBSTR ;
		InvokeHelper(0x22f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, XML);
		return result;
	}
	short RequestComParInfo(short RackID, short ParamNum)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x230, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID, ParamNum);
		return result;
	}
	short RequestComMenuInfo(short RackID)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x231, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID);
		return result;
	}
	short RequestComConfigInfo(short RackID)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x232, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID);
		return result;
	}
	short SendSockOpt(long SockOpt)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x233, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SockOpt);
		return result;
	}
	short SaveImageFile(BSTR * filename)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x234, DISPATCH_METHOD, VT_I2, (void*)&result, parms, filename);
		return result;
	}
	short RequestSystemState(short RackID)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x235, DISPATCH_METHOD, VT_I2, (void*)&result, parms, RackID);
		return result;
	}
	short RequestDetectorState(short DetectorId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x236, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId);
		return result;
	}
	short PnpVersion(short ElementNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x237, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ElementNr);
		return result;
	}
	short EnableEventWithLevel(short DetectorId, short EventType, short Zone, short Level, short Active)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x238, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, EventType, Zone, Level, Active);
		return result;
	}
	short SendBinFirmware(LPSTR BinData, long DataLen, long NumSent, long NumToSend)
	{
		short result;
		static BYTE parms[] = VTS_UNKNOWN VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x239, DISPATCH_METHOD, VT_I2, (void*)&result, parms, BinData, DataLen, NumSent, NumToSend);
		return result;
	}
	short SendChangeInhibition(short DetectorId, short InhibNr)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x23a, DISPATCH_METHOD, VT_I2, (void*)&result, parms, DetectorId, InhibNr);
		return result;
	}
	short RequestIdList(short ElementType)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x23b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ElementType);
		return result;
	}
	short get_idlRackId(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlRackParentd(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x23d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlRackName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x23e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlRackIpAddress(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x23f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlTMSServerID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x240, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlTMSServerName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x241, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlTCPConnID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x242, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlTCPConnTMSID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x243, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlTCPConnName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x244, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlChannelID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x245, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlChannelTCPConnID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x246, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlChannelName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x247, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlDetectorID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x248, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlCameraID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x249, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlDetectorParentID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlCameraParentID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlDetectorName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlCameraName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlZoneID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlZoneDetectorID(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x24f, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	CString get_idlZoneName(short RecordNumber)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x250, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlZoneGroupNr(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x251, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short get_idlZoneLogZoneNr(short RecordNumber)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x252, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, RecordNumber);
		return result;
	}
	short ApplyScenario(short ScenarioId, short TargetGroupId, short Active)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x253, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ScenarioId, TargetGroupId, Active);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

CString GetServerName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}
void SetServerName(CString propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}
short GetServerPort()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}
void SetServerPort(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}
CString GetLastError()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}
void SetLastError(CString propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}
long GetLastErrorCode()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetLastErrorCode(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
short GetzdZoneId()
{
	short result;
	GetProperty(0x5, VT_I2, (void*)&result);
	return result;
}
void SetzdZoneId(short propVal)
{
	SetProperty(0x5, VT_I2, propVal);
}
short GetzdOccupancy()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}
void SetzdOccupancy(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}
short GetzdConfidenceLevel()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}
void SetzdConfidenceLevel(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}
short GetzdLength()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}
void SetzdLength(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}
short GetzdHeadway()
{
	short result;
	GetProperty(0x9, VT_I2, (void*)&result);
	return result;
}
void SetzdHeadway(short propVal)
{
	SetProperty(0x9, VT_I2, propVal);
}
long GetzdDensity()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetzdDensity(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
short GetDetectorId()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}
void SetDetectorId(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}
short GeteEventType()
{
	short result;
	GetProperty(0xc, VT_I2, (void*)&result);
	return result;
}
void SeteEventType(short propVal)
{
	SetProperty(0xc, VT_I2, propVal);
}
short GeteZoneId()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}
void SeteZoneId(short propVal)
{
	SetProperty(0xd, VT_I2, propVal);
}
BOOL GeteActive()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}
void SeteActive(BOOL propVal)
{
	SetProperty(0xe, VT_BOOL, propVal);
}
short GeteLevel()
{
	short result;
	GetProperty(0xf, VT_I2, (void*)&result);
	return result;
}
void SeteLevel(short propVal)
{
	SetProperty(0xf, VT_I2, propVal);
}
DATE GetTimestamp()
{
	DATE result;
	GetProperty(0x10, VT_DATE, (void*)&result);
	return result;
}
void SetTimestamp(DATE propVal)
{
	SetProperty(0x10, VT_DATE, propVal);
}
short GetResponseType()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}
void SetResponseType(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}
short GeteDetectorZone()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}
void SeteDetectorZone(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}
short GetiInfoType()
{
	short result;
	GetProperty(0x13, VT_I2, (void*)&result);
	return result;
}
void SetiInfoType(short propVal)
{
	SetProperty(0x13, VT_I2, propVal);
}
short GetiInfo1()
{
	short result;
	GetProperty(0x14, VT_I2, (void*)&result);
	return result;
}
void SetiInfo1(short propVal)
{
	SetProperty(0x14, VT_I2, propVal);
}
short GetiInfo2()
{
	short result;
	GetProperty(0x15, VT_I2, (void*)&result);
	return result;
}
void SetiInfo2(short propVal)
{
	SetProperty(0x15, VT_I2, propVal);
}
short GetiInfo3()
{
	short result;
	GetProperty(0x16, VT_I2, (void*)&result);
	return result;
}
void SetiInfo3(short propVal)
{
	SetProperty(0x16, VT_I2, propVal);
}
short GetiInfo4()
{
	short result;
	GetProperty(0x17, VT_I2, (void*)&result);
	return result;
}
void SetiInfo4(short propVal)
{
	SetProperty(0x17, VT_I2, propVal);
}
long GetzdSqHeadway()
{
	long result;
	GetProperty(0x18, VT_I4, (void*)&result);
	return result;
}
void SetzdSqHeadway(long propVal)
{
	SetProperty(0x18, VT_I4, propVal);
}
CString GetpParameters()
{
	CString result;
	GetProperty(0x19, VT_BSTR, (void*)&result);
	return result;
}
void SetpParameters(CString propVal)
{
	SetProperty(0x19, VT_BSTR, propVal);
}
CString GetiInfoMsg()
{
	CString result;
	GetProperty(0x1a, VT_BSTR, (void*)&result);
	return result;
}
void SetiInfoMsg(CString propVal)
{
	SetProperty(0x1a, VT_BSTR, propVal);
}
short GetwsAlarmFrame()
{
	short result;
	GetProperty(0x1b, VT_I2, (void*)&result);
	return result;
}
void SetwsAlarmFrame(short propVal)
{
	SetProperty(0x1b, VT_I2, propVal);
}
short GetwsFrameInterval()
{
	short result;
	GetProperty(0x1c, VT_I2, (void*)&result);
	return result;
}
void SetwsFrameInterval(short propVal)
{
	SetProperty(0x1c, VT_I2, propVal);
}
short GetLanguage()
{
	short result;
	GetProperty(0x1d, VT_I2, (void*)&result);
	return result;
}
void SetLanguage(short propVal)
{
	SetProperty(0x1d, VT_I2, propVal);
}
CString GetpParInfo()
{
	CString result;
	GetProperty(0x1e, VT_BSTR, (void*)&result);
	return result;
}
void SetpParInfo(CString propVal)
{
	SetProperty(0x1e, VT_BSTR, propVal);
}
short GetBlockMarker()
{
	short result;
	GetProperty(0x1f, VT_I2, (void*)&result);
	return result;
}
void SetBlockMarker(short propVal)
{
	SetProperty(0x1f, VT_I2, propVal);
}
short GetImgXPos()
{
	short result;
	GetProperty(0x20, VT_I2, (void*)&result);
	return result;
}
void SetImgXPos(short propVal)
{
	SetProperty(0x20, VT_I2, propVal);
}
short GetImgYPos()
{
	short result;
	GetProperty(0x21, VT_I2, (void*)&result);
	return result;
}
void SetImgYPos(short propVal)
{
	SetProperty(0x21, VT_I2, propVal);
}
short GetImgXRes()
{
	short result;
	GetProperty(0x22, VT_I2, (void*)&result);
	return result;
}
void SetImgXRes(short propVal)
{
	SetProperty(0x22, VT_I2, propVal);
}
short GetImgYRes()
{
	short result;
	GetProperty(0x23, VT_I2, (void*)&result);
	return result;
}
void SetImgYRes(short propVal)
{
	SetProperty(0x23, VT_I2, propVal);
}
BOOL GetImgIsPAL()
{
	BOOL result;
	GetProperty(0x24, VT_BOOL, (void*)&result);
	return result;
}
void SetImgIsPAL(BOOL propVal)
{
	SetProperty(0x24, VT_BOOL, propVal);
}
CString GetpMenuInfo()
{
	CString result;
	GetProperty(0x25, VT_BSTR, (void*)&result);
	return result;
}
void SetpMenuInfo(CString propVal)
{
	SetProperty(0x25, VT_BSTR, propVal);
}
CString GetpConfigInfo()
{
	CString result;
	GetProperty(0x26, VT_BSTR, (void*)&result);
	return result;
}
void SetpConfigInfo(CString propVal)
{
	SetProperty(0x26, VT_BSTR, propVal);
}
short GetImgResolution()
{
	short result;
	GetProperty(0x27, VT_I2, (void*)&result);
	return result;
}
void SetImgResolution(short propVal)
{
	SetProperty(0x27, VT_I2, propVal);
}
CString GetpDetectorVersion()
{
	CString result;
	GetProperty(0x28, VT_BSTR, (void*)&result);
	return result;
}
void SetpDetectorVersion(CString propVal)
{
	SetProperty(0x28, VT_BSTR, propVal);
}
CString GetpLastUpdate()
{
	CString result;
	GetProperty(0x29, VT_BSTR, (void*)&result);
	return result;
}
void SetpLastUpdate(CString propVal)
{
	SetProperty(0x29, VT_BSTR, propVal);
}
long GetWindowHandle()
{
	long result;
	GetProperty(0x2a, VT_I4, (void*)&result);
	return result;
}
void SetWindowHandle(long propVal)
{
	SetProperty(0x2a, VT_I4, propVal);
}
long GetDCHandle()
{
	long result;
	GetProperty(0x2b, VT_I4, (void*)&result);
	return result;
}
void SetDCHandle(long propVal)
{
	SetProperty(0x2b, VT_I4, propVal);
}
long GetiLength()
{
	long result;
	GetProperty(0x2c, VT_I4, (void*)&result);
	return result;
}
void SetiLength(long propVal)
{
	SetProperty(0x2c, VT_I4, propVal);
}
CString GetLastJpegString()
{
	CString result;
	GetProperty(0x2d, VT_BSTR, (void*)&result);
	return result;
}
void SetLastJpegString(CString propVal)
{
	SetProperty(0x2d, VT_BSTR, propVal);
}
long GetDatabaseLength()
{
	long result;
	GetProperty(0x2e, VT_I4, (void*)&result);
	return result;
}
void SetDatabaseLength(long propVal)
{
	SetProperty(0x2e, VT_I4, propVal);
}
CString GetDatabaseFormat()
{
	CString result;
	GetProperty(0x2f, VT_BSTR, (void*)&result);
	return result;
}
void SetDatabaseFormat(CString propVal)
{
	SetProperty(0x2f, VT_BSTR, propVal);
}
short GetDatabaseRecordLength()
{
	short result;
	GetProperty(0x30, VT_I2, (void*)&result);
	return result;
}
void SetDatabaseRecordLength(short propVal)
{
	SetProperty(0x30, VT_I2, propVal);
}
short GetzdNumClass()
{
	short result;
	GetProperty(0x31, VT_I2, (void*)&result);
	return result;
}
void SetzdNumClass(short propVal)
{
	SetProperty(0x31, VT_I2, propVal);
}
short GetwLogonType()
{
	short result;
	GetProperty(0x32, VT_I2, (void*)&result);
	return result;
}
void SetwLogonType(short propVal)
{
	SetProperty(0x32, VT_I2, propVal);
}
short GetwLogonUserId()
{
	short result;
	GetProperty(0x33, VT_I2, (void*)&result);
	return result;
}
void SetwLogonUserId(short propVal)
{
	SetProperty(0x33, VT_I2, propVal);
}
CString GetXML()
{
	CString result;
	GetProperty(0x34, VT_BSTR, (void*)&result);
	return result;
}
void SetXML(CString propVal)
{
	SetProperty(0x34, VT_BSTR, propVal);
}
short GetindZoneId()
{
	short result;
	GetProperty(0x35, VT_I2, (void*)&result);
	return result;
}
void SetindZoneId(short propVal)
{
	SetProperty(0x35, VT_I2, propVal);
}
short GetindDetectorZone()
{
	short result;
	GetProperty(0x36, VT_I2, (void*)&result);
	return result;
}
void SetindDetectorZone(short propVal)
{
	SetProperty(0x36, VT_I2, propVal);
}
long GetindSequenceNr()
{
	long result;
	GetProperty(0x37, VT_I4, (void*)&result);
	return result;
}
void SetindSequenceNr(long propVal)
{
	SetProperty(0x37, VT_I4, propVal);
}
long GetindGapTime()
{
	long result;
	GetProperty(0x38, VT_I4, (void*)&result);
	return result;
}
void SetindGapTime(long propVal)
{
	SetProperty(0x38, VT_I4, propVal);
}
short GetindLength()
{
	short result;
	GetProperty(0x39, VT_I2, (void*)&result);
	return result;
}
void SetindLength(short propVal)
{
	SetProperty(0x39, VT_I2, propVal);
}
short GetindSpeed()
{
	short result;
	GetProperty(0x3a, VT_I2, (void*)&result);
	return result;
}
void SetindSpeed(short propVal)
{
	SetProperty(0x3a, VT_I2, propVal);
}
short GetindConfidence()
{
	short result;
	GetProperty(0x3b, VT_I2, (void*)&result);
	return result;
}
void SetindConfidence(short propVal)
{
	SetProperty(0x3b, VT_I2, propVal);
}
short GetindClassNr()
{
	short result;
	GetProperty(0x3c, VT_I2, (void*)&result);
	return result;
}
void SetindClassNr(short propVal)
{
	SetProperty(0x3c, VT_I2, propVal);
}
short GetindMilliSeconds()
{
	short result;
	GetProperty(0x3d, VT_I2, (void*)&result);
	return result;
}
void SetindMilliSeconds(short propVal)
{
	SetProperty(0x3d, VT_I2, propVal);
}
short GetidlElementType()
{
	short result;
	GetProperty(0x3e, VT_I2, (void*)&result);
	return result;
}
void SetidlElementType(short propVal)
{
	SetProperty(0x3e, VT_I2, propVal);
}
short GetidlNumRecords()
{
	short result;
	GetProperty(0x3f, VT_I2, (void*)&result);
	return result;
}
void SetidlNumRecords(short propVal)
{
	SetProperty(0x3f, VT_I2, propVal);
}
DATE GetconTimestamp()
{
	DATE result;
	GetProperty(0x40, VT_DATE, (void*)&result);
	return result;
}
void SetconTimestamp(DATE propVal)
{
	SetProperty(0x40, VT_DATE, propVal);
}
short GetconType()
{
	short result;
	GetProperty(0x41, VT_I2, (void*)&result);
	return result;
}
void SetconType(short propVal)
{
	SetProperty(0x41, VT_I2, propVal);
}
short GetconState()
{
	short result;
	GetProperty(0x42, VT_I2, (void*)&result);
	return result;
}
void SetconState(short propVal)
{
	SetProperty(0x42, VT_I2, propVal);
}
CString GetconUserName()
{
	CString result;
	GetProperty(0x43, VT_BSTR, (void*)&result);
	return result;
}
void SetconUserName(CString propVal)
{
	SetProperty(0x43, VT_BSTR, propVal);
}
CString GetconMessage()
{
	CString result;
	GetProperty(0x44, VT_BSTR, (void*)&result);
	return result;
}
void SetconMessage(CString propVal)
{
	SetProperty(0x44, VT_BSTR, propVal);
}


};

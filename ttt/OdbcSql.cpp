// OdbcSql.cpp     The implement file of OdbcSql.h
//2001年9月12日

#include "stdafx.h"
#include "OdbcSql.h"

BOOL COdbcSql::Close()
{
	return TRUE;
}

COdbcSql::COdbcSql()
{//construct function
	m_bSuccess = TRUE;
	m_bIsConnected = FALSE;
	m_henv = NULL;
	m_hdbc = NULL;
	m_hstmt = NULL;
	m_pszPassword = NULL;
	m_pszSourceName = NULL;
	m_pszTempSQL = NULL;
	m_pszUserId = NULL;
	sr = 0;
}

COdbcSql::~COdbcSql() 
{//disconstruct function

}

BOOL COdbcSql::Connect( LPCSTR pszSourceName, LPCSTR pszUserId, LPCSTR pszPassword ) 
{//connect the specified DataBase 
	ASSERT (m_henv == SQL_NULL_HENV );

	BOOL bReturn = TRUE;
	SWORD wLengthUID = 0;
	SWORD wLengthPSW = 0;

	//分配环境句柄
	sr=::SQLAllocHandle ( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "分配环境句柄错误!" );
		return FALSE;
	}

	//设置ODBC版本
	sr=::SQLSetEnvAttr ( m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,	SQL_IS_INTEGER );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "设置ODBC版本错误!" );
		return FALSE;
	}

	//分配ODBC连接句柄
	sr=::SQLAllocHandle ( SQL_HANDLE_DBC, m_henv, &m_hdbc );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "分配连接句柄错误!" );
		return FALSE;
	}

	//设置连接时间
	sr=SQLSetConnectAttr( m_hdbc, SQL_ATTR_LOGIN_TIMEOUT, (void *)5, 0 );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "设置连接时间失败!" );
		return FALSE;
	}

	m_pszSourceName = new char[strlen(pszSourceName)+1];
	strcpy ( m_pszSourceName, pszSourceName );

	if ( pszUserId != NULL ) //如果有用户名的话，处理
	{
		m_pszUserId = new char[strlen(pszUserId)+1];
		strcpy( m_pszUserId , pszUserId );
		wLengthUID = SQL_NTS;
	}

	if ( pszPassword != NULL ) //如果有密码的话，处理
	{
		m_pszPassword = new char[strlen(pszPassword)+1];
		strcpy( m_pszPassword , pszPassword );
		wLengthPSW = SQL_NTS;
	}

	//连接数据库
	sr=::SQLConnect ( m_hdbc, 
		              (PUCHAR)pszSourceName, SQL_NTS, 
					  (PUCHAR)pszUserId, wLengthUID, 
		              (PUCHAR)pszPassword, wLengthPSW );

	if ( ( SQL_SUCCESS == sr ) || ( SQL_SUCCESS_WITH_INFO == sr) )
	{
		m_bIsConnected = TRUE;
	}
	else
	{
		AfxMessageBox("无法与数据库连接! ");
		return FALSE;
	}
	
	return TRUE;
}

BOOL COdbcSql::ExeSQLSearch( char *sqltext )
{
	sr=::SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "申请语句句柄失败!" );
		exit ( 0 );
	}

	sr=::SQLPrepare ( m_hstmt, (unsigned char *)sqltext, SQL_NTS );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "查询准备失败!" );
		exit ( 0 );
	}
	
/*	sr=::SQLExecDirect(m_hstmt, (SQLTCHAR *)sqltext, SQL_NTS );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "SQL语句执行失败!" );
		exit ( 0 );
	}
*/
	return TRUE;
}

/*
//BOOL COdbcSql::SQLBindCol( SQLUSMALLINT nColNum , SQLSMALLINT TargetType , SQLPOINTER TargetValue , SQLINTEGER BufferLength , SQLINTEGER *StrLen )
{
	sr = ::SQLBindCol( m_hstmt , (SQLSMALLINT)nColNum,  ( short )TargetValue , TargetValue , BufferLength , StrLen );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "绑定数据库失败!" );
		exit ( 0 );
	}
	return TRUE;
}

//BOOL COdbcSql::Fetch( )
{
	sr = ::SQLFetch( m_hstmt );
	if ( sr != SQL_SUCCESS )
	{
		TRACE ( "取数据失败!" );
		exit ( 0 );
	}
	return TRUE;
}
*/

void COdbcSql::DisConnect( ) 
{//disconnect from the DataBase
	if ( m_pszSourceName )
	{
		delete [] m_pszSourceName;
		m_pszSourceName = NULL;
	}

	if ( m_pszUserId )
	{
		delete [] m_pszUserId;
		m_pszUserId = NULL;
	}

	if ( m_pszPassword )
	{
		delete [] m_pszPassword;
		m_pszPassword = NULL;
	}

	if ( m_hdbc )
	{
		if ( m_bIsConnected )
		{
			if ( m_hstmt )
			{
				::SQLFreeHandle ( SQL_HANDLE_STMT , m_hstmt );
				m_hstmt = SQL_NULL_HSTMT;
			}
			::SQLDisconnect ( m_hdbc );	
			m_bIsConnected = FALSE;
		}
		::SQLFreeHandle ( SQL_HANDLE_DBC, m_hdbc );
		m_hdbc = SQL_NULL_HDBC;
	}

	if ( m_henv )
	{
		sr = ::SQLFreeHandle( SQL_HANDLE_ENV, m_henv );//释放环境句柄
		m_henv = SQL_NULL_HENV;
	}
}
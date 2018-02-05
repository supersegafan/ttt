// OdbcSql.h
//2001年9月12日 

#ifndef __OdbcSql_H__
#define __OdbcSql_H__

#include "sql.h"
#include "sqlext.h"
#include "sqltypes.h"

class COdbcSql
{
private:

public:
	BOOL m_bSuccess;                    //
	BOOL m_bIsConnected;                //连接标志
	SQLHENV m_henv;                     //环境句柄 
	SQLHDBC m_hdbc;                     //ODBC句柄
	SQLHSTMT m_hstmt;                   //语句句柄 
	SQLRETURN sr;                       //SQL语句的返回值
	char *m_pszSourceName;              //数据源名称
	char *m_pszTempSQL;                 //语句指针
	char *m_pszUserId;					//用户名	
	char *m_pszPassword;				//密码

	COdbcSql();
	
	~COdbcSql();

	BOOL Close( void );

	BOOL Connect( LPCSTR pszSourceName, LPCSTR pszUserId, LPCSTR pszPassword );
	
	BOOL ExeSQLSearch( char *sqltext );

//	BOOL SQLBindCol( SQLUSMALLINT nColNum , SQLSMALLINT TargetType , SQLPOINTER TargetValue , SQLINTEGER BufferLength , SQLINTEGER *StrLen );

//	BOOL Fetch( );

	void DisConnect( );

protected:

};

#endif  //OdbcSql.h

// OdbcSql.h
//2001��9��12�� 

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
	BOOL m_bIsConnected;                //���ӱ�־
	SQLHENV m_henv;                     //������� 
	SQLHDBC m_hdbc;                     //ODBC���
	SQLHSTMT m_hstmt;                   //����� 
	SQLRETURN sr;                       //SQL���ķ���ֵ
	char *m_pszSourceName;              //����Դ����
	char *m_pszTempSQL;                 //���ָ��
	char *m_pszUserId;					//�û���	
	char *m_pszPassword;				//����

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

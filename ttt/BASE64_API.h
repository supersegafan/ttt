#pragma once
#include "stdafx.h"
 
#include <windows.h>
 
#ifdef  __cplusplus
extern "C" {
#endif
 
/*
���ܣ�������������ת����BASE64�����ַ���
����˵����
  inputBuffer��Ҫ����Ķ���������
  inputCount�����ݳ���
  outputBuffer���洢ת�����BASE64�����ַ���
����ֵ��
   -1����������
  >=0����Ч���볤�ȣ��ַ�����,�������ַ�����������
��ע��
  ��Ч��openssl��EVP_EncodeBlock����
*/
INT BASE64_Encode( const BYTE* inputBuffer, INT inputCount, TCHAR* outputBuffer );
 
/*
���ܣ���BASE64�����ַ���ת��Ϊ����������
����˵����
  inputBuffer��BASE64�����ַ���
  inputCount�����볤�ȣ��ַ�����,Ӧ��Ϊ4�ı�����
  outputBuffer���洢ת����Ķ���������
����ֵ��
   -1����������
   -2�����ݴ���
  >=0��ת������ֽ���
��ע��
  ��Ч��openssl��EVP_DecodeBlock����
*/
INT BASE64_Decode( const TCHAR* inputBuffer, INT inputCount, BYTE* outputBuffer );
 
#ifdef __cplusplus
}
#endif
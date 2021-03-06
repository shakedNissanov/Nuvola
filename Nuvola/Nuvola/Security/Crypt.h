#if !defined(AFX_MYCNGCRYPTFILE_H__E72946B6_46C1_44A5_B25A_02E983654883__INCLUDED_)
#define AFX_MYCNGCRYPTFILE_H__E72946B6_46C1_44A5_B25A_02E983654883__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _AFXDLL 
#include <afx.h>
#include <Windows.h>
#include <bcrypt.h>

#ifndef NTSTATUS
typedef LONG NTSTATUS, *PNSTATUS;
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
#define STATUS_NOT_SUPPORTED            ((NTSTATUS)0xC00000BBL)
#define STATUS_UNSUCCESSFUL             ((NTSTATUS)0xC0000001L)
#define STATUS_INVALID_PARAMETER        ((NTSTATUS)0xC000000DL)
#define STATUS_HMAC_NOT_SUPPORTED       ((NTSTATUS)0xC000A001L)
#define STATUS_BUFFER_TOO_SMALL         ((NTSTATUS)0xC0000023L)
#define STATUS_NOT_IMPLEMENTED          ((NTSTATUS)0xC0000002L)
#define STATUS_ENTRYPOINT_NOT_FOUND     ((NTSTATUS)0xC0000139l)
#endif

const DWORD CHUNK_SIZE = 16;

#define SYMM_KEY_SIZE_SECRET 16

//Set IV
static const BYTE rgbIV[] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

//Set AES KEY
static const BYTE rgbAES128Key[] =
{
	'D', 'r', '.', 'L', 'u', 'i', 'j', 'i',
	'C', 'N', 'G', ' ', 'T', 'e', 's', 't'
};

class CMyCNGCryptFile
{
	//File 
	void SetLenghtFileToOpen(ULONGLONG iLenghtFileToOpen);
	bool LastCryptBuffRead();
	void SetTotByteRead(UINT iByteRead);
	ULONGLONG m_iLenghtFileToOpen;
	ULONGLONG m_iTotalByteRead;


	//Handle 
	BCRYPT_ALG_HANDLE       m_hAesAlg;
	BCRYPT_KEY_HANDLE       m_hKey;
	PBYTE                   m_pbKeyObject;
	PBYTE                   m_pbIV;

	//Handle for Hash
	BCRYPT_HASH_HANDLE		m_hHash;
	PBYTE					m_pbHashObject;
	BCRYPT_ALG_HANDLE		m_hHashAlg;

	// 
	bool OpenMSPrimitiveProviderAES();
	bool CreateSymmetricKey_AES_CBC(DWORD &cbKeyObject, DWORD &cbIV);
	bool CreateSymmetricKey_SHA1_Hash(PCWSTR pwszText, DWORD cbKeyObj);
	bool Crypt(bool bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave);
	bool CryptLastByte(bool bEncrypt, PUCHAR pbufFileToOpen, ULONG iBytesRead, ULONG cbIV, PBYTE pbufFileToSave, DWORD& iBufToSave);


	CString m_sError;
public:
	bool EnumProviders(CStringList *lstRegisteredProviders);
	bool CryptFile(bool bEncrypt, CString sFileToOpen, CString sFileToCrypt, CString sKey);
	CMyCNGCryptFile();
	virtual ~CMyCNGCryptFile();
	CString GetLastError();

};

#endif // !defined(AFX_MYCNGCRYPTFILE_H__E72946B6_46C1_44A5_B25A_02E983654883__INCLUDED_)

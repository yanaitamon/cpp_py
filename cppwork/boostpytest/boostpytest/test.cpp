// test :[

// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#endif

// ���Ŏw�肳�ꂽ��`�̑O�ɑΏۃv���b�g�t�H�[�����w�肵�Ȃ���΂Ȃ�Ȃ��ꍇ�A�ȉ��̒�`��ύX���Ă��������B
// �قȂ�v���b�g�t�H�[���ɑΉ�����l�Ɋւ���ŐV���ɂ��ẮAMSDN ���Q�Ƃ��Ă��������B
#ifndef WINVER				// Windows XP �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B
#define WINVER 0x0501		// ����� Windows �̑��̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
#endif

#ifndef _WIN32_WINNT		// Windows XP �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B                   
#define _WIN32_WINNT 0x0501	// ����� Windows �̑��̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B
#define _WIN32_WINDOWS 0x0410 // ����� Windows Me �܂��͂���ȍ~�̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
#endif

#ifndef _WIN32_IE			// IE 6.0 �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B
#define _WIN32_IE 0x0600	// ����� IE �̑��̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �ꕔ�� CString �R���X�g���N�^�͖����I�ł��B

// ��ʓI�Ŗ������Ă����S�� MFC �̌x�����b�Z�[�W�̈ꕔ�̔�\�����������܂��B
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������

#include <afxdisp.h>        // MFC �I�[�g���[�V���� �N���X

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT
// ]: test

#define BOOST_PYTHON_STATIC_LIB
#include <string>
#include <boost/python.hpp>
#include <boost/python/handle.hpp>

#include "resource.h"

#include "TAPI.h"
#include "ModelIO_API.h"
#include "CamCalc_API.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

using namespace boost::python;
 
//struct World
//{
//    void set(std::string msg) { this->msg = msg; }
//    std::string greet() { return msg; }
//    std::string msg;
//};
// 
//BOOST_PYTHON_MODULE(boostpytest)
//{
//    class_<World>("World")
//        .def("greet", &World::greet)
//        .def("set", &World::set)
//    ;
//}

class foo {
public:
  CString m_str;

public:
  void set(std::string str){ m_str = str.c_str(); }
  std::string get(){ return static_cast<LPCTSTR>(m_str); }

};

// �������}�b�v�g�t�@�C���̂��߂̎w��
#define DATA_SIZE 1024
HANDLE hMapFile = (HANDLE)0xFFFFFFFF;
LPVOID lpMem = NULL;
static LPCTSTR MAP_FILENAME = _T("SharedMemory");

//�e�X�g�p�̋��L�f�[�^�^ 
typedef struct SharedData
{
  char m_mylineNo[256];
  char m_url[256];
  int m_Value;
  std::vector<CString> m_vecstrStatus;
  CString m_strStatus;
} SHARED_DATA;

// �n���h���E�B���h�E�擾
HWND GetWindowHandle(	// �߂�l: ���� �]�݂�HWND / ���s NULL
	const DWORD TargetID)	// �v���Z�XID
{
	HWND hWnd = GetTopWindow(NULL);
	do {
		if(GetWindowLong( hWnd, -8/*GWL_HWNDPARENT*/) != 0 || !IsWindowVisible( hWnd))
			continue;
		DWORD ProcessID;
		GetWindowThreadProcessId( hWnd, &ProcessID);
		if(TargetID == ProcessID)
			return hWnd;
	} while((hWnd = GetNextWindow( hWnd, GW_HWNDNEXT)) != NULL);

	return NULL;
}

const int wmComCLStatusNotify   = RegisterWindowMessage( _T("WM_CHANGECLSTATUS") );
const int wmComOptStatusNotify  = RegisterWindowMessage( _T("WM_CHANGEOPTSTATUS") );
const int wmComSolStatusNotify  = RegisterWindowMessage( _T("WM_CHANGESOLSTATUS") );
const int wmComCamMsgNotify     = RegisterWindowMessage( _T("WM_CAMERRORMESSAGE") );
const int wmComNCMsgNotify      = RegisterWindowMessage( _T("WM_CHANGENCSTATUS") );
const int wmComFileMsgNotify    = RegisterWindowMessage( _T("WM_IGNOREWRITE") );
const int wmComRequestClDisp    = RegisterWindowMessage( _T( "TOOLSWM_REQUEST_CL_DISP" ) ) ;
const int wmComPostMsgNotify    = RegisterWindowMessage( _T("WM_POSTERRORMESSAGE") );
const int wmCalcStartNotify     = RegisterWindowMessage( _T("WM_AUTOCALCSTART") );

// �e�X�g�_�C�A���O
class MyDlg : public CDialog
{
// �R���X�g���N�V����
public:
	MyDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^
	~MyDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG1 };

protected:
  LRESULT checkDoingStatus( int nType, WPARAM wParam, LPARAM lParam );
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnCLStatusNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOptStatusNotify(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSolStatusNotify( WPARAM wParam, LPARAM lParam );
  afx_msg LRESULT OnCamMessageNotify( WPARAM wParam, LPARAM lParam );
  afx_msg LRESULT OnCamNCNotify( WPARAM wParam, LPARAM lParam );
  afx_msg LRESULT OnCamFileNotify( WPARAM wParam, LPARAM lParam );
  afx_msg LRESULT OnCamRequestClDisp( WPARAM wParam, LPARAM lParam );    // Add 2005/05/20 M.Maiwa V3.1 Update 2-7
  afx_msg LRESULT OnPostMessageNotify( WPARAM wParam, LPARAM lParam );   // :V3.1u:[2005.06.23 M.Su M-9]
  afx_msg LRESULT OnCalcStart( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

  //ModelIO_API* m_pModelIoAPI;  //  ���f���t�@�C���Ƃ̊ԂŃf�[�^�̎󂯓n�����s�� API
  CamCalc_API* m_pCalcAPI;  // ���Z�H���\�Ƃ̊ԂŃf�[�^�̎󂯓n�����s�� API

  CString strModelPath;     // ���f���t�@�C���t���p�X
  CString strProcName;          // �H���\��
  CString strOriginName;    // ���Z���_����
  CString strSheetPath;     // ���Z�H���\�t���p�X
  CString strCalcKey;       // ���Z�H���\�L�[

public:
  BOOL DoCalculation();
  void disposeAllCalcObjects();

  void setModelPath( wstring str ) { strModelPath = str.c_str(); }
  void setProcName( wstring str ) { strProcName = str.c_str(); }
  void setOriginName( wstring str ) { strOriginName = str.c_str(); }
  void setSheetPath( wstring str ) { strSheetPath = str.c_str(); }
};

MyDlg::MyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MyDlg::IDD, pParent)
  , strModelPath(_T(""))
  , strProcName(_T(""))
  , strOriginName(_T(""))
  , strSheetPath(_T(""))
  , strCalcKey(_T(""))
{
}

MyDlg::~MyDlg()
{
  disposeAllCalcObjects();
}

BOOL MyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

  PostMessage( wmCalcStartNotify, 0, 0);
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void MyDlg::disposeAllCalcObjects()
{
  // Before the contents of m_vecCalcSheet is cleared, CalcSheet object shall be deleted.
  if ( m_pCalcAPI ){
    delete m_pCalcAPI;
    m_pCalcAPI = NULL;
  }
}

BEGIN_MESSAGE_MAP(MyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
 	ON_REGISTERED_MESSAGE(wmComCLStatusNotify, OnCLStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComOptStatusNotify, OnOptStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComSolStatusNotify, OnSolStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComCamMsgNotify, OnCamMessageNotify)
 	ON_REGISTERED_MESSAGE(wmComNCMsgNotify, OnCamNCNotify)
 	ON_REGISTERED_MESSAGE(wmComFileMsgNotify, OnCamFileNotify)
 	ON_REGISTERED_MESSAGE(wmComRequestClDisp, OnCamRequestClDisp)
 	ON_REGISTERED_MESSAGE(wmComPostMsgNotify, OnPostMessageNotify)
  ON_REGISTERED_MESSAGE(wmCalcStartNotify, OnCalcStart)
END_MESSAGE_MAP()


////////////////////////////////////////////////////////////////////////////
// ���Z��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnCLStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCLStatusNotify, wParam, lParam  ); }

// �œK����Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnOptStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComOptStatusNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnSolStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComSolStatusNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnCamMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCamMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnCamNCNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComNCMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnCamFileNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComFileMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnCamRequestClDisp( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComRequestClDisp, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT MyDlg::OnPostMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComPostMsgNotify, wParam, lParam  ); }
////////////////////////////////////////////////////////////////////////////

// wmCalcStartNotify
LRESULT MyDlg::OnCalcStart( WPARAM wParam, LPARAM lParam )
{
  try
  {
    DoCalculation();
  }
  catch(...)
  {
    TRACE(_T("�Ȃ񂩃G���[!"));
    return FALSE;
  }
  UpdateWindow();
  return TRUE;
}

LRESULT MyDlg::checkDoingStatus( int nType,  WPARAM wParam, LPARAM lParam )
{
  LRESULT lRet = 0L;

  CString strStatus(_T("�G���["));
  try{
    int nStatus = 0;
    int nRtn = m_pCalcAPI->getSheetStatus( strCalcKey, nStatus );

    // IDC_STATIC
    if( nStatus == API_CalcStatusCalc ){
      strStatus.Format( _T("Calculating") );
    }
    else if( nStatus == API_CalcStatusWait ){
      strStatus.Format( _T("Waiting") );
    }
    else if( nStatus == API_CalcStatusSuspend ){
      strStatus.Format( _T("Suspended") );
    }
    else if( nStatus == API_CalcStatusTerminate ){
      strStatus.Format( _T("Canceled") );
    }
    else{
      strStatus.Format( _T("Finished") );
    }
  }
  catch(...)
  {
    lRet = -1;
  }

  this->SetDlgItemText( IDC_STATIC, strStatus );
  UpdateData(FALSE);

  return lRet;
}

// ���Z�J�n
BOOL MyDlg::DoCalculation()
{
  // �ݒ肪������Ή��Z���Ȃ�
  if( strModelPath.IsEmpty()
   || strProcName.IsEmpty()
   || strOriginName.IsEmpty()
   || strSheetPath.IsEmpty()
   ) return FALSE;


  unsigned long dw = GetCurrentProcessId();
  HWND myhd = this->GetSafeHwnd();
  HWND h1 = GetWindowHandle(dw);

  HWND hWinAppHandle = ::FindWindow(_T("cmd"), NULL);
  if(NULL == hWinAppHandle)
    hWinAppHandle = ::FindWindow(_T("python"), NULL);

  int hl;
  if ( NULL != h1 ) hl = reinterpret_cast<int>(hWinAppHandle/*h1*/);
  //HWND h2 = handle();
  CString strText(_T(""));
  strText.Format( _T("Process ID: %d, WindowHandle : %d, \n"),dw, myhd );
  AfxMessageBox(strText, MB_OK);

  m_pCalcAPI = new CamCalc_API( strModelPath );
  if( !m_pCalcAPI ) return FALSE;

  strCalcKey = _T("");
  int nProcNum = -1;
  int nStatus = static_cast<int>(API_NormalStatus);
  {
    // ���Z�H���\�쐬
    nProcNum = m_pCalcAPI->CreateProcessSheet( strProcName, strSheetPath, myhd/*this->GetSafeHwnd()*/, strCalcKey );
    nStatus = m_pCalcAPI->getLastErrStatus();
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // ���Z�H���\�ւ̃��[�N�̔��f
    nStatus = m_pCalcAPI->SetSolidProfile( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
    // ���Z�H���\�ւ̐��i�`��̔��f
    nStatus = m_pCalcAPI->SetModelSolidProfile( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
    // �œK��ON
    nStatus = m_pCalcAPI->OnCamOptimizeRange( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // ���Z���_�̐ݒ��CalcControl�ɒʒm
    nStatus = m_pCalcAPI->SetSequenceEditionAndOriginForAll( strProcName, strCalcKey, strOriginName );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // �ۑ�
    nStatus = m_pCalcAPI->SaveModelFile();
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
  }

  int nRtn = m_pCalcAPI->setProcessSheetCalcExec( strCalcKey );

  return TRUE;
}

//////
// TOOLS.cpp���DoCommand�֐����قڂ��̂܂܃R�s�[���Ă���
// �O��exe��CAM-TOOL�̑O�ʂɕ\������Ă���ԁA��ʂ��^�����ɂȂ�Ȃ��悤�ɂ��Ă���
int DoCommand( LPCTSTR lpszCmdLine, bool bIsHide /*= false*/ )
{
  DWORD ExitCode ;

  try{
    STARTUPINFO StartUpInfo;
    PROCESS_INFORMATION ProcInfo;

    CString strc(_T(""));
    
    ::ZeroMemory( &StartUpInfo, sizeof( StartUpInfo ) ); 

    StartUpInfo.cb            = sizeof( STARTUPINFO ) ; 
    StartUpInfo.dwFlags       = 0 ;
  /* �������o���Ȃ��ꍇ
    StartUpInfo.dwFlags       = STARTF_USESTDHANDLES ; 
    StartUpInfo.hStdInput     = NULL ; 
    StartUpInfo.hStdOutput    = NULL ; 
    StartUpInfo.hStdError     = NULL ; 
  */
  //  if ( !g_bCommandShow ){//�E�B���h�E���o���Ȃ��ꍇ
      StartUpInfo.dwFlags       = STARTF_USESHOWWINDOW ;
    // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: �g�p�����_�񏑃E�B���h�E�����ƁA���̃E�B���h�E���\������" �ւ̑Ή�
    if( bIsHide ) {
      StartUpInfo.wShowWindow = SW_SHOW;
    } else {
    //  2011.02.21 M.Su "Mantis-0003451: �g�p�����_�񏑃E�B���h�E�����ƁA���̃E�B���h�E���\������" �ւ̑Ή� ]:V7.1:
      StartUpInfo.wShowWindow   = SW_HIDE ; 
    } // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: �g�p�����_�񏑃E�B���h�E�����ƁA���̃E�B���h�E���\������" �ւ̑Ή� ]



  //  }

    if ( !::CreateProcess( NULL,
                         (LPTSTR)lpszCmdLine,
                         NULL,
                         NULL,
                         FALSE,
                         CREATE_DEFAULT_ERROR_MODE|NORMAL_PRIORITY_CLASS,
                         NULL,
                         NULL,
                         &StartUpInfo,
                         &ProcInfo ) ) {

	    LPVOID lpMsgBuf ;

      ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       ::GetLastError(),
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                       (LPTSTR) &lpMsgBuf,
                       0,
                       NULL ) ;

      //// Display the string.
      //AfxMessageBox( (LPCSTR)lpMsgBuf ) ;

      // Free the buffer.
      LocalFree( lpMsgBuf ) ;

      return -1 ;
    } else {

      if( bIsHide ) {
        // �I���܂ő҂ԁA��ʂ̍ĕ`��̂ݍs��
        // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: �g�p�����_�񏑃E�B���h�E�����ƁA���̃E�B���h�E���\������" �ւ̑Ή�
        // while ( 1 ){
        //   DWORD dwRet = WaitForSingleObject( ProcInfo.hProcess, 100 ) ;
        //   if( dwRet == WAIT_OBJECT_0 ) break;
        while ( WaitForSingleObject(ProcInfo.hProcess, 0) != WAIT_OBJECT_0 ) {
        //  2011.02.21 M.Su "Mantis-0003451: �g�p�����_�񏑃E�B���h�E�����ƁA���̃E�B���h�E���\������" �ւ̑Ή� ]:V7.1:
          // �E�B���h�E ���b�Z�[�W������B�f�B�X�p�b�`����B
          MSG msg;
          while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
          }
        }
      } else {
        while ( WaitForSingleObject( ProcInfo.hProcess, INFINITE ) != WAIT_OBJECT_0 );
      }
   
      CloseHandle( ProcInfo.hThread ) ;
    
      ::GetExitCodeProcess( ProcInfo.hProcess, &ExitCode );
      CloseHandle( ProcInfo.hProcess );
    }
  }
  catch(...)
  {
    TRACE( "TMICutHoleCancel::OnCutHoleRemove Exception Occured.\n" );
  }

  return ExitCode ;
}
//////


class DlgCaller {
protected:
public:
  BOOL DoCalculation(std::wstring str, std::wstring str2,
    std::wstring str3, std::wstring str4, std::wstring str5)
  {
    CString szCommandLine( _T("") );
    CString sz( str.c_str() );
    CString sz2( str2.c_str() );
    CString sz3( str3.c_str() );
    CString sz4( str4.c_str() );
    CString sz5( str5.c_str() );
    szCommandLine.Format( _T("C:\\Python27\\DLLs\\anotherone.exe \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"")
                        , sz, sz2, sz3, sz4, sz5 );

    //AfxMessageBox( szCommandLine, MB_OK );

    DoCommand( szCommandLine, true );

    //MyDlg* d = new MyDlg();
    //d->setModelPath(str);
    //d->setProcName(str2);
    //d->setOriginName(str3);
    //d->setSheetPath(str4);
    //d->DoModal();
    //delete d;
    //d = NULL;
    return TRUE;
  }

  //void setModelPath( std::wstring str){ d.setModelPath(str); }
  //void setProcName( std::wstring str){ d.setProcName(str); }
  //void setOriginName( std::wstring str){ d.setOriginName(str); }
  //void setSheetPath( std::wstring str){ d.setSheetPath(str); }
};

// �X�e�[�^�X��Ԃ�
std::wstring getCalcStatus()
{
  wstring retStr = L"failed.";

  // �������}�b�v�h�t�@�C���̍쐬�A�m��
  hMapFile = ::CreateFileMapping(
              INVALID_HANDLE_VALUE,
              NULL,
              PAGE_READWRITE,
              0,
              DATA_SIZE,
              MAP_FILENAME);

  BOOL bExists = (GetLastError() == ERROR_ALREADY_EXISTS);
  lpMem = ::MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, DATA_SIZE);
  if (!bExists)
      ZeroMemory(lpMem, DATA_SIZE);

  SharedData* data = static_cast<SharedData*>(lpMem);

  if(NULL != data){

    const unsigned int dataSize = data->m_strStatus.GetLength();
    char* buf = new char[dataSize+1];
    strcpy( buf, data->m_strStatus );
    wchar_t* wlocal = new wchar_t[dataSize+1];

    int ret = MultiByteToWideChar( CP_ACP, 
                                  MB_PRECOMPOSED,
                                  buf,
                                  dataSize+1,
                                  wlocal,
                                  dataSize+2 );

    retStr = wlocal;
    delete []buf;
    delete []wlocal;

//MultiByteToWideChar
//
//std::wstring iso = L"iso";
//CString ms = "ms";
//
//ms = iso.c_str();
//iso = ms.GetString();

    //LPCWSTR sss = (data->m_strStatus);
    //std::wstring hi2( sss );
    //retStr = hi2;
  }

  return retStr;
}


// �����ɕ������A�����ĕԂ��֐�
string add_hello( string s )
{
  return "Hello, " + s;
}

// ������2�悵�ĕԂ��֐�
int square( int n )
{
  return n * n;
}

int test_save_api()
{
  CString strSrc = _T("C:\\work\\test\\naaa\\b�e�X�g\\v3-denkyoku1-KSTM01.gmd");
  CString strDst = _T("C:\\work\\test\\naaa\\Output_test\\hozon.gmd");
  ModelIO_API* pModelIoAPI = new ModelIO_API( strSrc, false );
  int nStatus = pModelIoAPI->SaveModelFile( strDst );
  return nStatus;
}

int test_save_name_api( wstring src, wstring dst )
{
  CString strSrc( src.c_str() );
  TRACE( _T("%s\n"), strSrc );

  CString strName( dst.c_str() );
  CString strDst = _T("C:\\work\\test\\naaa\\Output_test\\") + strName + _T(".gmd");
  AfxMessageBox(_T("stop"), MB_OK );
  ModelIO_API* pModelIoAPI = new ModelIO_API( strSrc, false );
  int nStatus = pModelIoAPI->SaveModelFile( strDst );
  return nStatus;
}

int test_save_name_api2( foo* src, foo* dst )
{
  CString strSrc = src->get().c_str();
  TRACE( _T("%s\n"), strSrc );

  CString strName= dst->get().c_str();
  CString strDst = _T("C:\\work\\test\\naaa\\Output_test\\") + strName + _T(".gmd");
  ModelIO_API* pModelIoAPI = new ModelIO_API( strSrc, false );
  int nStatus = pModelIoAPI->SaveModelFile( strDst );
  return nStatus;
}

// ���W���[���̏��������[�`��:���W���[����=my_sample
BOOST_PYTHON_MODULE( boostpytest )
{
  class_<foo>("foo")
    .def( "set", &foo::set )
    .def( "get", &foo::get/*, return_value_policy<copy_const_reference>()*/ )
    ;

  //class_<MyDlg>("MyDlg")
  //  .def( "DoCalculation", &MyDlg::DoCalculation )
  //  ;

  class_<DlgCaller>("DlgCaller")
    .def( "DoCalculation", &DlgCaller::DoCalculation )
    //.def( "get", &DlgCaller::setModelPath )
    //.def( "get", &DlgCaller::setProcName )
    //.def( "get", &DlgCaller::setOriginName )
    //.def( "get", &DlgCaller::setSheetPath )
    ;

  // C++��add_hello�֐����Agreet�Ƃ������O��python�p�Ɍ��J
  boost::python::def( "greet", add_hello );

  // C++��square�֐����Asquare�Ƃ������O��python�p�Ɍ��J
  boost::python::def( "square", square );

  // test_api()�֐����Atest_model_save�Ƃ������O��python�p�Ɍ��J
  boost::python::def( "model_save_test", test_save_api );

  boost::python::def( "model_name_save", test_save_name_api );
  boost::python::def( "model_name_save2", test_save_name_api2 );
}

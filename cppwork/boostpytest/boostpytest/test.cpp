// test :[

// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Windows ヘッダーから使用されていない部分を除外します。
#endif

// 下で指定された定義の前に対象プラットフォームを指定しなければならない場合、以下の定義を変更してください。
// 異なるプラットフォームに対応する値に関する最新情報については、MSDN を参照してください。
#ifndef WINVER				// Windows XP 以降のバージョンに固有の機能の使用を許可します。
#define WINVER 0x0501		// これを Windows の他のバージョン向けに適切な値に変更してください。
#endif

#ifndef _WIN32_WINNT		// Windows XP 以降のバージョンに固有の機能の使用を許可します。                   
#define _WIN32_WINNT 0x0501	// これを Windows の他のバージョン向けに適切な値に変更してください。
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 以降のバージョンに固有の機能の使用を許可します。
#define _WIN32_WINDOWS 0x0410 // これを Windows Me またはそれ以降のバージョン向けに適切な値に変更してください。
#endif

#ifndef _WIN32_IE			// IE 6.0 以降のバージョンに固有の機能の使用を許可します。
#define _WIN32_IE 0x0600	// これを IE の他のバージョン向けに適切な値に変更してください。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 一部の CString コンストラクタは明示的です。

// 一般的で無視しても安全な MFC の警告メッセージの一部の非表示を解除します。
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分

#include <afxdisp.h>        // MFC オートメーション クラス

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
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

// メモリマップトファイルのための指定
#define DATA_SIZE 1024
HANDLE hMapFile = (HANDLE)0xFFFFFFFF;
LPVOID lpMem = NULL;
static LPCTSTR MAP_FILENAME = _T("SharedMemory");

//テスト用の共有データ型 
typedef struct SharedData
{
  char m_mylineNo[256];
  char m_url[256];
  int m_Value;
  std::vector<CString> m_vecstrStatus;
  CString m_strStatus;
} SHARED_DATA;

// ハンドルウィンドウ取得
HWND GetWindowHandle(	// 戻り値: 成功 望みのHWND / 失敗 NULL
	const DWORD TargetID)	// プロセスID
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

// テストダイアログ
class MyDlg : public CDialog
{
// コンストラクション
public:
	MyDlg(CWnd* pParent = NULL);	// 標準コンストラクタ
	~MyDlg();

// ダイアログ データ
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

  //ModelIO_API* m_pModelIoAPI;  //  モデルファイルとの間でデータの受け渡しを行う API
  CamCalc_API* m_pCalcAPI;  // 演算工程表との間でデータの受け渡しを行う API

  CString strModelPath;     // モデルファイルフルパス
  CString strProcName;          // 工程表名
  CString strOriginName;    // 演算原点名称
  CString strSheetPath;     // 演算工程表フルパス
  CString strCalcKey;       // 演算工程表キー

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
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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
// 演算状態のステータスが変わった
LRESULT MyDlg::OnCLStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCLStatusNotify, wParam, lParam  ); }

// 最適化状態のステータスが変わった
LRESULT MyDlg::OnOptStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComOptStatusNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT MyDlg::OnSolStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComSolStatusNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT MyDlg::OnCamMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCamMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT MyDlg::OnCamNCNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComNCMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT MyDlg::OnCamFileNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComFileMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT MyDlg::OnCamRequestClDisp( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComRequestClDisp, wParam, lParam  ); }

// ？？状態のステータスが変わった
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
    TRACE(_T("なんかエラー!"));
    return FALSE;
  }
  UpdateWindow();
  return TRUE;
}

LRESULT MyDlg::checkDoingStatus( int nType,  WPARAM wParam, LPARAM lParam )
{
  LRESULT lRet = 0L;

  CString strStatus(_T("エラー"));
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

// 演算開始
BOOL MyDlg::DoCalculation()
{
  // 設定が無ければ演算しない
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
    // 演算工程表作成
    nProcNum = m_pCalcAPI->CreateProcessSheet( strProcName, strSheetPath, myhd/*this->GetSafeHwnd()*/, strCalcKey );
    nStatus = m_pCalcAPI->getLastErrStatus();
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // 演算工程表へのワークの反映
    nStatus = m_pCalcAPI->SetSolidProfile( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
    // 演算工程表への製品形状の反映
    nStatus = m_pCalcAPI->SetModelSolidProfile( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
    // 最適化ON
    nStatus = m_pCalcAPI->OnCamOptimizeRange( strCalcKey );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // 演算原点の設定をCalcControlに通知
    nStatus = m_pCalcAPI->SetSequenceEditionAndOriginForAll( strProcName, strCalcKey, strOriginName );
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }

    // 保存
    nStatus = m_pCalcAPI->SaveModelFile();
    if ( API_NormalStatus != nStatus ){
      return FALSE;
    }
  }

  int nRtn = m_pCalcAPI->setProcessSheetCalcExec( strCalcKey );

  return TRUE;
}

//////
// TOOLS.cppよりDoCommand関数をほぼそのままコピーしてきた
// 外部exeがCAM-TOOLの前面に表示されている間、画面が真っ白にならないようにしている
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
  /* 文字を出さない場合
    StartUpInfo.dwFlags       = STARTF_USESTDHANDLES ; 
    StartUpInfo.hStdInput     = NULL ; 
    StartUpInfo.hStdOutput    = NULL ; 
    StartUpInfo.hStdError     = NULL ; 
  */
  //  if ( !g_bCommandShow ){//ウィンドウを出さない場合
      StartUpInfo.dwFlags       = STARTF_USESHOWWINDOW ;
    // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: 使用許諾契約書ウィンドウを閉じると、他のウィンドウが表示する" への対応
    if( bIsHide ) {
      StartUpInfo.wShowWindow = SW_SHOW;
    } else {
    //  2011.02.21 M.Su "Mantis-0003451: 使用許諾契約書ウィンドウを閉じると、他のウィンドウが表示する" への対応 ]:V7.1:
      StartUpInfo.wShowWindow   = SW_HIDE ; 
    } // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: 使用許諾契約書ウィンドウを閉じると、他のウィンドウが表示する" への対応 ]



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
        // 終了まで待つ間、画面の再描画のみ行う
        // :V7.1:[ 2011.02.21 M.Su "Mantis-0003451: 使用許諾契約書ウィンドウを閉じると、他のウィンドウが表示する" への対応
        // while ( 1 ){
        //   DWORD dwRet = WaitForSingleObject( ProcInfo.hProcess, 100 ) ;
        //   if( dwRet == WAIT_OBJECT_0 ) break;
        while ( WaitForSingleObject(ProcInfo.hProcess, 0) != WAIT_OBJECT_0 ) {
        //  2011.02.21 M.Su "Mantis-0003451: 使用許諾契約書ウィンドウを閉じると、他のウィンドウが表示する" への対応 ]:V7.1:
          // ウィンドウ メッセージがある。ディスパッチする。
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

// ステータスを返す
std::wstring getCalcStatus()
{
  wstring retStr = L"failed.";

  // メモリマップドファイルの作成、確保
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


// 引数に文字列を連結して返す関数
string add_hello( string s )
{
  return "Hello, " + s;
}

// 引数を2乗して返す関数
int square( int n )
{
  return n * n;
}

int test_save_api()
{
  CString strSrc = _T("C:\\work\\test\\naaa\\bテスト\\v3-denkyoku1-KSTM01.gmd");
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

// モジュールの初期化ルーチン:モジュール名=my_sample
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

  // C++のadd_hello関数を、greetという名前でpython用に公開
  boost::python::def( "greet", add_hello );

  // C++のsquare関数を、squareという名前でpython用に公開
  boost::python::def( "square", square );

  // test_api()関数を、test_model_saveという名前でpython用に公開
  boost::python::def( "model_save_test", test_save_api );

  boost::python::def( "model_name_save", test_save_name_api );
  boost::python::def( "model_name_save2", test_save_name_api2 );
}

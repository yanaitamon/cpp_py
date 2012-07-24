// anotheroneDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "anotherone.h"
#include "anotheroneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const int wmComCLStatusNotify   = RegisterWindowMessage( _T("WM_CHANGECLSTATUS") );
const int wmComOptStatusNotify  = RegisterWindowMessage( _T("WM_CHANGEOPTSTATUS") );
const int wmComSolStatusNotify  = RegisterWindowMessage( _T("WM_CHANGESOLSTATUS") );
const int wmComCamMsgNotify     = RegisterWindowMessage( _T("WM_CAMERRORMESSAGE") );
const int wmComNCMsgNotify      = RegisterWindowMessage( _T("WM_CHANGENCSTATUS") );
const int wmComFileMsgNotify    = RegisterWindowMessage( _T("WM_IGNOREWRITE") );
const int wmComRequestClDisp    = RegisterWindowMessage( _T( "TOOLSWM_REQUEST_CL_DISP" ) ) ;
const int wmComPostMsgNotify    = RegisterWindowMessage( _T("WM_POSTERRORMESSAGE") );
const int wmCalcStartNotify     = RegisterWindowMessage( _T("WM_AUTOCALCSTART") );

// CanotheroneDlg ダイアログ

CanotheroneDlg::CanotheroneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CanotheroneDlg::IDD, pParent)
  , strModelPath(_T(""))
  , strProcName(_T(""))
  , strOriginName(_T(""))
  , strSheetPath(_T(""))
  , strCalcKey(_T(""))
  , m_pModelAPI( NULL )
  , m_pCalcAPI( NULL )
  , m_sdata( NULL )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CanotheroneDlg::~CanotheroneDlg()
{
  disposeAllCalcObjects();
}

void CanotheroneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CanotheroneDlg::disposeAllCalcObjects()
{
  // Before the contents of m_vecCalcSheet is cleared, CalcSheet object shall be deleted.
  if ( m_pModelAPI ){
    delete m_pModelAPI;
    m_pModelAPI = NULL;
  }

  if ( m_pCalcAPI ){
    delete m_pCalcAPI;
    m_pCalcAPI = NULL;
  }
}

BEGIN_MESSAGE_MAP(CanotheroneDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
 	ON_REGISTERED_MESSAGE(wmComCLStatusNotify, OnCLStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComOptStatusNotify, OnOptStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComSolStatusNotify, OnSolStatusNotify)
 	ON_REGISTERED_MESSAGE(wmComCamMsgNotify, OnCamMessageNotify)
 	ON_REGISTERED_MESSAGE(wmComNCMsgNotify, OnCamNCNotify)
 	ON_REGISTERED_MESSAGE(wmComFileMsgNotify, OnCamFileNotify)
 	ON_REGISTERED_MESSAGE(wmComRequestClDisp, OnCamRequestClDisp)
 	ON_REGISTERED_MESSAGE(wmComPostMsgNotify, OnPostMessageNotify)
  ON_REGISTERED_MESSAGE(wmCalcStartNotify, OnCalcStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CanotheroneDlg メッセージ ハンドラ

BOOL CanotheroneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定


  CString szCommandLine( _T("") );
  CString sz( strModelPath );
  szCommandLine.Format( _T("C:\\Python27\\DLLs\\anotherone.exe\n model: \"%s\"\n proc: \"%s\"\n origin: \"%s\"\n sheetpath: \"%s\"\n template: \"%s\"\n")
                      , strModelPath, strProcName, strOriginName, strSheetPath, strTargetTemplate );

  //AfxMessageBox( szCommandLine, MB_OK );

	// TODO: 初期化をここに追加します。
	// メモリマップドファイルの生成
	m_hMapping = ::CreateFileMapping(
		(HANDLE)0xffffffff,     // 共有メモリの場合は0xffffffffを指定
		NULL,                   // セキュリティ属性。NULLでよい
		PAGE_READWRITE,         // プロテクト属性を読み書き可能に指定
		0,                      // ファイルサイズの上位32ビット
		1024,                   // ファイルサイズの下位32ビット
		_T("SharedMemory") );   // メモリマップドファイルの名前

	// プロセス内のアドレス空間にファイルのビューをマップ
	//m_pMappingView = ::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData*));
  //m_sdata = new SharedData();
  LPVOID pMappingView = ::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData*));
	m_sdata = reinterpret_cast<SharedData*>( pMappingView );

	// ミューテックスオブジェクトの生成
	m_pMutex = new CMutex(FALSE, "UKFileMappingTest_Mutex");

  PostMessage( wmCalcStartNotify, 0, 0);



CString str = _T( "testtttt" );
const unsigned int dataSize = str.GetLength();
char* buf = new char[dataSize+1];
strcpy( buf, str );
//wchar_t wlocal[dataSize+1] = {0x00};
wchar_t* wlocal = new wchar_t[dataSize+1];

int ret = MultiByteToWideChar( CP_ACP, 
                              MB_PRECOMPOSED,
                              buf,
                              dataSize+1, // new char[dataSize+1] の数と合致する
                              wlocal,
                              dataSize+2 ); // 第4引数の+1

//ERROR_INSUFFICIENT_BUFFER
//ERROR_INVALID_FLAGS
//ERROR_INVALID_PARAMETER
//ERROR_NO_UNICODE_TRANSLATION

std::wstring iso = wlocal;
delete []buf;
delete []wlocal;



	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CanotheroneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CanotheroneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////
// 演算状態のステータスが変わった
LRESULT CanotheroneDlg::OnCLStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCLStatusNotify, wParam, lParam  ); }

// 最適化状態のステータスが変わった
LRESULT CanotheroneDlg::OnOptStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComOptStatusNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnSolStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComSolStatusNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnCamMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCamMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnCamNCNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComNCMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnCamFileNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComFileMsgNotify, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnCamRequestClDisp( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComRequestClDisp, wParam, lParam  ); }

// ？？状態のステータスが変わった
LRESULT CanotheroneDlg::OnPostMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComPostMsgNotify, wParam, lParam  ); }
////////////////////////////////////////////////////////////////////////////

// wmCalcStartNotify
LRESULT CanotheroneDlg::OnCalcStart( WPARAM wParam, LPARAM lParam )
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

LRESULT CanotheroneDlg::checkDoingStatus( int nType,  WPARAM wParam, LPARAM lParam )
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

  this->SetDlgItemText( IDC_STATIC1, strStatus );
  UpdateData(FALSE);

  //m_sdata->m_vecstrStatus.push_back(strStatus);
  m_sdata->m_strStatus = strStatus;

  // ★共有メモリへ書き込む。このときミューテックスオブジェクトを
	// 使用して同期処理をおこなう
	m_pMutex->Lock(INFINITE);
	memcpy(m_pMappingView, m_sdata, sizeof(SharedData));
	m_pMutex->Unlock();

  return lRet;
}

// 演算開始
BOOL CanotheroneDlg::DoCalculation()
{
  // 設定が無ければ演算しない
  if( strModelPath.IsEmpty()
   || strProcName.IsEmpty()
   || strOriginName.IsEmpty()
   || strSheetPath.IsEmpty()
   || strTargetTemplate.IsEmpty()
   ) return FALSE;


  unsigned long dw = GetCurrentProcessId();
  HWND myhd = this->GetSafeHwnd();

  HWND hWinAppHandle = ::FindWindow(_T("cmd"), NULL);
  if(NULL == hWinAppHandle)
    hWinAppHandle = ::FindWindow(_T("python"), NULL);

  CString strText(_T(""));
  strText.Format( _T("Process ID: %d, WindowHandle : %d, \n"),dw, myhd );
  //AfxMessageBox(strText, MB_OK);

  // ステータス
  int nStatus = static_cast<int>(API_NormalStatus);

  m_pModelAPI = new ModelIO_API( strModelPath, false );
  if( !m_pModelAPI ) return FALSE;
  // if 見つかったら APIで割付 演算対象として記憶
  // テンプレートファイルを開く。
  CString szTemplateKey = _T("");
  bool bRet = m_pModelAPI->SetTemplate( strTargetTemplate, szTemplateKey );  // 正常終了時の戻り値はテンプレートファイルを識別する Id
  if( !bRet ) return FALSE;

  CString szFileListKey = _T("");
  // 第3引数のプロファイルリスト名をNULLで渡すと全部登録
  bRet = m_pModelAPI->ImportTemplateProfileList( szTemplateKey, szFileListKey );
  if( !bRet ) return FALSE;

  // 上で登録したプロファイル群をテンプレート名でリストにまとめる
  bRet = m_pModelAPI->SetCalcSheetName( szFileListKey, strProcName ) ;
  if( !bRet ) return FALSE;

  strModelPath = _T("C:\\work\\test\\naaa\\bテスト\\v3-denkyoku1-KSTM01-2.gmd");
  nStatus= m_pModelAPI->SaveModelFile( strModelPath );
  if ( API_NormalStatus != nStatus ){
    return FALSE;
  }

  CString strRetOrigin(_T(""));
  // 演算原点名称を返してもらって演算工程表を作成する時に反映する
  nStatus = m_pModelAPI->SetCamSettingCommnadToModel( 0, 0.1, 1, 0, 0.1, 0.05, strRetOrigin );

  CString strMessage(_T(""));
  strMessage.Format( _T("Origin : %s\n"), strRetOrigin );
  //AfxMessageBox( strMessage, MB_OK );

  nStatus= m_pModelAPI->SaveModelFile( strModelPath );
  if ( API_NormalStatus != nStatus ){
    return FALSE;
  }

  delete m_pModelAPI;
  m_pModelAPI = NULL;


  m_pCalcAPI = new CamCalc_API( strModelPath );
  if( !m_pCalcAPI ) return FALSE;

  strCalcKey = _T("");
  int nProcNum = -1;
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

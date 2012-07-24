// anotherone.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "anotherone.h"
#include "anotheroneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CanotheroneApp

BEGIN_MESSAGE_MAP(CanotheroneApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CanotheroneApp コンストラクション

CanotheroneApp::CanotheroneApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CanotheroneApp オブジェクトです。

CanotheroneApp theApp;

class CLEditCommandLineInfo : public CCommandLineInfo
{
	static int s_nArgIndex;
	static int s_nHwnd;
  static CString strModelPath;     // モデルファイルフルパス
  static CString strProcName;          // 工程表名
  static CString strOriginName;    // 演算原点名称
  static CString strSheetPath;     // 演算工程表フルパス
  static CString strTargetTemplate;

public:
	CLEditCommandLineInfo();
	~CLEditCommandLineInfo();

  static int GetHwnd(){ return s_nHwnd; }
  static CString GetModelPath();  //{ return strModelPath; }
  static CString GetProcName();   //{ return strProcName; }
  static CString GetOriginName(); //{ return strOriginName; }
  static CString GetSheetPath();  //{ return strSheetPath; }
  static CString GetTargetTemplate();
  //static std::wstring strModelPath;     // モデルファイルフルパス
  //static std::wstring strProcName;          // 工程表名
  //static std::wstring strOriginName;    // 演算原点名称
  //static std::wstring strSheetPath;     // 演算工程表フルパス

	virtual	void	ParseParam(LPCTSTR, BOOL, BOOL);
};

CLEditCommandLineInfo::CLEditCommandLineInfo()
{
	s_nArgIndex = 0;
  s_nHwnd = -1;
  strModelPath = L"";
  strProcName = L"";
  strOriginName = L"";
  strSheetPath = L"";
  strTargetTemplate = L"";
}

CLEditCommandLineInfo::~CLEditCommandLineInfo()
{
}

CString CLEditCommandLineInfo::GetModelPath(){ return strModelPath; }
CString CLEditCommandLineInfo::GetProcName(){ return strProcName; }
CString CLEditCommandLineInfo::GetOriginName(){ return strOriginName; }
CString CLEditCommandLineInfo::GetSheetPath(){ return strSheetPath; }
CString CLEditCommandLineInfo::GetTargetTemplate(){ return strTargetTemplate; }

void CLEditCommandLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
  try{
	  CCommandLineInfo::ParseParam(lpszParam,bFlag, bLast );

    TRACE(_T("command line param %d : %s\n"), s_nArgIndex, lpszParam);

    CStringW strParam(lpszParam);
    std::wstring strString(strParam);

    switch(s_nArgIndex) {
	  case 0:
      strModelPath = lpszParam/*strString*/;
      break;
    case 1:
      strProcName = lpszParam;
      break;
    case 2:
      strOriginName = lpszParam;
      break;
    case 3:
      strSheetPath = lpszParam;
      break;
    case 4:
      strTargetTemplate = lpszParam;
      break;
    default:
      break;
    }
  } catch ( ... ) {
    TRACE(_T("error."));
  }
	s_nArgIndex++;
}

int CLEditCommandLineInfo::s_nArgIndex = 0;
int CLEditCommandLineInfo::s_nHwnd = -1;
CString CLEditCommandLineInfo::strModelPath = _T("")/*L""*/;     // モデルファイルフルパス
CString CLEditCommandLineInfo::strProcName = _T("");          // 工程表名
CString CLEditCommandLineInfo::strOriginName = _T("");    // 演算原点名称
CString CLEditCommandLineInfo::strSheetPath = _T("");     // 演算工程表フルパス
CString CLEditCommandLineInfo::strTargetTemplate = _T("");     // 演算工程表フルパス

// CanotheroneApp 初期化

BOOL CanotheroneApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CLEditCommandLineInfo pCmdInfo;
	ParseCommandLine(pCmdInfo);

	INT_PTR nResponse = 0;
  CWnd* pCWnd = NULL;

  if( 0 < pCmdInfo.GetHwnd() ){
    pCWnd = CWnd::FromHandle( (HWND)pCmdInfo.GetHwnd() );
  	CanotheroneDlg dlg(pCWnd);
    dlg.setModelPath(pCmdInfo.GetModelPath());
    dlg.setProcName(pCmdInfo.GetProcName());
    dlg.setOriginName(pCmdInfo.GetOriginName());
    dlg.setSheetPath(pCmdInfo.GetSheetPath());
    dlg.setTargetTemplate(pCmdInfo.GetTargetTemplate());
	  m_pMainWnd = &dlg;
    nResponse = dlg.DoModal();
  } else {
  	CanotheroneDlg dlg(pCWnd);
    dlg.setModelPath(pCmdInfo.GetModelPath());
    dlg.setProcName(pCmdInfo.GetProcName());
    dlg.setOriginName(pCmdInfo.GetOriginName());
    dlg.setSheetPath(pCmdInfo.GetSheetPath());
    dlg.setTargetTemplate(pCmdInfo.GetTargetTemplate());
	  m_pMainWnd = &dlg;

    //AfxMessageBox(_T("before domodal"), MB_OK);

    nResponse = dlg.DoModal();
  }


	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

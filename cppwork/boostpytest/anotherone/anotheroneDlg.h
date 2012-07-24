// anotheroneDlg.h : ヘッダー ファイル
//

#pragma once

#include <afxmt.h>
#include "TAPI.h"
#include "ModelIO_API.h"
#include "CamCalc_API.h"

//テスト用の共有データ型 
typedef struct SharedData
{
  char m_mylineNo[256];
  char m_url[256];
  int m_Value;
  std::vector<CString> m_vecstrStatus;
  CString m_strStatus;
} SHARED_DATA;

// CanotheroneDlg ダイアログ
class CanotheroneDlg : public CDialog
{
// コンストラクション
public:
	CanotheroneDlg(CWnd* pParent = NULL);	// 標準コンストラクタ
  ~CanotheroneDlg();

// ダイアログ データ
	enum { IDD = IDD_ANOTHERONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

  LRESULT checkDoingStatus( int nType, WPARAM wParam, LPARAM lParam );
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

  ModelIO_API* m_pModelAPI;  // 演算工程表との間でデータの受け渡しを行う API
  CamCalc_API* m_pCalcAPI;  // 演算工程表との間でデータの受け渡しを行う API

  CString strModelPath;     // モデルファイルフルパス
  CString strProcName;          // 工程表名
  CString strOriginName;    // 演算原点名称
  CString strSheetPath;     // 演算工程表フルパス
  CString strTargetTemplate;  // gmtファイルフルパス
  CString strCalcKey;       // 演算工程表キー

// インプリメンテーション
protected:
	HANDLE m_hMapping;    // メモリマップドファイルのハンドル
	void *m_pMappingView; // ファイルのビューへのポインタ
	CMutex *m_pMutex;     // ミューテックスオブジェクト
  SharedData* m_sdata;  // テスト用構造体

public:
  BOOL DoCalculation();
  void disposeAllCalcObjects();

  void setModelPath( /*std::wstring*/LPCTSTR str ) {
    //CString str1( str.c_str() );
    strModelPath = /*str1*/str;
  }
  void setProcName( LPCTSTR str ) {
    //CString str1( str.c_str() );
    strProcName = str;
  }
  void setOriginName( LPCTSTR str ) {
    //CString str1( str.c_str() );
    strOriginName = str;
  }
  void setSheetPath( LPCTSTR str ) {
    //CString str1( str.c_str() );
    strSheetPath = str;
  }
  void setTargetTemplate( LPCTSTR str ) {
    //CString str1( str.c_str() );
    strTargetTemplate = str;
  }
};

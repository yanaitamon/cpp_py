// anotheroneDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include <afxmt.h>
#include "TAPI.h"
#include "ModelIO_API.h"
#include "CamCalc_API.h"

//�e�X�g�p�̋��L�f�[�^�^ 
typedef struct SharedData
{
  char m_mylineNo[256];
  char m_url[256];
  int m_Value;
  std::vector<CString> m_vecstrStatus;
  CString m_strStatus;
} SHARED_DATA;

// CanotheroneDlg �_�C�A���O
class CanotheroneDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CanotheroneDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^
  ~CanotheroneDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ANOTHERONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

  ModelIO_API* m_pModelAPI;  // ���Z�H���\�Ƃ̊ԂŃf�[�^�̎󂯓n�����s�� API
  CamCalc_API* m_pCalcAPI;  // ���Z�H���\�Ƃ̊ԂŃf�[�^�̎󂯓n�����s�� API

  CString strModelPath;     // ���f���t�@�C���t���p�X
  CString strProcName;          // �H���\��
  CString strOriginName;    // ���Z���_����
  CString strSheetPath;     // ���Z�H���\�t���p�X
  CString strTargetTemplate;  // gmt�t�@�C���t���p�X
  CString strCalcKey;       // ���Z�H���\�L�[

// �C���v�������e�[�V����
protected:
	HANDLE m_hMapping;    // �������}�b�v�h�t�@�C���̃n���h��
	void *m_pMappingView; // �t�@�C���̃r���[�ւ̃|�C���^
	CMutex *m_pMutex;     // �~���[�e�b�N�X�I�u�W�F�N�g
  SharedData* m_sdata;  // �e�X�g�p�\����

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

// anotherone.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
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


// CanotheroneApp �R���X�g���N�V����

CanotheroneApp::CanotheroneApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CanotheroneApp �I�u�W�F�N�g�ł��B

CanotheroneApp theApp;

class CLEditCommandLineInfo : public CCommandLineInfo
{
	static int s_nArgIndex;
	static int s_nHwnd;
  static CString strModelPath;     // ���f���t�@�C���t���p�X
  static CString strProcName;          // �H���\��
  static CString strOriginName;    // ���Z���_����
  static CString strSheetPath;     // ���Z�H���\�t���p�X
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
  //static std::wstring strModelPath;     // ���f���t�@�C���t���p�X
  //static std::wstring strProcName;          // �H���\��
  //static std::wstring strOriginName;    // ���Z���_����
  //static std::wstring strSheetPath;     // ���Z�H���\�t���p�X

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
CString CLEditCommandLineInfo::strModelPath = _T("")/*L""*/;     // ���f���t�@�C���t���p�X
CString CLEditCommandLineInfo::strProcName = _T("");          // �H���\��
CString CLEditCommandLineInfo::strOriginName = _T("");    // ���Z���_����
CString CLEditCommandLineInfo::strSheetPath = _T("");     // ���Z�H���\�t���p�X
CString CLEditCommandLineInfo::strTargetTemplate = _T("");     // ���Z�H���\�t���p�X

// CanotheroneApp ������

BOOL CanotheroneApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));

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
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <�L�����Z��> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}

	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	//  �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

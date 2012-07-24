// anotheroneDlg.cpp : �����t�@�C��
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

// CanotheroneDlg �_�C�A���O

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


// CanotheroneDlg ���b�Z�[�W �n���h��

BOOL CanotheroneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�


  CString szCommandLine( _T("") );
  CString sz( strModelPath );
  szCommandLine.Format( _T("C:\\Python27\\DLLs\\anotherone.exe\n model: \"%s\"\n proc: \"%s\"\n origin: \"%s\"\n sheetpath: \"%s\"\n template: \"%s\"\n")
                      , strModelPath, strProcName, strOriginName, strSheetPath, strTargetTemplate );

  //AfxMessageBox( szCommandLine, MB_OK );

	// TODO: �������������ɒǉ����܂��B
	// �������}�b�v�h�t�@�C���̐���
	m_hMapping = ::CreateFileMapping(
		(HANDLE)0xffffffff,     // ���L�������̏ꍇ��0xffffffff���w��
		NULL,                   // �Z�L�����e�B�����BNULL�ł悢
		PAGE_READWRITE,         // �v���e�N�g������ǂݏ����\�Ɏw��
		0,                      // �t�@�C���T�C�Y�̏��32�r�b�g
		1024,                   // �t�@�C���T�C�Y�̉���32�r�b�g
		_T("SharedMemory") );   // �������}�b�v�h�t�@�C���̖��O

	// �v���Z�X���̃A�h���X��ԂɃt�@�C���̃r���[���}�b�v
	//m_pMappingView = ::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData*));
  //m_sdata = new SharedData();
  LPVOID pMappingView = ::MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData*));
	m_sdata = reinterpret_cast<SharedData*>( pMappingView );

	// �~���[�e�b�N�X�I�u�W�F�N�g�̐���
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
                              dataSize+1, // new char[dataSize+1] �̐��ƍ��v����
                              wlocal,
                              dataSize+2 ); // ��4������+1

//ERROR_INSUFFICIENT_BUFFER
//ERROR_INVALID_FLAGS
//ERROR_INVALID_PARAMETER
//ERROR_NO_UNICODE_TRANSLATION

std::wstring iso = wlocal;
delete []buf;
delete []wlocal;



	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CanotheroneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CanotheroneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////
// ���Z��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnCLStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCLStatusNotify, wParam, lParam  ); }

// �œK����Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnOptStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComOptStatusNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnSolStatusNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComSolStatusNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnCamMessageNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComCamMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnCamNCNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComNCMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnCamFileNotify( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComFileMsgNotify, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
LRESULT CanotheroneDlg::OnCamRequestClDisp( WPARAM wParam, LPARAM lParam )
{ return checkDoingStatus( wmComRequestClDisp, wParam, lParam  ); }

// �H�H��Ԃ̃X�e�[�^�X���ς����
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
    TRACE(_T("�Ȃ񂩃G���[!"));
    return FALSE;
  }
  UpdateWindow();
  return TRUE;
}

LRESULT CanotheroneDlg::checkDoingStatus( int nType,  WPARAM wParam, LPARAM lParam )
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

  this->SetDlgItemText( IDC_STATIC1, strStatus );
  UpdateData(FALSE);

  //m_sdata->m_vecstrStatus.push_back(strStatus);
  m_sdata->m_strStatus = strStatus;

  // �����L�������֏������ށB���̂Ƃ��~���[�e�b�N�X�I�u�W�F�N�g��
	// �g�p���ē��������������Ȃ�
	m_pMutex->Lock(INFINITE);
	memcpy(m_pMappingView, m_sdata, sizeof(SharedData));
	m_pMutex->Unlock();

  return lRet;
}

// ���Z�J�n
BOOL CanotheroneDlg::DoCalculation()
{
  // �ݒ肪������Ή��Z���Ȃ�
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

  // �X�e�[�^�X
  int nStatus = static_cast<int>(API_NormalStatus);

  m_pModelAPI = new ModelIO_API( strModelPath, false );
  if( !m_pModelAPI ) return FALSE;
  // if ���������� API�Ŋ��t ���Z�ΏۂƂ��ċL��
  // �e���v���[�g�t�@�C�����J���B
  CString szTemplateKey = _T("");
  bool bRet = m_pModelAPI->SetTemplate( strTargetTemplate, szTemplateKey );  // ����I�����̖߂�l�̓e���v���[�g�t�@�C�������ʂ��� Id
  if( !bRet ) return FALSE;

  CString szFileListKey = _T("");
  // ��3�����̃v���t�@�C�����X�g����NULL�œn���ƑS���o�^
  bRet = m_pModelAPI->ImportTemplateProfileList( szTemplateKey, szFileListKey );
  if( !bRet ) return FALSE;

  // ��œo�^�����v���t�@�C���Q���e���v���[�g���Ń��X�g�ɂ܂Ƃ߂�
  bRet = m_pModelAPI->SetCalcSheetName( szFileListKey, strProcName ) ;
  if( !bRet ) return FALSE;

  strModelPath = _T("C:\\work\\test\\naaa\\b�e�X�g\\v3-denkyoku1-KSTM01-2.gmd");
  nStatus= m_pModelAPI->SaveModelFile( strModelPath );
  if ( API_NormalStatus != nStatus ){
    return FALSE;
  }

  CString strRetOrigin(_T(""));
  // ���Z���_���̂�Ԃ��Ă�����ĉ��Z�H���\���쐬���鎞�ɔ��f����
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

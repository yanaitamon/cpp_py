// anotherone.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CanotheroneApp:
// ���̃N���X�̎����ɂ��ẮAanotherone.cpp ���Q�Ƃ��Ă��������B
//

class CanotheroneApp : public CWinApp
{
public:
	CanotheroneApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CanotheroneApp theApp;
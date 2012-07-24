// anotherone.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CanotheroneApp:
// このクラスの実装については、anotherone.cpp を参照してください。
//

class CanotheroneApp : public CWinApp
{
public:
	CanotheroneApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CanotheroneApp theApp;
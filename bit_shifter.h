// 
// bit_shifter.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы

#include "bit_switcher.h"

// CApp:
// Сведения о реализации этого класса: bit_shifter.cpp
//

class CApp : public CWinApp
{
public:
	CApp();

	BitSwitcher& GetBitSwitcher() { return bitSwitcher; }

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()

	BitSwitcher bitSwitcher;
};

extern CApp theApp;

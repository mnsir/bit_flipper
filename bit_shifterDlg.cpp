
// bit_shifterDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "bit_shifter.h"
#include "bit_shifterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAppDlg

BEGIN_DHTML_EVENT_MAP(CAppDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("cb"), OnCheckBox)
END_DHTML_EVENT_MAP()


CAppDlg::CAppDlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_BIT_SHIFTER_DIALOG, IDR_HTML_BIT_SHIFTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAppDlg, CDHtmlDialog)
END_MESSAGE_MAP()


// Обработчики сообщений CAppDlg

BOOL CAppDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CAppDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CAppDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

HRESULT CAppDlg::OnCheckBox(IHTMLElement* pElement)
{
	// получаем аттрибут чекбокса нажат/не нажат
	CComVariant var;
	if (SUCCEEDED(pElement->getAttribute(CComBSTR(_T("checked")), 0/*- BOOL, 2 - BSTR*/, &var)) &&
		var.vt == VARENUM::VT_BOOL)
	{
		// получить номер под чекбоксом (см. HTML)
		// для этого нужно получить текст родителя
		CComPtr<IHTMLElement> pParent;
		if (S_OK == pElement->get_parentElement(&pParent))
		{
			CComBSTR bstrPos;
			if (S_OK == pParent->get_innerText(&bstrPos)) // номер
			{
				// вызвать модель и положить туда новое значение бита value в позицию pos
				auto& bs = theApp.GetBitSwitcher();
				bs.SetBit(static_cast<size_t>(_ttoi((LPCTSTR)bstrPos)), // перевести BSTR в size_t
						  var.boolVal == VARIANT_TRUE);					// перевести VARIANT_BOOL в bool

				SetElementText(_T("debug_info"), CComBSTR(bs.DebugInfo().c_str()));
				CString sDouble;
				sDouble.Format(L"%f", bs.GetDouble());
				SetElementText(_T("double"), CComBSTR(sDouble));
				sDouble.Format(L"%f", bs.GetFloat1());
				SetElementText(_T("float1"), CComBSTR(sDouble));
				sDouble.Format(L"%f", bs.GetFloat0());
				SetElementText(_T("float0"), CComBSTR(sDouble));
				//AfxMessageBox(CA2T(bs.DebugInfo().c_str()));

				return S_OK;
			}
		}
	}
}

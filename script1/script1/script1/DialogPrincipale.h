#pragma once
#include "Resource.h"		// main symbols
#include "afxwin.h"

// finestra di dialogo DialogPrincipale

class DialogPrincipale : public CDialog
{
	DECLARE_DYNAMIC(DialogPrincipale)

public:
	DialogPrincipale(CWnd* pParent = NULL);   // costruttore standard
	virtual ~DialogPrincipale();

// Dati della finestra di dialogo
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Supporto DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CButton disassata;
	afx_msg void OnBnClickedCancel();
	int opzione2;
	afx_msg void OnBnClickedRadio4();
};

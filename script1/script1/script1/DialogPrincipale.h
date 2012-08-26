#pragma once
#include "Resource.h"		// main symbols
#include "afxwin.h"

// finestra di dialogo DialogPrincipale

class DialogPrincipale : public CDialog
{
	DECLARE_DYNAMIC(DialogPrincipale)

public:
	DialogPrincipale(CWnd* pParent);   // costruttore standard, MODIFICATO nello!
	virtual ~DialogPrincipale();

// Dati della finestra di dialogo
	enum { IDD = IDD_DIALOG1 };

	//void SetPointValue( int item, const ON_3dPoint& pt );
	void KillDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Supporto DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedCancel();
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit2();

	
	// valore disassamento. inseriti il valore massimo e minimo.
	int ValoreDisassamento;
};

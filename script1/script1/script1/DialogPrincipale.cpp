// DialogPrincipale.cpp : file di implementazione
//

#include "stdafx.h"
#include "DialogPrincipale.h"
#include "Resource.h"


// finestra di dialogo DialogPrincipale

IMPLEMENT_DYNAMIC(DialogPrincipale, CDialog)

DialogPrincipale::DialogPrincipale(CWnd* pParent)
	: CRhinoDialog(DialogPrincipale::IDD, pParent)  
	, VAR_Valore_Disassamento(0) 
	, VAR_Altezza_Tacco(_T("140"))
	, StatusRadio1_Centrale(0)
	, StatusRadio3_Iniezione_Centrale(0)
	, StatusRadio7_Fondello_di_ferro(0)
	, ValIniezioneDisassamento(_T("+12"))
	, ValoreAltezzaFondello(_T("20"))
{
}

DialogPrincipale::~DialogPrincipale()
{
}

void DialogPrincipale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, VAR_Valore_Disassamento);
	DDV_MinMaxInt(pDX, VAR_Valore_Disassamento, -12, +12);
	DDX_CBString(pDX, IDC_CMBAltezzaTacco, VAR_Altezza_Tacco);
	DDX_Control(pDX, IDC_CMBAltezzaTacco, m_comboAltTacco);
	DDX_Radio(pDX, IDC_RADIO1, StatusRadio1_Centrale);
	DDX_Radio(pDX, IDC_RADIO2, StatusRadio2_Dissasata);
	DDX_Radio(pDX, IDC_RADIO3, StatusRadio3_Iniezione_Centrale);
	DDX_Radio(pDX, IDC_RADIO4, StatusRadio4_Iniezione_Disassata);
	DDX_Radio(pDX, IDC_RADIO7, StatusRadio7_Fondello_di_ferro);
	DDX_Radio(pDX, IDC_RADIO8, StatusRadio8_Fondello_di_alluminio);
	DDX_CBString(pDX, IDC_COMBO1, ValIniezioneDisassamento);
	DDX_CBString(pDX, IDC_COMBO5, ValoreAltezzaFondello);
	DDX_Control(pDX, IDC_CHECK1, StatusCheckTaccoSpina);
}


BEGIN_MESSAGE_MAP(DialogPrincipale, CDialog)
	ON_BN_CLICKED(IDCANCEL, &DialogPrincipale::OnBnClickedCancel)	
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogPrincipale::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO5, &DialogPrincipale::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogPrincipale::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &DialogPrincipale::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDIT2, &DialogPrincipale::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &DialogPrincipale::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT3, &DialogPrincipale::OnEnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_CMBAltezzaTacco, &DialogPrincipale::OnCbnSelchangeCmbaltezzatacco)
	ON_BN_CLICKED(IDC_RADIO3, &DialogPrincipale::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO1, &DialogPrincipale::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO7, &DialogPrincipale::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO2, &DialogPrincipale::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &DialogPrincipale::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO8, &DialogPrincipale::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_CHECK1, &DialogPrincipale::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_RICHEDIT21, &DialogPrincipale::OnEnChangeRichedit21)
END_MESSAGE_MAP()


// gestori di messaggi DialogPrincipale

void DialogPrincipale::OnBnClickedCancel()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	OnCancel();
}



void DialogPrincipale::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnCbnSelchangeCombo5()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedButton1()
{	
	
	 RhinoApp().RunScript( L"! _GenPianoVis", 0 );

 
}/*CHIUSURA DIALOGPRINCIPALE::ONBNCLICKEDBUTTON1*/

void DialogPrincipale::OnCbnSelchangeCombo2()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnEnChangeEdit2()
{
	UpdateData (TRUE);
	// TODO:  Se si tratta di un controllo RICHEDIT, il controllo non
	// invierà questa notifica a meno che non si esegua l'override della funzione CDialog::OnInitDialog()
	// e venga eseguita la chiamata a CRichEditCtrl().SetEventMask()
	// con il flag ENM_CHANGE introdotto dall'operatore OR nella maschera.

	// TODO:  Aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::KillDialog()
{
  OnCancel();
}
void DialogPrincipale::OnBnClickedOk()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	OnOK();
}

void DialogPrincipale::OnEnChangeEdit3()
{
	// TODO:  Se si tratta di un controllo RICHEDIT, il controllo non
	// invierà questa notifica a meno che non si esegua l'override della funzione CRhinoDialog::OnInitDialog()
	// e venga eseguita la chiamata a CRichEditCtrl().SetEventMask()
	// con il flag ENM_CHANGE introdotto dall'operatore OR nella maschera.

	// TODO:  Aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnCbnSelchangeCmbaltezzatacco()
{
	UpdateData(true);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio3()
{
	UpdateData (TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio1()
{	
	UpdateData (TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	StatusRadio7_Fondello_di_ferro = 0;
	StatusRadio8_Fondello_di_alluminio = -1;
	UpdateData (FALSE);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio7()
{
	UpdateData (TRUE);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio2()
{
	UpdateData (TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	StatusRadio8_Fondello_di_alluminio = 0;
	StatusRadio7_Fondello_di_ferro = -1;
	UpdateData (FALSE);

	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio4()
{
	UpdateData (TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedRadio8()
{
	UpdateData (TRUE);
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedCheck1()
{
	if (CWnd::IsDlgButtonChecked(IDC_CHECK1) ) {
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	}
	else {
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	}

	
	

	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnEnChangeRichedit21()
{
	// TODO:  Se si tratta di un controllo RICHEDIT, il controllo non
	// invierà questa notifica a meno che non si esegua l'override della funzione CRhinoDialog::OnInitDialog()
	// e venga eseguita la chiamata a CRichEditCtrl().SetEventMask()
	// con il flag ENM_CHANGE introdotto dall'operatore OR nella maschera.

	// TODO:  Aggiungere qui il codice per la gestione della notifica del controllo.
}

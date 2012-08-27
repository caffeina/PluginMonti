// DialogPrincipale.cpp : file di implementazione
//

#include "stdafx.h"
#include "DialogPrincipale.h"


// finestra di dialogo DialogPrincipale

IMPLEMENT_DYNAMIC(DialogPrincipale, CDialog)

DialogPrincipale::DialogPrincipale(CWnd* pParent, CRhinoDoc& doc)
	: CDialog(DialogPrincipale::IDD, pParent)
	, ValoreDisassamento(0),
	m_doc(doc)
{
}

DialogPrincipale::~DialogPrincipale()
{
}

void DialogPrincipale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Text(pDX, IDC_EDIT2, ValoreDisassamento);
	DDV_MinMaxInt(pDX, ValoreDisassamento, -12, +12);
}


BEGIN_MESSAGE_MAP(DialogPrincipale, CDialog)
	ON_BN_CLICKED(IDCANCEL, &DialogPrincipale::OnBnClickedCancel)
	
	ON_CBN_SELCHANGE(IDC_COMBO1, &DialogPrincipale::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO5, &DialogPrincipale::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogPrincipale::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &DialogPrincipale::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDIT2, &DialogPrincipale::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &DialogPrincipale::OnBnClickedOk)
END_MESSAGE_MAP()


// gestori di messaggi DialogPrincipale

void DialogPrincipale::OnBnClickedCancel()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
	OnCancel();
}



void DialogPrincipale::OnCbnSelchangeCombo1()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnCbnSelchangeCombo5()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnBnClickedButton1()
{
  /*GET THE LAYER NAME*/
  CRhinoGetString gs;
  gs.SetCommandPrompt( L"NAME OF LAYER WHICH CONTAINS VISIONAL PLANE :" );
  gs.GetString();
  if( gs.CommandResult() != CRhinoCommand::success )
  {
	  exit(-1);
  }
  /*VALIDATE THE STRING*/
  ON_wString layer_name = gs.String();
  layer_name.TrimLeftAndRight();
  if( layer_name.IsEmpty() )
  {
	  exit(-1);
  }
    
  /*GET A REFERENCE TO THE LAYER TABLE*/
  CRhinoLayerTable& layer_table = m_doc.m_layer_table;
 
  /*FIND THE LAYER*/ 
  int layer_index = layer_table.FindLayer(layer_name );
  if( layer_index < 0 )
  {
    RhinoApp().Print( L"LAYER \"%s\" DOES NOT EXIST.\n", layer_name );
  }
  else
  {
	  ON_Layer currentLayer;
	  int numLayers = layer_table.LayerCount();
	  layer_table.SetCurrentLayerIndex(layer_index);
	  for(int i = 0; i < numLayers; i++)
	  {
		  if(i != layer_index)
		  {
			  currentLayer = layer_table[i];
			  currentLayer.SetVisible(false);
			  layer_table.ModifyLayer(currentLayer, i);
		  }
	  }
	  m_doc.Redraw();
	  const CRhinoLayer& layer = m_doc.m_layer_table[layer_index];
	  ON_SimpleArray<CRhinoObject*> obj_list;

      int object_count = m_doc.LookupObject( layer, obj_list );
      if( object_count > 0 )
      {
	  
		//CRhinoGetObject go;
		//go.SetCommandPrompt( L"SELECT OBJECT LINE" );
		//CRhinoGet::result res = go.GetObjects( 1, 1 );
		//if( res == CRhinoGet::object )
		//{
		//  const CRhinoObjRef& obj_ref = go.Object( 0 );
		//  const CRhinoObject* obj = obj_ref.Object();
		//  if( obj )
		//  {
			  int R = 0;
		//	// TODO
		//  }
		//}

		  /*SELECT ALL OF THE LAYER OBJECTS*/ 
		 // for(int i = 0; i < object_count; i++ )
		 // {
			//CRhinoObject* obj = obj_list[i];
			//if( obj && obj->IsSelectable() )
			//  obj->Select();
		 // }
	  }/*CHIUSURA IF( OBJECT_COUNT > 0 )*/
	int R = 0;
  }
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnCbnSelchangeCombo2()
{
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}

void DialogPrincipale::OnEnChangeEdit2()
{
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

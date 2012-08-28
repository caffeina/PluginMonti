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
		 /********************************************************************/
		 //CRhinoObject* obj = obj_list[0];
		 //if( obj && obj->IsSelectable() )
		 //{
			// obj->Select(true);
			// obj->Highlight(true);
			// m_doc.Redraw();
		 //}
		 /********************************************************************/
		 CRhinoGetObject gc;
		 gc.SetCommandPrompt( L"Select line to extend" );
         gc.SetGeometryFilter( CRhinoGetObject::curve_object );
         gc.GetObjects( 1, 1 );
		 if(gc.CommandResult() == CRhinoCommand::success )
		 {
			const CRhinoObjRef& objref = gc.Object(0);
            const ON_Curve* pC = ON_Curve::Cast( objref.Geometry() );
			ON_Curve* crv0 = pC->DuplicateCurve();
			ON_Curve* crv1 = pC->DuplicateCurve();
			bool rc0 = RhinoExtendCurve(crv0, CRhinoExtend::Line, 1, 5);
			bool rc1 = RhinoExtendCurve(crv0, CRhinoExtend::Line, 0, 15);
			m_doc.ReplaceObject(objref, *crv0 );
            m_doc.Redraw();
			
			ON_3dPoint p0 = crv0->PointAtStart();
            ON_3dPoint p1 = crv0->PointAtEnd();

			gc.SetCommandPrompt( L"ENTRY ANTERIOR ANGLE EXTENSION (ALPHA=30°):" );
			gc.get_string;
			ON_wString alphaAngle = gc.String();
			//CRhinoGetObject gc;
			gc.SetCommandPrompt( L"ENTRY ANTERIOR EXTENSION LENGTH(L=80mm):" );
			gc.get_string;
			ON_wString antLength = gc.String();

			//CRhinoGetObject gc;
			gc.SetCommandPrompt( L"ENTRY POSTERIOR ANGLE EXTENSION (BETA=ALPHA+10°):" );
			gc.get_string;
			ON_wString betaAngle = gc.String();
			//CRhinoGetObject gc;
			gc.SetCommandPrompt( L"ENTRY POSTERIOR EXTENSION LENGTH(L=80mm):" );
			gc.get_string;
			ON_wString posLength = gc.String();



			/*CLEAN UP OR LEAK*/ 
			delete crv0;
			crv0 = 0;
			int R = 0;
	     }
	  }/*CHIUSURA IF( OBJECT_COUNT > 0 )*/
  }/*CHIUSURA ELSE*/
	// TODO: aggiungere qui il codice per la gestione della notifica del controllo.
}/*CHIUSURA DIALOGPRINCIPALE::ONBNCLICKEDBUTTON1*/

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

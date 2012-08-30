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
  gs.SetCommandPrompt( L"NAME OF LAYER WHICH CONTAINS VISIONAL PLANE : " );
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
		 gc.SetCommandPrompt( L"SELECT LINE TO EXTEND" );
         gc.SetGeometryFilter( CRhinoGetObject::curve_object );
         gc.GetObjects( 1, 1 );
		 if(gc.CommandResult() == CRhinoCommand::success )
		 {
			const CRhinoObjRef& objref = gc.Object(0);
            const ON_Curve* pC = ON_Curve::Cast( objref.Geometry() );
			ON_Curve* crv0 = pC->DuplicateCurve();
			bool rc0 = RhinoExtendCurve(crv0, CRhinoExtend::Line, 1, 5);
			bool rc1 = RhinoExtendCurve(crv0, CRhinoExtend::Line, 0, 15);
			m_doc.ReplaceObject(objref, *crv0 );
            m_doc.Redraw();
			
			ON_3dPoint p0 = crv0->PointAtStart();
            ON_3dPoint p1 = crv0->PointAtEnd();
 
			CRhinoGetNumber gn;
			gn.SetCommandPrompt( L"ENTER ANTERIOR ANGLE FOR EXTENSION : " );
			gn.SetCommandPromptDefault(L"30°");
			gn.GetNumber();
			double alphaAngle = gn.Number();

			gn.SetCommandPrompt( L"ENTER ANTERIOR LENGTH FOR EXTENSION : " );
			gn.SetCommandPromptDefault(L"80mm");
			gn.GetNumber();
			double antLen = gn.Number();

			gn.SetCommandPrompt( L"ENTER ANTERIOR FILLET RADIUS : " );
			gn.SetCommandPromptDefault(L"6mm");
			gn.GetNumber();
			double antRad = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR ANGLE FOR EXTENSION : " );
			gn.SetCommandPromptDefault(L"ALPHA + 10°");
			gn.GetNumber();
			double betaAngle = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR LENGTH FOR EXTENSION : " );
			gn.SetCommandPromptDefault(L"80mm");
			gn.GetNumber();
			double posLen = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR FILLET RADIUS : " );
			gn.SetCommandPromptDefault(L"13mm");
			gn.GetNumber();
			double posRad = gn.Number();

		
			ON_3dPoint pointStart;
            ON_3dPoint pointEnd;
		 
			//// Fillet radius
			//double radius = 1.0;
		 
			// Do the fillet calculation
			double t0 = 0.0, t1 = 0.0;
 
			ON_Plane plane;
			plane.plane_equation.y = 1.0;

			pointStart = crv0->PointAtStart();
			
			pointEnd   = crv0->PointAtEnd();

			ON_3dPoint point0((pointStart.x - posLen*cos(betaAngle*acos(-1.0)/180.0)), 0.0, (pointStart.z + posLen*sin(betaAngle*acos(-1.0)/180.0)));
			ON_3dPoint point1((pointEnd.x + antLen*cos(alphaAngle*acos(-1.0)/180.0)), 0.0, (pointEnd.z - antLen*sin(alphaAngle*acos(-1.0)/180.0)));


			//double len = sqrt((pointStart.x - pointEnd.x)*(pointStart.x - pointEnd.x) + 
			//	              (pointStart.y - pointEnd.y)*(pointStart.y - pointEnd.y) + 
			//				  (pointStart.z - pointEnd.z)*(pointStart.z - pointEnd.z));


			/*CREATE THE LINE CURVES TO FILLET*/ 
			ON_LineCurve curve0( pointStart, point0 );
			ON_LineCurve curve1( point1, pointEnd );

			// Fillet at the end points of the line curves
			double curve0_t = crv0->Domain().Max();
			double curve1_t = curve1.Domain().Max();


			if( RhinoGetFilletPoints(curve1,  *crv0, antRad, curve0_t, curve1_t, t0, t1, plane) )
			{
				// Trim back the two line curves
				ON_Interval domain0( curve1.Domain().Max(), t0 );
				curve1.Trim( domain0 );
		 
				ON_Interval domain1( crv0->Domain().Max(), t1 );
				crv0->Trim( domain1 );
		 
				// Compute the fillet curve
				ON_3dVector radial0 = curve1.PointAt(t0) - plane.Origin();
				radial0.Unitize();
		 
				ON_3dVector radial1 = crv0->PointAt(t1) - plane.Origin();
				radial1.Unitize();
		 
				double angle = acos( radial0 * radial1 );
				ON_Plane fillet_plane( plane.Origin(), radial0, radial1 );
				ON_Arc fillet( fillet_plane, plane.Origin(), antRad, angle );
		 
				/*ADD THE GEOMETRY*/ 
				m_doc.AddCurveObject( curve1 );
				m_doc.ReplaceObject(objref, *crv0 );
				m_doc.AddCurveObject( fillet );
				m_doc.Redraw();
			}

			//t0 = 0.0, t1 = 0.0;
			///*FILLET AT THE END POINTS OF THE LINE CURVES*/
			//curve0_t = crv0->Domain().Max();
			//curve1_t = curve0.Domain().Min();

			//if( RhinoGetFilletPoints(curve0, *crv0, antRad, curve0_t, curve1_t, t0, t1, plane) )
			//{
			//	// Trim back the two line curves
			//	ON_Interval domain0( curve0.Domain().Min(), t0 );
			//	curve0.Trim( domain0 );
		 //
			//	ON_Interval domain1( crv0->Domain().Max(), t1 );
			//	crv0->Trim( domain1 );
		 //
			//	// Compute the fillet curve
			//	ON_3dVector radial0 = curve0.PointAt(t0) - plane.Origin();
			//	radial0.Unitize();
		 //
			//	ON_3dVector radial1 = crv0->PointAt(t1) - plane.Origin();
			//	radial1.Unitize();
		 //
			//	double angle = acos( radial0 * radial1 );
			//	ON_Plane fillet_plane( plane.Origin(), radial0, radial1 );
			//	ON_Arc fillet( fillet_plane, plane.Origin(), antRad, angle );
		 //
			//	/*ADD THE GEOMETRY*/ 
			//	m_doc.AddCurveObject( curve0 );
			//	m_doc.ReplaceObject(objref, *crv0 );
			//	m_doc.AddCurveObject( fillet );
			//	m_doc.Redraw();
			//}

			m_doc.AddCurveObject( curve0 );
			m_doc.Redraw();

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

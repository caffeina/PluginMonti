/////////////////////////////////////////////////////////////////////////////
// cmdscript1.cpp : command file
// 

#include "stdafx.h"
#include "script1PlugIn.h"
#include "DialogPrincipale.h"
#include "afxwin.h"
#include "script1App.h"


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN script1 command
//

// Do NOT put the definition of class CCommandscript1 in a header
// file.  There is only ONE instance of a CCommandscript1 class
// and that instance is the static thescript1Command that appears
// immediately below the class definition.

class CCommandscript1 : public CRhinoCommand
{
public:
  // The one and only instance of CCommandscript1 is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandscript1::CCommandscript1()
  // is called exactly once when static thescript1Command is created.
	CCommandscript1() {}

  // CCommandscript1::~CCommandscript1()
  // is called exactly once when static thescript1Command is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandscript1() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		// {E9A6EA80-C645-4996-888E-D0070191CA83}
    static const GUID script1Command_UUID =
    { 0xE9A6EA80, 0xC645, 0x4996, { 0x88, 0x8E, 0xD0, 0x7, 0x1, 0x91, 0xCA, 0x83 } };
    return script1Command_UUID;
	}

  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"script1"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"script1"; }

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandscript1 object.  
// Do NOT create any other instance of a CCommandscript1 class.
static class CCommandscript1 thescript1Command;

CRhinoCommand::result CCommandscript1::RunCommand( const CRhinoCommandContext& context )
{
  // CCommandscript1::RunCommand() is called when the user runs the "script1"
  // command or the "script1" command is run by a history operation.

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or scriptable interface.

  Cscript1PlugIn& plugin = script1PlugIn();

  bool bVisible = plugin.IsDlgVisible();

  if( context.IsInteractive() )
  {
    if( false == bVisible )
		plugin.DisplayDlg(); // tolto come parametro context.m_doc
  }

  return CRhinoCommand::success;
}

//
// END script1 command
//IT WORKS FINE!
//IT WORKS FINE2!
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN new command
//
class CGenPianoVis : public CRhinoTestCommand
{
public:
  // The one and only instance of CCommandscript1 is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandscript1::CCommandscript1()
  // is called exactly once when static thescript1Command is created.
	CGenPianoVis() {}

  // CCommandscript1::~CCommandscript1()
  // is called exactly once when static thescript1Command is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CGenPianoVis() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		
static const GUID CGenPianoVisCommand_UUID = 
{ 0xc80ef0d2, 0xbe2f, 0x48c0, { 0x84, 0x56, 0x55, 0xd5, 0x75, 0x92, 0x3f, 0x25 } };
	return CGenPianoVisCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GenPianoVis"; }
	const wchar_t* LocalCommandName() { return L"GenPianoVis"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

static class CGenPianoVis theGenPianoVisCommand;
CRhinoCommand::result CGenPianoVis::RunCommand( const CRhinoCommandContext& context )
{

	
	////////////////////////
  /*GET THE LAYER NAME*/
  CRhinoGetString gs;
  gs.SetCommandPrompt( L"NAME OF LAYER WHICH CONTAINS VISIONAL PLANE : " );
  gs.GetString();
  if( gs.CommandResult() != CRhinoCommand::success )
  {
	  return gs.CommandResult();
  }
  /*VALIDATE THE STRING*/
  ON_wString layer_name = gs.String();
  layer_name.TrimLeftAndRight();
  if( layer_name.IsEmpty() )
  {
	  return CRhinoCommand::cancel;
  }
    
  /*GET A REFERENCE TO THE LAYER TABLE*/
  CRhinoLayerTable& layer_table = context.m_doc.m_layer_table;
 
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
	  context.m_doc.Redraw();
	  const CRhinoLayer& layer = context.m_doc.m_layer_table[layer_index];
	  ON_SimpleArray<CRhinoObject*> obj_list;

	 
	  
      int object_count = context.m_doc.LookupObject( layer, obj_list );
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
		 //aniello gegin
		 // Disable redrawing
		 //CRhinoView::EnableDrawing( FALSE ); meglio tenerlo disabilitato altrimenti la schermata non si aggiorna.
 
         // Get the next runtime object serial number before scripting
		 unsigned int first_sn = CRhinoObject::NextRuntimeObjectSerialNumber();
	     //aniello end
	     /////////////////////
		  
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
			context.m_doc.ReplaceObject(objref, *crv0 );
            context.m_doc.Redraw();

			
			ON_3dPoint p0 = crv0->PointAtStart();
            ON_3dPoint p1 = crv0->PointAtEnd();
 
			CRhinoGetNumber gn;
			//double default_value = 30;
			gn.SetCommandPrompt( L"ENTER ANTERIOR ANGLE FOR EXTENSION in grad: " );
			gn.SetCommandPromptDefault(L"30");
			gn.SetDefaultNumber(30);
			//gn.AcceptNothing(true);
			gn.GetNumber();
			double alphaAngle = gn.Number();
			
			

			gn.SetCommandPrompt( L"ENTER ANTERIOR LENGTH FOR EXTENSION in mm: " );
			gn.SetCommandPromptDefault(L"80");
			gn.SetDefaultNumber(80);
			gn.GetNumber();
			double antLen = gn.Number();

			gn.SetCommandPrompt( L"ENTER ANTERIOR FILLET RADIUS in mm: " );
			gn.SetCommandPromptDefault(L"6");
			gn.SetDefaultNumber(6);
			gn.GetNumber();
			double antRad = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR ANGLE FOR EXTENSION default <ALPHA + 10°= 40°> : " );
			gn.SetCommandPromptDefault(L"40");
			gn.SetDefaultNumber(40);
			gn.GetNumber();
			double betaAngle = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR LENGTH FOR EXTENSION in mm: " );
			gn.SetCommandPromptDefault(L"80");
			gn.SetDefaultNumber(80);
			gn.GetNumber();
			double posLen = gn.Number();

			gn.SetCommandPrompt( L"ENTER POSTERIOR FILLET RADIUS in mm: " );
			gn.SetCommandPromptDefault(L"13");
			gn.SetDefaultNumber(13);
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
			ON_LineCurve curve0( pointStart, point0 ); //LINEA A SINISTRA IN FRONT VIEW
			ON_LineCurve curve1( point1, pointEnd );   //LINEA A DESTRA IN FRONT VIEW 

			
			
			/*FILLET AT THE END/START POINTS OF THE LINE CURVES*/ 
			double curve0_t = crv0->Domain().Max();
			double curve1_t = curve1.Domain().Min();
			
			
			
			if( RhinoGetFilletPoints(curve1,  *crv0, antRad, curve1_t, curve0_t, t1, t0, plane) )
			{
				/*TRIM BACK THE TWO LINE CURVES*/ 
				ON_Interval domain1( curve1.Domain().Min(), t1 );
				curve1.Trim( domain1 );
		 
				ON_Interval domain0( crv0->Domain().Min(), t0 );
				crv0->Trim( domain0 );
		 
				/*COMPUTE THE FILLET CURVE*/ 
				ON_3dVector radial0 = curve1.PointAt(t1) - plane.Origin();
				radial0.Unitize();
		 
				ON_3dVector radial1 = crv0->PointAt(t0) - plane.Origin();
				radial1.Unitize();
		 
				double angle = acos( radial0 * radial1 );
				ON_Plane fillet_plane( plane.Origin(), radial0, radial1 );
				ON_Arc fillet( fillet_plane, plane.Origin(), antRad, angle );
		 
				//ADD THE GEOMETRY
				context.m_doc.AddCurveObject( curve1 );
				context.m_doc.ReplaceObject(objref, *crv0 );
				context.m_doc.AddCurveObject( fillet );
				context.m_doc.Redraw();
			}
			

			t0 = 0.0, t1 = 0.0;
			/*FILLET AT THE START POINTS OF THE LINE CURVES*/
			curve0_t = crv0->Domain().Min();
			curve1_t = curve0.Domain().Min();

			if( RhinoGetFilletPoints(curve0, *crv0, posRad, curve1_t, curve0_t, t1, t0, plane) )
			{
				// Trim back the two line curves
				ON_Interval domain0( t1, curve0.Domain().Max() );
				curve0.Trim( domain0 );
		 
				ON_Interval domain1( t0, crv0->Domain().Max() );
				crv0->Trim( domain1 );
				

				/*COMPUTE THE FILLET CURVE*/ 
				ON_3dVector radial0 = curve0.PointAt(t1) - plane.Origin();
				radial0.Unitize();
		 
				ON_3dVector radial1 = crv0->PointAt(t0) - plane.Origin();
				radial1.Unitize();
		 
				double angle = acos( radial0 * radial1 );
				ON_Plane fillet_plane( plane.Origin(), radial0, radial1 );
				ON_Arc fillet( fillet_plane, plane.Origin(), posRad, angle );
		 
				/*ADD THE GEOMETRY*/ 
				context.m_doc.AddCurveObject( curve0 );
				context.m_doc.ReplaceObject(objref, *crv0 );
				context.m_doc.AddCurveObject( fillet );
				context.m_doc.Redraw();
			}
			/*CLEAN UP OR LEAK*/ 
			delete crv0;
			crv0 = 0;

			/*JOIN LINES TOGETHER*/
			CRhinoGetObject go;
			go.SetCommandPrompt( L"Select objects to group" );
			go.EnableGroupSelect();
			go.GetObjects(1,0);
			if( go.CommandResult() != CRhinoCommand::success )
			{
				return go.CommandResult();
			}
			 
			int i = 0, count = go.ObjectCount();
			ON_SimpleArray<const CRhinoObject*> members( count );
			 
			for( i = 0; i < count; i++ )
			{
				members.Append( go.Object(i).Object() );
			}
			 
			int index = context.m_doc.m_group_table.AddGroup( ON_Group(), members );
			context.m_doc.Redraw();
			//return (index >= 0) ? CRhinoCommand::success : CRhinoCommand::failure;

			ON_3dPoint center_point( 0.0, 0.0, 0.0 );
			double radius = 63.5;
			ON_3dPoint height_point( 0.0, 0.0, 140.0 );
			ON_3dVector zaxis = height_point - center_point;
			ON_Plane planeCir( center_point, zaxis );

			/*ADD CIRCLE FOR CYLINDER'S BASE*/
			ON_Circle circle( planeCir, radius );

			/*ADD CYLINDER*/
			ON_Cylinder cylinder( circle, zaxis.Length() );
			ON_Brep* brep = ON_BrepCylinder( cylinder, TRUE, TRUE );
			if( brep )
			{
				CRhinoBrepObject* cylinder_object = new CRhinoBrepObject();
				cylinder_object->SetBrep( brep );
				if( context.m_doc.AddObject(cylinder_object) )
				{
					context.m_doc.Redraw();
				}
				else
				{
					delete cylinder_object;
				}
			}

			

	     }
	  }/*CHIUSURA IF( OBJECT_COUNT > 0 )*/
  }/*CHIUSURA ELSE*/

  return CRhinoCommand::success;
}
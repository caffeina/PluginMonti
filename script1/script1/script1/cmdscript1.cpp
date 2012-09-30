/////////////////////////////////////////////////////////////////////////////
// cmdscript1.cpp : command file
// 

#include "stdafx.h"
#include "script1PlugIn.h"
#include "DialogPrincipale.h"
#include "afxwin.h"
#include "script1App.h"
#include "atlstr.h"



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


/*******************/
/*BEGIN NEW COMMAND*/
/*******************/
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

  Cscript1PlugIn& plugin = script1PlugIn();

  if( !plugin.IsDlgVisible() )
  {
    return CRhinoCommand::nothing;
  }


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
			/******************/
			/*CLEAN UP OR LEAK*/ 
			/******************/
			delete crv0;
			crv0 = 0;

			
			// code temp
// aniello begin
// Get the next runtime object serial number after scripting
  unsigned int next_sn = CRhinoObject::NextRuntimeObjectSerialNumber();

 
  // Enable redrawing
  //CRhinoView::EnableDrawing( TRUE );
 
  // if the two are the same, then nothing happened
 /* if( first_sn == next_sn )
    //return CRhinoCommand::nothing;
	return;
*/ //commento questo per far compilare :-)
 
  // The the pointers of all of the objects that were added during scripting
  ON_SimpleArray<const CRhinoObject*> objects;
  for( unsigned int sn = first_sn; sn < next_sn; sn++ )
  {
    const CRhinoObject* obj = context.m_doc.LookupObjectByRuntimeSerialNumber( sn );
    if( obj && !obj->IsDeleted() )
      objects.Append( obj );
  }
 
  /*
  // Sort and cull the list, as there may be duplicates
  if( objects.Count() > 1 )
  {
    objects.HeapSort( CompareObjectPtr );
    const CRhinoObject* last_obj = objects[objects.Count()-1];
    for( int i = objects.Count()-2; i >= 0; i-- )
    {
      const CRhinoObject* prev_obj = objects[i];
     if( last_obj == prev_obj )
        objects.Remove(i);
      else
        last_obj = prev_obj;
    }
  }
	*/
  // Do something with the list...
  for( int i = 0; i < objects.Count(); i++ )
  {
    const CRhinoObject* obj = objects[i];
    if( obj->IsSelectable(true) )
      obj->Select( true );
  }
//aniello end
			//end code temp

  			/*********************/
			/*JOIN LINES TOGETHER*/
			/*********************/
			ON_SimpleArray<const ON_Curve*> lines;
			ON_SimpleArray<CRhinoObject*> objectsLine;
			ON_SimpleArray<ON_Curve*> output;
			double tolerance = context.m_doc.AbsoluteTolerance();
			int LinesCount = context.m_doc.LookupObject( layer, objectsLine);

			if( LinesCount > 0 )
			{
				for(int i = 0; i < LinesCount; i++)
				{
					const CRhinoCurveObject* curve_obj = CRhinoCurveObject::Cast( objectsLine[i] );
					if( curve_obj )
					{
						lines.Append(curve_obj->Curve());
					}
				}
			}
		    if( RhinoMergeCurves(lines, output, tolerance) )
		    {
				for(int i = 0; i < output.Count(); i++ )
				{
					CRhinoCurveObject* crv = new CRhinoCurveObject;
					crv->SetCurve( output[i] );
					if( context.m_doc.AddObject(crv) )
					{
						crv->Select();
					}
					else
					{
						delete crv;
					}
				}
		    }
			/************************/
			/*DELETE CHILDREN CURVES*/
			/************************/
			for(int i = 0; i < LinesCount; i++ )
			{
				context.m_doc.DeleteObject(objectsLine[i]);
			}
			context.m_doc.Redraw();

			/*************************/
			/*END JOIN LINES TOGETHER*/
			/*************************/




	     }
	  }/*CHIUSURA IF( OBJECT_COUNT > 0 )*/
  }/*CHIUSURA ELSE*/

  return CRhinoCommand::success;
}

/***********************/
/*BEGIN NEW COMMAND 2ND*/
/***********************/
class CGenCylinder : public CRhinoTestCommand
{
public:
  // The one and only instance of CCommandscript1 is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandscript1::CCommandscript1()
  // is called exactly once when static thescript1Command is created.
	CGenCylinder() {}

  // CCommandscript1::~CCommandscript1()
  // is called exactly once when static thescript1Command is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CGenCylinder() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		
	static const GUID CGenCylinderCommand_UUID = 
	{0x340e4824, 0x1cf2, 0x4f05, {0xbd, 0x74, 0xbb, 0xe7, 0x70, 0x12, 0xc1, 0x91}};
	return CGenCylinderCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GenCylinder"; }
	const wchar_t* LocalCommandName() { return L"GenCylinder"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

static class CGenCylinder theCGenCylinderCommand;
CRhinoCommand::result CGenCylinder::RunCommand( const CRhinoCommandContext& context )
{

	Cscript1PlugIn& plugin = script1PlugIn();
	if( !plugin.IsDlgVisible() )
	{
		return CRhinoCommand::nothing;
	}

	/*****************************************/
	/*CHECKING IF THERE IS ALREADY A CYLINDER*/
	/*****************************************/
	const CRhinoLayer& layer = context.m_doc.m_layer_table.CurrentLayer();
	ON_SimpleArray<CRhinoObject*> objects;
	int object_count = context.m_doc.LookupObject( layer, objects );
	if( object_count > 0 )
	{
		int brep_obj_count = 0;
		const CRhinoObject* object = 0;
		for(int i = 0; i < object_count; i++ )
		{
			object = objects[ i ];
			/************************************/
			/*TRY CASTING AS A RHINO BREP OBJECT*/ 
			/************************************/
			const CRhinoBrepObject* brep_obj = CRhinoBrepObject::Cast( object );
			if( brep_obj)
			{
				brep_obj_count++;
			}
		}
		if( brep_obj_count == 0)
		{
			ON_3dPoint center_point( 0.0, 0.0, 0.0 );
			double radius = 63.5;
			int __count = plugin.m_dialog->m_comboAltTacco.GetCount();

			int nIndex = plugin.m_dialog->m_comboAltTacco.GetCurSel();
			CString strCBText;
			plugin.m_dialog->m_comboAltTacco.GetLBText( nIndex, strCBText);
			int height = _wtoi(strCBText);


			ON_3dPoint height_point( 0.0, 0.0, height);
			ON_3dVector zaxis = height_point - center_point;
			ON_Plane planeCir( center_point, zaxis );

			/*ADD CIRCLE FOR CYLINDER'S BASE*/
			ON_Circle circle( planeCir, radius );

			/*ADD CYLINDER*/
			ON_Cylinder cylinder( circle, zaxis.Length() );
			ON_Brep* brep = ON_BrepCylinder( cylinder, TRUE, TRUE );
			if( brep )
			{
				/********************/
				/*TRANSLATE CYLINDER*/
				/********************/
				brep->Translate(ON_3dVector( 0.0, 0.0, -(_wtof(plugin.m_dialog->ValoreAltezzaFondello))));
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
		}/*CLOSED IF OVER CHECKING BREP COUNT OBJECT*/
		else
		{
			RhinoMessageBox(L"THERE IS ALREADY A CYLINDER OBJECT", PlugIn()->PlugInName(), MB_OK | MB_ICONEXCLAMATION );
		}
	}
	/**********************************************************************/



  return CRhinoCommand::success;
}



/***********************/
/*BEGIN Traslazione Ruotazione*/
/***********************/
class CTraslRuota : public CRhinoTestCommand
{
public:
  // The one and only instance of CCommandscript1 is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandscript1::CCommandscript1()
  // is called exactly once when static thescript1Command is created.
	CTraslRuota() {}

  // CCommandscript1::~CCommandscript1()
  // is called exactly once when static thescript1Command is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CTraslRuota() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
	
		// {9EDB030E-81A5-4e20-A7E6-0DAEB4D077D2}



	static const GUID CTraslRuotaCommand_UUID = 
	{ 0x9edb030e, 0x81a5, 0x4e20, { 0xa7, 0xe6, 0xd, 0xae, 0xb4, 0xd0, 0x77, 0xd2 } };
	return CTraslRuotaCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TraslaRuota"; }
	const wchar_t* LocalCommandName() { return L"TraslaRuota"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

static class CTraslRuota theCTraslRuotaCommand;
CRhinoCommand::result CTraslRuota::RunCommand( const CRhinoCommandContext& context )
{
		Cscript1PlugIn& plugin = script1PlugIn();
		if( !plugin.IsDlgVisible() )
		{
			return CRhinoCommand::nothing;
		}

		/*GET A REFERENCE TO THE LAYER TABLE*/
	  CRhinoLayerTable& layer_table = context.m_doc.m_layer_table;
	  


	  ON_Layer currentLayer;
		  int numLayers = layer_table.LayerCount();
		 
		  for(int i = 0; i < numLayers; i++)
	{
			  
				  currentLayer = layer_table[i];
				  const CRhinoLayer& layer = layer_table[i];

				  currentLayer.SetVisible(true);
				  
				  layer_table.ModifyLayer(currentLayer, i);
				  layer_table.SetCurrentLayerIndex(i);
				  
			  
		  
		  
		  
		  
		  const CRhinoLayer& current_layer = layer_table.CurrentLayer();

		  int layer_index = layer_table.CurrentLayerIndex();
		  const CRhinoLayer& layer2 = layer_table[layer_index];

		  ON_SimpleArray<CRhinoObject*> obj_list;
		  int j, obj_count = context.m_doc.LookupObject( layer2, obj_list );
		  for( j = 0; j < obj_count; j++ )
		  {
				  CRhinoObject* obj = obj_list[j];
				  if( obj && obj->IsSelectable() )
					  obj->Select();
				  if( obj_count )
					context.m_doc.Redraw();
		  }
		  
	}  

		  context.m_doc.Redraw();

			//inizio rotazione
		  
		  double m_angle=(_wtof(plugin.m_dialog->ValoreRotazione));
		  ON_Plane plane = RhinoActiveCPlane();
		  
		CRhinoGetObject go1;
		  go1.GetObjects( 1, 0 );
		  int numero1 = go1.ObjectCount();
		for( int k = 0; k < go1.ObjectCount(); k++ )
		{
		 // Get an object reference
			const CRhinoObjRef& ref = go1.Object(k);
 
			// Get the real object
			const CRhinoObject* obj = ref.Object();
			if( !obj )
			continue;

			ON_Xform xform;
    xform.Rotation( m_angle * ON_PI / 180.0, plane.zaxis, plane.Origin() );
	context.m_doc.TransformObject( obj, xform, true, true, true );
	context.m_doc.Redraw();
		}

		//fine rotazione


			//inizio traslazione		 
		  CRhinoGetObject go;
		  int numero = go.ObjectCount();
		  go.GetObjects( 1, 0 );
		  
		for( int i = 0; i < go.ObjectCount(); i++ )
		{
		 // Get an object reference
			const CRhinoObjRef& ref = go.Object(i);
 
			// Get the real object
			const CRhinoObject* obj = ref.Object();
			if( !obj )
			continue;

			ON_Xform xform;
    xform.Rotation( m_angle * ON_PI / 180.0, plane.zaxis, plane.Origin() );
	//context.m_doc.TransformObject( obj, xform, true, true, true );
	context.m_doc.Redraw();
	xform.Translation((_wtof(plugin.m_dialog->ValoreTraslazione)),0,0);
	context.m_doc.TransformObject( obj, xform, true, true, true );
	context.m_doc.Redraw();
		}
			// fine traslazione

		
		 context.m_doc.Redraw();







}


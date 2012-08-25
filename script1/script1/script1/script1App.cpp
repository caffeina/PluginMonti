/////////////////////////////////////////////////////////////////////////////
// script1App.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "script1App.h"
#include "DialogPrincipale.h"

//
//	Note!
//
//    A Rhino plug-in is an MFC DLL.
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


// Cscript1App

BEGIN_MESSAGE_MAP(Cscript1App, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cscript1App construction

Cscript1App::Cscript1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only Cscript1App object
Cscript1App theApp;

/////////////////////////////////////////////////////////////////////////////
// Cscript1App initialization

BOOL Cscript1App::InitInstance()
{	
	// Initializes OLE support for the application.
	if( !AfxOleInit() )
	{
		AfxMessageBox( IDP_OLE_INIT_FAILED );
		return FALSE;
	}

  // InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	
  // Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &InitCtrls );

	CWinApp::InitInstance();

	AfxEnableControlContainer();

 
  DialogPrincipale dlg;
  m_pMainWnd = &dlg;
  INT_PTR nResponse = dlg.DoModal();
  if( nResponse == IDOK )
	{
		// TODO:
  }
	else if (nResponse == IDCANCEL)
	{
		// TODO
	}
	

	return TRUE;
}




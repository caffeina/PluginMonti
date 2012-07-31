/////////////////////////////////////////////////////////////////////////////
// script1PlugIn.h : main header file for the script1 plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Cscript1PlugIn
// See script1PlugIn.cpp for the implementation of this class
//

class Cscript1PlugIn : public CRhinoUtilityPlugIn
{
public:
  Cscript1PlugIn();
  ~Cscript1PlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Online help overrides
  BOOL AddToPlugInHelpMenu() const;
  BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

Cscript1PlugIn& script1PlugIn();




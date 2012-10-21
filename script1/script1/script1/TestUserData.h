/////////////////////////////////////////////////////////////////////////////
// TestUserData.h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// TestUserData.h

class CTestUserData : public ON_UserData
{
  // Opennurbs classes that are saved in .3dm files require
  // an ON_OBJECT_DECLARE call in their declaration.
  ON_OBJECT_DECLARE(CTestUserData);

public:

  /*
  Returns:
    Uuid used to identify this type of user data.
    This is the value saved in m_userdata_uuid and
    passed to ON_Object::GetUserData().
  */
  static ON_UUID Id();

  CTestUserData();
  ~CTestUserData();

  // NOTE WELL:
  //   Because the members of this class are class are types 
  //   that have fully functional copy constructors and 
  //   operator=s, it is NOT necessary to provide an explicit
  //   a copy constructor and operator=.  In fact, it would 
  //   be best to use the ones C++ generates. 
  //   They are included in this example to demonstrate the
  //   correct way to implement a copy constructor and
  //   operator= because this is a task that trips up
  //   many people that attempt to implement them.
  CTestUserData(const CTestUserData& src);
  CTestUserData& operator=(const CTestUserData& src);

  // override virtual ON_UserData::GetDescription()
  BOOL GetDescription( ON_wString& description );

  // override virtual ON_UserData::Archive()
  BOOL Archive() const; 

  // override virtual ON_UserData::Write()
  BOOL Write(
         ON_BinaryArchive& binary_archive
       ) const;

  // override virtual ON_UserData::Read()
  BOOL Read(
         ON_BinaryArchive& binary_archive
       );

  ON_wString m_my_string;
  ON_3dPoint m_my_point;
};
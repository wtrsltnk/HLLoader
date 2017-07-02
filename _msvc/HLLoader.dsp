# Microsoft Developer Studio Project File - Name="HLLoader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HLLoader - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HLLoader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HLLoader.mak" CFG="HLLoader - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HLLoader - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HLLoader - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HLLoader - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HLLoader - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../_shared" /I "../_msvc" /I "../" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "HLLoader - Win32 Release"
# Name "HLLoader - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\CApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\CWin.cpp
# End Source File
# Begin Source File

SOURCE=..\FileLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\Keys.cpp
# End Source File
# Begin Source File

SOURCE=..\ThreeD.cpp
# End Source File
# Begin Source File

SOURCE=..\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\_shared\wiskunde.cpp
# End Source File
# Begin Source File

SOURCE=..\WtrCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\WtrEngine.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\_shared\ArrayList.h
# End Source File
# Begin Source File

SOURCE=..\CApplication.h
# End Source File
# Begin Source File

SOURCE=..\CWin.h
# End Source File
# Begin Source File

SOURCE=..\FileLoader.h
# End Source File
# Begin Source File

SOURCE=..\Keys.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\ThreeD.h
# End Source File
# Begin Source File

SOURCE=..\..\_shared\wiskunde.h
# End Source File
# Begin Source File

SOURCE=..\WtrCamera.h
# End Source File
# Begin Source File

SOURCE=..\WtrEngine.h
# End Source File
# End Group
# Begin Group "BSP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\BSP\BSPFile.cpp
# End Source File
# Begin Source File

SOURCE=..\BSP\BSPFile.h
# End Source File
# Begin Source File

SOURCE=..\BSP\BSPLump.cpp
# End Source File
# Begin Source File

SOURCE=..\BSP\BSPLump.h
# End Source File
# Begin Source File

SOURCE=..\BSP\bsptypes.h
# End Source File
# End Group
# Begin Group "WAD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\WAD\WADFile.cpp
# End Source File
# Begin Source File

SOURCE=..\WAD\WADFile.h
# End Source File
# Begin Source File

SOURCE=..\WAD\WADLump.cpp
# End Source File
# Begin Source File

SOURCE=..\WAD\WADLump.h
# End Source File
# Begin Source File

SOURCE=..\WAD\WADMiptex.cpp
# End Source File
# Begin Source File

SOURCE=..\WAD\WADMiptex.h
# End Source File
# Begin Source File

SOURCE=..\WAD\wadtypes.h
# End Source File
# End Group
# Begin Group "MAP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MAP\MAPBrush.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPBrush.h
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPEntity.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPEntity.h
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPFace.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPFace.h
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPFile.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPFile.h
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPParser.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPParser.h
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPPropertie.cpp
# End Source File
# Begin Source File

SOURCE=..\MAP\MAPPropertie.h
# End Source File
# End Group
# Begin Group "RMF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\RMF\RMF2MS3D.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMF2MS3D.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFCorner.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFCorner.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFEntity.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFEntity.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFFace.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFFace.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFFile.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFFile.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFGroup.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFKey.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFKey.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFObject.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFObject.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFPath.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFPath.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFSolid.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFSolid.h
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFVisGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\RMF\RMFVisGroup.h
# End Source File
# End Group
# Begin Group "MS3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\MS3D\MS3DFile.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DFile.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DGroup.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DJoint.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DJoint.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DKeyFramePos.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DKeyFramePos.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DKeyFrameRot.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DKeyFrameRot.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DMaterial.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DObject.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DObject.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DTriangle.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DTriangle.h
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DVertex.cpp
# End Source File
# Begin Source File

SOURCE=..\MS3D\MS3DVertex.h
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\BaseFile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\BaseFile.h
# End Source File
# Begin Source File

SOURCE=..\common\ByteContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\common\ByteContainer.h
# End Source File
# Begin Source File

SOURCE=..\common\ByteIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\common\ByteIterator.h
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryFile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryFile.h
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryFolder.cpp
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryFolder.h
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryNode.cpp
# End Source File
# Begin Source File

SOURCE=..\common\DirectoryNode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\hl.ico
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# End Target
# End Project

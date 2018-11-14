# Microsoft Developer Studio Project File - Name="stlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=stlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "stlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "stlib.mak" CFG="stlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stlib - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "stlib - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "stlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "stlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "stlib - Win32 Release"
# Name "stlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\st_arry.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_asyncqueue.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_avltree.c
# End Source File
# Begin Source File

SOURCE="..\..\src\st_b+_tree.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\src\st_b_tree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_btree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_dlist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_extendible_hashing.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_ghash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_gtree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_hash_common.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_huffmantree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_log.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_mempool.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_open_addressing_double_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_open_addressing_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_open_addressing_hash_2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_open_addressing_hash_with_hashing_again.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_pthread_pool.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_qsort.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_quene.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_rbtree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_rbtree_lk.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_separate_chaining_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_slist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_splaytree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_stack.c
# End Source File
# Begin Source File

SOURCE=..\..\src\st_treaptree.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\st_arry.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_asyncqueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_avltree.h
# End Source File
# Begin Source File

SOURCE="..\..\include\st_b+_tree_cpp.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\st_b_tree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_btree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_dlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_drlist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_extendible_hashing.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_ghash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_gtree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_hash_common.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_huffmantree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_log.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_mempool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_open_addressing_double_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_open_addressing_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_open_addressing_hash_2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_open_addressing_hash_with_hashing_again.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_pthread_pool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_qsort.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_quene.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_rbtree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_rbtree_bsd.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_rbtree_lk.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_separate_chaining_hash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_slist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_splaytree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_stack.h
# End Source File
# Begin Source File

SOURCE=..\..\include\st_treaptree.h
# End Source File
# Begin Source File

SOURCE=..\..\include\stlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\test\stlibtest.c
# End Source File
# End Group
# End Target
# End Project

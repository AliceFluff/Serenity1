// Preprocessor Directives
#ifndef _LOG_HPP_
#define _LOG_HPP_

////////////////////////////////////
////// External Header file's //////
#include <stdio.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <windows.h>
#include <wchar.h>
#include <iomanip>
#include <sstream>
#include <shlobj.h>
#include <fcntl.h>
#include <io.h>
#include <shellapi.h>

/////////////////////////////////
////// Local Header file's //////


/////////////////////////////////////
////// External Library file's //////
#pragma comment(lib, "shell32")

//////////////////////////////////
////// Local Library file's //////


//////////////////////////////////
////// External Namespace's //////


///////////////////////////////
////// Local Namespace's //////
using namespace std;

/////////////////////////////////////////////
////// Error Reporting Message Macro's //////
#define ERRORMSG(m_Msg)(MessageBox(NULL, m_Msg, L"INFO!", MB_ICONERROR));
#define SUCCESSMSG(m_Msg)(MessageBox(NULL, m_Msg, L"SUCCESS!", MB_ICONINFORMATION));
#define INFOMSG(m_Msg)(MessageBox(NULL, m_Msg, L"INFO!", MB_ICONWARNING));

///////////////////////
////// Log Class //////
class cLog
{
	///////////////////////////////////////////
	////// Log Methods - Class interface //////
public:	
	////// Constructor's //////
	cLog(void);														// Constructor
	~cLog(void);													// Deconstructor

	////// Log Methods's //////
	bool ConsoleInit(void);											// initalise console KEEPING
	bool TextLogInit(wstring szDirectory_, wstring szFileName_);	// initalise texst log KEEPING

	bool OpenConsole(void);											// open console window up during run time
	bool OpenTextLog(wstring szDirectory, wstring szFilename);		// open text file for recording output to file
	bool OpenDirectory(void);										// open the file output target directory and file

	wstring Write(wstring msg_, bool display_, bool console_, bool textlog_, UINT msgbox_);	// Writes to text buffer							// write continuous 
	wstring WriteLine(wstring msg, bool console, bool textlog, UINT msgbox);		// get message, write 1 line and print
	
private:
	////// Member's //////
	SYSTEMTIME mSystemTime;											// system time represention
	wofstream mOutStream;											// stream out text to file

	TCHAR Path[1024];												// directory path buffer
	wstring mszLogDirectoryName;									// complete directory path
	wstring mszsFileName;											// Text File Neame
	wstringstream mszsTextFileOut;									// Text stream buffer for text file
	wstringstream mszsStreamBuffer;									// Text stream buffer for Write()
	wstring clear;													// Clears the text
	wstring mVTab;													// virticle tab
	wstring mHTab;													// horizontal tab
	bool mConsoleOn;												// Switch for console on/off
	wstring mConsoleOnText;											// String for Console on text
	wstring mTextFileOnText;										// String for Text File on text

	////// Method's //////
	wstring DateStamp(void);										// time stamp
	wstring TimeStamp(void);										// date stamp	

	bool PrintMsgToConsole(wstring msg);							// print line to console
	bool PrintMsgTotTextLog(wstring StrLog);						// print line to text file
};

#endif // !_LOG_HPP_
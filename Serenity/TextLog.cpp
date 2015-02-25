/////////////////////////////////
////// Local Header file's //////
#include <TextLog.hpp>

///////////////////////////
////// Constructor's //////
cLog::cLog(void)
{
	GetLocalTime(&mSystemTime);

	mVTab = L"\n\n\n\n";
	mHTab = L"\t";

	clear = L"";

	mConsoleOn = false;
	mConsoleOnText = L"Console Active";
	mTextFileOnText = L"TextFile Active";
}
cLog::~cLog(void)
{

}

//////////////////////
////// Method's //////
// initalise console KEEPING
bool cLog::ConsoleInit(void)
{
	AllocConsole();

	HANDLE handle_out;// = GetStdHandle(STD_OUTPUT_HANDLE);
	if (FAILED(handle_out = GetStdHandle(STD_OUTPUT_HANDLE)))
		ERRORMSG(L"cLog::ConsoleInit() Failed GetStdHandle()");

	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	if (FAILED(handle_in = GetStdHandle(STD_INPUT_HANDLE)))
		ERRORMSG(L"cLog::ConsoleInit() Failed GetStdHandle()");

	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	system("Color 1A");
	mConsoleOn = true;
	WriteLine(mConsoleOnText.c_str(), 1, 0, 0);
	return true;
}

// initalise texst log KEEPING
bool cLog::TextLogInit(wstring szDirectory_, wstring szFileName_)
{	
	if (!SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, NULL, Path))
	{
		wstringstream szsBuffer;
		szsBuffer << clear.c_str();
		if (szsBuffer.str() == clear.c_str())
		{
			szsBuffer << Path << "\\" << szDirectory_.c_str();
			szDirectory_ = szsBuffer.str();
			SHCreateDirectory(NULL, szDirectory_.c_str());
			mszLogDirectoryName = szDirectory_.c_str();
		}
		else
		{
			ERRORMSG(L"cLog::TextLogInit() Failed szsBuffer Not NULL");
			return false;
		}		
	}
	else
	{
		ERRORMSG(L"**** SHGetFolderPath() Failed to create/find %LOCALAPPDATA% Directory!! ****");
		return false;
	}

	wstringstream szsFilenameBuffer;
	szsFilenameBuffer << clear.c_str();
	if (szsFilenameBuffer.str() == clear.c_str())
	{
		szsFilenameBuffer << szDirectory_.c_str() << "\\" << mSystemTime.wYear << setfill(L'0') << setw(2)
			<< mSystemTime.wMonth << setfill(L'0') << setw(2) << mSystemTime.wDay << "_" << setfill(L'0') << setw(2)
			<< mSystemTime.wHour << setfill(L'0') << setw(2) << mSystemTime.wMinute << setfill(L'0') << setw(2)
			<< mSystemTime.wSecond << "_" << szFileName_.c_str() << ".txt";
		mszsFileName = szsFilenameBuffer.str();
	}
	else
	{
		ERRORMSG(L"cLog::TextLogInit() Failed szsFilenameBuffer Not NULL");
		return false;
	}

	if (mConsoleOn)
		WriteLine(mConsoleOnText.c_str(), 0, 1, 0);

	WriteLine(mTextFileOnText.c_str(), 1, 1, 0);
	return true;
}

wstring cLog::Write(wstring msg_, bool display_, bool console_, bool textlog_, UINT msgbox_)
{
	if (mszsStreamBuffer.str() == clear.c_str())
	{
		mszsStreamBuffer << msg_.c_str();
	}
	else
	{
		mszsStreamBuffer.eof();
		mszsStreamBuffer << " " << msg_.c_str();

		if (msgbox_ != 0)
		{
			switch (msgbox_)
			{
			case 1:
				if (console_)
				{
					WriteLine(mszsStreamBuffer.str(), 1, 0, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgToConsole()");
				}

				if (textlog_)
				{
					WriteLine(mszsStreamBuffer.str(), 0, 1, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgTotTextLog()");
				}

				if (mszsStreamBuffer)
				{
					mszsStreamBuffer.str(clear.c_str());
					mszsStreamBuffer.beg;
				}
				else
				{
					ERRORMSG(L"cLog::Write() Faled at switch (msgbox_) to clear mszsStreamBuffer");
				}

				break;
			case 2:
				if (console_)
				{
					WriteLine(mszsStreamBuffer.str(), 1, 0, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgToConsole()");
				}

				if (textlog_)
				{
					WriteLine(mszsStreamBuffer.str(), 0, 1, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgTotTextLog()");
				}

				if (mszsStreamBuffer)
				{
					mszsStreamBuffer.str(clear.c_str());
					mszsStreamBuffer.beg;
				}
				else
				{
					ERRORMSG(L"cLog::Write() Faled at switch (msgbox_) to clear mszsStreamBuffer");
				}

				break;
			case 3:
				if (console_)
				{
					WriteLine(mszsStreamBuffer.str(), 1, 0, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgToConsole()");
				}

				if (textlog_)
				{
					WriteLine(mszsStreamBuffer.str(), 0, 1, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgTotTextLog()");
				}

				if (mszsStreamBuffer)
				{
					mszsStreamBuffer.str(clear.c_str());
					mszsStreamBuffer.beg;
				}
				else
				{
					ERRORMSG(L"cLog::Write() Faled at switch (msgbox_) to clear mszsStreamBuffer");
				}

				break;
			default:
				ERRORMSG(L"cLog::Write() Faled at switch (msgbox_)");
				break;
			}
		}
		else
		{
			if (display_)
			{
				if (console_)
				{
					WriteLine(mszsStreamBuffer.str(), 1, 0, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgToConsole()");
				}

				if (textlog_)
				{
					WriteLine(mszsStreamBuffer.str(), 0, 1, msgbox_);
				}
				else
				{
					ERRORMSG(L"cLog::WriteLine() Failed PrintMsgTotTextLog()");
				}

				if (mszsStreamBuffer)
				{
					mszsStreamBuffer.str(clear.c_str());
					mszsStreamBuffer.beg;
				}
				else
				{
					ERRORMSG(L"cLog::Write() Faled at switch (msgbox_) to clear mszsStreamBuffer");
				}
			}
		}
	}
	return msg_.c_str();
};

// get message, write 1 line and print
wstring cLog::WriteLine(wstring msg_, bool console_, bool textlog_, UINT msgbox_)
{
	wstringstream szsbuffer;
	szsbuffer << clear.c_str();
	if (szsbuffer.str() == clear.c_str())
	{
		szsbuffer << mHTab.c_str() << msg_.c_str();
		msg_ = szsbuffer.str();
	}
	else
	{
		ERRORMSG(L"cLog::WriteLine() Failed szsbuffer Not Clear");
	}

	if (msgbox_ != 0)
	{
		switch (msgbox_)
		{
		case 1:
			if (console_)
				PrintMsgToConsole(msg_.c_str());

			if (textlog_)
				PrintMsgTotTextLog(msg_.c_str());

			ERRORMSG(msg_.c_str());
			break;

		case 2:
			if (console_)
				PrintMsgToConsole(msg_.c_str());

			if (textlog_)
				PrintMsgTotTextLog(msg_.c_str());

			SUCCESSMSG(msg_.c_str());
			break;

		case 3:
			if (console_)
				PrintMsgToConsole(msg_.c_str());

			if (textlog_)
				PrintMsgTotTextLog(msg_.c_str());

			INFOMSG(msg_.c_str());
			break;

		default:
			ERRORMSG(L"cLog::WriteLine() Faled at switch (msgbox_)");
			break;
		}
	}
	else
	{
		if (console_)
			PrintMsgToConsole(msg_.c_str());

		if (textlog_)
			PrintMsgTotTextLog(msg_.c_str());
	}
	return msg_.c_str();
}

// print line to console
bool cLog::PrintMsgToConsole(wstring msg)
{
	GetLocalTime(&mSystemTime);
	wstringstream szsBuffer;
	szsBuffer.beg;
	szsBuffer.str(clear.c_str());
	if (szsBuffer.str() == clear.c_str())
	{
		szsBuffer << L"\n\n" << DateStamp().c_str() << TimeStamp().c_str() << msg.c_str();
		msg = szsBuffer.str();
		wprintf(msg.c_str());
	}
	else
	{
		ERRORMSG(L"cLog::PrintMsgToConsole() Faled szsBuffer Not NULL");
	}
	return true;
}

// print line to text file
bool cLog::PrintMsgTotTextLog(wstring StrLog)
{
	GetLocalTime(&mSystemTime);
	mOutStream.open(mszsFileName.c_str());
	if (mOutStream.is_open())
	{
		mOutStream.eof();
		mszsTextFileOut << L"\n\n" << DateStamp().c_str() << TimeStamp().c_str() << StrLog.c_str();
		StrLog = mszsTextFileOut.str();
		mOutStream << StrLog.c_str();
	}
	mOutStream.close();
	return true;
}

// open console window up during run time
bool cLog::OpenConsole(void)
{
	if (MessageBox(NULL, L"Do you want to see the Console?", L"Question", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		if (!ConsoleInit())
			ERRORMSG(L"cLog::OpenConsole - ConsoleInit() Failed");
	}
	return true;
}

// open text file for recording output to file
bool cLog::OpenTextLog(wstring szDirectory, wstring szFilename)
{
	if (MessageBox(NULL, L"Do you want to generate a text log?", L"Question", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		if (!TextLogInit(szDirectory.c_str(), szFilename.c_str()))
			ERRORMSG(L"cLog::OpenConsole - ConsoleInit() Failed");
	}
	return true;
}

// open the file output target directory and file
bool cLog::OpenDirectory(void)
{
	if (MessageBoxEx(NULL, L"Would you like to see Log Directory?", L"Open Log(s)", MB_ICONQUESTION | MB_YESNO, 0) == IDYES)
	{
		WriteLine(L"Showing Directory and Text Log File.", 1, 1, 0);

		ShellExecute(NULL, L"open", mszLogDirectoryName.c_str(), NULL, NULL, SW_SHOWDEFAULT);
		ShellExecute(NULL, L"open", mszsFileName.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}
	else
	{
		WriteLine(L"Not Showing Directory and Text Log File.", 1, 1, 0);
	}	
	return true;
}

// date stamp	
wstring cLog::DateStamp(void)
{
	wstringstream szsBuffer;
	szsBuffer.beg;
	szsBuffer.str(clear.c_str());
	if (szsBuffer.str() == clear.c_str())
	{
		szsBuffer << setfill(L'0') << setw(2) << mSystemTime.wYear << L"/" << setfill(L'0') << setw(2)
			<< mSystemTime.wMonth << L"/" << setfill(L'0') << setw(2) << mSystemTime.wDay << " ";
		return szsBuffer.str();
	}
	else
	{
		ERRORMSG(L"cLog::DateStamp Failed szsBuffer Not NULL");
		return clear.c_str();
	}	
}

// time stamp
wstring cLog::TimeStamp(void)
{
	wstringstream szsBuffer;
	szsBuffer.beg;
	szsBuffer.str(clear.c_str());
	if (szsBuffer.str() == clear.c_str())
	{
		szsBuffer << setfill(L'0') << setw(2) << mSystemTime.wHour << ":" << setfill(L'0') << setw(2)
			<< mSystemTime.wMinute << ":" << setfill(L'0') << setw(2) << mSystemTime.wSecond << " -";
		return szsBuffer.str();
	}
	else
	{
		ERRORMSG(L"cLog::DateStamp Failed szsBuffer Not NULL");
		return clear.c_str();
	}
}
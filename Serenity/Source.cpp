////////////////////////////////////
////// External Header file's //////


/////////////////////////////////
////// Local Header file's //////
#include <App.hpp>

/////////////////////////////////////
////// External Library file's //////


//////////////////////////////////
////// Local Library file's //////


//////////////////////////////////
////// External Namespace's //////
using namespace std;

///////////////////////////////
////// Local Namespace's //////

/////////////////////////////////////////
////// Main Window Execution Point //////
int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	cApp App(hInstance, L"Serenity", 800, 600, true);

	App.InitApp();

	return App.Run();
}
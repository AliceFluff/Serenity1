////////////////////////////////////
////// External Header file's //////


/////////////////////////////////
////// Local Header file's //////
#include <System.hpp>

/////////////////////////////////////
////// External Library file's //////


//////////////////////////////////
////// Local Library file's //////


//////////////////////////////////
////// External Namespace's //////


///////////////////////////////
////// Local Namespace's //////


//////////////////
////// DXGI //////
// initialise the DXGI 
bool cSystem::DXGIInit(void)
{
	SystemLog.WriteLine(L" -- cSystem::DXGIInit() Begin -- \n\n", 1, 1, 0);

	// GET HOLD THE INTERFACES
	mD3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&mDXGIDevice);
	if (mDXGIDevice == NULL)
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIDevice NULL", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIDevice Acquired Successfully", 1, 1, 0);
	}

	mDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDXGIAdapter);
	if (mDXGIAdapter == NULL)
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIAdapter NULL", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIAdapter Acquired Successfully", 1, 1, 0);
	}

	mDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDXGIFactory);
	if (mDXGIFactory == NULL)
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIFactory NULL", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::DXGIInit() - mDXGIFactory Acquired Successfully", 1, 1, 0);
	}

	SystemLog.WriteLine(L" -- cSystem::DXGIInit() Success -- \n\n", 1, 1, 0);
	return true;
}
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


/////////////////////////
////// Direct3D 11 //////
bool cSystem::InitDirect3D11(UINT width, UINT height, UINT x, UINT y)
{
	SystemLog.WriteLine(L"-- cSystem::InitDirect3D11() Begin -- \n\n", 1, 1, 0);

	UINT createDeviceFlags = 0;
#if defined (DEBUG) || (_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	UINT FeatureLevel = 0;
	D3D_FEATURE_LEVEL FeatureLevels[4] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};

	if (FeatureLevels[0] == D3D_FEATURE_LEVEL_11_0)
	{
		FeatureLevel = 0;
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() # D3D_FEATURE_LEVEL_11_0 # Supported", 1, 1, 0);
	}
	else if (FeatureLevels[1] == D3D_FEATURE_LEVEL_10_1)
	{
		FeatureLevel = 1;
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() # D3D_FEATURE_LEVEL_10_1 # Supported", 1, 1, 0);
	}
	else if (FeatureLevels[2] == D3D_FEATURE_LEVEL_10_0)
	{
		FeatureLevel = 2;
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() # D3D_FEATURE_LEVEL_10_0 # Supported", 1, 1, 0);
	}
	else if (FeatureLevels[3] == D3D_FEATURE_LEVEL_9_3)
	{
		FeatureLevel = 3;
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() # D3D_FEATURE_LEVEL_9_3 # Supported", 1, 1, 0);
	}
	else
	{
		ERROR(L"Direct3D D3D_FEATURE_LEVEL_X_X Not Supported.");
		return false;
	}

	if (FAILED(result = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &FeatureLevels[FeatureLevel], ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION,
		&mD3D11Device, NULL, &mD3D11DeviceContext)))
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - D3D11CreateDevice() Failed", 1, 1, 1);
	}
	else
	{

		SystemLog.WriteLine(L"cSystem::InitDirect3D11() D3D11CreateDevice Success", 1, 1, 0);
	}

	for (UINT sampleCount = 1; sampleCount <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; sampleCount++)
	{
		UINT counter = 0;
		UINT maxQualityLevel = 0;
		result = mD3D11Device->CheckMultisampleQualityLevels(mDXGIFormat[0],
			sampleCount, &maxQualityLevel);

		if (maxQualityLevel > 0)
		{
			maxQualityLevel--;
			if (sampleCount <= 1)
			{
				SystemLog.WriteLine(L"\n\n\tChecking MultiSampling and Anti-Aliasing Starting", 1, 1, 0);
			}
		}

		if (result != S_OK)
		{
			SystemLog.WriteLine(L"cSystem::InitDirect3D11() - CheckMultisampleQualityLevels() Failed", 1, 1, 1);
		}

		if (maxQualityLevel > 0)
		{
			wstringstream stream;
			wstring string;
			stream << L"MSAA " << sampleCount << "X Supported with " <<
				maxQualityLevel << " quality levels.";
			string = stream.str();
			SystemLog.WriteLine(string.c_str(), 1, 1, 0);

			counter++;
			mMSAASample[counter] = sampleCount;
			mMSAAQuality[counter] = maxQualityLevel;
		}

		if (sampleCount == 4 && maxQualityLevel >= 8)
		{
			counter++;
			mMSAASample[counter] = sampleCount;
			mMSAAQuality[counter] = maxQualityLevel;
			SystemLog.WriteLine(L"CSAA Mode 8x is Supported", 1, 1, 0);
		}

		if (sampleCount == 8 && maxQualityLevel >= 8)
		{
			counter++;
			mMSAASample[counter] = sampleCount;
			mMSAAQuality[counter] = maxQualityLevel;
			SystemLog.WriteLine(L"CSAA Mode 8xQ is Supported", 1, 1, 0);
		}

		if (sampleCount == 4 && maxQualityLevel >= 16)
		{
			counter++;
			mMSAASample[counter] = sampleCount;
			mMSAAQuality[counter] = maxQualityLevel;
			SystemLog.WriteLine(L"CSAA Mode 16x is Supported", 1, 1, 0);
		}

		if (sampleCount == 8 && maxQualityLevel >= 16)
		{
			counter++;
			mMSAASample[counter] = sampleCount;
			mMSAAQuality[counter] = maxQualityLevel;
			SystemLog.WriteLine(L"CSAA Mode 16xQ is Supported\n\n\tChecking MultiSampling and Anti-Aliasing Complete",
				1, 1, 0);

		}
	}

	if (FAILED(result = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION,
		&mD3D11Device, NULL, &mD3D11DeviceContext)))
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - D3D11CreateDevice() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - D3D11CreateDevice() Success", 1, 1, 0);
	}

	if (!DXGIInit())
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - DXGIInit() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - DXGIInit() Success", 1, 1, 0);
	}

	// Create swapchain information
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;										// one back buffer
	scd.BufferDesc.Format = mDXGIFormat[0];						// use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// how swap chain is to be used
	scd.OutputWindow = mhWnd;									// the window to be used
	scd.SampleDesc.Count = 4;									// how many multisamples
	scd.Windowed = TRUE;										// windowed/full-screen mode	

	// Create Swap Chain	
	if (FAILED(result = mDXGIFactory->CreateSwapChain(mD3D11Device, &scd, &mD3D11SwapChain)))
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - CreateSwapChain() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - CreateSwapChain() Success", 1, 1, 0);
	}


	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	if (FAILED(result = mD3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - mD3D11SwapChain->GetBuffer() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - mD3D11SwapChain->GetBuffer() Success", 1, 1, 0);
	}

	// use the back buffer address to create the render target
	if (FAILED(result = mD3D11Device->CreateRenderTargetView(pBackBuffer, NULL, &mD3D11RenderTargetView)))
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - mD3D11Device->CreateRenderTargetView() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - mD3D11Device->CreateRenderTargetView() Success", 1, 1, 0);
	}
	if (pBackBuffer)
	{
		pBackBuffer->Release();
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - pBackBuffer->Release() Success", 1, 1, 0);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - pBackBuffer->Release() Failed", 1, 1, 1);
	}

	if (!ResizeApp())
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - ResizeApp() Failed", 1, 1, 1);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::InitDirect3D11() - ResizeApp() Success", 1, 1, 0);
	}

	SystemLog.WriteLine(L"-- cSystem::InitDirect3D11() Success -- \n\n", 1, 1, 0);
	return true;
}

bool cSystem::ShutdownDirect3D11(void)
{
	SystemLog.WriteLine(L"-- cSystem::ShutdownDirect3D11() Begin -- \n\n", 1, 1, 0);

	// close and release all existing COM objects
	if (mD3D11SwapChain)
	{
		mD3D11SwapChain->Release();
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11SwapChain->Release() Success", 1, 1, 0);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11SwapChain->Release() Failed", 1, 1, 1);
	}

	if (mD3D11RenderTargetView)
	{
		mD3D11RenderTargetView->Release();
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11BackBuffer->Release() Success", 1, 1, 0);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11BackBuffer->Release() Failed", 1, 1, 1);
	}

	if (mD3D11SwapChain)
	{
		mD3D11Device->Release();
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11Device->Release() Success", 1, 1, 0);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11Device->Release() Failed", 1, 1, 1);
	}

	if (mD3D11SwapChain)
	{
		mD3D11DeviceContext->Release();
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11DeviceContext->Release() Success", 1, 1, 0);
	}
	else
	{
		SystemLog.WriteLine(L"cSystem::ShutdownDirect3D11() - mD3D11DeviceContext->Release() Failed", 1, 1, 1);
	}
	SystemLog.WriteLine(L"-- cSystem::ShutdownDirect3D11() Success -- \n\n", 1, 1, 0);
	return true;
}
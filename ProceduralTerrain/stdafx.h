// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib" )
#pragma comment(lib, "d3dcompiler.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<iostream>
#include<atlbase.h>

#include<vector>
#include<map>
#include<string>

#include"RenderStatement.h"

#include<d3d11.h>
#include<dxgi.h>

#include<d3dcompiler.h>

#include<DirectXMath.h>
#include<DirectXColors.h>

#include"Data.h"

#include"Geometry.h"
#include"Texture.h"

#include"Instance.h"

#include"Camera.h"

#include"Scene.h"

#include"HLSLCompiler.h"

#include"BufferManager.h"

#include"Terrain.h"

#include"Core.h"

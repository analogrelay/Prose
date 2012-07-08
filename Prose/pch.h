//
// pch.h
// Header for standard system include files.
//

#pragma once

// WRL
#include <wrl.h>
#include <collection.h>

// DirectX
#include <d3d11.h>
#include <d3d11_1.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <d2d1_1helper.h>
#include <dwrite.h>

// CRT
#include <string>
#include <stdio.h>
#include <stdarg.h>

// Prose Common
#include "Helpers.h"
#include "DX.h"
#include "Common.h"

#include "ObjectTracking.h"

// Debug thingies
#ifdef _DEBUG

//#define OBJECT_TRACKING
//#define TRACE_RENDER
//#define TRACE_LAYOUT
//#define SHOW_DOCUMENTVIEWER_BORDERS
#define SHOW_DOCUMENTHOST_BORDERS
#define SHOW_SURFACE_BORDERS

#endif
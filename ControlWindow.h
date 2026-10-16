// ControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define CONTROL_WINDOW_CLASS_NAME												WC_LISTBOX

#define CONTROL_WINDOW_EXTENDED_STYLE											WS_EX_CLIENTEDGE
#define CONTROL_WINDOW_STYLE													( WS_CHILD | LBS_NOINTEGRALHEIGHT )
// Note that control window is not visible by default
// It will be made visible when the tab is selected

#define CONTROL_WINDOW_TEXT														NULL

HWND ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL ControlWindowHide( HWND hWndControl );

BOOL ControlWindowMove( HWND hWndControl, int nLeft, int nTop, int nWidth, int nHeight );

BOOL ControlWindowShow( HWND hWndControl );

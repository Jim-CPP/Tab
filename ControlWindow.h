// ControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define CONTROL_WINDOW_CLASS_NAME												WC_LISTVIEW

#define CONTROL_WINDOW_EXTENDED_STYLE											( WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT )
#define CONTROL_WINDOW_STYLE													( WS_CHILD | LVS_REPORT )
// Note that control window is not visible by default
// It will be made visible when the tab is selected

#define CONTROL_WINDOW_TEXT														NULL

#define CONTROL_WINDOW_COLUMN_NAMES												{ "Name" }

int ControlWindowAddItem( HWND hWndControl, LPTSTR lpszItemText );

int ControlWindowAutoSizeAllColumns( HWND hWndControl );

HWND ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL ControlWindowHide( HWND hWndControl );

BOOL ControlWindowMove( HWND hWndControl, int nLeft, int nTop, int nWidth, int nHeight );

BOOL ControlWindowPopulate( HWND hWndControl, LPTSTR lpszData );

BOOL ControlWindowShow( HWND hWndControl );

typedef enum
{
	CONTROL_WINDOW_NAME_COLUMN = 0,

	CONTROL_WINDOW_NUMBER_OF_COLUMNS

} CONTROL_WINDOW_COLUMNS;

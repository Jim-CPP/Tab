// TabControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#include "ControlWindow.h"

#define TAB_CONTROL_WINDOW_CLASS_NAME											WC_TABCONTROL

#define TAB_CONTROL_WINDOW_EXTENDED_STYLE										0
#define TAB_CONTROL_WINDOW_STYLE												( WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE )
#define TAB_CONTROL_WINDOW_TEXT													NULL

#define TAB_CONTROL_WINDOW_TITLE_FORMAT_STRING									"Tab: \"%s\""

#define TAB_CONTROL_WINDOW_UNABLE_TO_SAVE_TABS_WARNING_MESSAGE					"Unable to save tabs\r\n\r\nAre you sure that you want to close?"

typedef struct
{
	TCITEMHEADER tcItemHeader;

	HWND hWndControl;
	char cData[ STRING_LENGTH + sizeof( char ) ];
	char cStatusMessage[ STRING_LENGTH + sizeof( char ) ];

} TAB_CONTROL_WINDOW_DATA;

BOOL IsTabControlWindow( HWND hWnd );

int TabControlWindowAddTab( LPCTSTR lpszItemText );

BOOL TabControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL TabControlWindowGetItemText( int nWhichItem, LPTSTR lpszItemText );

int TabControlWindowGetSelectedItem();

LRESULT TabControlWindowHandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

int TabControlWindowLoad( LPCTSTR lpszFileName );

BOOL TabControlWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

BOOL TabControlWindowOnItemSelected( int nWhichItem, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

int TabControlWindowSave( LPCTSTR lpszFileName );

BOOL TabControlWindowOnSelect( BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

HWND TabControlWindowSetFocus();

BOOL TabControlWindowUpdate();

// TabControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define TAB_CONTROL_WINDOW_CLASS_NAME											WC_TABCONTROL

#define TAB_CONTROL_WINDOW_EXTENDED_STYLE										0
#define TAB_CONTROL_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS )
#define TAB_CONTROL_WINDOW_TEXT													NULL

BOOL IsTabControlWindow( HWND hWndSupplied );

int TabControlWindowAddTab( LPCTSTR lpszTitle );

BOOL TabControlWindowCallSelectFunction( BOOL( *lpSelectFunction )( int nWhichTab, LPCTSTR lpszTitle ) );

BOOL TabControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

LRESULT TabControlWindowHandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpSelectFunction )( int nWhichTab, LPCTSTR lpszTitle ) );

BOOL TabControlWindowMove( int nLeft, int nTop, int nWidth, int nHeight );

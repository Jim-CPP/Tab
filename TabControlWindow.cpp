// TabControlWindow.cpp

#include "TabControlWindow.h"

// Global variables
static HWND g_hWndTabControl;

BOOL IsTabControlWindow( HWND hWndSupplied )
{
	BOOL bResult = FALSE;

	// See if supplied window is tab control window
	if( hWndSupplied == g_hWndTabControl )
	{
		// Supplied window is tab control window

		// Update return value
		bResult = TRUE;

	} // End of supplied window is tab control window

	return bResult;

} // End of function IsTabControlWindow

int TabControlWindowAddTab( LPCTSTR lpszTitle )
{
	int nResult = -1;

	TCITEM tcItem;
	int nTabCount;

	// Count tabs
	nTabCount = SendMessage( g_hWndTabControl, TCM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Clear tab control item structure
	ZeroMemory( &tcItem, sizeof( tcItem ) );

	// Initialise tab control item structure
	tcItem.mask		= TCIF_TEXT | TCIF_IMAGE;
	tcItem.iImage	= -1;
	tcItem.pszText	= ( LPTSTR )lpszTitle;

	// Add tab
	nResult = SendMessage( g_hWndTabControl, TCM_INSERTITEM, ( WPARAM )nTabCount, ( LPARAM )&tcItem );

	return nResult;

} // End of function TabControlWindowAddTab

BOOL TabControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	BOOL bResult = FALSE;

	// Create tab control window
	g_hWndTabControl = CreateWindowEx( TAB_CONTROL_WINDOW_EXTENDED_STYLE, TAB_CONTROL_WINDOW_CLASS_NAME, TAB_CONTROL_WINDOW_TEXT, TAB_CONTROL_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that tab control window was created
	if( g_hWndTabControl )
	{
		// Successfully created tab control window

		// Set tab control window font
		SendMessage( g_hWndTabControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created tab control window

	return bResult;

} // End of function TabControlWindowCreate

BOOL TabControlWindowMove( int nLeft, int nTop, int nWidth, int nHeight )
{
	// Move tab control window
	return MoveWindow( g_hWndTabControl, nLeft, nTop, nWidth, nHeight, TRUE );

} // End of function TabControlWindowMove

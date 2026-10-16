// ControlWindow.cpp

#include "ControlWindow.h"

HWND ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	HWND hWndControl;

	// Create control window
	hWndControl = CreateWindowEx( CONTROL_WINDOW_EXTENDED_STYLE, CONTROL_WINDOW_CLASS_NAME, CONTROL_WINDOW_TEXT, CONTROL_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that control window was created
	if( hWndControl )
	{
		// Successfully created control window

		// Set control window font
		SendMessage( hWndControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

	} // End of successfully created control window

	return hWndControl;

} // End of function ControlWindowCreate

BOOL ControlWindowHide( HWND hWndControl )
{
	// Hide control window
	return ShowWindow( hWndControl, SW_HIDE );

} // End of function ControlWindowHide

BOOL ControlWindowMove( HWND hWndControl, int nLeft, int nTop, int nWidth, int nHeight )
{
	// Move control window
	return SetWindowPos( hWndControl, NULL, nLeft, nTop, nWidth, nHeight, SWP_NOACTIVATE );

} // End of function ControlWindowMove

BOOL ControlWindowShow( HWND hWndControl )
{
	// Show control window
	return ShowWindow( hWndControl, SW_SHOWNORMAL );

} // End of function ControlWindowShow

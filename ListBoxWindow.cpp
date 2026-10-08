// ListBoxWindow.cpp

#include "ListBoxWindow.h"

// Global variables
static HWND g_hWndListBox;

BOOL IsListBoxWindow( HWND hWndSupplied )
{
	BOOL bResult = FALSE;

	// See if supplied window is list box window
	if( hWndSupplied == g_hWndListBox )
	{
		// Supplied window is list box window

		// Update return value
		bResult = TRUE;

	} // End of supplied window is list box window

	return bResult;

} // End of function IsListBoxWindow

int ListBoxWindowAddText( LPCTSTR lpszText )
{
	// Add text to list box window
	return SendMessage( g_hWndListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszText );

} // End of function ListBoxWindowAddText

BOOL ListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	BOOL bResult = FALSE;

	// Create list box window
	g_hWndListBox = CreateWindowEx( LIST_BOX_WINDOW_EXTENDED_STYLE, LIST_BOX_WINDOW_CLASS_NAME, LIST_BOX_WINDOW_TEXT, LIST_BOX_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that list box window was created
	if( g_hWndListBox )
	{
		// Successfully created list box window

		// Set list box window font
		SendMessage( g_hWndListBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created list box window

	return bResult;

} // End of function ListBoxWindowCreate

LRESULT ListBoxWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) )
{
	LRESULT lResult = 0;

	// Select list box window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A list box window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get selected item
			nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Display selected item text
				MessageBox( hWndMain, lpszSelected, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );;

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a list box window double click notification code
		case LBN_SELCHANGE:
		{
			// A list box window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get selected item
			nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Call status function
				( *lpStatusFunction )( lpszSelected );

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a list box window selection change notification code
		default:
		{
			// Default list box window notification code

			// Call default procedure
			lResult = DefWindowProc( hWndMain, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default list box window notification code

	}; // End of selection for list box window notification code

	return lResult;

} // End of function ListBoxWindowHandleCommandMessage

BOOL ListBoxWindowMove( int nLeft, int nTop, int nWidth, int nHeight )
{
	// Move list box window
	return MoveWindow( g_hWndListBox, nLeft, nTop, nWidth, nHeight, TRUE );

} // End of function ListBoxWindowMove

int ListBoxWindowPopulate()
{
	int nResult;

	// Add text to list box window
	ListBoxWindowAddText( "1234567890" );
	ListBoxWindowAddText( "qwertyuiop" );
	ListBoxWindowAddText( "asdfghjkl" );
	ListBoxWindowAddText( "zxcvbnm" );

	// Update return value
	nResult = SendMessage( g_hWndListBox, LB_GETCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	return nResult;

} // End of function ListBoxWindowPopulate

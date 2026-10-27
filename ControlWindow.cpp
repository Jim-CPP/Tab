// ControlWindow.cpp

#include "ControlWindow.h"

int ControlWindowAddItem( HWND hWndControl, LPTSTR lpszItemText )
{
	int nResult = 0;

	LVITEM lvItem;
	int nItemCount;

	// Count items on list view window
	nItemCount = SendMessage( hWndControl, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= STRING_LENGTH;
	lvItem.iItem		= nItemCount;
	lvItem.iSubItem		= 0;
	lvItem.pszText		= lpszItemText;

	// Add item to list view window
	nResult = SendMessage( hWndControl, LVM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )&lvItem );

	return nResult;

} // End of function ControlWindowAddItem

int ControlWindowAutoSizeAllColumns( HWND hWndControl )
{
	int nResult = 0;

	int nWhichColumn;

	// Loop through all columns
	for( nWhichColumn = 0; nWhichColumn < CONTROL_WINDOW_NUMBER_OF_COLUMNS; nWhichColumn ++ )
	{
		// Auto-size current column
		if( SendMessage(hWndControl, LVM_SETCOLUMNWIDTH, ( WPARAM )nWhichColumn, ( LPARAM )LVSCW_AUTOSIZE_USEHEADER ) )
		{
			// Successfully auto-sized current column

			// Update return value
			nResult ++;

		} // End of successfully auto-sized current column

	}; // End of loop through all columns

	return nResult;

} // End of function ControlWindowUpdateColumnWidths

HWND ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	HWND hWndControl;

	// Create control window
	hWndControl = CreateWindowEx( CONTROL_WINDOW_EXTENDED_STYLE, CONTROL_WINDOW_CLASS_NAME, CONTROL_WINDOW_TEXT, CONTROL_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that control window was created
	if( hWndControl )
	{
		// Successfully created control window
		LVCOLUMN lvColumn;
		int nWhichColumn;
		LPCTSTR lpszColumnTitles [] = CONTROL_WINDOW_COLUMN_NAMES;

		// Set control window font
		SendMessage( hWndControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Set extended list view window style
		SendMessage( hWndControl, LVM_SETEXTENDEDLISTVIEWSTYLE, ( WPARAM )0, ( LPARAM )CONTROL_WINDOW_EXTENDED_STYLE );

		// Clear list view window column structure
		ZeroMemory( &lvColumn, sizeof( lvColumn ) );

		// Initialise list view window column structure
		lvColumn.mask = ( LVCF_TEXT | LVCF_SUBITEM );

		// Loop through all columns
		for( nWhichColumn = 0; nWhichColumn < CONTROL_WINDOW_NUMBER_OF_COLUMNS; nWhichColumn ++ )
		{
			// Initialise list view window column structure for current column
			lvColumn.pszText = ( LPTSTR )( lpszColumnTitles[ nWhichColumn ] );

			// Insert column
			SendMessage(hWndControl, LVM_INSERTCOLUMN, ( WPARAM )nWhichColumn, ( LPARAM )&lvColumn );

		}; // End of loop through all columns

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
	BOOL bResult = FALSE;

	// Move control window
	if( SetWindowPos( hWndControl, NULL, nLeft, nTop, nWidth, nHeight, SWP_NOACTIVATE ) )
	{
		// Successfully moved control window

		// Auto-size all columns
		ControlWindowAutoSizeAllColumns( hWndControl );

	} // End of successfully moved control window

	return bResult;

} // End of function ControlWindowMove

BOOL ControlWindowShow( HWND hWndControl )
{
	// Show control window
	return ShowWindow( hWndControl, SW_SHOWNORMAL );

} // End of function ControlWindowShow

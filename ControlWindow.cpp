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

		// Update return value
		bResult = TRUE;

	} // End of successfully moved control window

	return bResult;

} // End of function ControlWindowMove

BOOL ControlWindowPopulate( HWND hWndControl, LPTSTR lpszData )
{
	BOOL bResult = FALSE;

	WIN32_FIND_DATA wfd;
	HANDLE hFind;

	// Allocate string memory
	LPTSTR lpszParentFolderPath		= new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszFullSearchPattern	= new char[ STRING_LENGTH + sizeof( char ) ];

	// Store parent folder path
	lstrcpy( lpszParentFolderPath, lpszData );

	// Ensure that parent folder path ends with a back-slash
	if( lpszParentFolderPath[ lstrlen( lpszParentFolderPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
	{
		// Parent folder path does not end with a back-slash

		// Append a back-slash onto parent folder path
		lstrcat( lpszParentFolderPath, ASCII_BACK_SLASH_STRING );

	} // End of parent folder path does not end with a back-slash

	// Copy parent folder path into full search pattern
	lstrcpy( lpszFullSearchPattern, lpszParentFolderPath );

	// Append all files filter onto full search pattern
	lstrcat( lpszFullSearchPattern, ALL_FILES_FILTER );

	// Find the first item
	hFind = FindFirstFile( lpszFullSearchPattern, &wfd );

	// Ensure that first item was found
	if( hFind != INVALID_HANDLE_VALUE )
	{
		// Successfully found first item
		LVITEM lvItem;
		int nItem;

		// Delete all items on list view window
		SendMessage( hWndControl, LVM_DELETEALLITEMS, ( WPARAM )NULL, ( LPARAM )NULL );

		// Clear list view item structure
		ZeroMemory( &lvItem, sizeof( lvItem ) );

		// Initialise list view item structure
		lvItem.mask			= LVIF_TEXT;
		lvItem.cchTextMax	= STRING_LENGTH;
		lvItem.iItem		= 0;

		// Loop through all found items
		do
		{
			// See if found item is a folder
			if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// Found item is a folder

				// Ensure that found item is not dots
				if( wfd.cFileName[ 0 ] != ASCII_FULL_STOP_CHARACTER )
				{
					// Found item is not dots

					// Update list view item structure for found item
					lvItem.iSubItem	= 0;
					lvItem.pszText	= wfd.cFileName;

					// Add item to list view window
					nItem = SendMessage( hWndControl, LVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&lvItem );

					// Ensure that item was added to list view window
					if( nItem >= 0 )
					{
						// Successfully added item was added to list view window

					} // End of successfully added item was added to list view window

				} // End of found item is not dots

			} // End of found item is a folder
			else
			{
				// Found item is a file

				// Update list view item structure for found item
				lvItem.iSubItem	= 0;
				lvItem.pszText	= wfd.cFileName;

				// Add item to list view window
				nItem = SendMessage( hWndControl, LVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&lvItem );

				// Ensure that item was added to list view window
				if( nItem >= 0 )
				{
					// Successfully added item was added to list view window

				} // End of successfully added item was added to list view window

			} // End of found item is a file

		} while( FindNextFile( hFind, &wfd ) != 0 ); // End of loop through all found items

		// Update return value
		bResult = TRUE;

		// Close file find
		FindClose( hFind );

	} // End of successfully found first item

	return bResult;

} // End of function ControlWindowPopulate

BOOL ControlWindowShow( HWND hWndControl )
{
	// Show control window
	return ShowWindow( hWndControl, SW_SHOWNORMAL );

} // End of function ControlWindowShow

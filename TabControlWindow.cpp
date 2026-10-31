// TabControlWindow.cpp

#include "TabControlWindow.h"

// Global variables
static HWND g_hWndTabControl;
static HWND g_hWndSelectedControl;

BOOL IsTabControlWindow( HWND hWnd )
{
	// See if supplied window is tab control window
	return( hWnd == g_hWndTabControl );

} // End of function IsTabControlWindow

int TabControlWindowAddTab( LPCTSTR lpszData )
{
	int nResult = -1;

	HWND hWndControl;
	HFONT hFont;

	// Get font
	hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

	// Create control window
	hWndControl = ControlWindowCreate( g_hWndTabControl, NULL, hFont );

	// Ensure that control window was created
	if( hWndControl )
	{
		// Successfully created control window
		TAB_CONTROL_WINDOW_DATA tcwData;
		int nItemCount;

		// Allocate string memory
		LPTSTR lpszTitle = new char[ STRING_LENGTH + sizeof( char ) ];

		// Format title
		wsprintf( lpszTitle, TAB_CONTROL_WINDOW_TITLE_FORMAT_STRING, lpszData );

		// Clear tab control window data structure
		ZeroMemory( &tcwData, sizeof( tcwData ) );

		// Initialise tab control window data structure
		tcwData.tcItemHeader.mask		= ( TCIF_TEXT | TCIF_PARAM );
		tcwData.tcItemHeader.cchTextMax	= STRING_LENGTH;
		tcwData.tcItemHeader.pszText	= lpszTitle;
		tcwData.hWndControl				= hWndControl;

		// Update tab control window data string
		lstrcpy( tcwData.cData, lpszData );

		// Populate control window
		ControlWindowPopulate( tcwData.hWndControl, ( LPTSTR )lpszData, tcwData.cStatusMessage );

		// Count items on tab
		nItemCount = SendMessage( g_hWndTabControl, TCM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Add tab
		nResult = SendMessage( g_hWndTabControl, TCM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )( LPTCITEMHEADER )( &tcwData ) );

	} // End of successfully created control window

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
		int nExtraBytes;

		// Calculate extra bytes
		nExtraBytes = ( sizeof( TAB_CONTROL_WINDOW_DATA ) - sizeof( TCITEMHEADER ) );

		// Allocate extra memory for tab data
		if( SendMessage( g_hWndTabControl, TCM_SETITEMEXTRA, ( WPARAM )nExtraBytes, ( LPARAM )NULL ) )
		{
			// Successfully allocated extra memory for tab data

			// Set tab control window font
			SendMessage( g_hWndTabControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

			// Clear selected control window
			g_hWndSelectedControl = NULL;

			// Update return value
			bResult = TRUE;

		} // End of successfully allocated extra memory for tab data

	} // End of successfully created tab control window

	return bResult;

} // End of function TabControlWindowCreate

BOOL TabControlWindowGetItemText( int nWhichItem, LPTSTR lpszItemText )
{
	BOOL bResult = FALSE;

	TCITEM tcItem;

	// Clear tab control item structure
	ZeroMemory( &tcItem, sizeof( tcItem ) );

	// Initialise tab control item structure
	tcItem.mask			= TCIF_TEXT;
	tcItem.cchTextMax	= STRING_LENGTH;
	tcItem.pszText		= lpszItemText;

	// Get tab control item
	if( SendMessage( g_hWndTabControl, TCM_GETITEM, ( WPARAM )nWhichItem, ( LPARAM )&tcItem ) )
	{
		// Successfully got tab control item

		// Update return value
		bResult = TRUE;

	} // End of successfully got tab control item

	return bResult;

} // End of function TabControlWindowGetItemText

BOOL TabControlWindowGetRect( LPRECT lpRect )
{
	// Get tab control window rect
	return GetWindowRect( g_hWndTabControl, lpRect );

} // End of function TabControlWindowGetRect

int TabControlWindowGetSelectedItem()
{
	// Get selected item
	return SendMessage( g_hWndTabControl, TCM_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function TabControlWindowGetSelectedItem

LRESULT TabControlWindowHandleNotifyMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) )
{
	LRESULT lResult = 0;

	LPNMHDR lpNmhdr;

	// Get notify message handler
	lpNmhdr = ( ( LPNMHDR )lParam );

	// Select tab control window notification code
	switch( lpNmhdr->code )
	{
		case TCN_SELCHANGING:
		{
			// A selection changing notification code

			// Break out of switch
			break;

		}// End of a selection changing notification code
		case TCN_SELCHANGE:
		{
			// A selection change notification code

			// Select item
			TabControlWindowOnSelect( lpStatusFunction );

			// Break out of switch
			break;

		}// End of a selection change notification code
		default:
		{
			// Default notification code

			// Call default window procedure
			lResult = DefWindowProc( hWndMain, WM_NOTIFY, wParam, lParam );

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for tab control window notification code

	return lResult;

} // End of function TabControlWindowHandleNotifyMessage

int TabControlWindowLoad( LPCTSTR lpszFileName )
{
	int nResult = 0;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size

			// Allocate string memory
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text
				LPTSTR lpszTab;

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Get first tab
				lpszTab = strtok( lpszFileText, NEW_LINE_TEXT );

				// Loop through all tabs
				while( lpszTab )
				{
					// Add tab
					if( TabControlWindowAddTab( lpszTab ) >= 0 )
					{
						// Successfully added tab

						// Update return value
						nResult ++;

						// Get next tab
						lpszTab = strtok( NULL, NEW_LINE_TEXT );

					} // End of successfully added tab
					else
					{
						// Unable to add tab

						// Force exit from loop
						lpszTab = NULL;

					} // End of unable to add tab

				}; // End of loop through all tabs

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return nResult;

} // End of function TabControlWindowLoad

BOOL TabControlWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	BOOL bResult = FALSE;

	// Move tab control window
	if( MoveWindow( g_hWndTabControl, nX, nY, nWidth, nHeight, bRepaint ) )
	{
		// Successfully moved tab control window

			// Update tab control window (to resize control windows)
			if( TabControlWindowUpdate() )
			{
				// Successfully updated tab control window (to resize control windows)

				// Update return value
				bResult = TRUE;

			} // End of successfully updated tab control window (to resize control windows)

	} // End of successfully moved tab control window

	return bResult;

} // End of function TabControlWindowMove

BOOL TabControlWindowOnSelect( BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	int nSelectedItem;

	// Get selected item
	nSelectedItem = SendMessage( g_hWndTabControl, TCM_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

	// Ensure that selected item was got
	if( nSelectedItem >= 0 )
	{
		// Successfully got selected item
		TAB_CONTROL_WINDOW_DATA tcwData;

		// Clear tab control window data structure
		ZeroMemory( &tcwData, sizeof( tcwData ) );

		// Initialise tab control window data structure
		tcwData.tcItemHeader.mask = TCIF_PARAM;

		// Get tab control window data
		if( SendMessage( g_hWndTabControl, TCM_GETITEM, ( WPARAM )nSelectedItem, ( LPARAM )( LPTCITEMHEADER )( &tcwData ) ) )
		{
			// Successfully got tab control window data

			// Show item text on status bar window
			( *lpStatusFunction )( tcwData.cStatusMessage );

			// See if selected control window is valid
			if( g_hWndSelectedControl )
			{
				// Selected control window is valid

				// Hide selected control window
				ControlWindowHide( g_hWndSelectedControl );

			} // End of selected control window is valid

			// Update selected control window
			g_hWndSelectedControl = tcwData.hWndControl;

			// Update tab control window (to resize control windows)
			TabControlWindowUpdate();

			// Show selected control window
			ControlWindowShow( g_hWndSelectedControl );

			// Update return value
			bResult = TRUE;

		} // End of successfully got tab control window data

	} // End of successfully got selected item

	return bResult;

} // End of function TabControlWindowOnSelect

int TabControlWindowSave( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		int nTabCount;
		int nWhichTab;
		DWORD dwDataLength;
		DWORD dwNewLineTextLength;

		// Update return value (assume success)
		bResult = TRUE;

		// Get new line text length
		dwNewLineTextLength = lstrlen( NEW_LINE_TEXT );

		// Count tabs
		nTabCount = SendMessage( g_hWndTabControl, TCM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Loop through all tabs
		for( nWhichTab = 0; nWhichTab < nTabCount; nWhichTab ++ )
		{
			TAB_CONTROL_WINDOW_DATA tcwData;

			// Clear tab control window data structure
			ZeroMemory( &tcwData, sizeof( tcwData ) );

			// Initialise tab control window data structure
			tcwData.tcItemHeader.mask = TCIF_PARAM;

			// Get tab control window data
			if( SendMessage( g_hWndTabControl, TCM_GETITEM, ( WPARAM )nWhichTab, ( LPARAM )( LPTCITEMHEADER )( &tcwData ) ) )
			{
				// Successfully got tab control window data

				// Get data length
				dwDataLength = lstrlen( tcwData.cData );

				// Write data to file
				if( WriteFile( hFile, tcwData.cData, dwDataLength, NULL, NULL ) )
				{
					// Successfully wrote data to file

					// Write new line text to file
					WriteFile( hFile, NEW_LINE_TEXT, dwNewLineTextLength, NULL, NULL );

				} // End of successfully wrote data to file
				else
				{
					// Unable to write data to file

					// Update return value
					bResult = FALSE;

					// Force exit from loop
					nWhichTab = nTabCount;

				} // End of unable to write data to file

			} // End of successfully got tab control window data
			else
			{
				// Unable to get tab control window data

				// Update return value
				bResult = FALSE;

				// Force exit from loop
				nWhichTab = nTabCount;

			} // End of unable to get tab control window data

		}; // End of loop through all tabs

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function TabControlWindowSave

HWND TabControlWindowSetFocus()
{
	// Focus on tab control window
	return SetFocus( g_hWndTabControl );

} // End of function TabControlWindowSetFocus

BOOL TabControlWindowUpdate()
{
	BOOL bResult = FALSE;

	RECT rc;

	// Get tab control window client size
	if( GetClientRect( g_hWndTabControl, &rc ) )
	{
		// Successfully got tab control window client size
		int nControlWindowWidth;
		int nControlWindowHeight;

		// Adjust rect to fit control window
		SendMessage( g_hWndTabControl, TCM_ADJUSTRECT, ( WPARAM )FALSE, ( LPARAM )&rc );

		// Calculate control window size
		nControlWindowWidth		= ( rc.right - rc.left );
		nControlWindowHeight	= ( rc.bottom - rc.top );

		// Move selected control window
		if( ControlWindowMove( g_hWndSelectedControl, rc.left, rc.top, nControlWindowWidth, nControlWindowHeight ) )
		{
			// Successfully moved selected control window

			// Update return value
			bResult = TRUE;

		} // End of successfully moved selected control window

	} // End of successfully got tab control window client size

	return bResult;

} // End of function TabControlWindowUpdate

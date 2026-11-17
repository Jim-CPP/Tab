// BrowseForFolder.cpp

#include "BrowseForFolder.h"

INT CALLBACK BrowseCallbackFunction( HWND hWndBrowse, UINT uMessage, LPARAM, LPARAM lpData )
{
	int nResult = 0;

	// Select message
	switch( uMessage )
	{
		case BFFM_INITIALIZED:
		{
			// A browse for folder initialised message

			// Select initial folder
			SendMessage( hWndBrowse, BFFM_SETSELECTION, ( WPARAM )TRUE, ( LPARAM )lpData );

		} // End of a browse for folder initialised message

	}; // End of selection for message

	return nResult;

} // End of function BrowseCallbackFunction

BOOL BrowseForFolder( HWND hWndParent, LPTSTR lpszFolderPath )
{
	BOOL bResult = FALSE;

	BROWSEINFO browseInfo;
	LPITEMIDLIST lpItemIdList;

	// Clear browse information structure
	ZeroMemory( &browseInfo, sizeof( browseInfo ) );

	// Initialise browse information structure
	browseInfo.hwndOwner		= hWndParent;
	browseInfo.pidlRoot			= NULL;
	browseInfo.pszDisplayName	= lpszFolderPath;
	browseInfo.lpszTitle		= BROWSE_FOR_FOLDER_TITLE;
	browseInfo.ulFlags			= 0;
	browseInfo.lpfn				= BrowseCallbackFunction;
	browseInfo.lParam			= ( LPARAM )lpszFolderPath; // For use in BFFM_INITIALIZED
	browseInfo.iImage			= -1;

	// Browse for folder
	lpItemIdList = SHBrowseForFolder( &browseInfo );

	// Ensure that browse was successful
	if( lpItemIdList )
	{
		// Successfully browsed for folder

		// Get folder path
		if( SHGetPathFromIDList( lpItemIdList, lpszFolderPath ) )
		{
			// Successfully got folder path

			// Update return value
			bResult = TRUE;

		} // End of successfully got folder path

	} // End of successfully browsed for folder

	return bResult;

} // End of function BrowseForFolder

// ListBoxWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define LIST_BOX_WINDOW_CLASS_NAME												WC_LISTBOX

#define LIST_BOX_WINDOW_EXTENDED_STYLE											0
#define LIST_BOX_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define LIST_BOX_WINDOW_TEXT													NULL

#define LIST_BOX_WINDOW_POPULATE_STATUS_MESSAGE_FORMAT_STRING					"%d items"

BOOL IsListBoxWindow( HWND hWndSupplied );

int ListBoxWindowAddText( LPCTSTR lpszText );

BOOL ListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

LRESULT ListBoxWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszItemText ) );

BOOL ListBoxWindowMove( int nLeft, int nTop, int nWidth, int nHeight );

int ListBoxWindowPopulate();

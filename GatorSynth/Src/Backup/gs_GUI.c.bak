#include "DIALOG.h"
#include "gs_GUI.h"
#include "sdio.h"
#include "synthesis.h"
#include <string.h>

#define ID_WINDOW_0    (GUI_ID_USER + 0x00)
#define ID_BUTTON_0    (GUI_ID_USER + 0x01)
#define ID_SLIDER_0    (GUI_ID_USER + 0x02)
#define ID_LISTBOX_0    (GUI_ID_USER + 0x03)
#define ID_SLIDER_2   (GUI_ID_USER + 0x04)

#define ID_WINDOW_1     (GUI_ID_USER + 0x10)
#define ID_BUTTON_1     (GUI_ID_USER + 0x11)

WM_HWIN hWin1;
WM_HWIN hWin2;
WM_HWIN sliderItem1;
WM_HWIN sliderItem2;
uint32_t readValue = 0;
extern struct SoundFile sample;

static const GUI_WIDGET_CREATE_INFO _aDialogCreateWin1[] =
		{
			  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 320, 240, 0, 0x0, 0 },
			  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 27, 24, 80, 20, 0, 0x0, 0 },
			  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 25, 95, 268, 20, 0, 0x0, 0 },
			  { LISTBOX_CreateIndirect, "Listbox", ID_LISTBOX_0, 218, 16, 80, 60, 0, 0x0, 0 },
			  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_2, 31, 169, 264, 20, 0, 0x0, 0 },};

static const GUI_WIDGET_CREATE_INFO _aDialogCreateWin2[] =
{
{ WINDOW_CreateIndirect, "Window", ID_WINDOW_1, 0, 0, 320, 240, 0, 0x0, 0 },
{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 223, 98, 80, 20, 0, 0x0, 0 }, };

static void win1Callback(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;
	int NCode;
	int Id;


	//Make sure slider range is valid based on current sample
	sliderItem1 = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
	SLIDER_SetRange(sliderItem1, 1, sample.numSamples - 1);
	sliderItem2 = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
	SLIDER_SetRange(sliderItem2, 0, sample.numSamples - 1);

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		//
		// Initialization of 'Listbox'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);

		open_dir("/");
		char* fileName = "";
		while(strcmp(fileName = read_one_name(), "done\0"))
		{
			LISTBOX_AddString(hItem, fileName);
		}

		SLIDER_SetValue(sliderItem2, sample.numSamples - 1);

		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id)
		{
		case ID_BUTTON_0: // Notifications sent by 'Button'
			switch (NCode)
			{
			case WM_NOTIFICATION_CLICKED:
				WM_HideWindow(hWin1);
				WM_ShowWindow(hWin2);
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;
		case ID_SLIDER_0: // Notifications sent by 'Slider'
			switch (NCode)
			{
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_VALUE_CHANGED:
				readValue = (uint32_t) SLIDER_GetValue(sliderItem1);
				if(readValue > sample.startSample)
					sample.endSample = readValue;
				break;
			}
			break;
		case ID_SLIDER_2: // Notifications sent by 'Slider'
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_VALUE_CHANGED:
				readValue = (uint32_t) SLIDER_GetValue(sliderItem2);
				if(readValue < sample.endSample)
					sample.startSample = readValue;
				break;
			}
			break;
		case ID_LISTBOX_0: // Notifications sent by 'Listbox'
			switch (NCode)
			{
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				break;
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

static void win2Callback(WM_MESSAGE * pMsg)
{
	int NCode;
	int Id;
	switch (pMsg->MsgId)
	{
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id)
		{
		case ID_BUTTON_1: // Notifications sent by 'Button'
			switch (NCode)
			{
			case WM_NOTIFICATION_CLICKED:
				WM_HideWindow(hWin2);
				WM_ShowWindow(hWin1);
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN Createmenu1(void)
{
	hWin1 = GUI_CreateDialogBox(_aDialogCreateWin1,
			GUI_COUNTOF(_aDialogCreateWin1), win1Callback, WM_HBKWIN, 0, 0);
	return hWin1;
}

WM_HWIN Createmenu2(void)
{
	hWin2 = GUI_CreateDialogBox(_aDialogCreateWin2,
			GUI_COUNTOF(_aDialogCreateWin2), win2Callback, WM_HBKWIN, 0, 0);
	return hWin2;
}

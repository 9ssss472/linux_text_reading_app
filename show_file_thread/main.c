#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <config.h>
#include <draw.h>
#include <encoding_manager.h>
#include <fonts_manager.h>
#include <display.h>
#include <string.h>
#include "input.h"
#include "debug_manager.h"

/*
*@Usage:./filename -s wordsize -d screentype -f wordtype -h hzk textname
*/
int main(int argc, char ** argv)
{

    int iError;
    int bList = 0;
    int iFontSize = 16;
    char acDisplay[128];
    char acFreeTypeFile[128];
    char acGbkFile[128];
    char acTextFile[128];
    T_EventOpr g_tEventOpr;

    iError = DebugInit();
    if (iError)
	{
		DBG_PRINTF("DebugInit error!\n");
		return -1;
	}
    printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    iError = DebugChanelInit();
    if (iError)
	{
		DBG_PRINTF("DebugChanelInit error!\n");
		return -1;
	}

    printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    while((iError = getopt(argc, argv, "ls:d:f:h:")) != -1)
    {
        switch (iError)
        {
        case 'l':
            bList = 1;
            break;
        
        case 's':
            iFontSize = strtoul(optarg, NULL, 0);
            break;

        case 'd':
            strncpy(acDisplay, optarg, 128);
            acDisplay[127] = '\0';
            break;

        case 'f':
            strncpy(acFreeTypeFile,optarg, 128);
            acFreeTypeFile[127] = '\0';
            break;

        case 'h':
            strncpy(acGbkFile, optarg, 128);
            acGbkFile[127] = '\0';
            break;
        
        default:
            DBG_PRINTF("Usage: %s [-s Size] [-d display] [-f font_file] [-h HZK] <text_file>\n", argv[0]);
            DBG_PRINTF("Usage: %s -l\n", argv[0]);
            return -1;
        }
    }

    if(!bList && (optind >=argc) )
    {
        DBG_PRINTF("Usage: %s [-s Size] [-d display] [-f font_file] [-h HZK] <text_file>\n", argv[0]);
        DBG_PRINTF("Usage: %s -l\n", argv[0]);
        return -1;
    }
    DBG_PRINTF("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    iError = DisplayInit();
    if(iError)
    {
        DBG_PRINTF("DisplayInit failed!\r\n");
        return -1;
    }



    iError = FontInit();
    if (iError)
	{
		DBG_PRINTF("FontsInit error!\n");
		return -1;
	}

 

    iError = EncodingInit();
    if (iError)
	{
		DBG_PRINTF("EncodingInit error!\n");
		return -1;
	}

    iError = InputInit();
    if(iError)
    {
        DBG_PRINTF("InputInit failed\r\n");
        return -1;
    }

   

    if (bList)
	{
		DBG_PRINTF("supported display:\n");
		showDispOpr();

		DBG_PRINTF("supported font:\n");
		showFontOpr();

		DBG_PRINTF("supported encoding:\n");
		showEncodingOpr();

        DBG_PRINTF("supported input:\n");
        showInputOpr();

        DBG_PRINTF("supported debug:\n");
        ShowInputOpr();

		return 0;
	}

    strncpy(acTextFile, argv[optind], 128);
    acTextFile[127] = '\0';


    iError = OpenTextFile(acTextFile);
    if(iError)
    {
        DBG_PRINTF("OpenTextFile failed\r\n");
        return -1;
    }

    

    iError = SetTextDetail(acGbkFile,acFreeTypeFile,iFontSize );
    if(iError)
    {
        DBG_PRINTF("SetTextDetail failed\r\n");
        return -1;
    }

    iError = SelectDiapOpr(acDisplay);
    if(iError)
    {
        DBG_PRINTF("SelectDiapOpr failed\r\n");
        return -1;
    }


    iError = AllInputDevicesInit();
    if(iError)
    {
        DBG_PRINTF("AllInputDevicesInit failed\r\n");
        return -1;
    }


    iError = ShowNextPage();
    if(iError)
    {
        DBG_PRINTF("ShowNextPage failed\r\n");
        return -1;
    }

    while(1)
    {
        if (0  == GetInputEvent(&g_tEventOpr))
        {
            if(g_tEventOpr.iVal == INPUT_VALUE_UP)
            {
                ShowPrePage();
            }
            else if(g_tEventOpr.iVal == INPUT_VALUE_DOWN)
            {
                ShowNextPage();
            }
            else if(g_tEventOpr.iVal == INPUT_VALUE_EXIT)
            {
                return 0;
            }
        }
    }

    return 0;
}
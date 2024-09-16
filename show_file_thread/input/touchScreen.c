#include "input.h"
#include <tslib.h>
#include "display.h"
#include "config.h"

static int TouchScreenInit(void);
static int GetTouchScreenEvent(PT_EventOpr ptEventOpr);

T_InputOpr T_TouchScreenOpr =  {
    .name = "TouchScreen",
    .InputDevInit = TouchScreenInit,
    .GetInputEvent = GetTouchScreenEvent,
};

struct tsdev * g_tsdev;
int g_iXres, g_iYres;

static int TouchScreenInit(void)
{
    g_tsdev = ts_setup(NULL, 0);
    if(g_tsdev == NULL)
    {
        DBG_PRINTF("ts_setup failed!\r\n");
        return -1;
    }

    if(getResolution(&g_iXres, &g_iYres))
    {
        DBG_PRINTF("getResolution failed\r\n");
        return -1;
    }

    return 0;
}


static int isOutOf500ms(struct timeval *preTime, struct timeval *curTime)
{
    unsigned int preMs, curMs;

    preMs = preTime ->tv_sec * 1000 + preTime ->tv_usec /1000;
    curMs = curTime ->tv_sec * 1000 + curTime ->tv_usec /1000;

    return (curMs > preMs + 500);
}


static int GetTouchScreenEvent(PT_EventOpr ptEventOpr)
{
    struct ts_sample tSample;
    static struct timeval tPreTime;
    int iRet;


    iRet = ts_read(g_tsdev, &tSample, 1);
    if(iRet < 0)
    {
        return -1;
    }

    if(isOutOf500ms(&tPreTime, &tSample.tv))
    {
        tPreTime = tSample.tv;

        ptEventOpr ->tTime = tSample.tv;
        ptEventOpr ->iType = INPUT_TYPE_TOUCHSCREEN;

        if(tSample.y < g_iYres / 3)
        {
            ptEventOpr ->iVal = INPUT_VALUE_UP;
        }
        else if(tSample.y > g_iYres *2 /3 )
        {
            ptEventOpr ->iVal = INPUT_VALUE_DOWN;
        }
        else
        {
            ptEventOpr ->iVal = INPUT_VALUE_UNKNOWN;
        }
            return 0;
    }
    else
    {
        return -1;
    }

    return 0;
}


int registerTouchScreen(void)
{
    return registerInputOpr(&T_TouchScreenOpr);
}

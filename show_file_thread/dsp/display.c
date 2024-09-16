#include "display.h"
#include <string.h>
#include "config.h"

static PT_dispOpr PT_dispOprHead = NULL;

/*
*@brief:为链表添加表头或节点
*/
int registerDisOpr(PT_dispOpr dispOpr)
{
    if(PT_dispOprHead == NULL)
    {
        PT_dispOprHead = dispOpr;
        dispOpr ->pNext = NULL;
    }
    else
    {
        PT_dispOpr PT_Tmp = PT_dispOprHead;

        while(PT_Tmp ->pNext != NULL)
        {
            PT_Tmp = PT_Tmp ->pNext;
        }
        PT_Tmp ->pNext = dispOpr;
        dispOpr ->pNext = NULL;

    }
    
    return 0;
}

/*
*@brief:把链表上各个节点的名字打印出来
*/
int showDispOpr(void)
{
    int i = 1;

    PT_dispOpr PT_Tmp = PT_dispOprHead;

    while(PT_Tmp)
    {
        DBG_PRINTF("%d: %s\r\n",i++,PT_Tmp ->name);
        PT_Tmp = PT_Tmp ->pNext;
    }

    return 0;
}


/*
*@brief:获取name符合参数一的节点
*/
PT_dispOpr getDispOpr(char * name)
{
    PT_dispOpr PT_Tmp = PT_dispOprHead;

    while(PT_Tmp)
    {
        if(strcmp(name, PT_Tmp ->name) == 0)
        {
            return PT_Tmp;
        }

        PT_Tmp = PT_Tmp ->pNext;
    }
    return NULL;
}



int DisplayInit(void)
{
    int Error;

    Error = FbInit();

    return Error;
}
#include "fonts_manager.h"
#include "string.h"
#include "config.h"

static  PT_FontOpr g_ptFontOprHead = NULL;
/*
*@brief:为链表添加一给新的PT_FontOpr类型的节点
*/       
int registerFontOpr(PT_FontOpr fontOpr)
{

    if(!g_ptFontOprHead)   
    {
        g_ptFontOprHead = fontOpr;
        g_ptFontOprHead -> pNext = NULL;
    }
    else
    {
        PT_FontOpr ptTmp = g_ptFontOprHead;
        while(ptTmp -> pNext)
        {
            ptTmp = ptTmp ->pNext;
        }
        ptTmp ->pNext = fontOpr;
        fontOpr ->pNext =NULL;
    }
    return 0;
}

/*
*@brief:打印链表上各个节点的name
*/
int showFontOpr(void)
{
    PT_FontOpr ptTmp = g_ptFontOprHead;
    int i = 0;
    while(ptTmp )
    {
        DBG_PRINTF("%02d: %s\r\n", i++, ptTmp ->name );
        ptTmp  = ptTmp -> pNext;
    }

    return 0;
}


/*
*@brief:在链表中获取满足参数一解码方式的节点指针
*@arg:编码方式,ascil/utf8等
*/
PT_FontOpr getFontOpr(char * name)
{
    PT_FontOpr ptTmp = g_ptFontOprHead;

    while(ptTmp)
    {
        if( strcmp(ptTmp ->name , name) == 0)
        {
            return ptTmp;
        }

        ptTmp = ptTmp->pNext;
    }

    return NULL;
} 

int FontInit(void)
{
    ascilInit();
    FreeTypeInit();
    GBKInit();

    return 0;
}

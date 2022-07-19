#include "framework.h"

void Fps::Init(Fps** Fps)
{
    (*Fps) = (Fps*)malloc(sizeof(Fps));
    (*Fps)->frameCnt = 0;
    (*Fps)->fpsTextBuffer = (char*)malloc(sizeof(char) * 10);
    sprintf((*Fps)->fpsTextBuffer, "FPS:%d", (*Fps)->frameCnt);
    (*Fps)->fpsOldTime = clock();
}

void Fps::Draw(Fps** Fps)
{    
    //출력코드
    (*Fps)->frameCnt++;
    (*Fps)->fpsCurTime = clock();
    if ((*Fps)->fpsCurTime - (*Fps)->fpsOldTime >= 1000)
    {
        sprintf((*Fps)->fpsTextBuffer, "FPS:%d", (*Fps)->frameCnt);
        (*Fps)->fpsOldTime = clock();
        (*Fps)->frameCnt = 0;
    }

     ScreenPrint(0, 0, (*Fps)->fpsTextBuffer);
}

void Fps::Destoy(Fps** Fps)
{
    free((*Fps)->fpsTextBuffer);
    free(*Fps);
}

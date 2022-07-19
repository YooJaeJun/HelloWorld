#pragma once

class Fps
{
public:
    clock_t fpsCurTime, fpsOldTime;
    int frameCnt;
    string fpsTextBuffer;

public:
    void Init(Fps** fpsData);
    void Draw(Fps** fpsData);
    void Destoy(Fps** fpsData);
};


#include "GettingStarted.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
int main()
{
    GettingStarted::GetStart gs(800,800, "Getting Started");
    //gs.HelloTriangle();
    //gs.HelloSquare();
    //gs.HelloTriangleExer1();
    //gs.HelloTriangleExer2();
    //gs.HelloTriangleExer3();
    //gs.TriangleChangingColor();
    //gs.TriangleRainbow();
    //gs.UpSideDownTriangle();
    //gs.XOffset();
    //gs.outputVerPostoFrag();
    //gs.containerTexture1();
    //gs.containerWithAwesomeFaceTexture1();
    //gs.containerWithAwesomeFaceTextureLookReverse();
    //gs.containerWithAwesomeFaceTexture4Smiley();
    //gs.containerWithAwesomeFaceTextureDisplayCenterPixel();
    //gs.containerWithAwesomeFaceTextureUniformMix3rdPara();
    //gs.containerWithAwesomeFaceTextureRotating();
    gs.containerWithAwesomeFaceTextureExchangeTranslateAndRotating();



    //std::println("{}", _MSC_VER);
    return 0;
}
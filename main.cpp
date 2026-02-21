#include "GettingStarted.h"

#ifdef _WIN32
#include <windows.h>
extern "C"
{
    // These tell the Windows drivers to use the dedicated GPU by default
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif
#include <cstdlib>
#include <iostream>

#ifdef __linux__
void ensure_high_performance_gpu() {
    if (std::getenv("__NV_PRIME_RENDER_OFFLOAD") == nullptr) {
        std::cout << "Restarting with NVIDIA GPU..." << std::endl;
        setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 1);
        setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 1);
        // This part is messy: you have to re-execute your own binary
    }
}
#endif
int main()
{
    ensure_high_performance_gpu();
    GettingStarted::GetStart gs(1200,1200, "Getting Started");
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
    //gs.containerWithAwesomeFaceTextureExchangeTranslateAndRotating();
    //gs.DrawSecondContrainerViaTransformations();
    //gs.going3d();
    //gs.more3d();
    //gs.moreCubes();
    //gs.make3rdContainerRotate();
    //gs.tryCamera();
    //gs.walkAround();
    gs.tryMouse();



    //std::println("{}", _MSC_VER);
    return 0;
}
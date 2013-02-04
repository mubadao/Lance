#include "IOSPlatform.h"
#include "FMLayerWebView.h"

void IosPlatform::navigateToURL( CCNode* layer, const char* url )
{
    FMLayerWebView* web = FMLayerWebView::shared(); 
    web->show(layer, url);
}



#include "DownloadThread.h"
#include "CommonObject.h"
#include "DrawThread.h"
#include <iostream>

int main() {
    CommonObjects common; // Create an instance of CommonObjects

    // Initialize GUI and set up the DrawThread
    DrawThread drawThread;
    drawThread(common);

    return 0;
}

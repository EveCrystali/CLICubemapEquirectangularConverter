#pragma once
#include <atomic>
#include <mutex>

// Global variable to signal the end of the processing
extern std::atomic<bool> processingDone;
// Global variable to temporarily stop the animation (e.g. during concurrent
// output)
extern std::atomic<bool> pauseAnimation;

// Mutex for synchronizing output
extern std::mutex coutMutex;

// Declaration of the animation function
void loadingAnimation();
void stopAnimation();
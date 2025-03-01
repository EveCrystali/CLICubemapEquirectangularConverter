#include "LoadingAnimation.hpp"
#include <chrono>
#include <iostream>

std::atomic<bool> processingDone(false);
std::atomic<bool> pauseAnimation(false);
std::mutex coutMutex;

void loadingAnimation() {
  const char symbols[] = {'|', '/', '-', '\\'};
  int i = 0;

  while (!processingDone) {
    if (!pauseAnimation) {
      std::lock_guard<std::mutex> lock(coutMutex);
      std::cout << "\rProcessing... " << symbols[i % 4] << std::flush;
      i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  // Efface l'animation et affiche le message final
  {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "\r" << std::string(30, ' ') << "\r";
  }
}

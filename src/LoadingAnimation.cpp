#include "LoadingAnimation.hpp"
#include <chrono>
#include <iostream>

/**
 * @brief Indicates whether the processing is finished.
 * - `false` : the animation continues to run.
 * - `true` : the animation stops definitively.
 * Used mainly in `main.cpp` to signal the end of the program.
 */
std::atomic<bool> processingDone(false);

/**
 * @brief Allows to temporarily pause the animation.
 * - `false` : the animation continues as usual.
 * - `true` : the animation is temporarily stopped and can resume later.
 * Used to prevent the animation from writing to the console when an important
 * message needs to be displayed (e.g. "Image loaded : ..." in `loadImage()`).
 */
std::atomic<bool> pauseAnimation(false);

std::mutex coutMutex;

void loadingAnimation() {
  const char symbols[] = {'|', '/', '-', '\\'};
  int i = 0;

  while (!processingDone) {
    if (!pauseAnimation) {
      std::lock_guard<std::mutex> lock(coutMutex);
      std::cout << "\rEn cours de traitement... " << symbols[i % 4]
                << std::flush;
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

void stopAnimation() {
  processingDone = true;
  pauseAnimation = true;
  std::cout << "\r" << std::string(30, ' ') << "\r"; // Efface l'animation
}

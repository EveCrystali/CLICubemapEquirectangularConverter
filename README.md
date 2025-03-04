# 🌍 Cubemap to Equirectangular Converter

## 📌 Description

Ce projet permet de convertir un **cubemap** (6 images projetées sur un cube) en une **image panoramique équirectangulaire** de haute résolution.  
Il est conçu pour être **rapide et optimisé**, exploitant les performances du C++ et d'OpenCV.

## ✨ Fonctionnalités

- 🔄 **Conversion rapide et précise** d'un cubemap en panorama équirectangulaire.
- 🎭 **Optimisation de la compression d'image**.
- ⚡ **Traitement optimisé** pour de meilleures performances.
- 🛠️ **Interface en ligne de commande simple**.

## 📥 Installation

### 1️⃣ Télécharger le projet

Clonez le repository :
```bash
git clone https://github.com/votre-repository.git
cd votre-repository
```

### 2️⃣ Installation des dépendances

Le projet utilise CMake et OpenCV. Assurez-vous que ces outils sont bien installés.

- OpenCV : https://github.com/opencv/opencv
- CMake 3.10+ : https://cmake.org/download/


### 3️⃣ Compilation

Avec CMake :

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

L'exécutable sera généré dans le dossier build/.

## 🚀 Utilisation

Exécutez le programme en ligne de commande :

```bash
Exo_AC_C__.exe
```

Puis suivez les instructions pour fournir le dossier contenant vos images cubemap.

📌 Format des fichiers attendus :

Votre dossier doit contenir 6 images nommées :
- front.jpg
- back.jpg
- left.jpg
- right.jpg
- top.jpg
- bottom.jpg

Le programme générera automatiquement une image panoramique.

📸 Résultat attendu

L'image finale sera en format équirectangulaire et enregistrée sous panorama_result.jpg.

Exemple de sortie :


## 🛠️ Dépendances

- C++17
- OpenCV 4.x → https://github.com/opencv/opencv
- CMake 3.10+ → https://cmake.org/download/

## 📝 License

Ce projet est sous licence GPL-2.0, ce qui signifie que tout code modifié ou redistribué doit respecter les termes de la GPL-2.0.

🔹 Il utilise Equirectangular-CubeMapTransform, un projet également sous GPL-2.0 :
https://github.com/ema2159/Equirectangular-CubeMapTransform.

En conséquence, toute distribution de l’exécutable doit inclure le code source.

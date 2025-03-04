# 🌍 Cubemap to Equirectangular Converter

## 📌 Description

Ce projet permet de convertir un **cubemap** (6 images projetées sur un cube) en une **image panoramique équirectangulaire** de haute résolution.  
Il est conçu pour être **rapide et optimisé**, exploitant les performances du C++ et d'OpenCV.

## ✨ Fonctionnalités

- 🔄 **Conversion rapide et précise** d'un cubemap en panorama équirectangulaire.
- 📏 **Support des résolutions élevées** (ex: 5120x5120 par face).
- 🎭 **Optimisation de la compression d'image** (JPEG & JPEG 2000 avec contrôle de qualité).
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

Le projet utilise CMake et OpenCV.


### 3️⃣ Compilation

Avec CMake :

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

L'exécutable sera généré dans le dossier build/Release.

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
- 
Le programme générera automatiquement une image panoramique.

📸 Résultat attendu

L'image finale sera en format équirectangulaire et enregistrée sous panorama_result.jpg.

Exemple de sortie :


## 🛠️ Dépendances

C++17
OpenCV 4.x
CMake 3.10+

## 📝 License

Ce projet est sous licence **GPL-2.0**.  
Il utilise `Equirectangular-CubeMapTransform` (GPL-2.0), ce qui signifie que son exécutable doit être redistribué sous les termes de cette licence.

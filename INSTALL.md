# Comment installer ?

Prérequis :
- Un compilateur C++20 (g++10.3 ou plus / Visual Studio 2019...)
- [git](https://github.com/glfw/glfw.git)
- Accès à la ligne de commande (PowerShell sur Windows)

## 1 - Installer CMake (compilation cross-platform)

### Debian/Ubuntu
```
sudo apt install cmake
```
### Autre (dont Windows)
[Télécharger l'installeur](https://cmake.org/download/) et le lancer.
**Sélectionner la case "Ajouter au PATH" quand demandé.**

## 2 - Installer les dépendances de GLFW
Sur Windows, rien à faire.

Sur Debian/Ubuntu :
```
sudo apt install xorg-dev
```

Pour les autres systèmes, voir [ici](https://www.glfw.org/docs/3.3/compile.html).

## 3 - Télécharger le projet, le compiler, l'exécuter
Ouvrir un invité de commande dans le dossier où faire le téléchargement, puis :
```
git clone https://github.com/J-Vernay/phymat-JV/ --recursive
cd phymat-JV
mkdir build
cd build
cmake ..
cmake --build .
```
Les deux commandes `cmake` servent respectivement à configurer la compilation, puis à compiler.

Sous Windows avec Visual Studio d'installé, un projet Visual Studio a été créé dans le dossier "build"
et peut être ouvert et utilisé pour éditer/compiler/débugger le projet.

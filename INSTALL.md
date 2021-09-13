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


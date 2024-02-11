# Projet Candy Crush pour le cours de Langage de Programmation 2

Ce projet a été développé dans le cadre du cours de Langage de Programmation 2. Il s'agit d'une implémentation simple du jeu Candy Crush utilisant C++ et la bibliothèque graphique FLTK. Le jeu est destiné à être compilé et exécuté sur des systèmes Linux.

## Prérequis

Avant de compiler et d'exécuter le jeu, assurez-vous d'avoir installé la bibliothèque FLTK sur votre système. FLTK peut être installé via le gestionnaire de paquets de votre distribution Linux. Par exemple, sur les distributions basées sur Debian (comme Ubuntu), vous pouvez installer FLTK en utilisant la commande suivante :

```bash
sudo apt-get install libfltk1.3-dev
```

## Compilation

Pour compiler le jeu, ouvrez un terminal dans le répertoire contenant les fichiers du projet et exécutez la commande suivante :

```bash
make
```

Cette commande va compiler le jeu en utilisant les fichiers sources spécifiés dans le Makefile et générer l'exécutable `candy_crush`.

## Exécution

Une fois la compilation terminée, vous pouvez lancer le jeu en exécutant :

```bash
./candy_crush
```

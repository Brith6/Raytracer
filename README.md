# 🌟 Raytracer - Moteur de Ray Tracing en C++20

> Moteur de ray tracing modulaire écrit en C++20, utilisant une architecture basée sur des plugins dynamiques et des design patterns professionnels.

---

## 📋 Table des matières

1. [Description](#-description)
2. [Prérequis et installation](#-prérequis-et-installation)
3. [Compilation](#-compilation)
4. [Utilisation](#-utilisation)
5. [Architecture et structure du projet](#-architecture-et-structure-du-projet)
6. [Design Patterns](#-design-patterns)
7. [Fonctionnalités implémentées](#-fonctionnalités-implémentées)
8. [Fichiers de configuration](#-fichiers-de-configuration)
9. [Mathématiques et classes utilitaires](#-mathématiques-et-classes-utilitaires)
10. [Structure des fichiers](#-structure-des-fichiers)
11. [Collaboration et responsabilités](#-collaboration-et-responsabilités)
12. [Dépannage et FAQ](#-dépannage-et-faq)
13. [Licence](#-licence)

---

## 📖 Description

Le **Raytracer** est un moteur de rendu 3D basé sur la technique du **ray tracing**. Il simule le trajet de rayons lumineux depuis une caméra virtuelle à travers une scène 3D pour calculer la couleur de chaque pixel de l'image finale.

### Capacités principales

- Rendu de scènes 3D avec éclairage réaliste
- Support de primitives géométriques (sphères, plans)
- Système de lumières multiples (ponctuelles, directionnelles)
- Calcul des ombres portées
- Architecture à base de plugins `.so` (chargement dynamique)
- Lecture de scènes via fichiers de configuration `.cfg`
- Affichage via SFML

---

## 🔧 Prérequis et installation

### Dépendances requises

| Dépendance | Version | Rôle |
|---|---|---|
| `g++` | ≥ 12 (C++20) | Compilateur C++ |
| `libconfig++` | ≥ 1.7 | Parsing des fichiers `.cfg` |
| `libsfml-graphics` | ≥ 2.5 | Rendu graphique |
| `libsfml-window` | ≥ 2.5 | Gestion de fenêtre |
| `libsfml-system` | ≥ 2.5 | Utilitaires système SFML |
| `make` | - | Outil de construction |

### Installation des dépendances (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install g++ make libconfig++-dev libsfml-dev
```

### Installation des dépendances (Fedora/RHEL)

```bash
sudo dnf install gcc-c++ make libconfig-devel SFML-devel
```

### Cloner le projet

```bash
git clone <url-du-repo>
cd Raytracer
```

---

## ⚙️ Compilation

### Compiler le projet entier

```bash
make
```

Cette commande compile :
1. **Le cœur du moteur** (`core/`) → binaire `raytracer`
2. **Les plugins lumières** (`lights/`) → `new_repo/plugins/point_light.so` et `directional_light.so`
3. **Les plugins primitives** (`primitives/`) → `new_repo/plugins/sphere.so` et `plane.so`

### Commandes disponibles

| Commande | Description |
|---|---|
| `make` | Compile le projet complet |
| `make core` | Compile uniquement le cœur du moteur |
| `make lights` | Compile uniquement les plugins lumières |
| `make primitives` | Compile uniquement les plugins primitives |
| `make clean` | Supprime les fichiers objets (`.o`) |
| `make fclean` | Supprime les objets et le binaire + plugins `.so` |
| `make re` | Recompile tout depuis zéro (`fclean` + `all`) |

### Options de compilation

Le projet est compilé avec les flags suivants :

```
-std=c++20 -Wall -Wextra -Werror -fPIC -g3
```

---

## 🚀 Utilisation

### Lancer le raytracer

```bash
./raytracer <fichier_scene.cfg>
```

### Exemples de scènes disponibles

```bash
# Scène de démonstration principale
./raytracer new_repo/scenes/subject_example.cfg

# Scène avec des sphères
./raytracer new_repo/scenes/demo_sphere.cfg

# Scène avec des lumières
./raytracer new_repo/scenes/demo_lights.cfg

# Scène avec import
./raytracer new_repo/scenes/demo_import.cfg
```

### Contrôles de la fenêtre

| Touche / Action | Effet |
|---|---|
| `Échap` / Fermer la fenêtre | Quitter le programme |

---

## 🏗️ Architecture et structure du projet

Le projet suit une architecture **modulaire** avec séparation claire des responsabilités.

### Vue d'ensemble

```
new_repo/
├── core/              # Cœur du moteur de ray tracing
├── camera/            # Gestion de la caméra
├── parser/            # Analyse des fichiers de configuration
├── lights/            # Système de lumières (plugins)
├── primitives/        # Formes géométriques (plugins)
├── plugins/           # Plugins .so compilés
└── scenes/            # Fichiers de scènes .cfg
```

### `core/` — Cœur du moteur

Contient la logique principale du moteur :

- **`Main.cpp`** : Point d'entrée du programme
- **`RayTracer.cpp/.hpp`** : Boucle de rendu principale, lancement des rayons
- **`designPatterns/`** : Implémentation des design patterns (Factory, Observer, Composite)
- **`error/`** : Gestion des erreurs
- **`helpers/`** : Fonctions utilitaires
- **`math/`** : Classes mathématiques (Vector3D, Point3D, Matrix)
- **`scene/`** : Représentation de la scène (Scene, Image)

### `camera/` — Caméra

- **`Camera.hpp`** : Définition de la caméra (position, direction de visée, champ de vision)

### `parser/` — Analyseur de configuration

- **`Parser.cpp/.hpp`** : Lecture et analyse des fichiers `.cfg` via `libconfig++`
  - Lecture de la configuration caméra
  - Lecture des primitives (sphères, plans)
  - Lecture des lumières (ponctuelles, directionnelles)

### `lights/` — Système de lumières

- **`ILight.hpp`** : Interface commune pour toutes les lumières
- **`pointLight/`** : Implémentation de la lumière ponctuelle (PointLight)
- **`directionalLight/`** : Implémentation de la lumière directionnelle (DirectionalLight)

### `primitives/` — Formes géométriques

- **`IPrimitive.hpp`** : Interface commune pour toutes les primitives
- **`sphere/`** : Implémentation de la sphère (Sphere)
- **`plane/`** : Implémentation du plan (Plane)

### `plugins/` — Bibliothèques dynamiques

Contient les fichiers `.so` générés après compilation :
- `point_light.so`
- `directional_light.so`
- `sphere.so`
- `plane.so`

### `scenes/` — Fichiers de scènes

Fichiers de configuration décrivant les scènes à rendre :
- `subject_example.cfg` — Scène d'exemple complète
- `demo_sphere.cfg` — Démonstration sphères
- `demo_lights.cfg` — Démonstration lumières
- `demo_import.cfg` — Démonstration import de scènes

---

## 🎨 Design Patterns

### Factory Pattern

**Fichiers :** `core/designPatterns/Factory.hpp` et `Factory.cpp`

Le **Factory Pattern** permet la création dynamique d'objets (primitives et lumières) sans exposer la logique de création.

```cpp
Factory factory;

// Création d'un plan bleu sur l'axe Z
auto plane = factory.createPlane("Z", 0.0, Color(0.25, 0.25, 1.0));

// Création d'une lumière directionnelle jaune
auto light = factory.createDirectionalLight(
    math::Vector3D(-1.0, 0.0, 0.0),
    Color(1.0, 1.0, 0.0)
);
```

### Observer Pattern

**Fichier :** `core/designPatterns/Observer.hpp`

Le **Observer Pattern** gère les événements du système de rendu. Il permet de notifier automatiquement les composants intéressés lors de changements d'état.

### Composite Pattern

**Fichier :** `core/designPatterns/Composite.hpp`

Le **Composite Pattern** permet la gestion hiérarchique des objets de la scène, traitant de façon uniforme les objets individuels et les compositions d'objets.

---

## ✅ Fonctionnalités implémentées

| Fonctionnalité | Statut | Description |
|---|---|---|
| Ray tracing basique | ✅ | Lancer de rayons depuis la caméra |
| Lumière directionnelle | ✅ | Lumière avec direction définie |
| Lumière ponctuelle | ✅ | Lumière rayonnant depuis un point |
| Primitive : Sphère | ✅ | Intersection rayon-sphère |
| Primitive : Plan | ✅ | Intersection rayon-plan |
| Ombres portées | ✅ | Shadow casting |
| Gestion des matériaux | ✅ | Couleurs par objet |
| Système de plugins | ✅ | Chargement dynamique `.so` |
| Lecture de configuration | ✅ | Parsing `.cfg` avec libconfig++ |
| Affichage SFML | ✅ | Rendu en temps réel |

---

## 📄 Fichiers de configuration

Les scènes sont décrites dans des fichiers `.cfg` (format `libconfig`).

### Structure d'un fichier de scène

```cfg
# Configuration de la caméra
camera:
{
    resolution = { width = 1920; height = 1080; };
    position   = { x = 0.0; y = 25.0; z = 50.0; };
    lookAt     = { x = 0; y = 25; z = 49; };
    fieldOfView = 55.0; # En degrés
};

# Primitives dans la scène
primitives:
{
    spheres = (
        { x = -30.0; y = 5.0; z = -10.0; r = 25.0;
          color = { r = 0.25; g = 1.0; b = 0.25; }; },
        { x = 45.0; y = 35.0; z = -5.0; r = 25.0;
          color = { r = 1.0; g = 0.25; b = 0.25; }; }
    );

    planes = (
        { axis = "Z"; position = 0.0;
          color = { r = 0.25; g = 0.25; b = 1.0; }; }
    );
};

# Configuration des lumières
lights:
{
    ambient = 0.4;   # Multiplicateur de lumière ambiante
    diffuse = 200.0; # Multiplicateur de lumière diffuse

    point = (
        { origin = { x = 150.0; y = 200.0; z = -50.0; };
          color  = { r = 1.0; g = 1.0; b = 1.0; }; }
    );

    directional = (
        { origin    = { x = -70.0; y = 0.0; z = 0.0; };
          direction = { x = -1.0;  y = 0.0; z = 0.0; };
          color     = { r = 1.0;   g = 1.0; b = 0.0; }; }
    );
};
```

### Paramètres de la caméra

| Paramètre | Type | Description |
|---|---|---|
| `resolution` | `{width, height}` | Résolution de l'image en pixels |
| `position` | `{x, y, z}` | Position de la caméra dans l'espace |
| `lookAt` | `{x, y, z}` | Point cible que la caméra regarde |
| `fieldOfView` | `float` | Angle de champ de vision (en degrés) |

### Paramètres des sphères

| Paramètre | Type | Description |
|---|---|---|
| `x, y, z` | `float` | Centre de la sphère |
| `r` | `float` | Rayon de la sphère |
| `color` | `{r, g, b}` | Couleur (valeurs entre 0.0 et 1.0) |

### Paramètres des plans

| Paramètre | Type | Description |
|---|---|---|
| `axis` | `"X"`, `"Y"` ou `"Z"` | Axe perpendiculaire au plan |
| `position` | `float` | Position le long de l'axe |
| `color` | `{r, g, b}` | Couleur (valeurs entre 0.0 et 1.0) |

### Paramètres des lumières

| Paramètre | Type | Description |
|---|---|---|
| `ambient` | `float` | Intensité de la lumière ambiante globale |
| `diffuse` | `float` | Intensité de la lumière diffuse globale |
| `point[].origin` | `{x, y, z}` | Position de la lumière ponctuelle |
| `point[].color` | `{r, g, b}` | Couleur de la lumière ponctuelle |
| `directional[].origin` | `{x, y, z}` | Origine de la lumière directionnelle |
| `directional[].direction` | `{x, y, z}` | Direction de la lumière directionnelle |
| `directional[].color` | `{r, g, b}` | Couleur de la lumière directionnelle |

---

## 🔢 Mathématiques et classes utilitaires

### `math::Vector3D`

Représente un vecteur 3D avec les opérations :
- Addition, soustraction, multiplication scalaire
- Produit scalaire (`dot`), produit vectoriel (`cross`)
- Normalisation, calcul de norme

### `math::Point3D`

Représente un point dans l'espace 3D :
- Différence point-point → Vector3D
- Translation par Vector3D → Point3D

### `Color`

Représente une couleur RGB :
- Composantes `r`, `g`, `b` (valeurs entre 0.0 et 1.0)
- Opérateurs arithmétiques pour mélange et modulation

### `Ray`

Représente un rayon :
- `origin` : Point3D — origine du rayon
- `direction` : Vector3D — direction normalisée

### Gestion mémoire

Le projet utilise systématiquement les **smart pointers** :
- `std::unique_ptr<IPrimitive>` pour les primitives
- `std::unique_ptr<ILight>` pour les lumières

---

## 🗂️ Structure des fichiers

```
Raytracer/
├── Makefile                          # Système de build
├── README.md                         # Ce fichier
├── new_repo/
│   ├── core/
│   │   ├── Main.cpp                  # Point d'entrée
│   │   ├── RayTracer.cpp/.hpp        # Moteur principal
│   │   ├── designPatterns/
│   │   │   ├── Factory.cpp/.hpp      # Factory Pattern
│   │   │   ├── Observer.hpp          # Observer Pattern
│   │   │   └── Composite.hpp         # Composite Pattern
│   │   ├── error/                    # Gestion des erreurs
│   │   ├── helpers/                  # Fonctions utilitaires
│   │   ├── math/
│   │   │   ├── Math.hpp              # Vector3D, Point3D, Ray
│   │   │   └── Matrix.hpp            # Matrices de transformation
│   │   └── scene/
│   │       ├── Scene.cpp/.hpp        # Représentation de la scène
│   │       └── Image.cpp/.hpp        # Gestion de l'image de sortie
│   ├── camera/
│   │   └── Camera.hpp                # Définition de la caméra
│   ├── parser/
│   │   └── Parser.cpp/.hpp           # Parsing des fichiers .cfg
│   ├── lights/
│   │   ├── ILight.hpp                # Interface lumière
│   │   ├── pointLight/               # Lumière ponctuelle
│   │   └── directionalLight/         # Lumière directionnelle
│   ├── primitives/
│   │   ├── IPrimitive.hpp            # Interface primitive
│   │   ├── sphere/                   # Sphère
│   │   └── plane/                    # Plan
│   ├── plugins/
│   │   ├── point_light.so            # Plugin lumière ponctuelle
│   │   ├── directional_light.so      # Plugin lumière directionnelle
│   │   ├── sphere.so                 # Plugin sphère
│   │   └── plane.so                  # Plugin plan
│   └── scenes/
│       ├── subject_example.cfg       # Scène d'exemple principale
│       ├── demo_sphere.cfg           # Démo sphères
│       ├── demo_lights.cfg           # Démo lumières
│       ├── demo_import.cfg           # Démo import
│       └── imported_file.cfg         # Fichier importé
└── old_repo/                         # Ancienne version du projet
```

---

## 👥 Collaboration et responsabilités

| Membre | Composants | Design Pattern |
|---|---|---|
| **Emmanuela** | DirectionalLight, Plane | Factory Pattern |
| **Vanessa** | PointLight, Sphere | Composite Pattern |
| **Brayan** | Core, Parser, RayTracer | Observer Pattern |

### Détail des contributions

#### Emmanuela
- **`lights/directionalLight/`** : Calcul de la contribution lumineuse et gestion des ombres
- **`primitives/plane/`** : Intersection rayon-plan et calcul de la normale
- **`core/designPatterns/Factory.cpp/.hpp`** : Création dynamique de primitives et lumières

#### Vanessa
- **`lights/pointLight/`** : Lumière ponctuelle avec atténuation
- **`primitives/sphere/`** : Intersection rayon-sphère
- **`core/designPatterns/Composite.hpp`** : Gestion hiérarchique des objets de scène

#### Brayan
- **`core/RayTracer.cpp/.hpp`** : Boucle principale de rendu et lancer de rayons
- **`core/Main.cpp`** : Point d'entrée et initialisation
- **`parser/Parser.cpp/.hpp`** : Analyse des fichiers de configuration `.cfg`
- **`core/designPatterns/Observer.hpp`** : Gestion des événements du moteur

---

## 🛠️ Dépannage et FAQ

### Erreur : `libconfig++` non trouvé

```
error: libconfig.h++: No such file or directory
```

**Solution :**
```bash
sudo apt install libconfig++-dev
```

### Erreur : `SFML` non trouvé

```
error: SFML/Graphics.hpp: No such file or directory
```

**Solution :**
```bash
sudo apt install libsfml-dev
```

### Erreur : Plugin `.so` non trouvé

```
Error: cannot open shared object file
```

**Solution :** Assurez-vous d'avoir compilé les plugins avant de lancer le programme :
```bash
make
```

### Erreur de compilation : standard C++20

```
error: 'std::...' requires '-std=c++20'
```

**Solution :** Vérifiez que votre version de `g++` supporte C++20 :
```bash
g++ --version  # doit être >= 12
```

### L'affichage ne s'ouvre pas

- Vérifiez que vous êtes dans un environnement graphique (pas en SSH pur sans X11).
- Exportez la variable `DISPLAY` si nécessaire : `export DISPLAY=:0`

### Le fichier de scène n'est pas reconnu

- Vérifiez la syntaxe du fichier `.cfg` (points-virgules, accolades)
- Consultez les exemples dans `new_repo/scenes/`

---

## 📜 Licence

**Projet EPITECH 2025**

Ce projet a été réalisé dans le cadre du cursus EPITECH (École Pour l'Informatique et les Techniques Avancées).

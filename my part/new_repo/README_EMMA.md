# Implémentations d'Emmanuela - Raytracer

## 🎯 Responsabilités

### DirectionalLight (Lumière Directionnelle)
- **Fichier :** `lights/directionalLight/DirectionalLight.cpp`
- **Fonctionnalité :** Calcul de la contribution lumineuse avec gestion des ombres
- **Méthodes implémentées :**
  - `calculateContribution()` : Calcule la contribution lumineuse
  - `checkShadow()` : Vérifie les ombres portées

### Plane (Plan)
- **Fichier :** `primitives/plane/Plane.cpp`
- **Fonctionnalité :** Intersection rayon-plan et calcul de la normale
- **Méthodes implémentées :**
  - `hits()` : Calcul de l'intersection avec un rayon
  - `getNormal()` : Calcul de la normale du plan
  - `getColor()` : Retourne la couleur du plan
  - `getPlanePoint()` : Retourne un point sur le plan

### Factory Pattern
- **Fichiers :** `core/designPatterns/Factory.hpp` et `Factory.cpp`
- **Fonctionnalité :** Création dynamique d'objets (primitives et lumières)
- **Méthodes implémentées :**
  - `createPrimitive()` : Création de primitives
  - `createLight()` : Création de lumières
  - `createPlane()` : Création spécifique d'un plan
  - `createDirectionalLight()` : Création spécifique d'une lumière directionnelle

## 🏗️ Architecture

### DirectionalLight
```cpp
class DirectionalLight : public ILight 
{
    // Calcule la contribution lumineuse avec ombres
    Color calculateContribution(
        const math::Point3D &intersectionPoint,
        const math::Vector3D &normal,
        const std::vector<std::unique_ptr<IPrimitive>>& primitives
    ) const override;
};
```

### Plane
```cpp
class Plane : public IPrimitive 
{
    // Intersection rayon-plan
    double hits(const Ray &ray) const override;
    
    // Normale du plan (constante selon l'axe)
    math::Vector3D getNormal(const math::Point3D &point) const override;
    
    // Couleur du plan
    Color getColor() const override;
};
```

### Factory
```cpp
class Factory 
{
    // Création d'objets par type
    std::unique_ptr<IPrimitive> createPrimitive(PrimitiveType type);
    std::unique_ptr<ILight> createLight(LightType type);
    
    // Création spécifique
    std::unique_ptr<Plane> createPlane(const std::string &axis, double position, const Color &color);
    std::unique_ptr<DirectionalLight> createDirectionalLight(const math::Vector3D &direction, const Color &color);
};
```

## 🧪 Tests

### Compilation et test
```bash
cd new_repo
make
make test
```

### Fonctionnalités testées
1. **Factory Pattern :**
   - Création de plans
   - Création de lumières directionnelles

2. **Plane :**
   - Intersection avec des rayons
   - Calcul de la normale
   - Récupération de la couleur

3. **DirectionalLight :**
   - Calcul de la contribution lumineuse
   - Gestion des ombres

## 📊 Fonctionnalités Implémentées

### ✅ Obligatoires (Must)
- [x] Lumière directionnelle
- [x] Plan primitif
- [x] Translation (via Factory)

### ✅ Recommandées (Should)
- [x] Ombres portées
- [x] Factory pattern

### 🎯 Design Patterns
- [x] **Factory Pattern** : Création dynamique d'objets
- [ ] Composite Pattern (Vanessa)

## 🔧 Utilisation

### Création d'un plan
```cpp
Factory factory;
auto plane = factory.createPlane("Z", 0.0, Color(0.5, 0.5, 1.0));
```

### Création d'une lumière directionnelle
```cpp
auto light = factory.createDirectionalLight(
    math::Vector3D(0.0, -1.0, 0.0), 
    Color(1.0, 1.0, 1.0)
);
```

### Test d'intersection
```cpp
Plane plane("Z", 0.0, Color(0.5, 0.5, 1.0));
Ray ray(math::Point3D(0.0, 0.0, 10.0), math::Vector3D(0.0, 0.0, -1.0));
double distance = plane.hits(ray);
```

## 🚀 Prochaines étapes

1. **Intégration avec le projet principal**
2. **Tests avec les scènes existantes**
3. **Optimisation des performances**
4. **Ajout de fonctionnalités bonus**

## 📝 Notes techniques

- **Mathématiques :** Utilisation des classes `Vector3D` et `Point3D`
- **Couleurs :** Classe `Color` avec opérateurs arithmétiques
- **Rayons :** Classe `Ray` pour les calculs d'intersection
- **Gestion mémoire :** Utilisation de `std::unique_ptr` pour l'ownership

## 👥 Collaboration

- **Emmanuela :** DirectionalLight, Plane, Factory Pattern
- **Vanessa :** PointLight, Sphere, Composite Pattern
- **Brayan :** Core, parsing, Observer Pattern 
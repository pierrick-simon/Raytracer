# Primitive Plugins

## Description

A Primitive Plugin is a shared library used to add new shapes for the RayTracer.
It stores the implementation for the parsing of the added shape and the
implementation of the ray collision detection for the added IObject.

## Usage

To use a plugin, put the `*.so` file in a `plugins` directory, at the same level
as the executable.

## Creation

The plugin needs to have 2 entry points in C:

- `rayTracerLibEntryPoint` that returns a raw pointer to
  `RayTracer::IObjectPlugin`
- `rayTracerType` that returns `RayTracer::LibType::PRIMITIVE`

The subclass of `RayTracer::IObjectPlugin` must implement all the methods.

### The `IObjectPlugin::getObjectsTypeName` method
The `getObjectsTypeName` method returns the name of the objects that will be
specified in the scene configuration file.

For example, with this configuration file:

```cfg
primitives:
{
    spheres = (
        { x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; },
        { x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
    );

    planes = (
        { axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
    );
};
```

The `getObjectsTypeName` for a Sphere Plugin will return `"spheres"`, and for a
Plane Plugin it will return `"planes"`.

### The `IObjectPlugin::parseObjects` method

The `parseObjects` method returns a list of `IObject`s that will be parsed from
each element of the configuration.

Again, with the same configuration file, for the Sphere Plugin, it will return a
list of two spheres created from:
```
{ x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; }
```
and
```
{ x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; }
```

### Custom IObject

As stated previously, the `parseObjects` method returns a list of `IObject`s.
However, if you want to create a custom IObject, you can do so by inheriting
from `RayTracer::IObject`. The `IObject` class has a `hits` method that returns
a non-empty optional with `HitInfo` if the ray intersects the object.
The `HitInfo` holds the intersection point, and the normal vector of the surface.

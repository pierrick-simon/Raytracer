# Light Plugins

## Description

A Light Plugin is a shared library used to add new shapes for the RayTracer.
It stores the implementation for the parsing of the added shape and the
implementation of the ray collision detection for the added ILightSource.

## Usage

To use a plugin, put the `*.so` file in a `plugins` directory, at the same level
as the executable.

## Creation

The plugin needs to have 2 entry points in C:

- `rayTracerLibEntryPoint` that returns a raw pointer to
  `RayTracer::ILightSourcePlugin`
- `rayTracerType` that returns `RayTracer::LibType::LIGHT`

The subclass of `RayTracer::ILightSourcePlugin` must implement all the methods.

### The `ILightSourcePlugin::getLightsTypeName` method
The `getLightsTypeName` method returns the name of the lightSources that will be
specified in the scene configuration file.

For example, with this configuration file:

```cfg
# Light configuration
lights:
{
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light

    # List of point lights
    point_lights = (
        { x = 400.0; y = 100.0; z = 500.0; color = { r = 255; g = 64; b = 64; }; falloutDistance = 200.0; }
    );

    # List of spot lights
    spot_lights = (
        {
            position = {x=100; y=100; z=100};
            direction = {x=1; y=1; z=-1;};
            color = {r=255; g=255; b=255;};
            falloutDistance = 95;
            outerConeAngle = 45;
            innerConeAngle = 30;
        }
    );
};
```

The `getLightsTypeName` for a Point Light Plugin will return `"point_lights"`, and for a
Spotlight Plugin it will return `"spot_lights"`.

### The `ILightSourcePlugin::parseLight` method

The `parseLight` method returns a unique_ptr of `ILightSource` that will be parsed from
a single element of the configuration.

Again, with the same configuration file, for the Point Light Plugin, it will return
a point light created from:
```
{ x = 400.0; y = 100.0; z = 500.0; color = { r = 255; g = 64; b = 64; }; falloutDistance = 200.0; }
```

### Custom ILightSource

As stated previously, the `parseLightSources` method returns `ILightSource`s.
However, if you want to create a custom ILightSource, you can do so by inheriting
from `RayTracer::ILightSource`. The `ILightSource` class has a `getLightAmount`
method that returns the color of the light from a ray. If the color is `0, 0, 0` (black), then there is no light.

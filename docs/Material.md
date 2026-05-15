# Material

## Description

A Material is a layer that is added on the object that define multiple aspect of the object surface.

## Variables

- **Color** : The color of the material.
- **Metallic** : Between 0 and 1, controls how 'metal-like' your surface will be.
- **Specular** : Between 0 and 1, is a measure of how much light a surface reflects.
- **Roughness** : Between 0 and 1, control how rough or smooth a Material's surface is.
- **Opacity** : Between 0 and 1, control how opact or transparent a Material's surface is.
- **Refraction** : The index of refraction of an object (Air: 1.00).

## Preset Material

We preset some basic material to be use for everyone:
- Flat color
- Mirror
- Brushed metal
- Plastic
- Glass
- Water
- Diamond
- Ice
- Wood

## Config File

There are two-way to make material in the config file:

### Global Material

At the root of the config file make global Materials with all the variable are optional a part from the name of the created material. It can also have a type to herite of a preset Material.

```
materials = (
    {
        type = "Flat color";
        name = "red flat color";
        color = { r = 255; g = 64; b = 64; };
    },
    {
        name = "custom";
        metallic = 0.5;
        roughness = 0;
        specular = 1;
        opacity = 0.2;
        refraction = 1.33;
    }
);
```
To use the Globale Material is like the preset Material is simply by calling **material = "name"**:

```
primitives:
{
    spheres = (
        {
            x = 5; y = 60; z = 40; r = 25;
            material = "red flat color";
        },
        {
            x = 20; y = -40; z = 0; r = 35;
            material = "Mirror";
        }
    );
};
```

### Local Material

Like before the material can directly be created in the primitive:

```
primitives:
{
    spheres = (
        {
            x = 5; y = 60; z = 40; r = 25;
            material = {
                name = "FLat color";
                color = { r = 255; g = 64; b = 64; }
            };
        },
        {
            x = 20; y = -40; z = 0; r = 35;
            material = {
                metallic = 0.5;
                roughness = 0;
                specular = 1;
                opacity = 0.2;
                refraction = 1.33;
            };
        }
    );
};
```
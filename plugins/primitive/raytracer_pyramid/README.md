# Raytracer Plugin - Triangle (rectangle base pyramid) primitive

![Image representing a square based pyramid](Resources/right-square-pyramid.png)

## How to configure

The triangle need:
 - An **origin point**: `Point3D`
 - A **height**: `double`
 - A **width**: `double`
 - A **length**: `double`
 - A **color**: `RGB`

Width and length are for the **base**. Height is the height of the apex.

## Example

```cfg
primitives:
{
    pyramids= (
        {
            origin = { x = 60; y = 5; z = 40; };
            h = 25.0;
            w = 42.2;
            l = 20.6;
            material = {
                name = "Flat color"
                color = { r = 64; g = 255; b = 2; };
            };
        }
    );
};
```

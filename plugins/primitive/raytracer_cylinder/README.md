
## Example

```cfg
camera:
{
    resolution = { width = 1920; height = 1080; };
    position = { x = -100; y = 0; z = 5; };
    rotation = { x = 0.0; y = 0; z = 0.0; };
    fieldOfView = 72.0; # In degree
};

# Primitives in the scene
primitives:
{
    cylinders = (
    {
        origin = { x = -30; y = -40; z = -20; };
        r = 10.0; h = 10.0;
        material = {
            name = "Flat color";
            color = { r = 255; g = 0; b = 255; };
        };
    }
    );
};

# Light configuration
lights:
{
ambient = 0.4; # Multiplier of ambient light
diffuse = 0.6; # Multiplier of diffuse light

    # List of point lights
    point_lights = (
        { x = 100.0; y = 400.0; z = 500.0; color = { r = 255; g = 255; b = 255; }; falloutDistance = 5000.0; }
    );

    # List of directional lights
    directional = ();
};
```
# Texture Generation Plugins

## Description

A Texture Generation Plugin is a shared library used to add new way to generate texture for the RayTracer.
It stores the implementation for the parsing of the added texture generation and the
implementation of the generate PPM (Potable Pix Map).

## Usage

To use a plugin, put the `*.so` file in a `plugins` directory, at the same level
as the executable.

## Creation

The plugin needs to have 2 entry points in C:

- `rayTracerLibEntryPoint` that returns a raw pointer to
  `RayTracer::ITextureGenerationPlugin`
- `rayTracerType` that returns `RayTracer::LibType::TEXTURE_GENERATION`

The subclass of `RayTracer::ITextureGenerationPlugin` must implement all the methods.

### The `ITextureGenerationPlugin::getTexturesTypeName` method
The `getTexturesTypeName` method returns the name of the texture generation that will be
specified in the scene configuration file.

For example, with this configuration file:

```cfg
textures: {
    chessboards = (
        {
            name = "Blue Board";
            size = 100;
            nbSquare = 50;
            color = { r = 64; g = 64; b = 255; };
        }
    );
    perlinnoises = (
        {
            name = "Noise";
            size = {x = 1000; y = 1000};
            seed = 67;
            smooth = 10;
            spread = {x = 5; y = 5};
        }
    );
};
```

The `getTexturesTypeName` for a Chess Board Plugin will return `"chessboards"`, and for a
Perlin Noise Plugin it will return `"perlinnoises"`.

### The `ITextureGenerationPlugin::parseTexture` method

The `parseTexture` method returns a `ITextureGeneration` that will be parsed from
each element of the configuration.

### Custom ITextureGeneration

As stated previously, the `parseTexture` method returns a `ITextureGeneration`.
However, if you want to create a custom ITextureGeneration, you can do so by inheriting
from `RayTracer::ITextureGeneration`. The `ITextureGeneration` class has a `generate` method that returns
a PPM generate via the plugin.

# [fdf](https://en.wikipedia.org/wiki/Wire-frame_model)

A small 3D wireframe viewer written in C with GLFW and OpenGL. The program reads a `.fdf` height map, projects its points into 2D, and renders the result as a navigable wireframe.

## Features

- Parses `.fdf` height maps.
- Supports per-point colors in hexadecimal notation.
- Renders the map as a wireframe using OpenGL.
- Supports three projection modes:
  - Isometric.
  - Cabinet oblique.
  - Cavalier oblique.
- Camera translation and rotation.
- Zoom with the mouse wheel.
- Adjustable vertical scale.
- Toggleable color mode.
- Non-blocking interactive controls.
- GLFW is built automatically from the `external/glfw` directory.

## Requirements

- A Unix-like operating system.
- A C compiler such as `cc` or `clang`.
- `make`.
- CMake.
- OpenGL development libraries.
- X11 development libraries on Linux.

The project builds GLFW from the copy included in the repository. The `external/glfw` directory is intentionally not shown in the source listing because it is an external dependency.

## Build

From the project root:

```sh
make
```

This command:

1. Configures GLFW with CMake.
2. Builds GLFW in `external/glfw/build`.
3. Compiles the project sources.
4. Produces the `fdf` executable.

To remove object files and the GLFW build directory:

```sh
make clean
```

To remove all generated files, including the executable:

```sh
make fclean
```

To rebuild everything:

```sh
make re
```

## Usage

Run the program with one `.fdf` map file:

```sh
./fdf maps/42.fdf
```

The program rejects arguments that do not contain exactly one filename ending in `.fdf`.

## Map format

A map is a text file containing rows of integer altitude values. Every row must contain the same number of points.

Example:

```text
0 0 0 0
0 1 2 1
0 2 4 2
0 1 2 1
```

A point may optionally include a hexadecimal color after a comma:

```text
0,0xFFFFFF 1,0xFF0000 2,0x00FF00
1,0xFFFFFF 2,0xFFFF00 3,0x0000FF
```

When no color is provided, the default color is white.

## Controls

| Key or action | Effect |
|---|---|
| `W` | Move the camera upward |
| `S` | Move the camera downward |
| `A` | Move the camera left |
| `D` | Move the camera right |
| `Up` | Rotate the camera clockwise |
| `Down` | Rotate the camera counter-clockwise |
| Numpad `+` | Increase vertical scale |
| Numpad `-` | Decrease vertical scale |
| Mouse wheel | Zoom in or out |
| `0` | Isometric projection |
| `1` | Cabinet projection |
| `2` | Cavalier projection |
| `C` | Toggle colors |
| `Escape` | Close the window |

## Project structure

- `include/` — public headers and data structures.
- `sources/main.c` — program entry point.
- `sources/parse_arguments.c` — command-line validation.
- `sources/open_file.c` — map-file opening.
- `sources/parse_map.c` and `sources/parse_line.c` — map parsing.
- `sources/projections.c` — projection formulas.
- `sources/camera.c` — camera transformations.
- `sources/render.c` — OpenGL rendering and line drawing.
- `sources/callbacks.c` — keyboard and mouse callbacks.
- `external/glfw/` — GLFW dependency.
- `maps/` — example maps, if included in the repository.

## Implementation overview

The map is stored as a rectangular grid of points. Each point contains an altitude and a packed RGBA color.

During each frame, the program:

1. Converts grid coordinates into one of the supported projections.
2. Applies the altitude scale.
3. Applies camera rotation, zoom, and translation.
4. Draws horizontal and vertical connections between neighboring points.

The rendering uses immediate-mode OpenGL (`glBegin`, `glVertex2f`, and `glEnd`), which keeps the implementation straightforward and suitable for a learning project.

## Known limitations

This is a learning project and is not intended to be a production renderer.

- The program currently targets the OpenGL/GLFW environment described by the Makefile.
- The map must be rectangular: every row must contain the same number of values.
- Very large maps may require additional memory and may reduce rendering performance.
- Empty maps are reported with a warning rather than rejected immediately.
- The rendering code uses legacy OpenGL immediate mode rather than modern buffers and shaders.
- The color parser should validate the complete hexadecimal token and its range more strictly.
- The parser should close the file on every failure path and should use a consistent usage message.
- The camera zoom and vertical-scale controls do not currently enforce explicit minimum and maximum values.
- Platform-specific OpenGL and GLFW flags may require Makefile changes on macOS or other systems.

### Smaller improvements

- Clamp `camera.zoom` and `z_axis_scale` to avoid values becoming too small or too large after repeated input.
- Reject an empty map instead of continuing after printing a warning.
- Error reporting.

Any suggestion is welcomed.

## Project status

Functional learning project: a C/OpenGL wireframe viewer with parsing, projections, camera controls, and interactive rendering.

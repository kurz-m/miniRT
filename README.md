# miniRT

## Description
miniRT is a compact, efficient ray-tracing program developed in C. This project is designed to offer a straightforward implementation of ray-tracing, enabling the creation of visually appealing 3D renders using simple scene descriptions. As an educational venture, miniRT provides insights into the fundamental principles of ray-tracing technology, including light and shadow computation, reflection, and refraction. It's a practical approach to understanding the complexities of 3D rendering algorithms.

## Features

- Ray-tracing engine: Accurately computes light, shadow, reflection, and refraction.
- Scene parser: Interprets simple scene description files to render 3D scenes.
- Supports various geometric shapes: Spheres, planes, cylinders, etc.
- Camera and viewport handling: Allows defining viewpoint and perspective.
- Basic lighting model: Incorporates ambient, diffuse, and specular lighting.
- Multi-threading support: Leverages multi-core processors for faster rendering.
- Anti-aliasing: Uses a simple supersampling approach to smoothen out the edges.
- Simple and intuitive scene description language.

## Getting Started

### Dependencies

Requires a C compiler (gcc or clang recommended) and make utility.
Depend on the [MLX42](https://github.com/codam-coding-college/MLX42) graphics library. It will be automatically added as a submodule from the make file.

### Installing

```bash
Copy code
git clone https://github.com/kurz-m/miniRT.git
cd miniRT && make
```

The make command will compile the project and generate the executable.

### Running the Program
To run miniRT, use the following command:

```bash
Copy code
./miniRT scene/<scene.rt>
```
Replace <scene.rt> with the path to the scene you want to render.

### Example Scenes

<img width="1276" alt="Screen Shot 2023-11-27 at 6 38 52 PM" src="https://github.com/kurz-m/miniRT/assets/85294588/b0006ee3-6e85-435e-960d-f8bdf8f6b181">

<img width="1276" alt="Screen Shot 2023-12-07 at 11 25 33 AM" src="https://github.com/kurz-m/miniRT/assets/85294588/9848506f-f586-46d4-9224-5d23239a59f2">

## Authors

[Flo](https://github.com/flolau2k)

[Markus](https://github.com/kurz-m)

### License

This project is licensed under the GPL - see the [LICENSE](LICENCE) file in the repository for more details.

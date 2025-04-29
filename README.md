# Solar System Simulation

A 3D solar system simulation using OpenGL/GLUT.

## Installation Options

### Traditional Compilation
```
g++ main.cpp -o solar_system -framework OpenGL -framework GLUT
./solar_system
```

### Using Homebrew
You can install this application using Homebrew:

#### Option 1: Quick Installation
Run the provided installation script:
```
./install-with-brew.sh
```

#### Option 2: Manual Installation
1. If you haven't already, install Homebrew:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. Install the freeglut dependency:
```
brew install freeglut
```

3. Install the application from the local formula:
```
brew install --build-from-source ./solar-system.rb
```

## Usage
Once installed, you can run the application:
```
solar-system
```

### Controls
- Arrow keys: Rotate the view
- '+'/'-': Zoom in/out
- 'Enter': Pause/Resume simulation
- 'q' or 'ESC': Quit

## OpenGL Example Programs

This repository also includes three simple OpenGL example programs that demonstrate different concepts:

### Example 1: Colored Triangle (ex1.c)
A basic OpenGL demonstration that draws a colored triangle with red, green, and blue vertices.

**Compilation and Running:**
```
gcc ex1.c -o ex1 -framework OpenGL -framework GLUT
./ex1
```

**Features:**
- RGB colored triangle
- Simple vertex and color specification
- Clean white background
- Press ESC to exit

### Example 2: Circles on Grid (ex2.c)
Demonstrates drawing multiple circles with different colors on a grid background.

**Compilation and Running:**
```
gcc ex2.c -o ex2 -framework OpenGL -framework GLUT
./ex2
```

**Features:**
- Gray background grid
- Three colored circles (red, green, blue)
- Demonstrates using GL_TRIANGLE_FAN for circle rendering
- Press ESC to exit

### Example 3: Bouncing Ball Animation (ex3.c)
Interactive animation showing a ball bouncing around the screen boundaries.

**Compilation and Running:**
```
gcc ex3.c -o ex3 -framework OpenGL -framework GLUT
./ex3
```

**Features:**
- Red ball that bounces off window edges
- Press spacebar to start the animation
- Demonstrates physics simulation with boundary collision
- Uses double buffering for smooth animation
- Press ESC to exit

### Example 4: 3D Cube (ex4.c)
A simple 3D cube demonstration using vertex specification.

**Compilation and Running:**
```
gcc ex4.c -o ex4 -framework OpenGL -framework GLUT
./ex4
```

**Features:**
- 3D cube with colored vertices
- Demonstrates 3D geometry with proper depth testing
- Uses perspective projection
- Shows basic 3D transformations (translation and rotation)
- Each vertex has a different color for better visual understanding
- Press ESC to exit

## Platform-Specific Compilation

### macOS
```
gcc <filename>.c -o <output> -framework OpenGL -framework GLUT
```

### Windows
```
gcc <filename>.c -o <output>.exe -lfreeglut -lopengl32 -lglu32
```

### Linux
```
gcc <filename>.c -o <output> -lglut -lGL -lGLU
```

## Z-Buffer Information

In OpenGL, the Z-buffer value for each object (or planet in your case) is determined by the object's position in 3D space relative to the camera's viewpoint. Specifically, the Z-buffer value is determined by the Z-coordinate of each object after it has been transformed by the model-view matrix and the perspective projection.

In your program, each planet has a certain distance from the origin (the sun), and its Z-buffer value will depend on its position relative to the camera.

Determining the Z-buffer Value for Each Planet:
Each planet is rendered using the glutSolidSphere function, which places the planet at a specific (x, y, z) coordinate in 3D space. After this position is transformed (by rotations and translations), the Z-buffer value is determined by the transformed Z-coordinate.

Here's how the Z-buffer value is influenced:

1. Planet's Position:

* In your code, planets are drawn using drawPlanet(), and each planet's position is controlled by the distance variable, which is the distance from the sun (the origin):

```drawPlanet(planets[i].distance, planets[i].size, angles[i], planets[i].r, planets[i].g, planets[i].b)```

* The distance value controls how far the planet is from the center, but this value is in object space (before any transformations). Once transformed (e.g., rotated or translated), the actual position will be different.

2. Camera Transformation:

* The camera position and viewing direction are set by gluLookAt(), which defines where the camera is in the scene and where it's looking:

```gluLookAt(0.0, 15.0, 25.0,0.0, 0.0, 0.0,0.0, 1.0, 0.0)```

* his camera setup places the camera at (0, 15, 25) in world space and looks at the origin (0, 0, 0). The planets are positioned relative to this camera position.

* Transformations (Rotation and Translation):

The planets are rotated by a certain angle (angle) along the Y-axis using glRotated(angle, 0, 1, 0) and then translated by the distance value along the X-axis (glTranslated(distance, 0.0, 0.0)).

After these transformations, the Z-coordinate of the planet will depend on its position in 3D space relative to the camera.

Adjusting Z-buffer Values:
To manually adjust the Z-buffer values for each planet, you would need to modify their Z-positions relative to the camera.

Increase or decrease the distance: The distance parameter in drawPlanet() controls how far the planet is from the camera (in the X-direction). You can adjust this distance to move the planet closer or further along the X-axis, which directly affects the Z-buffer value.

Modify the Z-translation: You can also add or modify a Z-translation for each planet (like glTranslated(x, y, z)) to directly control their Z-position in world space. This can make the planets appear closer or farther from the camera along the Z-axis.

For example, if you want to make a planet move along the Z-axis (depth) instead of just the X-axis, you can modify the drawPlanet function like this:

```
void drawPlanet(double distance, double size, double angle, double r, double g, double b, double zOffset)
{
    glPushMatrix();
    glColor3d(r, g, b);
    glRotated(angle, 0, 1, 0);
    glTranslated(distance, 0.0, zOffset); // Add a Z offset to control the Z-position
    glutSolidSphere(size, slices, stacks);
    glPopMatrix();
}
```

And call it with a custom Z-offset value for each planet:

```
drawPlanet(planets[i].distance, planets[i].size, angles[i], planets[i].r, planets[i].g, planets[i].b, planets[i].zOffset);```

* This way, the zOffset will directly modify the Z-buffer value by changing the Z-coordinate of the planet. You can experiment with different Z-offsets to control the depth order.

### Key Considerations:
Near and Far Clipping Planes: The Z-buffer works within the range defined by the near and far clipping planes, which are set by gluPerspective(45.0 / zoomFactor, aspect_ratio, 1.0, 100.0);. The near plane is at 1.0, and the far plane is at 100.0. If you move planets too far or too close to the camera, they may either not be rendered (if they're beyond the far plane) or result in Z-buffer precision issues.

### Depth Precision: The Z-buffer has limited precision based on the range between the near and far clipping planes. The greater the range between the near and far planes, the less precise the Z-buffer is. This can result in depth artifacts, especially if planets are very close to each other.

By modifying the planet positions along the Z-axis or using an offset (like zOffset), you can control the Z-buffer values and adjust how objects overlap or occlude each other in the scene.
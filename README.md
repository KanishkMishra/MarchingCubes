# Assignment 5: Marching Cubes
### Kanishk Mishra
### March 20, 2023

---

## Format:

> Compiled: g++ MarchingCubes.cpp -o marchingCubes -lglfw -lGL -lGLEW

> Run With: `./marchingCubes {screen_width} {screen_height} {step_size} {min} {max} {isoval} {file_name}`

> Test with: `./marchingCubes 800 800 0.03 -5 5 0 hills`
* change marchingCubes function to have `hills` 3d scalar field 

> Test with: `./marchingCubes 800 800 0.03 -5 5 -1.5 cone`
* change marchingCubes function to have `cone` 3d scalar field

---

## Files and Functions:

* MarchingCubes.cpp
    - `float sphere(float x, float y, float z)`
    - `std::vector<float> marching_cubes(scalar_field_3d f, float isovalue, float min, float max, float stepsize)`
    - `std::vector<float> compute_normals(std::vector<float> vertices)`
    - `void writePly(std::vector<float> vertices, std::vector<float> normals, std::string fileName)`
    - `void cameraControls(glm::vec3& eye, float& yaw, float& pitch, float& r, bool& hold, float& lastX, float& lastY)`
    - `int main( int argc, char* argv[])`
* TriTable.hpp
    - `int marching_cubes_lut[256][16]`
    - `float vertTable[12][3]`

---

## Functionality:

This Program implements a **Marching Cubes** program with up to 7 parameters, but all possess default values which the program will use if not specified. The defaul values are `screen_width = 800`, `screen_height = 800`, `step_size = 0.1`, `min = -5`, `max = 5`, `isoval = 1`, `file_name = "marching"`, note that the **.ply extension** is not needed for the file name. This program creates a **window of the specified dimensions** with the title **Marching Cubes**. To display different models, the `scalar_field_3d` variable in `marching_cubes` needs to be manually changed.

The **Camera** has a **vertical field view of 45 degrees**, starting at **{5.0f, 5.0f, 5.0f}** looking at the origin, **{0.0f, 0.0f, 0.0f}**. The camera can be moves around using the **arrow keys** and **clicking and dragging the left mouse button**. The **arrow keys** move us further and closer to the origin, effectively acting as a **zoom**. The **mouse** lets us see from different angles by **seemingly rotating the object**. The three parameters of **radius**, **yaw** and **pitch** are manipulated to implement these changes in the **eye vector** using the function `cameraControls`. We use three additional parameters, we use **hold** to check if the mouse is being held down while **lastX** and **lastY** is the previous mouse position.

The next **Marching** in this program is done using the function `marching_cubes`, which is the core of this program. The provided **"TriTable.hpp"** file and it's two data structures `marching_cubes_lut` and `vertTable` are essential. The marching is done by a triple nested for loop **checking all x, y, z** positions between **min and max** using the **step size as increments**. For each x, y, z position a cube is made by checking the **scalar_field_3d** function for each corner and using **isovalue** to determine if that corner is covered by the shape. By combining all of the covered corner a **lookup** is implemented on `marching_cubes_lut` which returns to us an array of the corresponding triangles to make. We record the vertices of all the triangles by combining `vertTable`, **stepsize** and **x, y, z** values to record three vertices at a time.

The **Normals** are needed for the lighting effects, so we calculate them in the function `compute_normals`, as a paramter we only input the **vector of vertices**. The normal for each vertex is equal to the normal for that triangle, so we **increment through 9 float values** at a time, giving us all vertices in that triangle. We subtract the appriate values to find the **line vectors** corresponding to **vertex 2 - vertex 1** and **vertex 3 - vertex 1** which we then find the **cross product of then normalize**. We then store the normal three times, once for each vertex in that triangle, this ensures that the **size of the normal vector equals the vertex vector**.

Next to make sure all this work doesn't disapear once the program is complete we **Write a .ply file** to record all of the information. This file is written in `writePly` using the parameters of the **normals vector**, **vertices vector** and **file name** argument. Once again, this function appends `.ply` to file name so it shouldn't be part of the file name inputted by the user. We start by writing a simple header starting with **"ply"**, and ending with **"end_header"**, this header also specifies the number of vertices, faces and descibes the vertex data written. After this we simply loop through the **vertex and normal** vectors writing them down line by line. To write the **faces** down is simple as the same vertex is not used twice, though it may have dupliates, and are already in the correct order.

Finally our program gets to **Rendering** the modeled shape, we start by drawing the edges of a 3d box indicating the **marching volume** in a greyish colour. We then draw the **x, y, and z axis** with the colours red, green and blue respectively to add context. Two things to note is that the **origin is in the center of the cube** and the **axis are in-line with one corner of the cube**. The vertices and normals of the shape are **stored in VBOs** before the rendering loop with the vertices being assigned attribute 0 and normals attribute 1. All the vertices are rendered in order using a VAO along with `glDrawArrays`. The shape is drawn over time to start rendering quickly, but rendering during the "Marching" has not been implemented.

This program also uses **Shaders** to implement lighting, these shaders are also compiled before the render loop. The first shader, a **Vertex shader** uses the vertex positions and normals to set `gl_Position`, `eye_direction` is set to **{5,5,5}** as default. The matrices `MVP` and `V` along with `LightDir` are set as **uniform variables**, and also are used to pass along values. The **Fragment Shader** takes `normal_out` (normal), `eye_direction`and `light_direction` from the **Vertex Shader** and **uniform modelColor** as input. The `modelColor` input is the **base** colour for the lighting, the fragment shader uses a **Phong-like Shader**.
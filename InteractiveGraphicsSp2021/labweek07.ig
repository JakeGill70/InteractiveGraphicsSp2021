// camera name, pos x, pos y, pos z, fov, near plane, far plane
camera,3,3,3,60,0.1f,50
<endCameras>
// shader name, file name vertex shader, file name fragment shader, camera name
defaultShader,default,default,default
simple3DShader,simple3Dvertex.glsl,default,camera
<endShaders>
// vertex type, primitive, object name, shader name
PC,triangles,triangle,defaultShader
// x, y, z, r, g, b
 0.0f, 0.5f, 0, 1, 0, 0
-0.5f,-0.5f, 0, 0, 0, 1
 0.5f,-0.5f, 0, 0, 1, 0
// triangle specification
0, 1, 2
<endObject>
PC,cube,simple3DShader
-0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f
-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f 
0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f 
0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f 
0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f 
-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f
-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f
// face 1
0,1,2
0,2,3
// face 2
3,2,5
3,5,4
// face 3
4,5,6
4,6,7
// face 4
7,6,1
7,1,0
// Face 5
5,2,1
5,1,6
// Face 6
7,0,3
7,3,4
<endObject>
PC, lines, axis, simple3DShader
0, 0, 0, 1, 0, 0 
2.0f, 0, 0, 1, 0, 0 
0, 0, 0, 0, 1, 0 
0, 2.0f, 0, 0, 1, 0 
0, 0, 0, 0, 0, 1 
0, 0, 2.0f, 0, 0, 1
<endObject>
#version 450 core
layout (location = 0) in vec3 pos;

out vec3 tex_coords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    tex_coords = pos;
    vec4 position = projection * view * model * vec4(pos, 1.0);
    gl_Position = position.xyww;
}  
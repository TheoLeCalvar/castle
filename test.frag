#version 410

in vec4 position;
out vec4 color_out;

uniform vec2 resolution;


void main () {
  color_out = vec4 ( position.xyz, 1.0);
}
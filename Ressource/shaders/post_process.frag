#version 400

// texture coordinates from vertex shaders
in vec2 st;

// texture sampler
uniform sampler2D tex;

// output fragment colour RGBA
out vec4 frag_colour;

void main () {
  // invert colour of right-hand side
  vec3 colour = texture (tex, st).rgb;
  
  if (st.s >= 0.5) {
    colour.r = colour.r * cos(st.x);
    colour.g = colour.g * cos(st.y);
    colour.b = colour.b * sin(st.x);
  }

  frag_colour = vec4 (colour, 1.0);
}
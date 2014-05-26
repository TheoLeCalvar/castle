#version 400

// texture coordinates from vertex shaders
in vec2 st;

// texture sampler
uniform sampler2D tex;

// output fragment colour RGBA
out vec4 frag_colour;

vec3 greyscale(vec3 inColour)
{
    float coef = 0;

    inColour /= 3.0f;

    coef += inColour.r + inColour.g + inColour.b;

    return vec3(coef, coef, coef);	
}

vec3 sepia(vec3 inColour)
{
    vec3 colour = greyscale(inColour);


    colour.r = colour.r * 1.2;

    return colour;
}

vec3 invert(vec3 inColour)
{
  return 1 - inColour;
}


void main () {
  // invert colour of right-hand side
  vec3 colour = texture (tex, st).rgb;
  
  if (st.s >= 1 && st.t >= 1) 
  {
    colour = greyscale(colour);
  }
  else if(st.s <= 1 && st.t >= 1)
  {
    colour = sepia(colour);
  }
  else if(st.s <= 1 && st.t <= 1)
  {
    colour = invert(colour);
  }

  frag_colour = vec4 (colour, 1.0);
}

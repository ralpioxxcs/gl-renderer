#version 420 core

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec2 resolution;
uniform vec3 colorStart;
uniform vec3 colorEnd;
uniform float gradWeight;
uniform float radius;

out vec4 fragColor;

float roundedRect(vec2 pos, vec2 size, float radius) {
  vec2 d = abs(pos) - size + radius;
  return min(max(d.x,d.y), 0.0) + length(max(d, 0.0)) - radius;
}

/*
          [Texture]

  (0,0)                 (1,0)
    +--------------------+
    |                    |
    |                    |
    |                    |
    +--------------------+
  (0,1)                 (1,1)

*/

void main() {
  const vec2 aspectRatio = vec2(resolution.x / resolution.y, 1.0);

  // normalize in [-1, 1]
  vec2 uvPos = (2.0 * TexCoord - 1.0) * aspectRatio; 
  vec2 objPos = vec2(0.0f, 0.0f) * aspectRatio; // center of texture
  
  const vec2 size = vec2(0.95f, 0.95f);
  float dist = roundedRect((uvPos - objPos), size * aspectRatio, radius);

  float yStep = smoothstep(0.1f, gradWeight, uvPos.y - objPos.y);
  vec3 gradColor = mix(colorStart, colorEnd, yStep);

  vec3 col;
  col = (dist > 0.0) ? col : gradColor;

  float opacity = 1.0;
  opacity = (dist > 0.0) ? 0.0f : smoothstep(0.009, 0.01, abs(dist)); // determine draw or not

  fragColor = vec4(col, opacity);
}
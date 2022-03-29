#version 330 core

vec2 uv = vec2(0);

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec2 resolution;
uniform vec3 color;
uniform float radius;
uniform float thickness;

out vec4 fragColor;

float roundedRect(vec2 pos, vec2 size, float radius) {
  return length(max(abs(pos), size) - size) - radius;
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
  vec2 ratio = vec2(resolution.x / resolution.y, 1.0);
  vec2 uv = TexCoord;             // texture coordinates in [0.0, 1.0]
  uv = (2.0 * uv - 1.0) * ratio;  // normalize to [-1.0, 1.0]

  vec2 pos = vec2(0.0f, 0.0f);   // center
  vec2 size = vec2(0.8f, 0.8f);  // width, height proportion

  float dist = roundedRect(uv - pos, size, radius);
  float smoothedAlpha = smoothstep(0.66, 0.33, dist / thickness * 5.0);

  // outline(frame)
  // float smoothedAlpha = smoothstep(0.66, 0.33, abs(dist / thickness) * 5.0);

  if (smoothedAlpha >= 0.0) {
    fragColor = vec4(color, smoothedAlpha);
    } else {
      fragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}
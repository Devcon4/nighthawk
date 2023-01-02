#version 450

layout(location = 0) out vec3 fragColor;

vec2 positions[3] = vec2[](
  vec2(0.0, -0.5),
  vec2(0.5, 0.5),
  vec2(-0.5, 0.5)
);

vec3 colors[3] = vec3[](
  vec3(1, 0, 0),
  vec3(0, 1, 0),
  vec3(0, 0, 1)
);

layout(push_constant) uniform constants {
  float elapsedTime;
  float deltaTime;
} PushConstants;

void main() {
  gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
  fragColor = colors[gl_VertexIndex] * 600 * PushConstants.deltaTime;
}

// vec3(0.4470, 0.6980, 0.7411),
//   vec3(0.6509, 0.4823, 0.4941),
//   vec3(0.8980, 0.8549, 0.7686)
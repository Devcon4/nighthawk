#version 450

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

vec3 velocity[3] = vec3[](
  vec3(0.1, 0.0, 0.0),
  vec3(0.0, 0.0, 0.1),
  vec3(0.0, 0.0, 0.1)
);

layout(push_constant) uniform constants {
  float elapsedTime;
  float deltaTime;
} PushConstants;

void main() {
  outColor = vec4(fragColor.x, fragColor.y + (60 * PushConstants.deltaTime), fragColor.z, 1.0);
}


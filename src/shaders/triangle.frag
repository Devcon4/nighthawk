#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

vec3 mixVec3(vec3 v1, vec3 v2, float val) {
  return v1 * (1 - val) + v2 * val;
}

void main() {
    float percentage = .75;
    outColor = vec4(mixVec3(fragColor, texture(texSampler, fragTexCoord).rgb, percentage), 1.0);
}

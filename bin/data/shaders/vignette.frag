#version 120

uniform sampler2DRect tex0;

varying vec2 texCoordVarying;

const float RADIUS = 0.5;

const float SOFTNESS = 0.3;

vec2 resolution = vec2(1366, 768);

void main()
{
    vec4 texColor = texture2DRect(tex0, texCoordVarying);

    vec2 position = (texCoordVarying.xy / resolution.xy) - vec2(0.5);

    float len = length(position);

    float vignette = smoothstep(RADIUS, RADIUS-SOFTNESS, len);

    texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, 0.5);

    gl_FragColor = texColor;

}

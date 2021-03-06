#version 120

uniform sampler2DRect tex0;

varying vec2 texCoordVarying;

void main()
{
    float dx = 1.5;
    float dy = 3;
    vec2 Coord = vec2(dx * floor(texCoordVarying.x / dx),
                      dy * floor(texCoordVarying.y / dy));

    vec4 col = texture2DRect(tex0, Coord);

    gl_FragColor = col;
}

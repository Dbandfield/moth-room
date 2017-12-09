#version 120

uniform sampler2DRect tex0;

uniform float distort;

varying vec2 texCoordVarying;

void main()
{
    float dx = 1.1;
    float dy = 3;
    vec2 Coord = vec2(dx * floor(texCoordVarying.x / dx),
                      dy * floor(texCoordVarying.y / dy));

    if(mod(int(texCoordVarying.x), 3) == 0) Coord.y = Coord.y - distort;

    vec4 col = texture2DRect(tex0, Coord);
    //if(col.r > 0.5) col.r = 1.0;
    gl_FragColor = col;
}

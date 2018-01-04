#version 120

uniform sampler2DRect tex0;

varying vec2 texCoordVarying;

void main()
{
    float dx = 5;
    float dy = 5;
    vec2 Coord = vec2(dx * floor(texCoordVarying.x / dx),
                      dy * floor(texCoordVarying.y / dy));

    vec4 col = texture2DRect(tex0, Coord);
    //if(col.r > 0.5) col.r = 1.0;
    gl_FragColor = col;
}

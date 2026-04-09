uniform sampler2D tileset;
uniform sampler2D mapData;

uniform vec2 mapSize;
uniform float tilesPerRow;
uniform float tileSize;

float getId(vec2 t)
{
    return floor(texture2D(mapData, (t + 0.5) / mapSize).r * 255.0);
}

vec4 sampleTile(vec2 t, vec2 local)
{
    float id = getId(t);

    float row = floor(id / tilesPerRow);
    float col = mod(id, tilesPerRow);

    vec2 baseUV = vec2(col, row) / tilesPerRow;
    vec2 finalUV = baseUV + local / tilesPerRow;

    return texture2D(tileset, finalUV);
}

void main()
{
    vec2 tilePos = gl_TexCoord[0].xy * mapSize;

    vec2 tile = floor(tilePos);
    vec2 local = fract(tilePos);

    vec4 center = sampleTile(tile, local);
    vec4 east = sampleTile(tile + vec2(1,0), local);
    vec4 south = sampleTile(tile + vec2(0,1), local);
    vec4 se = sampleTile(tile + vec2(1,1), local);

    float fx = smoothstep(0.1, 1.0, local.x);
    float fy = smoothstep(0.1, 1.0, local.y);

    vec4 mixX1 = mix(center, east, fx);
    vec4 mixX2 = mix(south, se, fx);

    gl_FragColor = mix(mixX1, mixX2, fy);
}

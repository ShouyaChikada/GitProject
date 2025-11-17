xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 20;
 -192.50551;-102.68801;253.98601;,
 -192.50550;-102.68801;-259.86792;,
 192.50551;-102.68801;-259.08091;,
 192.50550;-102.68801;235.06162;,
 192.50552;102.68801;217.07837;,
 192.50552;102.68801;-243.95728;,
 -192.50552;102.68801;-237.74063;,
 -192.50552;102.68801;237.08680;,
 -241.35757;-19.37302;247.13050;,
 -192.50552;102.68801;-237.74063;,
 -241.35757;-7.17017;-249.57681;,
 -192.50550;-102.68801;-259.86792;,
 246.32298;-18.98701;227.73255;,
 192.50551;-102.68801;-259.08091;,
 246.32298;-7.19997;-252.04930;,
 192.50552;102.68801;-243.95728;,
 106.08690;-21.84877;345.04224;,
 -96.94879;-21.80095;345.04224;,
 120.57896;-4.89845;-345.04224;,
 -106.14841;-4.84509;-345.04224;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,7,9,10;,
 4;8,10,11,0;,
 4;12,3,13,14;,
 4;12,14,15,4;,
 3;16,3,12;,
 3;0,17,8;,
 4;3,16,17,0;,
 3;4,16,12;,
 4;7,17,16,4;,
 3;8,17,7;,
 3;14,13,18;,
 3;11,10,19;,
 4;18,2,1,19;,
 3;19,10,9;,
 3;18,15,14;,
 4;18,19,6,5;;
 
 MeshMaterialList {
  1;
  18;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.671373;0.370196;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\inseki.jpg";
   }
  }
 }
 MeshNormals {
  23;
  -0.003082;0.920117;-0.391632;,
  0.000380;-0.910721;-0.413022;,
  0.443883;-0.758220;-0.477567;,
  -0.203050;0.776612;0.596359;,
  0.008345;-0.944782;0.327592;,
  0.010500;0.920444;0.390734;,
  0.449110;-0.796835;0.404171;,
  -0.422361;-0.202766;-0.883457;,
  -0.879814;0.010225;-0.475208;,
  0.883768;-0.007668;-0.467863;,
  0.433570;-0.225522;-0.872443;,
  -0.414242;-0.295328;0.860921;,
  -0.874644;-0.020077;0.484349;,
  0.898854;-0.027897;0.437359;,
  0.485316;-0.310148;0.817482;,
  -0.921411;0.388558;0.004981;,
  -0.814564;0.396414;-0.423487;,
  -0.806174;-0.381705;-0.452088;,
  -0.796276;-0.411110;0.443772;,
  0.810164;0.415708;-0.413304;,
  0.820663;0.409477;0.398549;,
  0.019329;0.694433;0.719298;,
  -0.005672;0.693230;-0.720694;;
  18;
  4;4,1,2,6;,
  4;5,0,0,3;,
  4;12,15,16,8;,
  4;12,8,17,18;,
  4;13,6,2,9;,
  4;13,9,19,20;,
  3;14,6,13;,
  3;18,11,12;,
  4;6,14,11,4;,
  3;20,14,13;,
  4;3,21,21,5;,
  3;12,11,3;,
  3;9,2,10;,
  3;17,8,7;,
  4;10,2,1,7;,
  3;7,8,16;,
  3;10,19,9;,
  4;22,22,0,0;;
 }
 MeshTextureCoords {
  20;
  0.131949;1.000000;,
  0.000000;0.123426;,
  1.000000;0.124566;,
  0.840627;1.000000;,
  0.814568;0.000000;,
  1.000000;0.853518;,
  0.000000;0.844509;,
  0.156438;0.000000;,
  0.141884;0.594330;,
  0.844509;0.000000;,
  0.861661;0.534912;,
  0.876574;1.000000;,
  0.830007;0.592450;,
  0.124566;1.000000;,
  0.134756;0.535057;,
  0.146482;0.000000;,
  0.224457;0.606384;,
  0.751808;0.606151;,
  0.813183;0.523851;,
  0.224298;0.523591;;
 }
}

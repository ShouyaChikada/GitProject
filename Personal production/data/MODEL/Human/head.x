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
 28;
 -3.43158;6.45387;3.42317;,
 3.43158;6.45387;3.42317;,
 3.43158;6.45387;-3.41246;,
 -3.43158;6.45387;-3.41246;,
 -3.43158;0.00370;-3.41246;,
 3.43158;0.00370;-3.41246;,
 3.43158;0.00370;3.42317;,
 -3.43158;0.00370;3.42317;,
 3.43158;5.86425;-3.41246;,
 3.43158;0.00370;-3.41246;,
 -3.43158;0.00370;-3.41246;,
 -3.43158;5.89915;-3.41246;,
 -3.43158;6.45387;-3.41246;,
 3.43158;6.45387;-3.41246;,
 3.43158;4.18642;3.42317;,
 3.43158;0.00370;-3.41246;,
 3.43158;5.86425;-3.41246;,
 3.43158;6.45387;-3.41246;,
 -3.43158;4.22132;3.42317;,
 -3.43158;0.00370;3.42317;,
 3.43158;0.00370;3.42317;,
 3.43158;4.18642;3.42317;,
 3.43158;6.45387;3.42317;,
 -3.43158;6.45387;3.42317;,
 -3.43158;5.89915;-3.41246;,
 -3.43158;0.00370;-3.41246;,
 -3.43158;4.22132;3.42317;,
 -3.43158;6.45387;-3.41246;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,6,15,16;,
 4;14,16,17,1;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,25,7,26;,
 4;24,26,0,27;;
 
 MeshMaterialList {
  4;
  10;
  3,
  2,
  1,
  3,
  2,
  3,
  2,
  3,
  2,
  3;;
  Material {
   0.796863;0.743529;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.743529;0.674510;0.589804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\humanface.jpg";
   }
  }
  Material {
   0.800000;0.752941;0.549020;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,5,5,2;,
  4;2,2,6,6;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,7,7,4;,
  4;4,4,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.091411;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.086001;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.351533;,
  0.000000;1.000000;,
  0.000000;0.091411;,
  0.000000;0.000000;,
  1.000000;0.346122;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.351533;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.086001;,
  1.000000;1.000000;,
  0.000000;0.346122;,
  1.000000;0.000000;;
 }
}

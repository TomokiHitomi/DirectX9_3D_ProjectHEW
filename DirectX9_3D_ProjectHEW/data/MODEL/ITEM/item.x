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
 240;
 1.41421;22.49652;14.65685;,
 12.72792;14.49652;6.65685;,
 12.72792;25.81023;-4.65685;,
 1.41421;33.81025;3.34315;,
 0.00000;34.22446;0.92893;,
 11.31371;26.22445;-7.07107;,
 0.00000;18.22444;-15.07107;,
 -11.31371;26.22445;-7.07107;,
 -12.72792;23.81023;-6.65685;,
 -1.41421;15.81023;-14.65685;,
 -1.41421;4.49653;-3.34315;,
 -12.72792;12.49653;4.65685;,
 -11.31371;12.08231;7.07107;,
 0.00000;4.08231;-0.92893;,
 11.31371;12.08231;7.07107;,
 0.00000;20.08231;15.07107;,
 12.72792;12.49653;4.65685;,
 1.41421;4.49653;-3.34315;,
 1.41421;15.81023;-14.65685;,
 12.72792;23.81023;-6.65685;,
 -12.72792;14.49652;6.65685;,
 -1.41421;22.49652;14.65685;,
 -1.41421;33.81025;3.34315;,
 -12.72792;25.81023;-4.65685;,
 12.62027;26.27531;-5.27417;,
 1.30656;34.27532;2.72583;,
 12.31371;26.51734;-5.94975;,
 1.00000;34.51736;2.05025;,
 11.85491;26.49948;-6.58073;,
 0.54120;34.49949;1.41927;,
 -12.62027;24.42755;-7.12193;,
 -1.30656;16.42755;-15.12193;,
 -12.31371;25.10312;-7.36396;,
 -1.00000;17.10312;-15.36396;,
 -11.85491;25.73411;-7.34610;,
 -0.54120;17.73411;-15.34610;,
 1.30656;21.87920;15.12193;,
 12.62027;13.87921;7.12193;,
 1.00000;21.20363;15.36396;,
 12.31371;13.20363;7.36396;,
 0.54120;20.57264;15.34610;,
 11.85491;12.57265;7.34610;,
 -1.30656;4.03145;-2.72583;,
 -12.62027;12.03145;5.27417;,
 -1.00000;3.78942;-2.05025;,
 -12.31371;11.78942;5.94975;,
 -0.54120;3.80728;-1.41927;,
 -11.85491;11.80728;6.58073;,
 13.16147;14.03772;6.19805;,
 13.16147;25.35143;-5.11566;,
 13.31371;13.49652;5.65685;,
 13.31371;24.81023;-5.65685;,
 13.16147;12.95533;5.11566;,
 13.16147;24.26903;-6.19805;,
 -0.76537;15.50367;-14.96342;,
 -0.76537;4.18996;-3.64971;,
 0.00000;15.39602;-15.07107;,
 0.00000;4.08231;-3.75736;,
 0.76537;15.50367;-14.96342;,
 0.76537;4.18996;-3.64971;,
 0.76537;34.11681;3.64971;,
 0.76537;22.80308;14.96342;,
 0.00000;34.22446;3.75736;,
 0.00000;22.91073;15.07107;,
 -0.76537;34.11681;3.64971;,
 -0.76537;22.80308;14.96342;,
 -13.16147;12.95533;5.11566;,
 -13.16147;24.26903;-6.19805;,
 -13.31371;13.49652;5.65685;,
 -13.31371;24.81023;-5.65685;,
 -13.16147;14.03772;6.19805;,
 -13.16147;25.35143;-5.11566;,
 11.85491;25.73411;-7.34610;,
 0.54120;17.73411;-15.34610;,
 12.31371;25.10312;-7.36396;,
 1.00000;17.10312;-15.36396;,
 12.62027;24.42755;-7.12193;,
 1.30656;16.42755;-15.12193;,
 0.54120;3.80728;-1.41927;,
 11.85491;11.80728;6.58073;,
 1.00000;3.78942;-2.05025;,
 12.31371;11.78942;5.94975;,
 1.30656;4.03145;-2.72583;,
 12.62027;12.03145;5.27417;,
 -11.85491;26.49948;-6.58073;,
 -0.54120;34.49949;1.41927;,
 -12.31371;26.51734;-5.94975;,
 -1.00000;34.51736;2.05025;,
 -12.62027;26.27531;-5.27417;,
 -1.30656;34.27532;2.72583;,
 -0.54120;20.57264;15.34610;,
 -11.85491;12.57265;7.34610;,
 -1.00000;21.20363;15.36396;,
 -12.31371;13.20363;7.36396;,
 -1.30656;21.87920;15.12193;,
 -12.62027;13.87921;7.12193;,
 13.02081;25.72444;-6.15685;,
 12.98642;25.04609;-6.72755;,
 12.50819;25.86249;-6.86763;,
 0.29289;34.72446;2.84315;,
 -0.59032;34.64632;2.87265;,
 -0.11208;34.78639;2.05625;,
 -0.29289;16.31023;-15.57107;,
 0.59032;16.28072;-15.49292;,
 0.11208;17.09712;-15.63299;,
 13.02081;12.99653;6.57107;,
 12.98642;12.42583;5.89272;,
 12.50819;12.28575;6.70911;,
 -13.02081;25.31023;-6.57107;,
 -12.98642;25.88093;-5.89272;,
 -12.50819;26.02101;-6.70911;,
 -0.29289;3.58231;-2.84315;,
 0.59032;3.66046;-2.87265;,
 0.11208;3.52039;-2.05625;,
 0.29289;21.99652;15.57107;,
 -0.59032;22.02603;15.49292;,
 -0.11208;21.20963;15.63299;,
 -13.02081;12.58231;6.15685;,
 -12.98642;13.26066;6.72755;,
 -12.50819;12.44426;6.86763;,
 1.41421;22.49652;14.65685;,
 12.72792;14.49652;6.65685;,
 12.72792;25.81023;-4.65685;,
 1.41421;33.81025;3.34315;,
 0.00000;34.22446;0.92893;,
 11.31371;26.22445;-7.07107;,
 0.00000;18.22444;-15.07107;,
 -11.31371;26.22445;-7.07107;,
 -12.72792;23.81023;-6.65685;,
 -1.41421;15.81023;-14.65685;,
 -1.41421;4.49653;-3.34315;,
 -12.72792;12.49653;4.65685;,
 -11.31371;12.08231;7.07107;,
 0.00000;4.08231;-0.92893;,
 11.31371;12.08231;7.07107;,
 0.00000;20.08231;15.07107;,
 12.72792;12.49653;4.65685;,
 1.41421;4.49653;-3.34315;,
 1.41421;15.81023;-14.65685;,
 12.72792;23.81023;-6.65685;,
 -12.72792;14.49652;6.65685;,
 -1.41421;22.49652;14.65685;,
 -1.41421;33.81025;3.34315;,
 -12.72792;25.81023;-4.65685;,
 12.62027;26.27531;-5.27417;,
 1.30656;34.27532;2.72583;,
 12.31371;26.51734;-5.94975;,
 1.00000;34.51736;2.05025;,
 11.85491;26.49948;-6.58073;,
 0.54120;34.49949;1.41927;,
 -12.62027;24.42755;-7.12193;,
 -1.30656;16.42755;-15.12193;,
 -12.31371;25.10312;-7.36396;,
 -1.00000;17.10312;-15.36396;,
 -11.85491;25.73411;-7.34610;,
 -0.54120;17.73411;-15.34610;,
 1.30656;21.87920;15.12193;,
 12.62027;13.87921;7.12193;,
 1.00000;21.20363;15.36396;,
 12.31371;13.20363;7.36396;,
 0.54120;20.57264;15.34610;,
 11.85491;12.57265;7.34610;,
 -1.30656;4.03145;-2.72583;,
 -12.62027;12.03145;5.27417;,
 -1.00000;3.78942;-2.05025;,
 -12.31371;11.78942;5.94975;,
 -0.54120;3.80728;-1.41927;,
 -11.85491;11.80728;6.58073;,
 13.16147;14.03772;6.19805;,
 13.16147;25.35143;-5.11566;,
 13.31371;13.49652;5.65685;,
 13.31371;24.81023;-5.65685;,
 13.16147;12.95533;5.11566;,
 13.16147;24.26903;-6.19805;,
 -0.76537;15.50367;-14.96342;,
 -0.76537;4.18996;-3.64971;,
 0.00000;15.39602;-15.07107;,
 0.00000;4.08231;-3.75736;,
 0.76537;15.50367;-14.96342;,
 0.76537;4.18996;-3.64971;,
 0.76537;34.11681;3.64971;,
 0.76537;22.80308;14.96342;,
 0.00000;34.22446;3.75736;,
 0.00000;22.91073;15.07107;,
 -0.76537;34.11681;3.64971;,
 -0.76537;22.80308;14.96342;,
 -13.16147;12.95533;5.11566;,
 -13.16147;24.26903;-6.19805;,
 -13.31371;13.49652;5.65685;,
 -13.31371;24.81023;-5.65685;,
 -13.16147;14.03772;6.19805;,
 -13.16147;25.35143;-5.11566;,
 11.85491;25.73411;-7.34610;,
 0.54120;17.73411;-15.34610;,
 12.31371;25.10312;-7.36396;,
 1.00000;17.10312;-15.36396;,
 12.62027;24.42755;-7.12193;,
 1.30656;16.42755;-15.12193;,
 0.54120;3.80728;-1.41927;,
 11.85491;11.80728;6.58073;,
 1.00000;3.78942;-2.05025;,
 12.31371;11.78942;5.94975;,
 1.30656;4.03145;-2.72583;,
 12.62027;12.03145;5.27417;,
 -11.85491;26.49948;-6.58073;,
 -0.54120;34.49949;1.41927;,
 -12.31371;26.51734;-5.94975;,
 -1.00000;34.51736;2.05025;,
 -12.62027;26.27531;-5.27417;,
 -1.30656;34.27532;2.72583;,
 -0.54120;20.57264;15.34610;,
 -11.85491;12.57265;7.34610;,
 -1.00000;21.20363;15.36396;,
 -12.31371;13.20363;7.36396;,
 -1.30656;21.87920;15.12193;,
 -12.62027;13.87921;7.12193;,
 13.02081;25.72444;-6.15685;,
 12.98642;25.04609;-6.72755;,
 12.50819;25.86249;-6.86763;,
 0.29289;34.72446;2.84315;,
 -0.59032;34.64632;2.87265;,
 -0.11208;34.78639;2.05625;,
 -0.29289;16.31023;-15.57107;,
 0.59032;16.28072;-15.49292;,
 0.11208;17.09712;-15.63299;,
 13.02081;12.99653;6.57107;,
 12.98642;12.42583;5.89272;,
 12.50819;12.28575;6.70911;,
 -13.02081;25.31023;-6.57107;,
 -12.98642;25.88093;-5.89272;,
 -12.50819;26.02101;-6.70911;,
 -0.29289;3.58231;-2.84315;,
 0.59032;3.66046;-2.87265;,
 0.11208;3.52039;-2.05625;,
 0.29289;21.99652;15.57107;,
 -0.59032;22.02603;15.49292;,
 -0.11208;21.20963;15.63299;,
 -13.02081;12.58231;6.15685;,
 -12.98642;13.26066;6.72755;,
 -12.50819;12.44426;6.86763;;
 
 364;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;3,2,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,5,4;,
 4;30,31,9,8;,
 4;32,33,31,30;,
 4;34,35,33,32;,
 4;7,6,35,34;,
 4;36,37,1,0;,
 4;38,39,37,36;,
 4;40,41,39,38;,
 4;15,14,41,40;,
 4;11,10,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;47,46,13,12;,
 4;2,1,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;53,52,16,19;,
 4;10,9,54,55;,
 4;55,54,56,57;,
 4;57,56,58,59;,
 4;59,58,18,17;,
 4;0,3,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;65,64,22,21;,
 4;8,11,66,67;,
 4;67,66,68,69;,
 4;69,68,70,71;,
 4;71,70,20,23;,
 4;6,5,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,19,18;,
 4;14,13,78,79;,
 4;79,78,80,81;,
 4;81,80,82,83;,
 4;83,82,17,16;,
 4;4,7,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,23,22;,
 4;12,15,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,21,20;,
 3;2,49,24;,
 3;49,51,96;,
 3;96,24,49;,
 3;24,96,26;,
 3;51,53,97;,
 3;97,96,51;,
 3;96,97,98;,
 3;98,26,96;,
 3;26,98,28;,
 3;53,19,76;,
 3;76,97,53;,
 3;97,76,74;,
 3;74,98,97;,
 3;98,74,72;,
 3;72,28,98;,
 3;28,72,5;,
 3;25,60,3;,
 3;99,62,60;,
 3;60,25,99;,
 3;27,99,25;,
 3;100,64,62;,
 3;62,99,100;,
 3;101,100,99;,
 3;99,27,101;,
 3;29,101,27;,
 3;89,22,64;,
 3;64,100,89;,
 3;87,89,100;,
 3;100,101,87;,
 3;85,87,101;,
 3;101,29,85;,
 3;4,85,29;,
 3;31,54,9;,
 3;102,56,54;,
 3;54,31,102;,
 3;33,102,31;,
 3;103,58,56;,
 3;56,102,103;,
 3;104,103,102;,
 3;102,33,104;,
 3;35,104,33;,
 3;77,18,58;,
 3;58,103,77;,
 3;75,77,103;,
 3;103,104,75;,
 3;73,75,104;,
 3;104,35,73;,
 3;6,73,35;,
 3;37,48,1;,
 3;105,50,48;,
 3;48,37,105;,
 3;39,105,37;,
 3;106,52,50;,
 3;50,105,106;,
 3;107,106,105;,
 3;105,39,107;,
 3;41,107,39;,
 3;83,16,52;,
 3;52,106,83;,
 3;81,83,106;,
 3;106,107,81;,
 3;79,81,107;,
 3;107,41,79;,
 3;14,79,41;,
 3;8,67,30;,
 3;67,69,108;,
 3;108,30,67;,
 3;30,108,32;,
 3;69,71,109;,
 3;109,108,69;,
 3;108,109,110;,
 3;110,32,108;,
 3;32,110,34;,
 3;71,23,88;,
 3;88,109,71;,
 3;109,88,86;,
 3;86,110,109;,
 3;110,86,84;,
 3;84,34,110;,
 3;34,84,7;,
 3;10,55,42;,
 3;55,57,111;,
 3;111,42,55;,
 3;42,111,44;,
 3;57,59,112;,
 3;112,111,57;,
 3;111,112,113;,
 3;113,44,111;,
 3;44,113,46;,
 3;59,17,82;,
 3;82,112,59;,
 3;112,82,80;,
 3;80,113,112;,
 3;113,80,78;,
 3;78,46,113;,
 3;46,78,13;,
 3;0,61,36;,
 3;61,63,114;,
 3;114,36,61;,
 3;36,114,38;,
 3;63,65,115;,
 3;115,114,63;,
 3;114,115,116;,
 3;116,38,114;,
 3;38,116,40;,
 3;65,21,94;,
 3;94,115,65;,
 3;115,94,92;,
 3;92,116,115;,
 3;116,92,90;,
 3;90,40,116;,
 3;40,90,15;,
 3;43,66,11;,
 3;117,68,66;,
 3;66,43,117;,
 3;45,117,43;,
 3;118,70,68;,
 3;68,117,118;,
 3;119,118,117;,
 3;117,45,119;,
 3;47,119,45;,
 3;95,20,70;,
 3;70,118,95;,
 3;93,95,118;,
 3;118,119,93;,
 3;91,93,119;,
 3;119,47,91;,
 3;12,91,47;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;123,122,144,145;,
 4;145,144,146,147;,
 4;147,146,148,149;,
 4;149,148,125,124;,
 4;150,151,129,128;,
 4;152,153,151,150;,
 4;154,155,153,152;,
 4;127,126,155,154;,
 4;156,157,121,120;,
 4;158,159,157,156;,
 4;160,161,159,158;,
 4;135,134,161,160;,
 4;131,130,162,163;,
 4;163,162,164,165;,
 4;165,164,166,167;,
 4;167,166,133,132;,
 4;122,121,168,169;,
 4;169,168,170,171;,
 4;171,170,172,173;,
 4;173,172,136,139;,
 4;130,129,174,175;,
 4;175,174,176,177;,
 4;177,176,178,179;,
 4;179,178,138,137;,
 4;120,123,180,181;,
 4;181,180,182,183;,
 4;183,182,184,185;,
 4;185,184,142,141;,
 4;128,131,186,187;,
 4;187,186,188,189;,
 4;189,188,190,191;,
 4;191,190,140,143;,
 4;126,125,192,193;,
 4;193,192,194,195;,
 4;195,194,196,197;,
 4;197,196,139,138;,
 4;134,133,198,199;,
 4;199,198,200,201;,
 4;201,200,202,203;,
 4;203,202,137,136;,
 4;124,127,204,205;,
 4;205,204,206,207;,
 4;207,206,208,209;,
 4;209,208,143,142;,
 4;132,135,210,211;,
 4;211,210,212,213;,
 4;213,212,214,215;,
 4;215,214,141,140;,
 3;122,169,144;,
 3;169,171,216;,
 3;216,144,169;,
 3;144,216,146;,
 3;171,173,217;,
 3;217,216,171;,
 3;216,217,218;,
 3;218,146,216;,
 3;146,218,148;,
 3;173,139,196;,
 3;196,217,173;,
 3;217,196,194;,
 3;194,218,217;,
 3;218,194,192;,
 3;192,148,218;,
 3;148,192,125;,
 3;145,180,123;,
 3;219,182,180;,
 3;180,145,219;,
 3;147,219,145;,
 3;220,184,182;,
 3;182,219,220;,
 3;221,220,219;,
 3;219,147,221;,
 3;149,221,147;,
 3;209,142,184;,
 3;184,220,209;,
 3;207,209,220;,
 3;220,221,207;,
 3;205,207,221;,
 3;221,149,205;,
 3;124,205,149;,
 3;151,174,129;,
 3;222,176,174;,
 3;174,151,222;,
 3;153,222,151;,
 3;223,178,176;,
 3;176,222,223;,
 3;224,223,222;,
 3;222,153,224;,
 3;155,224,153;,
 3;197,138,178;,
 3;178,223,197;,
 3;195,197,223;,
 3;223,224,195;,
 3;193,195,224;,
 3;224,155,193;,
 3;126,193,155;,
 3;157,168,121;,
 3;225,170,168;,
 3;168,157,225;,
 3;159,225,157;,
 3;226,172,170;,
 3;170,225,226;,
 3;227,226,225;,
 3;225,159,227;,
 3;161,227,159;,
 3;203,136,172;,
 3;172,226,203;,
 3;201,203,226;,
 3;226,227,201;,
 3;199,201,227;,
 3;227,161,199;,
 3;134,199,161;,
 3;128,187,150;,
 3;187,189,228;,
 3;228,150,187;,
 3;150,228,152;,
 3;189,191,229;,
 3;229,228,189;,
 3;228,229,230;,
 3;230,152,228;,
 3;152,230,154;,
 3;191,143,208;,
 3;208,229,191;,
 3;229,208,206;,
 3;206,230,229;,
 3;230,206,204;,
 3;204,154,230;,
 3;154,204,127;,
 3;130,175,162;,
 3;175,177,231;,
 3;231,162,175;,
 3;162,231,164;,
 3;177,179,232;,
 3;232,231,177;,
 3;231,232,233;,
 3;233,164,231;,
 3;164,233,166;,
 3;179,137,202;,
 3;202,232,179;,
 3;232,202,200;,
 3;200,233,232;,
 3;233,200,198;,
 3;198,166,233;,
 3;166,198,133;,
 3;120,181,156;,
 3;181,183,234;,
 3;234,156,181;,
 3;156,234,158;,
 3;183,185,235;,
 3;235,234,183;,
 3;234,235,236;,
 3;236,158,234;,
 3;158,236,160;,
 3;185,141,214;,
 3;214,235,185;,
 3;235,214,212;,
 3;212,236,235;,
 3;236,212,210;,
 3;210,160,236;,
 3;160,210,135;,
 3;163,186,131;,
 3;237,188,186;,
 3;186,163,237;,
 3;165,237,163;,
 3;238,190,188;,
 3;188,237,238;,
 3;239,238,237;,
 3;237,165,239;,
 3;167,239,165;,
 3;215,140,190;,
 3;190,238,215;,
 3;213,215,238;,
 3;238,239,213;,
 3;211,213,239;,
 3;239,167,211;,
 3;132,211,167;;
 
 MeshMaterialList {
  1;
  364;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.605490;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  120;
  0.631353;0.475010;0.612992;,
  0.769334;0.377443;0.515424;,
  0.631352;0.612992;0.475010;,
  0.769334;0.515424;0.377442;,
  0.000000;0.797910;-0.602777;,
  0.137982;0.700343;-0.700343;,
  -0.137982;0.700343;-0.700343;,
  0.000000;0.602776;-0.797910;,
  -0.769334;-0.377443;-0.515424;,
  -0.631353;-0.475011;-0.612992;,
  -0.769334;-0.515424;-0.377444;,
  -0.631353;-0.612991;-0.475011;,
  -0.137980;-0.700343;0.700343;,
  0.000000;-0.797910;0.602777;,
  0.000000;-0.602776;0.797910;,
  0.137980;-0.700343;0.700343;,
  0.769334;-0.515424;-0.377444;,
  0.631353;-0.612991;-0.475011;,
  0.769334;-0.377443;-0.515424;,
  0.631353;-0.475011;-0.612991;,
  -0.769334;0.377444;0.515424;,
  -0.631353;0.475011;0.612992;,
  -0.769334;0.515424;0.377443;,
  -0.631353;0.612991;0.475011;,
  0.543117;0.793964;0.273213;,
  0.754610;0.644415;0.123665;,
  0.380737;0.921208;-0.080095;,
  0.594758;0.769872;-0.231431;,
  0.155590;0.899086;-0.409190;,
  0.346410;0.764155;-0.544120;,
  -0.754609;-0.123665;-0.644416;,
  -0.543115;-0.273213;-0.793965;,
  -0.594757;0.231431;-0.769872;,
  -0.380735;0.080094;-0.921209;,
  -0.346411;0.544118;-0.764156;,
  -0.155590;0.409188;-0.899087;,
  0.543115;0.273213;0.793965;,
  0.754609;0.123665;0.644416;,
  0.380735;-0.080095;0.921209;,
  0.594757;-0.231431;0.769872;,
  0.155589;-0.409188;0.899087;,
  0.346411;-0.544119;0.764156;,
  -0.754609;-0.644416;-0.123665;,
  -0.543115;-0.793965;-0.273213;,
  -0.594758;-0.769872;0.231431;,
  -0.380735;-0.921209;0.080094;,
  -0.346410;-0.764156;0.544119;,
  -0.155589;-0.899087;0.409188;,
  0.909238;0.168955;0.380448;,
  0.909238;0.380447;0.168954;,
  0.988398;-0.116137;0.097885;,
  0.988398;0.097885;-0.116137;,
  0.905137;-0.380472;-0.189651;,
  0.905137;-0.189651;-0.380472;,
  -0.388486;-0.748675;-0.537181;,
  -0.388486;-0.537182;-0.748675;,
  0.012906;-0.805914;-0.591891;,
  0.012906;-0.591892;-0.805914;,
  0.403138;-0.735439;-0.544618;,
  0.403138;-0.544618;-0.735439;,
  0.388486;0.537181;0.748676;,
  0.388487;0.748675;0.537182;,
  -0.012906;0.591891;0.805914;,
  -0.012906;0.805913;0.591893;,
  -0.403137;0.544618;0.735440;,
  -0.403138;0.735439;0.544619;,
  -0.909238;-0.380448;-0.168955;,
  -0.909238;-0.168955;-0.380448;,
  -0.988398;-0.097885;0.116137;,
  -0.988398;0.116137;-0.097885;,
  -0.905137;0.189651;0.380472;,
  -0.905138;0.380471;0.189651;,
  0.165917;0.416357;-0.893934;,
  0.337698;0.537824;-0.772467;,
  0.413536;0.086738;-0.906347;,
  0.579550;0.204128;-0.788957;,
  0.569255;-0.272185;-0.775799;,
  0.741036;-0.150717;-0.654331;,
  0.165917;-0.893934;0.416357;,
  0.337698;-0.772467;0.537825;,
  0.413536;-0.906347;0.086739;,
  0.579551;-0.788956;0.204129;,
  0.569255;-0.775799;-0.272185;,
  0.741036;-0.654331;-0.150717;,
  -0.337698;0.772466;-0.537826;,
  -0.165917;0.893933;-0.416359;,
  -0.579551;0.788956;-0.204130;,
  -0.413536;0.906346;-0.086740;,
  -0.741037;0.654331;0.150717;,
  -0.569256;0.775799;0.272185;,
  -0.337698;-0.537825;0.772467;,
  -0.165917;-0.416357;0.893934;,
  -0.579550;-0.204129;0.788957;,
  -0.413535;-0.086739;0.906347;,
  -0.741036;0.150717;0.654331;,
  -0.569255;0.272184;0.775799;,
  0.860224;0.469955;-0.197881;,
  0.848514;0.125655;-0.514038;,
  0.606790;0.538304;-0.584837;,
  0.192387;0.942188;0.274352;,
  -0.274628;0.919836;0.280144;,
  -0.032904;0.990636;-0.132507;,
  -0.192386;-0.274351;-0.942188;,
  0.274627;-0.280143;-0.919837;,
  0.032903;0.132504;-0.990636;,
  0.860223;-0.197881;0.469956;,
  0.848514;-0.514038;0.125656;,
  0.606790;-0.584837;0.538304;,
  -0.860223;0.197881;-0.469956;,
  -0.848515;0.514037;-0.125656;,
  -0.606790;0.584836;-0.538305;,
  -0.192386;-0.942189;-0.274351;,
  0.274627;-0.919837;-0.280143;,
  0.032903;-0.990636;0.132504;,
  0.192386;0.274351;0.942189;,
  -0.274627;0.280143;0.919837;,
  -0.032903;-0.132505;0.990636;,
  -0.860223;-0.469956;0.197881;,
  -0.848514;-0.125656;0.514037;,
  -0.606790;-0.538304;0.584837;;
  364;
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,25,24;,
  4;24,25,27,26;,
  4;26,27,29,28;,
  4;28,29,5,4;,
  4;30,31,9,8;,
  4;32,33,31,30;,
  4;34,35,33,32;,
  4;6,7,35,34;,
  4;36,37,1,0;,
  4;38,39,37,36;,
  4;40,41,39,38;,
  4;14,15,41,40;,
  4;10,11,43,42;,
  4;42,43,45,44;,
  4;44,45,47,46;,
  4;46,47,13,12;,
  4;3,1,48,49;,
  4;49,48,50,51;,
  4;51,50,52,53;,
  4;53,52,16,18;,
  4;11,9,55,54;,
  4;54,55,57,56;,
  4;56,57,59,58;,
  4;58,59,19,17;,
  4;0,2,61,60;,
  4;60,61,63,62;,
  4;62,63,65,64;,
  4;64,65,23,21;,
  4;8,10,66,67;,
  4;67,66,68,69;,
  4;69,68,70,71;,
  4;71,70,20,22;,
  4;7,5,73,72;,
  4;72,73,75,74;,
  4;74,75,77,76;,
  4;76,77,18,19;,
  4;15,13,78,79;,
  4;79,78,80,81;,
  4;81,80,82,83;,
  4;83,82,17,16;,
  4;4,6,84,85;,
  4;85,84,86,87;,
  4;87,86,88,89;,
  4;89,88,22,23;,
  4;12,14,91,90;,
  4;90,91,93,92;,
  4;92,93,95,94;,
  4;94,95,21,20;,
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,73;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;85,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;72,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,84;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;,
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,25,24;,
  4;24,25,27,26;,
  4;26,27,29,28;,
  4;28,29,5,4;,
  4;30,31,9,8;,
  4;32,33,31,30;,
  4;34,35,33,32;,
  4;6,7,35,34;,
  4;36,37,1,0;,
  4;38,39,37,36;,
  4;40,41,39,38;,
  4;14,15,41,40;,
  4;10,11,43,42;,
  4;42,43,45,44;,
  4;44,45,47,46;,
  4;46,47,13,12;,
  4;3,1,48,49;,
  4;49,48,50,51;,
  4;51,50,52,53;,
  4;53,52,16,18;,
  4;11,9,55,54;,
  4;54,55,57,56;,
  4;56,57,59,58;,
  4;58,59,19,17;,
  4;0,2,61,60;,
  4;60,61,63,62;,
  4;62,63,65,64;,
  4;64,65,23,21;,
  4;8,10,66,67;,
  4;67,66,68,69;,
  4;69,68,70,71;,
  4;71,70,20,22;,
  4;7,5,73,72;,
  4;72,73,75,74;,
  4;74,75,77,76;,
  4;76,77,18,19;,
  4;15,13,78,79;,
  4;79,78,80,81;,
  4;81,80,82,83;,
  4;83,82,17,16;,
  4;4,6,84,85;,
  4;85,84,86,87;,
  4;87,86,88,89;,
  4;89,88,22,23;,
  4;12,14,91,90;,
  4;90,91,93,92;,
  4;92,93,95,94;,
  4;94,95,21,20;,
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,73;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;85,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;72,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,84;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;;
 }
}

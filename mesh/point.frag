#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// フレームバッファに出力するデータ
layout (location = 0) out vec4 fc;                  // フラグメントの色

// 頂点色の補間値
in vec3 vc;

void main(void)
{
  fc = vec4(vc, 1.0);
}

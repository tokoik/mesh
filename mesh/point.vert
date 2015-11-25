#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 変換行列
uniform mat4 mc;                                    // クリッピング座標系への変換行列

// 頂点属性
layout (location = 0) in vec4 pv;                   // 頂点位置

// 頂点色
out vec3 vc;

void main(void)
{
  // 疑似カラー処理
  float z = pv.z * 6.0 + 2.0;
  vc = clamp(2.0 - abs(vec3(z - 4.0, z - 2.0, z)), 0.0, 1.0);

  gl_Position = mc * pv;
}

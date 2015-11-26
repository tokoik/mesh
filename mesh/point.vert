#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// �ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���_�ʒu
layout (location = 1) in vec3 nv;                   // �@���x�N�g��

// ���_�F
out vec3 vc;

void main(void)
{
  // �^���J���[����
  float z = pv.z * 6.0 + 2.0;
  vc = clamp(vec3(z - 2.0, 2.0 - abs(z - 2.0), 2.0 - z), 0.0, 1.0) * nv.z;

  gl_Position = mc * pv;
}

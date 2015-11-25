#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// �ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���_�ʒu

// ���_�F
out vec3 vc;

void main(void)
{
  // �^���J���[����
  float z = pv.z * 6.0 + 2.0;
  vc = clamp(2.0 - abs(vec3(z - 4.0, z - 2.0, z)), 0.0, 1.0);

  gl_Position = mc * pv;
}

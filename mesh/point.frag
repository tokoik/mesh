#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

// ���_�F�̕�Ԓl
in vec3 vc;

void main(void)
{
  fc = vec4(vc, 1.0);
}

#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec4 idiff;                                      // �g�U���ˌ����x
in vec4 ispec;                                      // ���ʔ��ˌ����x

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

void main(void)
{
  // �e�N�X�`���}�b�s���O���s���ĉA�e�����߂�
  fc = idiff + ispec;
}

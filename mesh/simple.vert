#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ����
uniform vec4 lamb;                                  // ��������
uniform vec4 ldiff;                                 // �g�U���ˌ�����
uniform vec4 lspec;                                 // ���ʔ��ˌ�����
uniform vec4 pl;                                    // �ʒu

// �ގ�
uniform vec4 kamb;                                  // �����̔��ˌW��
uniform vec4 kdiff;                                 // �g�U���ˌW��
uniform vec4 kspec;                                 // ���ʔ��ˌW��
uniform float kshi;                                 // �P���W��

// �ϊ��s��
uniform mat4 mw;                                    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                    // �@���x�N�g���̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���_���W�l
layout (location = 1) in vec4 nv;                   // �@���x�N�g��

// ���X�^���C�U�ɑ��钸�_����
out vec4 idiff;                                     // �g�U���ˌ����x
out vec4 ispec;                                     // ���ʔ��ˌ����x

void main(void)
{
  // ���W�v�Z
  vec4 p = mw * pv;                                 // ���_���W�n�̒��_�̈ʒu
  vec4 q = pl;                                      // ���_���W�n�̌����̈ʒu
  vec3 v = normalize(p.xyz / p.w);                  // �����x�N�g��
  vec3 l = normalize((q * p.w - p * q.w).xyz);      // �����x�N�g��
  vec3 n = normalize((mg * nv).xyz);                // �@���x�N�g��
  vec3 h = normalize(l - v);                        // ���ԃx�N�g��

  // �^���J���[����
  float z = pv.z * 6.0 + 2.0;
  vec3 vc = clamp(vec3(z - 2.0, 2.0 - abs(z - 2.0), 2.0 - z), 0.0, 1.0);

  // �A�e�v�Z
  idiff = (max(dot(n, l), 0.0) * kdiff * ldiff + kamb * lamb) * vec4(vc, 1.0);
  ispec = pow(max(dot(n, h), 0.0), kshi) * kspec * lspec;

  // �N���b�s���O���W�n�ɂ�������W�l
  gl_Position = mc * pv;
}

#pragma once

//
// �e��ݒ�
//

// �⏕�v���O����
#include "gg.h"
using namespace gg;

// �J�����ɑ΂���I�u�W�F�N�g�̒��S�ʒu
const GLfloat objectCenter[] = { 0.0f, 0.0f, -5.0f };

// �J�����p�����[�^
const GLfloat cameraFovy(1.0f);                         // ��p
const GLfloat cameraNear(0.1f);                         // �O���ʂ܂ł̋���
const GLfloat cameraFar(50.0f);                         // ����ʂ܂ł̋���

// �}�E�X����̌W��
const double motionFactor[] = { 1.0, 1.0, 0.05 };

// ����
const GgSimpleShader::Light light =
{
  { 0.2f, 0.2f, 0.2f, 1.0f },                           // ��������
  { 1.0f, 1.0f, 1.0f, 1.0f },                           // �g�U���ˌ�����
  { 1.0f, 1.0f, 1.0f, 1.0f },                           // ���ʌ�����
  { 0.0f, 0.0f, 5.0f, 1.0f }                            // �ʒu
};

// �ގ�
const GgSimpleShader::Material material =
{
  { 0.8f, 0.8f, 0.8f, 1.0f },                           // �����̔��ˌW��
  { 0.8f, 0.8f, 0.8f, 1.0f },                           // �g�U���ˌW��
  { 0.2f, 0.2f, 0.2f, 1.0f },                           // ���ʔ��ˌW��
  50.0f                                                 // �P���W��
};

// �w�i�F
const GLfloat background[] = { 0.1f, 0.2f, 0.3f, 0.0f };

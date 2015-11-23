#pragma once

//
// �E�B���h�E�֘A�̏���
//

// �e��ݒ�
#include "config.h"

//
// �E�B���h�E�֘A�̏�����S������N���X
//
class Window
{
  // �E�B���h�E�̎��ʎq
  GLFWwindow *const window;

  // �E�B���h�E�̕��ƍ���
  GLsizei size[2];

  // �J�����ɑ΂���I�u�W�F�N�g�̒��S�ʒu
  GLfloat eye[3];

  // �h���b�O�J�n�ʒu
  double start[2];

  // �g���b�N�{�[������
  GgTrackball trackball;

  // �v���W�F�N�V�����ϊ��s��
  GgMatrix mp;

  //
  // �R�s�[�R���X�g���N�^ (�R�s�[�֎~)
  //
  Window(const Window &w);

  //
  // ��� (����֎~)
  //
  Window &operator=(const Window &w);

public:

  //
  // �R���X�g���N�^
  //
  Window(int width = 640, int height = 480, const char *title = "GLFW Window",
    GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);

  //
  // �f�X�g���N�^
  //
  virtual ~Window();

  //
  // �E�B���h�E�̎��ʎq�̎擾
  //
  const GLFWwindow *get() const
  {
    return window;
  }

  //
  // �E�B���h�E�����ׂ����𔻒肷��
  //
  //   �E�`�惋�[�v�̌p�������Ƃ��Ďg��
  //
  bool shouldClose() const
  {
    // �E�B���h�E����邩 ESC �L�[���^�C�v����Ă���ΐ^
    return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
  }

  //
  // ��ʃN���A
  //
  //   �E�}�`�̕`��J�n�O�ɌĂяo��
  //   �E��ʂ̏����Ȃǂ��s��
  //
  void clear();

  //
  // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
  //
  //   �E�}�`�̕`��I����ɌĂяo��
  //   �E�_�u���o�b�t�@�����O�̃o�b�t�@�̓���ւ����s��
  //   �E�L�[�{�[�h���쓙�̃C�x���g�����o��
  //
  void swapBuffers();

  //
  // �E�B���h�E�̃T�C�Y�ύX���̏���
  //
  //   �E�E�B���h�E�̃T�C�Y�ύX���ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
  //   �E�E�B���h�E�̍쐬���ɂ͖����I�ɌĂяo��
  //
  static void resize(GLFWwindow *window, int width, int height);

  //
  // �}�E�X�{�^���𑀍삵���Ƃ��̏���
  //
  //   �E�}�E�X�{�^�����������Ƃ��ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
  //
  static void mouse(GLFWwindow *window, int button, int action, int mods);

  //
  // �}�E�X�z�C�[�����쎞�̏���
  //
  //   �E�}�E�X�z�C�[���𑀍삵�����ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
  //
  static void wheel(GLFWwindow *window, double x, double y);

  //
  // �L�[�{�[�h���^�C�v�������̏���
  //
  //   �D�L�[�{�[�h���^�C�v�������ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
  //
  static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);

  //
  // ���݂̃E�B���h�E�̃T�C�Y�𓾂�
  //
  const GLsizei *getSize() const
  {
    return size;
  }

  //
  // �r���[�ϊ��s��𓾂�
  //
  GgMatrix getMv() const
  {
    return ggTranslate(eye) * trackball.getMatrix();
  }

  //
  // �v���W�F�N�V�����ϊ��s��𓾂�
  //
  const GgMatrix &getMp() const
  {
    return mp;
  }
};

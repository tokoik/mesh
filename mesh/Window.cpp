#include "Window.h"

//
// �E�B���h�E�֘A�̏���
//

// �W�����C�u����
#include <cmath>

//
// �R���X�g���N�^
//
Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
  : window(glfwCreateWindow(width, height, title, monitor, share))
{
  // �E�B���h�E���J���Ă��Ȃ�������߂�
  if (!window) return;

  // ���݂̃E�B���h�E�������Ώۂɂ���
  glfwMakeContextCurrent(window);

  // �Q�[���O���t�B�b�N�X���_�̓s���ɂ��ƂÂ����������s��
  ggInit();

  // ���̃C���X�^���X�� this �|�C���^���L�^���Ă���
  glfwSetWindowUserPointer(window, this);

  // �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
  glfwSetFramebufferSizeCallback(window, resize);

  // �}�E�X�{�^���𑀍삵���Ƃ��̏���
  glfwSetMouseButtonCallback(window, mouse);

  // �}�E�X�z�C�[�����쎞�ɌĂяo������
  glfwSetScrollCallback(window, wheel);

  // �L�[�{�[�h�𑀍삵�����̏���
  glfwSetKeyCallback(window, keyboard);

  // ���_�̏����ʒu��ݒ肷��
  eye[0] = objectCenter[0];
  eye[1] = objectCenter[1];
  eye[2] = objectCenter[2];

  // �r���[�|�[�g�ƃv���W�F�N�V�����ϊ��s�������������
  resize(window, width, height);
}

//
// �f�X�g���N�^
//
Window::~Window()
{
  // �E�B���h�E��j������
  glfwDestroyWindow(window);
}

//
// ��ʃN���A
//
//   �E�}�`�̕`��J�n�O�ɌĂяo��
//   �E��ʂ̏����Ȃǂ��s��
//
void Window::clear()
{
  // �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
  glViewport(0, 0, size[0], size[1]);

  // �J���[�o�b�t�@�ƃf�v�X�o�b�t�@����������
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//
// �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
//
//   �E�}�`�̕`��I����ɌĂяo��
//   �E�_�u���o�b�t�@�����O�̃o�b�t�@�̓���ւ����s��
//   �E�L�[�{�[�h���쓙�̃C�x���g�����o��
//
void Window::swapBuffers()
{
  // �G���[�`�F�b�N
  ggError("SwapBuffers");

  // �J���[�o�b�t�@�����ւ���
  glfwSwapBuffers(window);

  // �C�x���g�����o��
  glfwPollEvents();

  // ���{�^���h���b�O
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
  {
    // �}�E�X�̈ʒu�𒲂ׂ�
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    // ���_����]����
    trackball.motion(float(x), float(y));
  }
}

//
// �E�B���h�E�̃T�C�Y�ύX���̏���
//
//   �E�E�B���h�E�̃T�C�Y�ύX���ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
//   �E�E�B���h�E�̍쐬���ɂ͖����I�ɌĂяo��
//
void Window::resize(GLFWwindow *window, int width, int height)
{
  // ���̃C���X�^���X�� this �|�C���^�𓾂�
  Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

  if (instance)
  {
    // �v���W�F�N�V�����ϊ��s���ݒ肷��
    instance->mp = ggPerspective(cameraFovy, GLfloat(width) / GLfloat(height), cameraNear, cameraFar);

    // �g���b�N�{�[�������͈̔͂�ݒ肷��
    instance->trackball.region(width, height);

    // �E�B���h�E�̕��ƍ�����ۑ����Ă���
    instance->size[0] = width;
    instance->size[1] = height;

    // �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
    glViewport(0, 0, width, height);
  }
}

//
// �}�E�X�{�^���𑀍삵���Ƃ��̏���
//
//   �E�}�E�X�{�^�����������Ƃ��ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
//
void Window::mouse(GLFWwindow *window, int button, int action, int mods)
{
  // ���̃C���X�^���X�� this �|�C���^�𓾂�
  Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

  if (instance)
  {
    // �}�E�X�̌��݈ʒu�����o��
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
      // ���{�^�������������̏���
      if (action)
      {
        // �g���b�N�{�[�������J�n
        instance->trackball.start(float(x), float(y));
      }
      else
      {
        // �g���b�N�{�[�������I��
        instance->trackball.stop(float(x), float(y));
      }
      break;
    case GLFW_MOUSE_BUTTON_2:
      // �E�{�^�������������̏���
      break;
    case GLFW_MOUSE_BUTTON_3:
      break;
      break;
    default:
      break;
    }
  }
}

//
// �}�E�X�z�C�[�����쎞�̏���
//
//   �E�}�E�X�z�C�[���𑀍삵�����ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
//
void Window::wheel(GLFWwindow *window, double x, double y)
{
  // ���̃C���X�^���X�� this �|�C���^�𓾂�
  Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

  if (instance)
  {
    // ���_��O��Ɉړ�����
    instance->eye[2] -= GLfloat(motionFactor[2] * (fabs(instance->eye[2]) + 1.0) * y);
  }
}

//
// �L�[�{�[�h���^�C�v�������̏���
//
//   �D�L�[�{�[�h���^�C�v�������ɃR�[���o�b�N�֐��Ƃ��ČĂяo�����
//
void Window::keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  // ���̃C���X�^���X�� this �|�C���^�𓾂�
  Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

  if (instance)
  {
    if (action == GLFW_PRESS)
    {
      // �L�[�{�[�h����ɂ�鏈��
      switch (key)
      {
      case GLFW_KEY_R:
        // ���_�̉�]�����Z�b�g����
        instance->trackball.reset();
        break;
      case GLFW_KEY_T:
        //���_�̈ʒu�����Z�b�g����
        instance->eye[0] = objectCenter[0];
        instance->eye[1] = objectCenter[1];
        instance->eye[2] = objectCenter[2];
        break;
      case GLFW_KEY_SPACE:
        break;
      case GLFW_KEY_BACKSPACE:
      case GLFW_KEY_DELETE:
        break;
      case GLFW_KEY_UP:
        break;
      case GLFW_KEY_DOWN:
        break;
      case GLFW_KEY_RIGHT:
        break;
      case GLFW_KEY_LEFT:
        break;
      default:
        break;
      }
    }
  }
}

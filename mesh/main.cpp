//
// ���b�V�����g�����}�`�`��̃T���v��
//

// �W�����C�u����
#include <iostream>
#include <cmath>

// �E�B���h�E�֘A�̏���
#include "Window.h"

//
// ���C���v���O����
//
int main()
{
  // GLFW ������������
  if (glfwInit() == GL_FALSE)
  {
    // GLFW �̏������Ɏ��s����
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return EXIT_FAILURE;
  }

  // �v���O�����I�����ɂ� GLFW ���I������
  atexit(glfwTerminate);

  // OpenGL Version 3.2 Core Profile ��I������
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // �E�B���h�E���J��
  Window window(640, 480, "Mesh Sample");
  if (!window.get())
  {
    // �E�B���h�E���쐬�ł��Ȃ�����
    std::cerr << "Can't open GLFW window." << std::endl;
    return EXIT_FAILURE;
  }

  // �w�i�F��ݒ肷��
  glClearColor(background[0], background[1], background[2], background[3]);

  // �B�ʏ���������L���ɂ���
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (!window.shouldClose())
  {
    // ��ʏ���
    window.clear();

    // �o�b�t�@�����ւ���
    window.swapBuffers();
  }
}

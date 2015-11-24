//
// ���b�V�����g�����}�`�`��̃T���v��
//

// �W�����C�u����
#include <iostream>
#include <cmath>

// �E�B���h�E�֘A�̏���
#include "Window.h"

// ���b�V���̗񐔂ƍs��
const auto slices(160), stacks(120);

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

  // ���b�V���`��p�̃V�F�[�_
  const auto point(ggLoadShader("point.vert", "point.frag"));
  const auto mcLoc(glGetUniformLocation(point, "mc"));

  // ���_�z��I�u�W�F�N�g
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_��
  const auto vertices(slices * stacks);

  // ���_�ʒu
  GLfloat position[vertices][3];

  // ���_�ʒu���i�[���钸�_�o�b�t�@�I�u�W�F�N�g
  GLuint positionBuffer;
  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�̃��������m�ۂ���
  glBufferData(GL_ARRAY_BUFFER, sizeof position, nullptr, GL_DYNAMIC_DRAW);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�� 0 �Ԃ� attribute �ϐ�������o��
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

  // ���̃C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̃��������m�ۂ���
  const auto indexes((slices - 1) * (stacks - 1) * 2 * 3);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes * sizeof (GLuint), nullptr, GL_STATIC_DRAW);

  // ���̃C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�ɃC���f�b�N�X���i�[����
  auto index(static_cast<GLuint *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
  for (int j = 0; j < stacks - 1; ++j)
  {
    for (int i = 0; i < slices - 1; ++i)
    {
      index[0] = slices * j + i;
      index[1] = index[5] = index[0] + 1;
      index[2] = index[4] = index[0] + slices;
      index[3] = index[2] + 1;
      index += 6;
    }
  }
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

  // ���̒��_�z��I�u�W�F�N�g�̌�������������
  glBindVertexArray(0);

  // �w�i�F��ݒ肷��
  glClearColor(background[0], background[1], background[2], background[3]);

  // �B�ʏ���������L���ɂ���
  glEnable(GL_DEPTH_TEST);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (!window.shouldClose())
  {
    // ��ʏ���
    window.clear();

    // ���_�ʒu���i�[���钸�_�o�b�t�@�I�u�W�F�N�g�ɒ��_���W�l��ݒ肷��
    static int frame(0);
    const int cycle(100);
    const float pi(3.14159265f);
    for (auto i = 0; i < slices * stacks; ++i)
    {
      const auto x((GLfloat(i % slices) / GLfloat(slices - 1) - 0.5f) * GLfloat(slices) / GLfloat(stacks));
      const auto y((GLfloat(i / slices) / GLfloat(stacks - 1) - 0.5f));
      const auto r(sqrt(x * x + y * y) * 6.0f * pi);

      position[i][0] = x;
      position[i][1] = y;
      position[i][2] = sin(r - float(frame) * pi * 2.0f / float(cycle)) / (r + pi);
    }
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof position, position);
    if (++frame >= cycle) frame = 0;

    // �V�F�[�_�̎w��
    glUseProgram(point);
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, (window.getMp() * window.getMv()).get());

    // �`��
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexes, GL_UNSIGNED_INT, 0);

    // �o�b�t�@�����ւ���
    window.swapBuffers();
  }

  // ���_�z��I�u�W�F�N�g���폜����
  glDeleteVertexArrays(1, &vao);

  // ���_�o�b�t�@�I�u�W�F�N�g���폜����
  glDeleteBuffers(1, &positionBuffer);
}

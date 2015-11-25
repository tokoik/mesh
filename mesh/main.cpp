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


  // ���_�ʒu
  GLfloat position[stacks][slices][3];

  // �@���x�N�g��
  GLfloat normal[stacks][slices][3];

  // ���_�z��I�u�W�F�N�g
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�ʒu���i�[���钸�_�o�b�t�@�I�u�W�F�N�g
  GLuint positionBuffer;
  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�̃��������m�ۂ���
  glBufferData(GL_ARRAY_BUFFER, sizeof position, nullptr, GL_DYNAMIC_DRAW);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�� 0 �Ԃ� attribute �ϐ�������o��
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // �@���x�N�g�����i�[���钸�_�o�b�t�@�I�u�W�F�N�g
  GLuint normalBuffer;
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�̃��������m�ۂ���
  glBufferData(GL_ARRAY_BUFFER, sizeof normal, nullptr, GL_DYNAMIC_DRAW);

  // ���̒��_�o�b�t�@�I�u�W�F�N�g�� 1 �Ԃ� attribute �ϐ�������o��
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

  // ���̃C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̃��������m�ۂ���
  const auto indexes((slices - 1) * (stacks - 1) * 2 * 3);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes * sizeof (GLuint), nullptr, GL_STATIC_DRAW);

  // ���̃C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�ɃC���f�b�N�X���i�[����
  auto index(static_cast<GLuint *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)));
  for (auto j = 0; j < stacks - 1; ++j)
  {
    for (auto i = 0; i < slices - 1; ++i)
    {
      const auto k(slices * j + i);
      index[0] = k;
      index[1] = index[5] = k + 1;
      index[2] = index[4] = k + slices;
      index[3] = k + slices + 1;
      index += 6;
    }
  }
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

  // ���̒��_�z��I�u�W�F�N�g�̌�������������
  glBindVertexArray(0);

  // ���b�V���`��p�̃V�F�[�_
  const auto point(ggLoadShader("point.vert", "point.frag"));
  const auto mcLoc(glGetUniformLocation(point, "mc"));

  // �w�i�F��ݒ肷��
  glClearColor(background[0], background[1], background[2], background[3]);

  // �B�ʏ���������L���ɂ���
  glEnable(GL_DEPTH_TEST);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (!window.shouldClose())
  {
    // ��ʏ���
    window.clear();

    // �V�F�[�_�̎w��
    glUseProgram(point);
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, (window.getMp() * window.getMv()).get());

    // ���_�ʒu���i�[���钸�_�o�b�t�@�I�u�W�F�N�g�ɒ��_���W�l��ݒ肷��
    static auto frame(0);
    const auto cycle(100);
    const auto t(float(frame) / float(cycle));
    const auto pi(3.14159265f);
    for (auto j = 0; j < stacks; ++j)
    {
      for (auto i = 0; i < slices; ++i)
      {
        const auto x((GLfloat(i) / GLfloat(slices - 1) - 0.5f) * GLfloat(slices) / GLfloat(stacks));
        const auto y((GLfloat(j) / GLfloat(stacks - 1) - 0.5f));
        const auto r(hypot(x, y) * 6.0f * pi);

        position[j][i][0] = x;
        position[j][i][1] = y;
        position[j][i][2] = sin(r - 2.0f * pi * t) / (r + pi);
      }
    }
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof position, position);
    if (++frame >= cycle) frame = 0;

    // �@���x�N�g�����i�[���钸�_�o�b�t�@�I�u�W�F�N�g�ɖ@���x�N�g����ݒ肷��
    for (auto j = 0; j < stacks; ++j)
    {
      for (auto i = 0; i < slices; ++i)
      {
        // i �����̐ڐ��x�N�g��
        const auto i0(i > 0 ? i - 1 : 0);
        const auto i1(i < slices - 1 ? i + 1 : slices - 1);
        const GLfloat vi[] =
        {
          position[j][i1][0] - position[j][i0][0],
          position[j][i1][1] - position[j][i0][1],
          position[j][i1][2] - position[j][i0][2]
        };

        // j �����̐ڐ��x�N�g��
        const auto j0(j > 0 ? j - 1 : 0);
        const auto j1(j < stacks - 1 ? j + 1 : stacks - 1);
        const GLfloat vj[] =
        {
          position[j1][i][0] - position[j0][i][0],
          position[j1][i][1] - position[j0][i][1],
          position[j1][i][2] - position[j0][i][2]
        };

        // �O��
        normal[j][i][0] = vi[1] * vj[2] - vi[2] * vj[1];
        normal[j][i][1] = vi[2] * vj[0] - vi[0] * vj[2];
        normal[j][i][2] = vi[0] * vj[1] - vi[1] * vj[0];

        //�@���K��
        const GLfloat nl(sqrt(
          normal[j][i][0] * normal[j][i][0] +
          normal[j][i][1] * normal[j][i][1] +
          normal[j][i][2] * normal[j][i][2]));
        if (nl > 0.0f)
        {
          normal[j][i][0] /= nl;
          normal[j][i][1] /= nl;
          normal[j][i][2] /= nl;
        }
      }
    }
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof normal, normal);

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
  glDeleteBuffers(1, &normalBuffer);
  glDeleteBuffers(1, &indexBuffer);
}

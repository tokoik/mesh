//
// メッシュを使った図形描画のサンプル
//

// 標準ライブラリ
#include <iostream>
#include <cmath>

// ウィンドウ関連の処理
#include "Window.h"

// メッシュの列数と行数
const auto slices(160), stacks(120);

//
// メインプログラム
//
int main()
{
  // GLFW を初期化する
  if (glfwInit() == GL_FALSE)
  {
    // GLFW の初期化に失敗した
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return EXIT_FAILURE;
  }

  // プログラム終了時には GLFW を終了する
  atexit(glfwTerminate);

  // OpenGL Version 3.2 Core Profile を選択する
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ウィンドウを開く
  Window window(640, 480, "Mesh Sample");
  if (!window.get())
  {
    // ウィンドウが作成できなかった
    std::cerr << "Can't open GLFW window." << std::endl;
    return EXIT_FAILURE;
  }


  // 頂点位置
  GLfloat position[stacks][slices][3];

  // 法線ベクトル
  GLfloat normal[stacks][slices][3];

  // 頂点配列オブジェクト
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // 頂点位置を格納する頂点バッファオブジェクト
  GLuint positionBuffer;
  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  // この頂点バッファオブジェクトのメモリを確保する
  glBufferData(GL_ARRAY_BUFFER, sizeof position, nullptr, GL_DYNAMIC_DRAW);

  // この頂点バッファオブジェクトを 0 番の attribute 変数から取り出す
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // 法線ベクトルを格納する頂点バッファオブジェクト
  GLuint normalBuffer;
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

  // この頂点バッファオブジェクトのメモリを確保する
  glBufferData(GL_ARRAY_BUFFER, sizeof normal, nullptr, GL_DYNAMIC_DRAW);

  // この頂点バッファオブジェクトを 1 番の attribute 変数から取り出す
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // インデックスバッファオブジェクト
  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

  // このインデックスバッファオブジェクトのメモリを確保する
  const auto indexes((slices - 1) * (stacks - 1) * 2 * 3);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes * sizeof (GLuint), nullptr, GL_STATIC_DRAW);

  // このインデックスバッファオブジェクトにインデックスを格納する
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

  // この頂点配列オブジェクトの結合を解除する
  glBindVertexArray(0);

  // メッシュ描画用のシェーダ
  const auto point(ggLoadShader("point.vert", "point.frag"));
  const auto mcLoc(glGetUniformLocation(point, "mc"));

  // 背景色を設定する
  glClearColor(background[0], background[1], background[2], background[3]);

  // 隠面消去処理を有効にする
  glEnable(GL_DEPTH_TEST);

  // ウィンドウが開いている間くり返し描画する
  while (!window.shouldClose())
  {
    // 画面消去
    window.clear();

    // シェーダの指定
    glUseProgram(point);
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, (window.getMp() * window.getMv()).get());

    // 頂点位置を格納する頂点バッファオブジェクトに頂点座標値を設定する
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

    // 法線ベクトルを格納する頂点バッファオブジェクトに法線ベクトルを設定する
    for (auto j = 0; j < stacks; ++j)
    {
      for (auto i = 0; i < slices; ++i)
      {
        // i 方向の接線ベクトル
        const auto i0(i > 0 ? i - 1 : 0);
        const auto i1(i < slices - 1 ? i + 1 : slices - 1);
        const GLfloat vi[] =
        {
          position[j][i1][0] - position[j][i0][0],
          position[j][i1][1] - position[j][i0][1],
          position[j][i1][2] - position[j][i0][2]
        };

        // j 方向の接線ベクトル
        const auto j0(j > 0 ? j - 1 : 0);
        const auto j1(j < stacks - 1 ? j + 1 : stacks - 1);
        const GLfloat vj[] =
        {
          position[j1][i][0] - position[j0][i][0],
          position[j1][i][1] - position[j0][i][1],
          position[j1][i][2] - position[j0][i][2]
        };

        // 外積
        normal[j][i][0] = vi[1] * vj[2] - vi[2] * vj[1];
        normal[j][i][1] = vi[2] * vj[0] - vi[0] * vj[2];
        normal[j][i][2] = vi[0] * vj[1] - vi[1] * vj[0];

        //　正規化
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

    // 描画
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexes, GL_UNSIGNED_INT, 0);

    // バッファを入れ替える
    window.swapBuffers();
  }

  // 頂点配列オブジェクトを削除する
  glDeleteVertexArrays(1, &vao);

  // 頂点バッファオブジェクトを削除する
  glDeleteBuffers(1, &positionBuffer);
  glDeleteBuffers(1, &normalBuffer);
  glDeleteBuffers(1, &indexBuffer);
}

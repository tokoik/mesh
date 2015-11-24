//
// メッシュを使った図形描画のサンプル
//

// 標準ライブラリ
#include <iostream>
#include <cmath>

// ウィンドウ関連の処理
#include "Window.h"

// メッシュの列数と行数
const auto slices(16), stacks(12);

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

  // メッシュ描画用のシェーダ
  const auto point(ggLoadShader("point.vert", "point.frag"));
  const auto mcLoc(glGetUniformLocation(point, "mc"));

  // 頂点配列オブジェクト
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // 頂点数
  const auto vertices(slices * stacks);

  // 頂点位置
  GLfloat position[stacks][slices][3];
  for (auto j = 0; j < stacks; ++j)
  {
    for (auto i = 0; i < slices; ++i)
    {
      const auto x((GLfloat(i) / GLfloat(slices - 1) - 0.5f) * GLfloat(slices) / GLfloat(stacks));
      const auto y((GLfloat(j) / GLfloat(stacks - 1) - 0.5f));

      position[j][i][0] = x;
      position[j][i][1] = y;
      position[j][i][2] = 0.0f;
    }
  }

  // 頂点位置を格納する頂点バッファオブジェクト
  GLuint positionBuffer;
  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  // この頂点バッファオブジェクトのメモリを確保する
  glBufferData(GL_ARRAY_BUFFER, sizeof position, position, GL_STATIC_DRAW);

  // この頂点バッファオブジェクトを 0 番の attribute 変数から取り出す
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // この頂点配列オブジェクトの結合を解除する
  glBindVertexArray(0);

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

    // 描画
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, vertices);

    // バッファを入れ替える
    window.swapBuffers();
  }

  // 頂点配列オブジェクトを削除する
  glDeleteVertexArrays(1, &vao);

  // 頂点バッファオブジェクトを削除する
  glDeleteBuffers(1, &positionBuffer);
}

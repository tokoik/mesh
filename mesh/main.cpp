//
// メッシュを使った図形描画のサンプル
//

// 標準ライブラリ
#include <iostream>
#include <cmath>

// ウィンドウ関連の処理
#include "Window.h"

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

  // 背景色を設定する
  glClearColor(background[0], background[1], background[2], background[3]);

  // 隠面消去処理を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // ウィンドウが開いている間くり返し描画する
  while (!window.shouldClose())
  {
    // 画面消去
    window.clear();

    // バッファを入れ替える
    window.swapBuffers();
  }
}

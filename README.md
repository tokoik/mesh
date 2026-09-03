# mesh - ポリゴンメッシュの動的生成とレンダリング

## 1. 概要

本プログラムは、頂点配列オブジェクト (VAO) および頂点バッファオブジェクト (VBO) を利用して、GPU 上で効率的にポリゴンメッシュを描画・制御するサンプルプログラムです。

- 移行元ブログ記事:
  - [ポリゴンメッシュの描画 - 床井研究室](https://tokoik.github.io/blog/2015/11/25/)

## 2. 対応環境

- **Windows**: Visual Studio 2019 / 2022 / 2026 (CMake 経由で GLFW を自動構成)
- **macOS**: Xcode (GLFW を自動ダウンロード、OpenGL Framework を使用)
- **Ubuntu Linux**: GCC / Make (システム標準の libglfw3-dev, libgl1-mesa-dev を使用)

## 3. ビルド手順

### Windows (Visual Studio)

```pwsh
cmake -B build -S .
cmake --build build --config Release
```

### macOS (Xcode)

```bash
cmake -B build -G Xcode
cmake --build build --config Release
```

### Ubuntu Linux (Makefile)

```bash
sudo apt-get update
sudo apt-get install -y libglfw3-dev libgl1-mesa-dev
cmake -B build -S .
cmake --build build
```

## 4. 起動方法

ビルド完了後、生成された実行ファイルを実行します。

- **Windows**: `build/Release/mesh.exe`
- **macOS**: `build/Release/mesh.app`
- **Linux**: `build/mesh`

## 5. 操作方法

- **マウスドラッグ**: シーンの視点回転
- **[q] / [Q] / [ESC]**: プログラムの終了

## 6. プログラムの解説

頂点座標・法線・テクスチャ座標を持つメッシュデータを構築し、シンプルなシェーダ（`simple.vert`, `simple.frag`）およびポイントシェーダ（`point.vert`, `point.frag`）によってレンダリングを行います。

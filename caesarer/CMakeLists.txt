# CMakeList.txt : caesarer の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (caesarer "caesarer.cpp" "caesarer.h" "ofwenc.h" "ofwenc.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET caesarer PROPERTY CXX_STANDARD 20)
endif()

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

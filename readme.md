# BRIDGE　
lipsync-Ver2

# 2021-5-22
AudioFrameBufferを256から4096に変更しました。
立ち上げてから現在までのframe数を表示しました。
音に反応する赤いサークルを除去しました。
画面のレイアウトを微調整しました。

# 2021-02-11
chartを新しくしました。

# 2021-2-8
video frameをallocateしました。
framesyncをonにしました。

# 2021-1-21
フォルダの中の
lip sync GM.exe
アプリを開いていただいたらコマンドプロンプトとアプリが立ち上がります。

音声をエンベデッドした映像をキャプチャし、
入力してください（フォルダに入ってるlipcheck.mp4を再生し、そのプレイヤーのアウトをキャプチャするとわかりやすいです）。

コマンドプロンプトを上にさかのぼっていただいたら、
現在使用可能なビデオ入力のIDが一覧で出ますので、
キーボードで入力しているIDの番号を押してください。
IDを間違えたときはアプリを再起動してください。

音声の入力はWindowsで選んでる入力が選択されます。

画面左上は入力した映像の輝度に反応した波形が表示されます(緑の波形)。
画面左下は入力した音声のvolに反応した波形が表示されます(赤の波形)。

画面中央には音声の波形と映像の波形両方が4倍、画面下には16倍で表示されています。
音声の波形と映像の波形の立ち上がり部分を合わせていただくと、
Lipsyncが合ってる状態です。
lipcheck.mp4のフラッシュとクリック音が合ってると波形の立ち上がりが合います。


Lipsyncが合ってない場合、
キャプチャの手前でFS（FA-1010とか？）を入れていただき、
そこで波形の立ち上がりが合うように合わせてください。

アプリの終了はescです。

#audioInputExample
--
![Screenshot of Example](audioInputExample.gif)

### Learning Objectives

This openFrameworks example is designed to demonstrate how to access, extract, and draw from your audio input's raw data.

Studying the code behind this example will help you understand:

* How to list all available audio devices with `soundStream.printDeviceList()` and set a specific audio input device for OF app with `settings.setInDevice(devices[0])`
* How audio functions work independent from draw and update loop by observe `bufferCounter` and `drawCounter`
* How to roughly calculate volume by using RMS (root mean square) value in `void audioIn`
* How to record data overtime with vector with `vector <float> volHistory`


### Expected Behavior

When launching this app, you should see

* Fast moving curve lines on the left, and big circle on the right that reacts to live audio input
* Graph of recorded volume data overtime under the big circle
* Text that shows difference in draw vs buffer counter

Instructions for use:

* make some noise or touch your microphone to see how sound manipulate the drawing.
* press `e` to stop live audio input, `s` to continue




### Classes used in this example

This example uses the following classes:

* ``ofSoundStream``
* ``ofSoundStreamSettings``

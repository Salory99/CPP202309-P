# 이 파일에 게임 스크립트를 입력합니다.

# image 문을 사용해 이미지를 정의합니다.
# image eileen happy = "eileen_happy.png"

# 게임에서 사용할 캐릭터를 정의합니다.
define test = Character('테스트', color="#c8ffc8")

init:
    define audio.clothes_drop_01 = "./renpy_example/game/audio/SE/freesound\clothes_drop_01.mp3"
    define audio.piano_hit01 = "./renpy_example/game/audio/SE/freesound\piano_hit01.wav"
    define audio.wind01 = "./renpy_example/game/audio/SE/freesound\wind01.wav"

init:
    define audio.Clair_de_Lune = "./renpy_example/game/audio/BGM/Clair_de_Lune.mp3"
    define audio.tampi01 = "./renpy_example/game/audio/BGM/TAMBGM\tampi01.mp3"


init:
    image black:
        "./renpy_example/game/images/BG/black.jpg"
        yalign 0.0
    image invisible:
        "./renpy_example/game/images/BG/invisible.png"
        yalign 0.0

init:
    image black bb:
        "./renpy_example/game/images/SCG/black_bb.jpg"
        yalign 0.0
    image invisible bb:
        "./renpy_example/game/images/SCG/invisible_bb.png"
        yalign 0.0



# 여기에서부터 게임이 시작합니다.
label start:

    test "테스트중"

    play music Clair_de_Lune fadein 0.5

    stop Clair_de_Lune fadeout 0.5

    play sound wind01

    show black bb with dissolve

    hide black

    scene invisible

    hide invisible



    return

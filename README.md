# Omok

C++ 을 활용해서 만든 오목게임 입니다.

PlayerManager.cpp PlayerManager.h 

메인메뉴 , 게임세팅 , 세이브 및 로드 , 리플레이 등에 필요한 Player에 구현한 함수들을 사용하여 전반적인 게임의 흐름을 관리

Player.cpp Player.h

실제로 커서,돌모양,돌의좌표와 순서 등 데이터들을 저장하고 게임에 필요한 승리체크와 메모리관리 등 플레이어가 가지고 있어야 할 정보와 기능 구현

MapDraw.cpp MapDraw.h

바둑판과 커서 그리고 놓여진 바둑돌을 그리는 함수를 구현하여 Player에서 필요할때마다 함수를 호출하여 사용할 수 있게 구현

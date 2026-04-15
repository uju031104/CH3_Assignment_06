# CH3_Assignment_01

프로젝트에 대한 간단한 설명   

### ACube class
   
Cube 클래스는 C++만 활용하여 `SceneComponent`와 `StaticMeshComponent`(StaticMesh, Material)를 설정하였다.   

**ACube의 기능**  
Tick() 함수의 `DeltaTime`을 이용하여 회전하는 기능을 구현하였다.   

***

### AMyActor class

MyActor 클래스는 Root와 StaticMesh를 `리플렉션 시스템`을 이용하여 블루프린트에서 설정하게 구현하였다.   

**AMyActor의 기능**   
이 클래스는 따로 구현한 `ActorComponent`를 사용하는 Actor이기 때문에 ActorComponent를 연결만 해줬다.  

***

### UActionComponent class

ActionComponent 클래스는 MyActor 클래스의 `ActorComponent`이다.   

**UActionComponent의 기능**   
Idle, UpDown, LeftRight, Scale, Rotate, Disappear, Teleport까지 총 7가지의 기능이 있다.   
AMyActor 클래스를 상속받는 블루프린트를 만들고 그 객체가 가지고 있는 ActionComponent를 7가지 행동중 내가 원하는 행동으로 설정할 수 있다.   
ActionInfo 구조체의 Duration(시간)을 0으로 하면 무한으로 동작하고, 0 이상의 설정값을 주면 해당 시간 동안만 동작한다.   
Idle부터 Scale까지는 `GetWorld()->GetTimeSeconds()`를 활용하여 DeltaTime의 누적값이 아닌 실제 시간에 따라 `Set` 해주는 방식으로 구현하였다.   
Disappear은 그냥 사라지는게 아닌 설정한 시간에 비례하여 크기가 0으로 줄어들면서 사라지게 구현하였다.(선형보간으로 Clamp와 Lerp사용)      
Teleport만 예외적으로 TeleportTime이라는 설정값에만 동작한다.   

***

### AMyGameModeBase class

MyGameModeBase클래스는 게임에 관한 설정을 하는 클래스다.


**AMyGameModeBase의 기능**   
게임 실행 시 설정한 횟수만큼 MyActor들을 랜덤한 위치에 스폰을 한다.   

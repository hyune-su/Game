# 기본 정보

이름: 송현수

학번: 20161642

# 구성

기본 구성은 FileManager, 인터페이스 클래스 ICleanUp, IRender, IUpdater / NonRenderObject, RenderableObject / Sphere, makeObject / Object / Renderer로 구성하였습니다.

파일매니저는 파일의 정보만을 읽어오며, 인터페이스 클래스의 ICleanUp은 shutDown의 공통 함수, IRender는 addObject()와 render()를 통해서 render()만을 호출하면 추가된 오브젝트를 출력할 수 있도록 하였습니다.
또한 IUpdater의 경우 현재는 아무 기능이 없으나 후에 기능의 확장이 있을 수 있기에 만들었으며 현재는 변수 초기화만을 넣어주었습니다.

NonRenderObject의 기능은 렌더링 하지 않을 (화면에 보이지 않을) 오브젝트를 만들기 위함이며 RenderableObject는 렌더링을 하기 위한 오브젝트를 만들기 위한 클래스입니다.

Sphere, makeObject가 RenderableObject를 상속받으며 RenderableObject는 Object를 상속 받습니다.

Renderer는 렌더링, 즉 읽어온 데이터를 출력하기 위한 클래스로 출력에 관한 주요 기능들을 합니다.
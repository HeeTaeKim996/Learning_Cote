package Behaviour;

public class State
{
    /*-------------------------------------------------------
    ■ State 패턴
    상태 변경 때마다, 상태에 따른 특정 코드가 실행되길 원할 때,
    코드 작성의 유지/보수 를 수월하게 하는 것을 목적으로 사용됨

    EX 3 을 보면 알다시피, State패턴을 안쓴다면 if else 가 꼬이게
    되기에, 상태가 많아질수록 코드 관리가 어려움.
    State 패턴을 쓰면 변경시 기존 상태에 따른
    코드를 개별로 만들 수 있기에 유지/보수가 수월함

    강의의 EX1, EX2 는 힙메모리에 할당/제거 가 빈번하기에 성능이 안좋지만,
    제미나이 추천으로 추가된 EX4 버전(상태 클래스들을 전역 변수로 미리 생성)
    을 쓰면, 성능도 잡으면서,
    EX 3 에서의 분기 처리 부분도 제거되기에, 조건 판별의 성능도 잡기에,
    EX4 버전은 EX3 버전보다 성능 면에서도
    우수하지 않을까 싶다.

    따라서 State패턴을 쓴다면, EX4 를 참고해서 쓰자
     ------------------------------------------------------*/


    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Door door = new Door();

        door.open();
        door.open();

        door.close();
        door.close();


        /*-----------------------
         *         EX 2
         * --------------------- */
        VideoPlayer player = new VideoPlayer();

        player.play();
        player.play();

        player.stop();
        player.play();

        player.stop();
        player.stop();

        player.stop();


        /*-----------------------
         *         EX 3
         *   (State 패턴이 없다면)
         * --------------------- */
        System.out.printf("\n\n\n");
        WrongPlayer player2 = new WrongPlayer();
        player2.play();
        player2.play();
        player2.stop();
        player2.play();
        player2.stop();
        player2.stop();
        player2.stop();

        /*---------------------------------------------------
         *                      EX 4
         *   (제미나이 추천 힙메모리 할당/제거 비용 완화 버전)
         * ----------------------------------------------- */
        System.out.printf("\n\n\n");
        StateAddr stateAddr = new StateAddr();
        stateAddr.up();
        stateAddr.up();
        stateAddr.down();
        stateAddr.up();
        stateAddr.down();
        stateAddr.down();
        stateAddr.down();
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    public static interface State1
    {
        void open(Door door);
        void close(Door door);
    }

    public static class ClosedState implements State1
    {
        @Override
        public void open(Door door)
        {
            System.out.println("문이 열렸습니다");
            door.setState(new OpenState());
        }

        @Override
        public void close(Door door)
        {
            System.out.println("문은 이미 닫혀있습니다");
        }
    }

    public static class OpenState implements State1
    {

        @Override
        public void open(Door door)
        {
            System.out.println("문은 이미 열려있습니다");
        }

        @Override
        public void close(Door door)
        {
            System.out.println("문을 닫습니다");
            door.setState(new ClosedState());
        }
    }


    public static class Door
    {
        private State1 state;
        public Door()
        {
            state = new ClosedState();
        }
        public void setState(State1 InState)
        {
            state = InState;
        }

        public void open()
        {
            state.open(this);
        }
        public void close()
        {
            state.close(this);
        }
    }







    /*-----------------------
     *         EX 2
     * --------------------- */
    public static interface State2
    {
        void play(VideoPlayer player);
        void stop(VideoPlayer player);
    }

    public static class StoppedState implements State2
    {
        @Override
        public void play(VideoPlayer player)
        {
            System.out.println("비디오 재생을 시작합니다");
            player.setState(new PlayingState());
        }

        @Override
        public void stop(VideoPlayer player)
        {
            System.out.println("비디오는 이미 멈춰있습니다");
        }
    }

    public static class PlayingState implements State2
    {

        @Override
        public void play(VideoPlayer player)
        {
            System.out.println("비디오는 이미 재생중입니다");
        }

        @Override
        public void stop(VideoPlayer player)
        {
            System.out.println("비디오를 일시 정지합니다");
            player.setState(new PausedState());
        }
    }

    public static class PausedState implements State2
    {

        @Override
        public void play(VideoPlayer player)
        {
            System.out.println("비디오를 재개합니다");
            player.setState(new PlayingState());
        }

        @Override
        public void stop(VideoPlayer player)
        {
            System.out.println("비디오를 멈춥니다");
            player.setState(new StoppedState());
        }
    }

    public static class VideoPlayer
    {
        private State2 state;

        public VideoPlayer()
        {
            state = new StoppedState();
        }
        public void setState(State2 InState)
        {
            state = InState;
        }

        public void play()
        {
            state.play(this);
        }

        public void stop()
        {
            state.stop(this);
        }
    }


    /*-----------------------
     *         EX 3
     *   (State 패턴이 없다면)
     * --------------------- */
    public static enum State3
    {
        stopped,
        playing,
        paused
    }
    public static class WrongPlayer
    {
        private State3 state;
        public WrongPlayer()
        {
            state = State3.stopped;
        }

        public void play()
        {
            if(state == State3.playing)
            {
                System.out.println("이미 재생중입니다");
            }
            else if(state == State3.paused)
            {
                System.out.println("영상을 재개합니다");
                state = State3.playing;
            }
            else if(state == State3.stopped)
            {
                System.out.println("영상을 시작합니다");
                state = State3.playing;
            }
        }

        public void stop()
        {
            if(state == State3.playing)
            {
                System.out.println("영상을 일시 중지합니다");
                state = State3.paused;
            }
            else if(state == State3.paused)
            {
                System.out.println("영상을 종료합니다");
                state = State3.stopped;
            }
            else if(state == State3.stopped)
            {
                System.out.println("영상은 이미 종료됐습니다");
            }
        }
    }

    /*---------------------------------------------------
     *                      EX 4
     *   (제미나이 추천 힙메모리 할당/제거 비용 완화 버전)
     * ----------------------------------------------- */
    public static interface State4
    {
        void up(StateAddr stateAddr);
        void down(StateAddr stateAddr);
    }

    public static class S1 implements State4
    {
        @Override
        public void up(StateAddr stateAddr)
        {
            System.out.println("업 2");
            stateAddr.setState(StateAddr.s2);
        }

        @Override
        public void down(StateAddr stateAddr)
        {
            System.out.println("다운 불가");
        }
    }
    public static class S2 implements State4
    {

        @Override
        public void up(StateAddr stateAddr)
        {
            System.out.println("업 3");
            stateAddr.setState(StateAddr.s3);
        }

        @Override
        public void down(StateAddr stateAddr)
        {
            System.out.println("다운 1");
            stateAddr.setState(StateAddr.s1);
        }
    }
    public static class S3 implements State4
    {

        @Override
        public void up(StateAddr stateAddr)
        {
            System.out.println("업 불가");
        }

        @Override
        public void down(StateAddr stateAddr)
        {
            System.out.println("다운 2");
            stateAddr.setState(StateAddr.s2);
        }
    }
    public static class StateAddr
    {
        public static final State4 s1 = new S1();
        public static final State4 s2 = new S2();
        public static final State4 s3 = new S3();

        private State4 state;
        public StateAddr()
        {
            state = s1;
        }

        public void setState(State4 InState)
        {
            state = InState;
        }
        public void up()
        {
            state.up(this);
        }
        public void down()
        {
            state.down(this);
        }
    }
}

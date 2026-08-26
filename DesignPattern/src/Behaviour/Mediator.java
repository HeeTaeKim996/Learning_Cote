package Behaviour;

import java.util.ArrayList;
import java.util.List;

public class Mediator
{
    /*---------------------------------------------
    ■ Mediator 패턴
    같은 타입의 개체들끼리 유기적으로 상호작용하는 구조에서,
    개체들끼리 직접 상호작용하지 않고,
    중재자를 두어 오직 중재자를 통해서 개체들끼리 상호작용하는 패턴

    서버 자체가 중재자 패턴 그 자체다.
    클라이언트끼리 채팅을 할 때 클라1 이 메세지를 서버에 보내면,
    서버는 나머지 클라들에게 메세지를 뿌린다.
    클라a가 서버의 특정 자원을 요구하면,
    서버는 특정 자원을 락을 걸고, 클라a에게만 접근을 허용한다

    EX1, EX2 예시를 보면 알다시피 패턴이라고는 하지만, 패턴 자체가 없다.
    패턴이라 할만한 유일한 공통점은,
    '상호작용하는 여러 개체가 오직 중재자를 통해서만 상호작용한다'
    라는 텍스트 그 자체 뿐이다.
     ---------------------------------------------*/

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        ChatMediator mediator = new ChatMediatorImpl();

        User user1 = new USerImpl(mediator, "Harry");
        User user2 = new USerImpl(mediator, "Bori");
        User user3 = new USerImpl(mediator, "Heetae");

        mediator.addUser(user1);
        mediator.addUser(user2);
        mediator.addUser(user3);

        user1.send("hi All");




        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        AirportControlTower controlTower = new AirportControlTower();

        Flight flight1 = new Flight(controlTower, "K1");
        Flight flight2 = new Flight(controlTower, "K2");
        Runway runway = new Runway(controlTower);

        flight1.land();
        flight2.land();

        runway.clear();
        flight2.land();
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    public static interface ChatMediator
    {
        void sendMessage(String message, User user);
        void addUser(User user);
    }

    public static class ChatMediatorImpl implements ChatMediator
    {
        private List<User> users;

        public ChatMediatorImpl()
        {
            users = new ArrayList<>();
        }


        @Override
        public void sendMessage(String message, User user)
        {
            for(User u : users)
            {
                if(u != user)
                {
                    u.receive(message);
                }
            }
        }

        @Override
        public void addUser(User user)
        {
            users.add(user);
        }
    }

    public static abstract class User
    {
        protected ChatMediator mediator;
        protected String name;

        public User(ChatMediator InMediator, String InName)
        {
            mediator = InMediator;
            name = InName;
        }

        public abstract void send(String message);
        public abstract void receive(String message);
    }

    public static class USerImpl extends User
    {
        public USerImpl(ChatMediator mediator, String name)
        {
            super(mediator, name);
        }

        @Override
        public void send(String message)
        {
            System.out.printf("%s : Sending Message = %s\n", name, message);
            mediator.sendMessage(message, this);
        }

        @Override
        public void receive(String message)
        {
            System.out.printf("%s : Receive Message = %s\n", name, message);
        }
    }








    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface AirportMediator
    {
        boolean isRunwayAvailable();
        void setRunwayAvailability(boolean status);
    }

    static class AirportControlTower implements AirportMediator
    {
        private boolean isRunwayAvailable = true;

        @Override
        public boolean isRunwayAvailable() {
            return isRunwayAvailable;
        }

        @Override
        public void setRunwayAvailability(boolean status)
        {
            isRunwayAvailable = status;
        }
    }

    static class Flight
    {
        private AirportMediator mediator;
        private String flightNumber;

        public Flight(AirportMediator InMediator, String InFlightNumber)
        {
            mediator = InMediator;
            flightNumber = InFlightNumber;
        }

        public void land()
        {
            if(mediator.isRunwayAvailable())
            {
                System.out.printf("Flight%s is landing\n", flightNumber);
                mediator.setRunwayAvailability(false);
            }
            else
            {
                System.out.printf("Flight%s is waiting to land\n", flightNumber);
            }
        }
    }

    static class Runway
    {
        private AirportMediator mediator;

        public Runway(AirportMediator InMediator)
        {
            mediator = InMediator;
        }

        public void clear()
        {
            System.out.println("Runway is clear");
            mediator.setRunwayAvailability(true);
        }
    }


}

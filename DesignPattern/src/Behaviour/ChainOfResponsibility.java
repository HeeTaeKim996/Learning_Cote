package Behaviour;


public class ChainOfResponsibility
{
    /*---------------------------------------------------
    ■ Chain Of Responsibility 패턴
    요청 처리의 발신자와, 수신자를 분리하여,
    요청처리의 유연성과 확장성을 높이는 패턴

    패턴이 구체적이다.
    1)
    abstract class 인 Handler 를 만들고,
    Handler 는 이벤트 데이터 를 인자로 하는 이벤트 핸들 함수와,
    Linked List 를 위해 필드로 Handler 클래스를 갖는다.
    2)
    Concrete 핸들러들을 LinkedList 로 연결하고,
    이벤트 발생시 루트 핸들러에 이벤트를 넘겨주고,
    각각 구현된 이벤트 핸들 함수에서 이벤트 데이터를 기준으로 처리할지 말지를
    결정 및 처리한다.
    이후 자신의 처리 결과에 따라, LinkedList 로 연결된 다음 핸들러에
    이벤트를 넘겨줄지 판단 후 필요시 넘겨준다.

    안드로이드 자바의
    dispatchTouchEvent(), onInterceptTouchEvent(), onTouchEvent()
    가 Chain Of Responsibility 패턴을 활용한 전형적인 예시다.
    간단하게 추가로 구현한 코드다 E3 다

     --------------------------------------------------*/

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Handler positive = new PositiveHandler();
        Handler even = new EvenHandler();
        Handler div3 = new DivisionBy3Number();

        positive.setNext(even);
        even.setNext(div3);

        positive.handle(-2);
        positive.handle(4);
        positive.handle(6);


        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        Logger networkLogger = new NetworkLogger(LogLevel.WARN);
        Logger fileLogger = new FileLogger(LogLevel.DEBUG);
        Logger consoleLogger = new ConsoleLogger(LogLevel.INFO);

        networkLogger.setNextLogger(fileLogger);
        fileLogger.setNextLogger(consoleLogger);

        networkLogger.logMessage(LogLevel.INFO, "This is INFO");
        networkLogger.logMessage(LogLevel.DEBUG, "This is DEBUG");
        networkLogger.logMessage(LogLevel.WARN, "This is WARN");


        /*-----------------------
         *         EX 3
         * --------------------- */
        System.out.printf("\n\n\n");
        A a = new A();
        B b = new B();
        C c = new C();

        a.setChild(b);
        b.setChild(c);

        MotionEvent e1 = new MotionEvent('a', 3, 4);
        MotionEvent e2 = new MotionEvent('b', 3, 6);
        MotionEvent e3 = new MotionEvent('c', 7, 7);

        a.dispatchTouchEvent(e1);
        a.dispatchTouchEvent(e2);
        a.dispatchTouchEvent(e3);
    }
    /*-----------------------
     *         EX 1
     * --------------------- */

    static abstract class Handler
    {
        protected Handler next;

        public void setNext(Handler inNext)
        {
            next = inNext;
        }

        public void handle(int number)
        {
            process(number);
            if(next != null)
            {
                next.handle(number);
            }
        }

        protected abstract void process(int number);
    }

    static class PositiveHandler extends Handler
    {

        @Override
        protected void process(int number)
        {
            if(number > 0)
            {
                System.out.printf("%d is positive number\n", number);
            }
        }
    }

    static class EvenHandler extends Handler
    {
        @Override
        protected void process(int number)
        {
            if(number % 2 == 0)
            {
                System.out.printf("%d is even number\n", number);
            }
        }
    }

    static class DivisionBy3Number extends Handler
    {
        @Override
        protected void process(int number)
        {
            if(number % 3 == 0)
            {
                System.out.printf("%d is divided by 3\n", number);
            }
        }
    }










    /*-----------------------
     *         EX 2
     * --------------------- */
    static enum LogLevel
    {
        INFO, DEBUG, WARN
    }

    static abstract class Logger
    {
        protected LogLevel level;
        protected Logger nextLogger;

        public Logger(LogLevel inLevel)
        {
            level = inLevel;
        }

        public void setNextLogger(Logger inNextLogger)
        {
            nextLogger = inNextLogger;
        }

        public void logMessage(LogLevel inLevel, String message)
        {
            if(level.ordinal() <= inLevel.ordinal())
            {
                write(message);
            }
            if(nextLogger != null)
            {
                nextLogger.logMessage(inLevel, message);
            }
        }

        public abstract void write(String message);
    }

    static class ConsoleLogger extends Logger
    {
        public ConsoleLogger(LogLevel inLevel)
        {
            super(inLevel);
        }

        @Override
        public void write(String message)
        {
            System.out.printf("Console::Loger: %s\n", message);
        }
    }

    static class FileLogger extends Logger
    {

        public FileLogger(LogLevel inLevel)
        {
            super(inLevel);
        }

        @Override
        public void write(String message)
        {
            System.out.printf("File::Loger: %s\n", message);
        }
    }

    static class NetworkLogger extends Logger
    {

        public NetworkLogger(LogLevel inLevel)
        {
            super(inLevel);
        }

        @Override
        public void write(String message)
        {
            System.out.printf("Network::Loger: %s\n", message);
        }
    }







    /*-----------------------
     *         EX 3
     * --------------------- */
    static class MotionEvent
    {
        public MotionEvent(char inType, float inX, float inY)
        {
            type = inType;
            x = inX;
            y = inY;
        }

        char type;
        float x;
        float y;

        public String toString()
        {
            return String.format("MotionEvent[type(%c), x(%f), y(%f)", type, x, y);
        }
    }

    static abstract class View
    {
        protected View child;
        public void setChild(View inChild) { child = inChild;}

        protected abstract boolean onInterceptTouchEvent(MotionEvent event);
        protected abstract boolean onTouchEvent(MotionEvent event);

        public boolean dispatchTouchEvent(MotionEvent event)
        {
            boolean handled = false;

            if(onInterceptTouchEvent(event) == false)
            {
                if(child != null)
                {
                    handled = child.dispatchTouchEvent(event);
                }
            }

            if(handled == false)
            {
                handled = onTouchEvent(event);
            }

            return handled;
        }
    }

    static class A extends View {

        @Override
        protected boolean onInterceptTouchEvent(MotionEvent event)
        {
            if(event.type == 'a')
            {
                System.out.printf("A Intercpet : %s\n", event.toString());
                return true;
            }
            return false;
        }

        @Override
        protected boolean onTouchEvent(MotionEvent event)
        {
            return false;
        }
    }

    static class B extends View
    {
        @Override
        protected boolean onInterceptTouchEvent(MotionEvent event)
        {
            return false;
        }

        @Override
        protected boolean onTouchEvent(MotionEvent event)
        {
            if(event.type == 'b')
            {
                System.out.printf("B Touch : %s\n", event.toString());
                return true;
            }
            return false;
        }
    }

    static class C extends View
    {
        @Override
        protected boolean onInterceptTouchEvent(MotionEvent event)
        {
            return false;
        }

        @Override
        protected boolean onTouchEvent(MotionEvent event)
        {
            if(event.type == 'c')
            {
                System.out.printf("C Touch : %s\n", event.toString());
                return true;
            }

            return false;
        }
    }


}

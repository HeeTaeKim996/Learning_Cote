package Structual;

public class Bridge
{
    /*-------------------------------------------------------
    ■ Bridge 패턴
    구현부(interface) 와 추상부(abstract class) 의 조합 구조를 사용해,
    다양한 경우의 수를 만들어낼 수 있는 패턴

    피자에서 토핑(구현부)의 종류가 n개, 크러스트(추상부)의 종류가 m개라 할 때,
    n * m 의 조합의 경우의 수를 만들어낼 수 있다

    구현부 는 interface 를 상속하여 구현되며,
    추상부는 abstract class 를 상속하여 구현된다.
    추상부는 구현부 interface 를 필드로 두어
    (추상부를 interface가 아닌 abstract class 로 구현한 이유),
    추상부의 함수를 호출시,
    구현부의 함수도 함께 호출되도록 하는 것이
    기본 구조다.
    (패턴이 구체적이기에, 위 구조는 외워둘 필요가 있다)
     -------------------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Device tv = new TV();
        Remote basicRemote = new BasicRemote(tv);
        basicRemote.power();
        basicRemote.volumeUp();

        System.out.println();

        Device radio = new Radio();
        AdvancedRemote advancedRemote = new AdvancedRemote(radio);
        advancedRemote.power();
        advancedRemote.mute();



        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.println("\n\n\n");
        MessageSender emailSender = new EmailSender();
        MessageSender smsSender = new SMSSender();

        Message textMessage = new TextMessage(emailSender);
        textMessage.send("Hello Harry");

        Message encryptedMessage = new EncryptedMessage(smsSender);
        encryptedMessage.send("Hi Bori");
    }



    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Device
    {
        void turnOn();
        void turnOff();
        void setVolume(int InVolume);
        boolean isEnabled();
    }

    // Concrete Implementors
    static class TV implements Device
    {
        private boolean bOn = false;
        private int volume = 30;

        @Override
        public void turnOn()
        {
            bOn = true;
            System.out.println("티비 온");
        }

        @Override
        public void turnOff()
        {
            bOn = false;
            System.out.println("티비 오프");
        }

        @Override
        public void setVolume(int InVolume)
        {
            volume = InVolume;
            System.out.printf("티비 볼륨 : %d\n", volume);
        }

        @Override
        public boolean isEnabled() {
            return bOn;
        }
    }

    // Concrete Implementors
    static class Radio implements Device
    {
        private boolean bOn = false;
        private int volume;

        @Override
        public void turnOn()
        {
            bOn = true;
            System.out.println("라디오 온");
        }

        @Override
        public void turnOff()
        {
            bOn = false;
            System.out.println("라디오 오프");

        }

        @Override
        public void setVolume(int InVolume)
        {
            volume = InVolume;
            System.out.printf("라디오 볼륨 설정 : %d\n", volume);
        }

        @Override
        public boolean isEnabled() {
            return bOn;
        }
    }

    // Abstraction
    static abstract class Remote
    {
        protected Device device;

        protected Remote(Device InDevice)
        {
            device = InDevice;
        }

        public abstract void power();

        public void volumeUp()
        {
            device.setVolume(device.isEnabled() ? 1 : 0);
        }
        public void volumeDown()
        {
            device.setVolume(device.isEnabled() ? -1 : 0);
        }
    }

    // Refined Abstraction
    static class BasicRemote extends Remote
    {

        protected BasicRemote(Device InDevice) {
            super(InDevice);
        }

        @Override
        public void power()
        {
            if(device.isEnabled())
            {
                device.turnOff();
            }
            else
            {
                device.turnOff();
            }
        }
    }

    static class AdvancedRemote extends Remote
    {

        protected AdvancedRemote(Device InDevice) {
            super(InDevice);
        }

        @Override
        public void power()
        {
            if(device.isEnabled())
            {
                device.turnOff();
            }
            else
            {
                device.turnOn();
            }
        }

        public void mute()
        {
            device.setVolume(0);
            System.out.println("음소거 처리됨");
        }
    }







    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface MessageSender
    {
        void sendMessage(String message);
    }

    static class EmailSender implements MessageSender
    {
        @Override
        public void sendMessage(String message)
        {
            System.out.printf("이메일을 보냅니다 [%s]\n", message);
        }
    }

    static class SMSSender implements MessageSender
    {
        @Override
        public void sendMessage(String message)
        {
            System.out.printf("SMS 를 보냅니다[%s]\n", message);
        }
    }

    static abstract class Message
    {
        protected MessageSender messageSender;

        protected Message(MessageSender InMessageSender)
        {
            messageSender = InMessageSender;
        }

        public abstract void send(String message);
    }


    static class TextMessage extends Message
    {

        protected TextMessage(MessageSender InMessageSender)
        {
            super(InMessageSender);
        }

        @Override
        public void send(String message)
        {
            messageSender.sendMessage("TextMessage: " + message);
        }
    }

    static class EncryptedMessage extends Message
    {
        protected EncryptedMessage(MessageSender InMessageSender)
        {
            super(InMessageSender);
        }

        @Override
        public void send(String message)
        {
            String encryptedMessage = encrypt(message);
            messageSender.sendMessage("EncryptedMessage : " + encryptedMessage);
        }

        private String encrypt(String message)
        {
            return new StringBuilder(message).reverse().toString();
        }
    }

}

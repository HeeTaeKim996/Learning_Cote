package Structual;

import java.util.ArrayList;
import java.util.List;


public class Adapter
{
    /*-----------------------------------------------
    ■ Adapter 패턴
    규격이 다른 외부 요인들을 호환하기 위한, 래퍼 클래스

    컨센트 '어댑터' 처럼, 해외여행을 갔을 때 자국의 전자기기는
    해외 콘센트와 호환이 안되는 경우가 많기에, 어댑터를 사용한다.

    어댑터는 고정된 디자인 패턴이라기보다는, 말그대로
    규격이 다른 외부 요인들을 호환하기 위한, 래퍼 클래스 이다

    (굳이 예문을 볼 필요도 없다)
     ----------------------------------------------*/

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        System.out.printf("\n");
        OldMessageSender oldSystem = new OldMessageSystem();
        ModernMessageSender adapter = new MessageAdapter(oldSystem);

        adapter.sendMessage("Hello world", "ttiiger1@naver.com");

        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        USB usb = new USB();
        HDMI hdmi = new HDMI();
        VGA vga = new VGA();

        List<DisplayAdapter> adapters = new ArrayList<>();
        adapters.add(new USBAdapter(usb, "video data"));
        adapters.add(new HDMIAdapter(hdmi, 1080));
        adapters.add(new VGAAdapter(vga, true));

        for(DisplayAdapter adapter1 : adapters)
        {
            adapter1.display();
        }

    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    // 여기서 interface 는 디자인 패턴이 아닌, 규격이 다른 외부 요인
    static interface ModernMessageSender
    {
        void sendMessage(String message, String recipient);
    }

    public static interface OldMessageSender
    {
        int send(String[] messageData);
    }

    static class OldMessageSystem implements OldMessageSender
    {

        @Override
        public int send(String[] messageData)
        {
            System.out.printf("OleMessageSystem : sendingMessage: [%s] to [%s]",
                    messageData[0], messageData[1]);
            return 1;
        }
    }

    static class MessageAdapter implements ModernMessageSender
    {
        private OldMessageSender oldSystem;

        public MessageAdapter(OldMessageSender InOldSystem)
        {
            oldSystem = InOldSystem;
        }

        @Override
        public void sendMessage(String message, String recipient)
        {
            String[] messageData = {message, recipient};
            int result = oldSystem.send(messageData);
            if(result != 1)
            {
                System.out.println("메세지 전송 실패");
            }
        }
    }


    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface DisplayAdapter
    {
        void display();
    }

    static class USB
    {
        void connectWithUsbCable(String data)
        {
            System.out.printf("USB 를 통한 Display[%s]\n", data);
        }
    }

    static class HDMI
    {
        void connectWithHDMICable(int resolution)
        {
            System.out.printf("HDMI 를 통한 Display[%d]p\n", resolution);
        }
    }

    static class VGA
    {
        void connectWithVgaCable(boolean highQuality)
        {
            System.out.printf("VGA 를 통한 Display[%b]\n", highQuality);
        }
    }

    static class USBAdapter implements DisplayAdapter
    {
        private USB usb;
        private String data;

        public USBAdapter(USB InUsb, String InData)
        {
            usb = InUsb;
            data = InData;
        }

        @Override
        public void display()
        {
            usb.connectWithUsbCable(data);
        }
    }

    static class HDMIAdapter implements DisplayAdapter
    {
        private HDMI hdmi;
        private int resolution;

        public HDMIAdapter(HDMI InHdmi, int InResolution)
        {
            hdmi = InHdmi;
            resolution = InResolution;
        }

        @Override
        public void display()
        {
            hdmi.connectWithHDMICable(resolution);
        }
    }

    static class VGAAdapter implements DisplayAdapter
    {
        private VGA vga;
        private boolean highQuality;

        public VGAAdapter(VGA InVga, boolean InHighQuality)
        {
            vga = InVga;
            highQuality = InHighQuality;
        }

        @Override
        public void display()
        {
            vga.connectWithVgaCable(highQuality);
        }
    }
}

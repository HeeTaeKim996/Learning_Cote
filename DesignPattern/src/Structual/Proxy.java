package Structual;

public class Proxy
{
    /*--------------------------------------------------
    ■ Proxy 패턴
    무거운(정보가 많은) 실체 클래스를 사용하지 않고,
    가벼운(실체 클래스의 정보 중 필요한 정보만 갖고 있는) Proxy 클래스를
    통해 작업을 우선 처리하고,
    조건부로 필요시 Proxy를 통해 실체 클래스를 불러오는 패턴

    사장(실제 클래스) 과 비서(사장의 업무 중 일부를 대신 처리하는 Proxy)
    를 예로 들 수 있다.
    비서는 사장의 업무를 대리하지만,
    권한 밖의 업무일 경우, 사장을 호출하여 사장이 직접 일을 처리한다.

    패턴의 정형화된 구조는 2개다.
    1) 실체 클래스와 Proxy 클래스가 공유하는 클래스(interface || abstract class) 를
       상속하여, 정보를 공유하며, Proxy 가 해당 정보를 위임하여 처리한다
    2) Proxy 클래스의 권한 밖의 일일 경우, Proxy 는 실체 클래스에 대한
       접근 정보(포인터(클래스) || 접근 경로 정보 || 직접 생성) 를 통해
       실체 클래스를 호출하여, 실체 클래스가 직접 처리한다


   ※ 아래 프록시의 예시들은 이전에 게임엔진에서 Physics 의 객체 Physics Proxy 를 통한
      PhysicsProxy[] 배열로 순회조회할 때의 그 장점을 보여주지 못하는 것 같다.
      프록시 패턴은 프록시들을 배열로 놓고 순회조회할 때 장점이 극대화된다.
      이를 사용하려면 프록시가 힙메모리에 malloc, free 되는 클래스가 아니라,
      지정한 메모리에 직접 할당되는 구조체(C++ 의 A a(...); 할당 / C#의 struct) 여야 한다.
      자바는 모든 구조체가 class 이기 때문에, 자바에서는 이 Proxy[] 의 순회조회의 장점을
      가져오기 어렵다.
      정리하면 프록시를 통한 순회조희는 C++, C# 등에서만 가능한 듯 싶다
     --------------------------------------------------*/

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        ProxyImage image = new ProxyImage("testing_image.jpg");

        System.out.printf("FileName : %s\n", image.getFileName());
        System.out.printf("File extension : %s\n", image.getFileExtension());

        image.display();



        /*-----------------------
         *         EX 2
         * --------------------- */
        BankAccount adminAccount = new BankAccountProxy("Admin", 1000);
        adminAccount.deposit(500);
        adminAccount.withdraw(300);

        BankAccount userAccount = new BankAccountProxy("User", 1000);
        userAccount.deposit(500);
        userAccount.withdraw(300);
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Image
    {
        void display();
        String getFileName();
    }

    static class RealImage implements Image
    {
        private String fileName;

        public RealImage(String InFileName)
        {
            fileName = InFileName;

        }

        private void loadFromDisk()
        {
            System.out.printf("Loading %s\n", fileName);
        }

        @Override
        public void display()
        {
            System.out.printf("Displaying %s\n", fileName);
        }

        @Override
        public String getFileName() {
            return fileName;
        }
    }

    static class ProxyImage implements Image
    {
        private RealImage realImage;
        private String fileName;

        public ProxyImage(String InFileName)
        {
            fileName = InFileName;
        }


        @Override
        public void display()
        {
            if(realImage == null)
            {
                realImage = new RealImage(fileName);
            }
            realImage.display();
        }

        @Override
        public String getFileName()
        {
            return fileName;
        }

        public String getFileExtension()
        {
            int lastIndex = fileName.lastIndexOf('.');
            if(lastIndex == -1) return "";

            return fileName.substring(lastIndex + 1);
        }
    }





    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface BankAccount
    {
        void withdraw(double amount);
        void deposit(double amount);
    }

    static class RealBankAccount implements BankAccount
    {
        private double balance;

        public RealBankAccount(double initialBalance)
        {
            balance = initialBalance;
        }

        @Override
        public void withdraw(double amount)
        {
            if(balance >= amount)
            {
                balance -= amount;
                System.out.printf("인출. 잔여 : %f\n", balance);
            }
            else
            {
                System.out.println("잔여부족");
            }
        }

        @Override
        public void deposit(double amount)
        {
            balance += amount;
            System.out.printf("적립. 잔여 : %f\n", balance);
        }
    }

    static class BankAccountProxy implements BankAccount
    {
        private RealBankAccount realBankAccount;
        private String userRole;

        public BankAccountProxy(String InUserRole, double initBalance)
        {
            userRole = InUserRole;
            realBankAccount = new RealBankAccount(initBalance);
        }

        private boolean hasAccess()
        {
            return "Admin".equalsIgnoreCase(userRole);
        }

        @Override
        public void withdraw(double amount)
        {
            if(hasAccess())
            {
                realBankAccount.withdraw(amount);
            }
            else
            {
                System.out.println("접근 불가. 관리자 권한 필요");
            }
        }

        @Override
        public void deposit(double amount)
        {
            realBankAccount.deposit(amount);
        }
    }
}

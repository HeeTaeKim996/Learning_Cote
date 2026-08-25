package Behaviour;

import java.util.IntSummaryStatistics;

public class Strategy
{

    /*
    ■ Strategy 패턴
    고정된 총을 사용한 채로, 총알만을 선택 교체하는 패턴.
    원형의 '총알' 을 주로 인터페이스로 구현하고, 이를 구현한 클래스를 총알 로 선택하여, 발사

    목적이 처음 정해진 후 불변하고, 이 목적을 달성할 방법은 새로 업데이트를 통해 추가/갱신 할 수 있기에,
    SOLID 패턴 중 O(개방/폐쇄 원칙. Open-Close) 를 달성함
     */

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        ShoppingCart cart = new ShoppingCart();

        cart.setPaymentStrategy(new CreditCardPayment("해리", "12345678"));
        cart.checkout(100);

        cart.setPaymentStrategy(new PayplaPayment("Bori@naver.com"));
        cart.checkout(200);



        /*-----------------------
         *         EX 2
         * --------------------- */
        Compressor compressor = new Compressor();
        String data = "aabbbcccccccaad";

        compressor.setStrategy(new RunLengthEncoding());
        System.out.printf("%s -> %s\n", data, compressor.compress(data));

        compressor.setStrategy(new SimpleReplacementCompression());
        System.out.printf("%s -> %s\n", data, compressor.compress(data));
    }


    /*-----------------------
     *         EX 1
     * --------------------- */
    interface IPaymentStrategy
    {
        void pay(int amount);
    }

    private static class CreditCardPayment implements IPaymentStrategy
    {
        private String name;
        private String cardNumber;

        public CreditCardPayment(String InName, String InCardNumber)
        {
            name = InName;
            cardNumber = InCardNumber;
        }

        @Override
        public void pay(int amount)
        {
            System.out.printf("%d 가 크레딧 카드로 지불됐습니다\n", amount);
        }
    }

    private static class PayplaPayment implements IPaymentStrategy
    {
        private String email;

        public PayplaPayment(String InEmail)
        {
            email = InEmail;
        }

        @Override
        public void pay(int amount)
        {
            System.out.printf("%d 가 페이팔로 지불됐습니다.\n", amount);
        }
    }

    private static class ShoppingCart
    {
        private IPaymentStrategy paymentStrategy;

        public void setPaymentStrategy(IPaymentStrategy InPaymentStrategy)
        {
            paymentStrategy = InPaymentStrategy;
        }

        public void checkout(int amount)
        {
            paymentStrategy.pay(amount);
        }
    }







    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface ICompressionStrategy
    {
        String compress(String data);
    }

    static class RunLengthEncoding implements ICompressionStrategy
    {

        @Override
        public String compress(String data)
        {
            StringBuilder compressed = new StringBuilder();
            int count = 1;
            for(int i = 1; i <= data.length(); i++)
            {
                if(i < data.length() && data.charAt(i) == data.charAt(i-1))
                {
                    count++;
                }
                else
                {
                    compressed.append(data.charAt(i - 1));
                    compressed.append(count);
                    count = 1;
                }
            }

            return compressed.toString();
        }
    }

    static class SimpleReplacementCompression implements ICompressionStrategy
    {

        @Override
        public String compress(String data)
        {
            return data.replace("a", "1")
                    .replace("e", "2")
                    .replace("i", "3")
                    .replace("o", "4")
                    .replace("u", "5");
        }
    }

    static class Compressor
    {
        private ICompressionStrategy strategy;

        public void setStrategy(ICompressionStrategy InStrategy)
        {
            strategy = InStrategy;
        }

        public String compress(String data)
        {
            return strategy.compress(data);
        }
    }
}

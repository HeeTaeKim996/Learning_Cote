package Creational;

import java.awt.print.Book;

public class FactoryMethod
{
    /*----------------------------------------------------------
    ■ FactoryMethod 패턴
    객체 생성을 유저가 처리하지 않고, 팩터리 클래스의 매서드에 위임하는 구조.


    생성되는 객체는 interface(interface 의 구현자) 이며,
    abstract class 팩터리(abstract의 구현자) || 팩터리 매서드의 인자
    등 다양한 경로를 통해, 생성되는 Concrete 객체가 달라지는 구조

    아래 예시로는 EX1 은 abstract 구현자의 종류에 따라 생성되는 객체가 달라지며,
    EX2 는 팩터리 매서드의 인자값에 따라 생성되는 객체가 달라지며,
    EX3 는 abstract 구현자의 종류에 따라 생성되는 객체가 달라지지만,
    각 개체의 프로퍼티는 팩터리 매서드의 인자값에 따라  할당값이 달라짐

    빌더 패턴과 비교하면, 객체 생성을 위임한다는 점에서는 공통점이 있지만,
    빌더 패턴은 객체의 프로퍼티를 빌더 함수를 통해 유저가 직접 할당하지만,
    팩토리 매서드 패턴은 좀 더 포괄적인 정보 (abstract의 구현자 || 팩터리 매서드의 인자값)
    를 통해 생성되는 객체 || 객체정보를 할당함
     ----------------------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        VehicleFactory carFactory = new CarFactory();
        carFactory.deliverVehicle();

        VehicleFactory motorcycleFactory = new MotorcycleFactory();
        motorcycleFactory.deliverVehicle();

        /*-----------------------
         *         EX 2
         * --------------------- */
        ProductFactory factory = new ConcreteProductFactory();

        Product electronics = factory.orderProduct("electronics");
        Product clothing = factory.orderProduct("clothing");
        Product book = factory.orderProduct("book");


        /*-----------------------
         *         EX 3
         * --------------------- */
        System.out.printf("\n\n\n");
        FinancialInfo userInfo
                = new FinancialInfo("1234-5678", "harry@naver.com");

        PaymentFactory factory1 = new CreditCardPaymentFactory();
        Payment payment = factory1.createPayment(userInfo);
        payment.processPayment(100);

        factory1 = new PalPaymentFactory();
        payment = factory1.createPayment(userInfo);
        payment.processPayment(200);
    }


    /*-----------------------
     *         EX 1
     * --------------------- */
    // Product Interface
    static interface Vehicle
    {
        void drive();
    }

    // Concrete Product
    static class Car implements Vehicle
    {
        @Override
        public void drive()
        {
            System.out.println("Driving a car");
        }
    }

    static class Motorcycle implements Vehicle
    {
        @Override
        public void drive()
        {
            System.out.println("Riding a motorcycle");
        }
    }

    // Creator abstract class
    static abstract class VehicleFactory
    {
        // Factory Method
        protected abstract Vehicle createVehicle();

        // Operating using the factory method
        public void deliverVehicle()
        {
            Vehicle vehicle = createVehicle();
            System.out.println("Driving the vehicle : ");
            vehicle.drive();
        }
    }

    static class CarFactory extends VehicleFactory
    {
        @Override
        protected Vehicle createVehicle()
        {
            return new Car();
        }
    }

    static class MotorcycleFactory extends VehicleFactory
    {
        @Override
        protected Vehicle createVehicle()
        {
            return new Motorcycle();
        }
    }




    /*-----------------------
     *         EX 2
     * --------------------- */
    public static interface Product
    {
        void create();
    }

    public static class Electronics implements Product
    {
        @Override
        public void create()
        {
            System.out.println("Electronics product created");
        }
    }

    public static class Clothing implements Product
    {
        @Override
        public void create()
        {
            System.out.println("Clothing Product created");
        }
    }

    public static class Book implements Product
    {
        @Override
        public void create()
        {
            System.out.println("Book Product created");
        }
    }

    public static abstract class ProductFactory
    {
        // Factory Method
        public abstract Product createProduct(String type);

        public Product orderProduct(String type)
        {
            Product product = createProduct(type);
            product.create();
            return product;
        }
    }

    public static class ConcreteProductFactory extends ProductFactory
    {
        @Override
        public Product createProduct(String type)
        {
            if(type.equalsIgnoreCase("electronics"))
            {
                return new Electronics();
            }
            else if(type.equalsIgnoreCase("clothing"))
            {
                return new Clothing();
            }
            else if(type.equalsIgnoreCase("book"))
            {
                return new Book();
            }
            else
            {
                return null;
            }
        }
    }


    /*-----------------------
     *         EX 3
     * --------------------- */
    static interface Payment
    {
        void processPayment(double amount);
    }

    static class CreditCardPayment implements Payment
    {
        private String creditCardNumber;
        public CreditCardPayment(String InCreditCardNumber)
        {
            creditCardNumber = InCreditCardNumber;
        }

        @Override
        public void processPayment(double amount)
        {
            System.out.printf("CreditCard : $%s\n", amount);
        }
    }

    static class PaypalPayment implements Payment
    {
        private String paypalEmail;

        public PaypalPayment(String InPayplEmail)
        {
            paypalEmail = InPayplEmail;
        }

        @Override
        public void processPayment(double amount)
        {
            System.out.printf("Paypal : $%s\n", amount);
        }
    }

    static class FinancialInfo
    {
        public String creditCardNumber;
        public String paypalEmail;

        public FinancialInfo(String InCreditCardNumber, String InPaypalEmail)
        {
            creditCardNumber = InCreditCardNumber;
            paypalEmail = InPaypalEmail;
        }
    }

    static abstract class PaymentFactory
    {
        abstract Payment createPayment(FinancialInfo info);
    }

    static class CreditCardPaymentFactory extends PaymentFactory
    {
        @Override
        Payment createPayment(FinancialInfo info)
        {
            return new CreditCardPayment(info.creditCardNumber);
        }
    }

    static class PalPaymentFactory extends PaymentFactory
    {

        @Override
        Payment createPayment(FinancialInfo info)
        {
            return new PaypalPayment(info.paypalEmail);
        }
    }
}

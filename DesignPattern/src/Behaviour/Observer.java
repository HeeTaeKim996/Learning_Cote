package Behaviour;

import java.util.ArrayList;
import java.util.List;

public class Observer
{
    /*----------------------------------------------------
    ■ Observer 패턴
    특정 클래스가 인터페이스 상속자들을 컨테이너(리스트) 로 갖고 있음으로써,
    구독 / 구독알림 / 구독해지 를 하는 패턴

    인플루언서와 팔로워의 관계가 대표적. 팔로워는 인플루언서의 인스타를
    구독 / 알림받기 / 해지 할 수 있음

    C# 의 델리게이트나, C++ 의 그 function<..> 을 weakPtr로 구독,
    언리얼의 DELEGATE 등에서
    너무 자주 사용했던 패턴이기에, 굳이 설명할 필요도 없다

    SOLID 의 D(의존 역전 원칙) 의 의존 역전 문제를 해결하는
    대표적인 패턴
     ---------------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        NewsAgency agency = new NewsAgency();

        NewsChannel channel1 = new NewsChannel("channel 1");
        NewsChannel channel2 = new NewsChannel("channel 2");

        agency.registerObserver(channel1);
        agency.registerObserver(channel2);

        agency.setNews("Breaking News : Observer Pattern is on Action !");

        agency.removeObserver(channel2);

        agency.setNews("Another Update : Channel 2 unsubscribed");


        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        WeatherData weatherData = new WeatherData();

        CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay();
        StatisticsDisplay statisticsDisplay = new StatisticsDisplay();
        ForecastDisplay forecastDisplay = new ForecastDisplay();

        weatherData.registerObserver(currentDisplay);
        weatherData.registerObserver(statisticsDisplay);
        weatherData.registerObserver(forecastDisplay);

        weatherData.setMeasurements(80, 65, 30.4f);
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Observer1
    {
        void update(String name);
    }

    static interface Subject
    {
        void registerObserver(Observer1 observer);
        void removeObserver(Observer1 observer);
        void notifyObservers();
    }

    static class NewsAgency implements Subject
    {
        private List<Observer1> observers = new ArrayList<>();
        private String news;

        @Override
        public void registerObserver(Observer1 observer)
        {
            observers.add(observer);
        }

        @Override
        public void removeObserver(Observer1 observer)
        {
            observers.remove(observer);
        }

        @Override
        public void notifyObservers()
        {
            for(Observer1 observer : observers)
            {
                observer.update(news);
            }
        }

        public void setNews(String InNews)
        {
            news = InNews;
            notifyObservers();
        }
    }

    static class NewsChannel implements Observer1
    {
        private String name;

        public NewsChannel(String InName)
        {
            name = InName;
        }

        @Override
        public void update(String news)
        {
            System.out.printf("%s received news : %s\n", name, news);
        }
    }





    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface WeatherStation
    {
        void registerObserver(WeatherObserver o);
        void removeObserver(WeatherObserver o);
        void notifyObservers();
    }

    static interface WeatherObserver
    {
        void update(float temp, float humidity, float pressure);
    }

    static class WeatherData implements WeatherStation
    {
        private List<WeatherObserver> observers = new ArrayList<>();
        private float temperature, humidity, pressure;

        public void setMeasurements(float InTemperature, float InHumidity, float InPressure)
        {
            temperature = InTemperature;
            humidity = InHumidity;
            pressure = InPressure;
            notifyObservers();
        }

        @Override
        public void registerObserver(WeatherObserver o)
        {
            observers.add(o);
        }

        @Override
        public void removeObserver(WeatherObserver o)
        {
            observers.remove(o);
        }

        @Override
        public void notifyObservers()
        {
            for(WeatherObserver observer : observers)
            {
                observer.update(temperature, humidity, pressure);
            }
        }
    }

    static class CurrentConditionsDisplay implements WeatherObserver
    {
        @Override
        public void update(float temp, float humidity, float pressure)
        {
            System.out.printf("Current : %fF, humidity : %f humidity\n", temp, humidity);
        }
    }

    static class StatisticsDisplay implements WeatherObserver
    {
        @Override
        public void update(float temp, float humidity, float pressure)
        {
            System.out.printf("Avg/Max/Min temp : %f/%f/%f\n", temp, temp + 2, temp - 2);
        }
    }

    static class ForecastDisplay implements WeatherObserver
    {
        @Override
        public void update(float temp, float humidity, float pressure)
        {
            System.out.printf("Forecast : %s\n", pressure < 29.92 ? "Rain" : "Sunny");
        }
    }
}

package Creational;

import java.util.HashMap;
import java.util.Map;

public class Builder
{
    /*
    ■ Builder 패턴
    객체의 멤버 변수 선택지가 많고, 생성 과정에서 사전 검수가 필요할 때,
    가독성/유지보수성 을 위해 사용되는 패턴

    ○
    과거 구두의 서브웨이 주문과 앱으로의 피자 주문의 차이점으로 예시를 들 수 있다

    전자의 경우 빵 - 야채 - 고기 순으로 고정되어 주문해야 하고,
    특정 손님이 야채 에서 고민하는 경우 야채 이전의 뒤 손님들은 기다려야 하는 단점이 있다.

    반면 후자의 경우 도우 - 토핑 - 소스 순서로 지키지 않고 주문해도 되며,
    주문이 완료된 후에 도우 - 토핑 - 소스 를 즉시 준비할 수 있기에, 효율적이다.
    (즉시 생성은 멀티스레딩에서의 객체 생성 때 도움이 된다 함)

    ○
    패턴은 고정적이다.
    Builder 클래스는 원형 클래스의 멤버 변수를 똑같이 들고 있고, set함수로 변수들을 할당한다.
    원형 클래스는 생성자로 Builder 클래스를 인자로 받으며,
    Builder 클래스는 build 함수 때 원형 클래스를 자신을 인자로 하여 생성하고 리턴한다.

    ○
    추가로 빌더 패턴에서 사전 검수를 하고,
    원형 클래스의 생성자 때에는 고정된 순서로 변수들을 할당할 수 있기에,
    보안/유지보수성도 향상될 수 있다
     */

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Pizza myPizza = new Pizza.Builder1().setDough("Thin Crust")
                .setSauce("Tomato").setTopping("Cheese").build();
        System.out.println();
        System.out.println(myPizza);


        /*-----------------------
         *         EX 2
         * --------------------- */
        HttpRequest httpRequest = new HttpRequest.Builder1(
                "GET", "http://naver.com")
                .addHeader("Authorizoation", "Bearer token")
                .addParameter("query", "builder-pattern")
                .build();

        System.out.println(httpRequest);
    }

    /*-----------------------
     *         EX 1
     * --------------------- */

    public static class Pizza
    {
        private String dough;
        private String sauce;
        private String topping;

        private Pizza(Builder1 builder)
        {
            dough = builder.dough;
            sauce = builder.sauce;
            topping = builder.topping;
        }

        public String toString()
        {
            return String.format("This Pizza is consisted of [%s], [%s], [%s]\n",
                    dough, sauce, topping);

        }

        public static class Builder1
        {
            public Pizza build()
            {
                return new Pizza(this);
            }

            private String dough;
            private String sauce;
            private String topping;

            public Builder1 setDough(String InDough)
            {
                dough = InDough;
                return this;
            }

            public Builder1 setSauce(String InSauce)
            {
                sauce = InSauce;
                return this;
            }

            public Builder1 setTopping(String InTopping)
            {
                topping = InTopping;
                return this;
            }
        }

    }





    /*-----------------------
     *         EX 2
     * --------------------- */
    public static class HttpRequest
    {
        private String method;
        private String url;
        private Map<String, String> headers;
        private Map<String, String> parameters;
        private String body;

        public HttpRequest(Builder1 builder)
        {
            method = builder.method;
            url = builder.url;
            headers = builder.headers;
            parameters = builder.parameters;
            body = builder.body;
        }

        public String toString()
        {
            return String.format("This http request is consist of " +
                    "[%s], [%s], [%s], [%s], [%s]\n", method, url, headers, parameters, body);
        }

        public static class Builder1
        {
            public HttpRequest build()
            {
                return new HttpRequest(this);
            }

            private String method;
            private String url;
            private Map<String, String> headers = new HashMap<>();
            private Map<String, String> parameters = new HashMap<>();
            private String body;

            public Builder1(String InMethod, String InUrl)
            {
                method = InMethod;
                url = InUrl;
            }

            public Builder1 addHeader(String key, String value)
            {
                headers.put(key, value);
                return this;
            }

            public Builder1 addParameter(String key, String value)
            {
                parameters.put(key, value);
                return this;
            }

            public Builder1 setBody(String InBody)
            {
                body = InBody;
                return this;
            }


        }
    }
}

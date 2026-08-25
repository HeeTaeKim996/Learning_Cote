package Behaviour;

public class TemplateMethod
{
    /*
    ■ TemplateMethod 패턴
    일들의 순서는 고정하여 지정하되, 일들의 세부 구현은 상속자들이 처리하는 패턴

    프랑스 전통 레스토랑은 에피타이저 - 메인요리 - 디저트로 식사가 제공돼어야 하지만,
    각 레스토랑들은 고유의 메뉴들을 위 항목에 맞게 변경할 수 있다.

    프레임워크(유니티, 언리얼, 안드로이드..) 가 템플릿 메서드를 구현한 것으로 볼 수 있다.
    유니티의 예로 초기화는 awake, start 순서를 고정하되, 세부 내용은 유저에게 맡긴다
     */
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Beverage tea = new Tea();
        Beverage coffee = new Coffee();

        System.out.printf("--차를 준비합니다--\n");
        tea.prepareRecipe();

        System.out.printf("--커피를 준비합니다--\n");
        coffee.prepareRecipe();

        /*-----------------------
         *         EX 2
         * --------------------- */
        DataProcessor csvProcessor = new CSVDataProcessor();
        csvProcessor.process("CSV data");

        DataProcessor jsonProcessor = new JSONDataProcessor();
        jsonProcessor.process("XML data");
    }


    /*-----------------------
     *         EX 1
     * --------------------- */
    static abstract class Beverage
    {
        final void prepareRecipe()
        {
            boilWater();
            brew();
            pourInCoup();
            addCondiments();
        }

        private void boilWater()
        {
            System.out.printf("물을 끓입니다\n");
        }
        private void pourInCoup()
        {
            System.out.printf("컵에 물을 따릅니다\n");
        }

        abstract void brew();
        abstract void addCondiments();
    }

    static class Tea extends Beverage
    {

        @Override
        void brew()
        {
            System.out.printf("차를 주조합니다\n");
        }

        @Override
        void addCondiments()
        {
            System.out.printf("레몬을 넣습니다\n");
        }
    }

    static class Coffee extends Beverage
    {

        @Override
        void brew()
        {
            System.out.printf("필터에 커피를 넣고 끓입니다\n");
        }

        @Override
        void addCondiments()
        {
            System.out.printf("설탕과 우유를 넣습니다\n");
        }
    }






    /*-----------------------
     *         EX 2
     * --------------------- */
    static abstract class DataProcessor
    {
        public final void process(String data)
        {
            loadData(data);
            if(isValidData(data))
            {
                processData(data);
                saveData(data);
            }
            else
            {
                System.out.println("데이터가 유효하지 않기에, 중단합니다");
            }
        }

        protected abstract void loadData(String data);
        protected abstract boolean isValidData(String data);
        protected abstract void processData(String data);
        protected abstract void saveData(String data);
    }

    static class CSVDataProcessor extends DataProcessor
    {

        @Override
        protected void loadData(String data)
        {
            System.out.printf("CSV 파일을 로드합니다 : %s\n", data);
        }

        @Override
        protected boolean isValidData(String data)
        {
            return data != null && data.contains("CSV");
        }

        @Override
        protected void processData(String data)
        {
            System.out.println("CSV 데이터를 처리합니다");
        }

        @Override
        protected void saveData(String data)
        {
            System.out.println(("CSV 파일을 저장합니다"));
        }
    }

    static class JSONDataProcessor extends DataProcessor
    {
        @Override
        protected void loadData(String data) {
            System.out.println("JSON 파일을 로드합니다: " + data);
        }

        @Override
        protected boolean isValidData(String data) {
            return data != null;
        }

        @Override
        protected void processData(String data) {
            System.out.println("JSON 데이터를 처리합니다");
        }

        @Override
        protected void saveData(String data) {
            System.out.println("JSON 파일을 저장합니다");
        }
    }
}

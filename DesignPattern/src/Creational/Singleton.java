package Creational;

public class Singleton
{
    /*-------------------------------------------------------
    ■ Singleton 패턴
    프로젝트에서 전역 하나로만 관리되어야 하는 필드들을 다룰 때 사용

    버거 프렌차이즈를 예로 들면, 버거 프렌차이즈명, CEO 명 같은
    해당 프렌차이즈에 공통으로 적용되는 것들은 싱글턴패턴에서 관리하고,
    프렌차이즈의 점포들은 인스턴스이므로, 싱글턴이 아닌 인스턴스에서 관리

    언어마다 싱글턴 구현에 차이는 있지만, 공통적으로,
    1) T instance 를 static으로 멤버로 들고 있다
    2) 생성자가 private으로 막혀있다
    3) getInstance 매서드에서 if(instance == null) { instnace = new.. }
       패턴으로 instance == null 일 때 생성자를 호출한다
    이다.

    전역 멤버들을 static으로만 다룰 수도 있지만, 싱글턴이 이에 대비하여
    갖는 장점은 크게 2가지인 것 같다.
    1) 생성자에서 멤버들의 값들을 일괄척으로 처리할 수 있다.
    2) getInstance가 호출되기 전까지, 싱글턴은 메모리에 올라오지 않기에,
       메모리가 미세하게나마 절약될 수 있다
    ------------------------------------------------------ */
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Button button = new Button("Submit");
        TextFiled textFiled = new TextFiled("Enter your name");

        button.display();
        textFiled.display();

        Theme.getInstance().setThemeColor("dark");
        button.display();
        textFiled.display();
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    public static class Theme
    {
        private static Theme instance;
        private Theme()
        {
            themeColor = "light";
        }
        public static Theme getInstance()
        {
            if(instance == null)
            {
                instance = new Theme();
            }
            return instance;
        }

        private String themeColor;
        public String getThemeColor() { return themeColor;}
        public void setThemeColor(String InThemeColor) { themeColor = InThemeColor;}
    }

    public static class Button
    {
        public Button(String InLabel)
        {
            label = InLabel;
        }
        private String label;

        public void display()
        {
            String themeColor = Theme.getInstance().getThemeColor();
            System.out.printf("Button[%s] displayed in [%s]theme\n", label, themeColor);
        }
    }

    public static class TextFiled
    {
        public TextFiled(String InText)
        {
            text = InText;
        }
        public void display()
        {
            String themeColor = Theme.getInstance().getThemeColor();
            System.out.printf("TextField[%s] displayed in [%s]theme\n", text, themeColor);
        }

        private String text;
    }
}

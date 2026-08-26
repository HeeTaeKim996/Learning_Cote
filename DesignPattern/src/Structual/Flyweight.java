package Structual;

import java.util.HashMap;
import java.util.Map;

public class Flyweight
{
    /*-------------------------------------------
    ■ Flyweight 패턴
    무거운(데이터가 큰) 개체를 하나만 생성하고,
    다른 클래스들이 이 개체를 함께 공유해서 사용함으로써,
    메모리를 절약하는 패턴

    게임 엔진 개발 때 데이터가 무거운 에셋(메터리얼, 컬러, 텍스쳐, 사운드..)를 하나만 생성하고,
    게임 오브젝트들이 이 에셋들을 공유했던 것이
    대표적인 Flyweight 패턴

    아래 두 예제에서는 유저가 특정 개체를 찾고 없을 때, 개체를 생성하는 구조를 사용했지만,
    갓오브워가 대표적으로 보여주듯, 시간/공간적 구역성에 따라
    유저가 직접 공유 개체들을 메모리에 로드/제거 하는 것이 효율적.

    페이징 기술로 인해 오버레이 개념은 많이 사라졌지만,
    위 플라이웨이트 패턴의 갓오버워에서 여전히 오버레이가 남아있는 걸로도 볼 수 있겠다
     ------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Book book1 = Bookshelf.getBook("a");
        book1.read();

        Book book2 = Bookshelf.getBook("a");
        book2.read();

        Book book3 = Bookshelf.getBook("b");
        book3.read();

        System.out.println(book1 == book2 ? "Same Book for a" : "Different Book for a");


        /*-----------------------
         *         EX 2
         * --------------------- */
        Font font1 = FontFactory.getFont("Arial", 12, "Black");
        font1.apply("Hello Harry");

        Font font2 = FontFactory.getFont("Arial", 12, "Black");
        font2.apply("Hi Bori");

        Font font3 = FontFactory.getFont("Times new romans", 14, "Blue");
        font3.apply("Design Pattern");

        Font font4 = FontFactory.getFont("Arial", 12, "Black");
        font4.apply("Also Algorithm");
    }


    /*-----------------------
     *         EX 1
     * --------------------- */
    static class Book
    {
        private final String title;

        Book(String Intitle)
        {
            title = Intitle;
        }

        public void read()
        {
            System.out.printf("Reading the book titled : %s\n", title);
        }
    }

    static class Bookshelf
    {
        private static final Map<String, Book> bookShelf = new HashMap<>();

        public static Book getBook(String title)
        {
            Book book = bookShelf.get(title);
            if(book == null)
            {
                book = new Book(title);
                bookShelf.put(title, book);
                System.out.printf("Adding a new book to bookShelf : %s\n", title);
            }
            else
            {
                System.out.printf("Reusing existing book for the bookShelf : %s\n", title
                );
            }

            return book;
        }
    }




    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface Font
    {
        void apply(String text);
    }

    static class ConcreteFont implements Font
    {
        private String font;
        private int size;
        private String color;

        public ConcreteFont(String InFont, int InSize, String InColor)
        {
            font = InFont;
            size = InSize;
            color = InColor;
        }

        @Override
        public void apply(String text)
        {
            System.out.printf("Text : %s, With font : %s, Size : %d, Color : %s\n",
                    text, font, size, color);
        }
    }

    static class FontFactory
    {
        private static final HashMap<String, Font> fontMap = new HashMap<>();

        public static Font getFont(String font, int size, String color)
        {
            String key = font + size + color;
            Font fontObject = fontMap.get(key);

            if(fontObject == null)
            {
                fontObject = new ConcreteFont(font, size, color);
                fontMap.put(key, fontObject);
                System.out.printf("Creating for %s\n", key);
            }
            else
            {
                System.out.printf("Reusing for %s\n", key);
            }

            return fontObject;
        }
    }
}

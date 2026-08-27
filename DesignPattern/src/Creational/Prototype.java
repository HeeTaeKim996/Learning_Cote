package Creational;

import org.w3c.dom.Text;

import javax.print.Doc;
import java.util.HashMap;
import java.util.Map;

public class Prototype
{
    /*---------------------------------------------
    ■ Prototype 패턴
    기존 객체를 토대로 새로운 객체에 깊은 복사하는 패턴

    clone 함수 그 자체
     ---------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Person origin = new Person("Harry", 15, "paju");
        origin.displayInfo();

        Person clone = origin.clone();
        clone.setAddress("cheonAn");

        System.out.println("---");
        origin.displayInfo();
        clone.displayInfo();


        /*-----------------------
         *         EX 2
         * --------------------- */
        DocumentTemplateManager
                .addTemplate("welcome", new TextDocument("welcome, {name}!"));
        DocumentTemplateManager
                .addTemplate("meeting", new TextDocument("Meeting scheduled on {date} at {time}"));

        Document welcomeDoc = DocumentTemplateManager.createDocument("welcome");
        if(welcomeDoc != null)
        {
            welcomeDoc.setContent(welcomeDoc.getContent().replace("{name}", "Harry"));

            System.out.printf("Welcome document : %s\n", welcomeDoc.getContent());
        }

        Document meetingDoc = DocumentTemplateManager.createDocument("meeting");
        if(meetingDoc != null)
        {
            meetingDoc.setContent(meetingDoc.getContent().replace("{date}", "2026-08-27")
                    .replace("{time}", "14:22"));
            System.out.printf("Meeting document : %s\n", meetingDoc.getContent());
        }



    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Prototype1
    {
        Prototype1 clone();
    }

    static class Person implements Prototype1
    {
        private String name;
        private int age;
        private String address;

        public Person(String inName, int inAge, String inAddress)
        {
            name = inName;
            age = inAge;
            address = inAddress;
        }

        public Person(Person other)
        {
            name = other.name;
            age = other.age;
            address = other.address;
        }

        @Override
        public Person clone()
        {
            return new Person(this);
        }

        public void setAddress(String newAddress)
        {
            address = newAddress;
        }

        public void displayInfo()
        {
            System.out.printf("Name[%s], age[%d], address[%s]\n", name, age, address);
        }
    }







    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface Prototype2
    {
        Prototype2 clone();
    }

    static interface Document extends Prototype2
    {
        void setContent(String content);
        String getContent();
    }

    static class TextDocument implements Document
    {
        private String content;

        public TextDocument(String inContent)
        {
            content = inContent;
        }


        @Override
        public void setContent(String inContent)
        {
            content = inContent;
        }

        @Override
        public String getContent()
        {
            return content;
        }

        @Override
        public Prototype2 clone()
        {
            return new TextDocument(this.content);
        }
    }

    static class DocumentTemplateManager
    {
        private static final Map<String, Document> templates = new HashMap<>();

        public static void addTemplate(String name, Document doc)
        {
            templates.put(name, doc);
        }

        public static Document createDocument(String templateName)
        {
            Document template = templates.get(templateName);
            if(template == null)
            {
                return null;
            }

            return (Document) template.clone();
        }
    }
}

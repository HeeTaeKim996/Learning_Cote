package Creational;

import javax.xml.crypto.Data;
import java.awt.image.DataBufferShort;

public class AbstractFactory
{
    /*----------------------------------------------
    ■ AbstractFactory
    Factory 매서드의 다중 제품(개체) 버전.

    Factory 매서드가 단일 제품(개체) 생산을 담당한다면,
    AbstractFactory 는 다중 제품(개체) 생산을 담당한다.

    그 외 모든 구조는 Factory매서드와 동일하다.
     ----------------------------------------------*/
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        GUIFactory windowFactory = new WindowsFactory();
        Application windowApp = new Application(windowFactory);
        windowApp.pain();

        System.out.println();

        GUIFactory macFactory = new MacFactory();
        Application macApp = new Application(macFactory);
        macApp.pain();


        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.println("---");
        DatabaseClient mySqlClient = new DatabaseClient(new MySqlFactory());
        mySqlClient.performDatabaseOperations();

        System.out.println("---");
        DatabaseClient mariaClient = new DatabaseClient(new MariaFactory());
        mariaClient.performDatabaseOperations();
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Button
    {
        void paint();
    }

    static interface Checkbox
    {
        void paint();
    }

    static class WindowsButton implements Button
    {
        @Override
        public void paint()
        {
            System.out.println("Rendering a button in Window style");
        }
    }

    static class WindowsCheckbox implements Checkbox
    {
        @Override
        public void paint()
        {
            System.out.println("Rendering a checkbox in Window style");
        }
    }

    static class MacButton implements Button
    {
        @Override
        public void paint()
        {
            System.out.println("Rendering a button in Mac Style");
        }
    }

    static class MacCheckbox implements Checkbox
    {
        @Override
        public void paint()
        {
            System.out.println("Rendering a checkbox in Mac style");
        }
    }

    static interface GUIFactory
    {
        Button createButton();
        Checkbox createCheckbox();
    }

    static class WindowsFactory implements GUIFactory
    {
        @Override
        public Button createButton()
        {
            return new WindowsButton();
        }

        @Override
        public Checkbox createCheckbox()
        {
            return new WindowsCheckbox();
        }
    }

    static class MacFactory implements GUIFactory
    {
        @Override
        public Button createButton()
        {
            return new MacButton();
        }

        @Override
        public Checkbox createCheckbox() {
            return new MacCheckbox();
        }
    }

    // Client Code
    static class Application
    {
        private Button button;
        private Checkbox checkbox;

        public Application(GUIFactory factory)
        {
            button = factory.createButton();
            checkbox = factory.createCheckbox();
        }
        public void pain()
        {
            button.paint();
            checkbox.paint();
        }
    }





    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface Connection
    {
        void open();
        void close();
    }

    static interface Command
    {
        void execute(String query);
    }

    static interface DatabaseFactory
    {
        Connection createConnection();
        Command createCommand();
    }

    static class MySqlConnection implements Connection
    {
        @Override
        public void open()
        {
            System.out.println("Opening MySql Connection");
        }

        @Override
        public void close()
        {
            System.out.println("Closing MySql Connection");
        }
    }

    static class MySqlCommand implements Command
    {
        @Override
        public void execute(String query)
        {
            System.out.printf("Executing MySql Query : %s\n", query);
        }
    }

    static class MariaConnection implements Connection
    {
        @Override
        public void open()
        {
            System.out.println("Opening Maria Connection");
        }

        @Override
        public void close()
        {
            System.out.println("Closing Maria Connection");
        }
    }

    static class MariaCommand implements Command
    {
        @Override
        public void execute(String query)
        {
            System.out.printf("Executing Maria Query : %s\n", query);
        }
    }

    static class MySqlFactory implements DatabaseFactory
    {
        @Override
        public Connection createConnection()
        {
            return new MySqlConnection();
        }

        @Override
        public Command createCommand()
        {
            return new MySqlCommand();
        }
    }

    static class MariaFactory implements DatabaseFactory
    {
        @Override
        public Connection createConnection()
        {
            return new MariaConnection();
        }

        @Override
        public Command createCommand() {
            return new MariaCommand();
        }
    }

    // Client Code
    static class DatabaseClient
    {
        private Connection connection;
        private Command command;

        public DatabaseClient(DatabaseFactory factory)
        {
            connection = factory.createConnection();
            command = factory.createCommand();
        }

        public void performDatabaseOperations()
        {
            connection.open();
            command.execute("SELECT * FROM users");
            connection.close();
        }
    }
}

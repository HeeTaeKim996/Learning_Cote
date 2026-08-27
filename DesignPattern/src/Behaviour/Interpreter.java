package Behaviour;

import java.util.*;

public class Interpreter
{
    /*
    ■ Interpreter 패턴
    강의를 들어도, 이게 왜 패턴인지 이해가 안된다.
    사칙연산 인터프리터와, 쿼리 인터프리터는 알고리즘 자체가 전혀 달라보인다.

    인터프리터 패턴에 공통적인 특징은 전혀 보이지 않는다.
    기껏해야 String 을 여러 연산자, 값 들로 나누는 것 뿐

    그냥 언어해석기 알고리즘 으로 이해하자. 알고리즘 내용은 전혀 모르고.
     */

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Expression five = new Number(5);
        Expression two = new Number(2);
        Expression three = new Number(3);

        Expression add = new Add(five, two);

        Expression sub = new Subtract(add, three);

        System.out.printf("(5 + 2) - 3 = %d\n", sub.interpret());

        /*-----------------------
         *         EX 2
         * --------------------- */
        Context context = new Context();

        String query1 = "SELECT * FROM users";
        Expression2 expr1 = SQLParser.parse(query1);
        List<Map<String, String>> result1 = expr1.interpret(context);

        System.out.println("Reuslt of query : " + result1);
        for(Map<String, String> row : result1)
        {
            System.out.println(row);
        }

        String query2 = "SELECT name,age FROM users WHERE age > 27";
        Expression2 expr2 = SQLParser.parse(query2);
        List<Map<String, String>> result2 = expr2.interpret(context);

        System.out.println("\nResult of query : " + query2);
        for(Map<String, String> row: result2)
        {
            System.out.println(row);
        }
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    public static interface Expression
    {
        int interpret();
    }

    public static class Number implements Expression
    {
        private int number;

        public Number(int inNumber)
        {
            number = inNumber;
        }

        @Override
        public int interpret()
        {
            return number;
        }
    }

    public static class Add implements Expression
    {
        private Expression leftExpression;
        private Expression rightExpression;

        public Add(Expression inLeftExpression, Expression inRightExpression)
        {
            leftExpression = inLeftExpression;
            rightExpression = inRightExpression;
        }

        @Override
        public int interpret()
        {
            return leftExpression.interpret() + rightExpression.interpret();
        }
    }

    public static class Subtract implements Expression
    {
        private Expression leftExpression;
        private Expression rightExpression;

        public Subtract(Expression inLeftExpression, Expression inRightExpression)
        {
            leftExpression = inLeftExpression;
            rightExpression = inRightExpression;
        }
        @Override
        public int interpret()
        {
            return leftExpression.interpret() - rightExpression.interpret();
        }
    }






    /*-----------------------
     *         EX 2
     * --------------------- */
    static class Context
    {
        private Map<String, List<Map<String, String>>> tables;

        public Context()
        {
            tables = new HashMap<>();
            List<Map<String, String>> users = new ArrayList<>();
            users.add(new HashMap<String, String>()
            {
                {
                    put("id", "1");
                    put("name", "john");
                    put("age", "30");
                }
            });

            users.add(new HashMap<String, String>()
            {
                {
                    put("id", "2");
                    put("name", "Jane");
                    put("age", "25");
                }
            });
            tables.put("users", users);
        }

        public List<Map<String, String>> getTable(String key)
        {
            return tables.get(key);
        }

        public void setTable(String key, List<Map<String, String>> table)
        {
            tables.put(key, table);
        }
    }

    static interface Expression2
    {
        List<Map<String, String>> interpret(Context context);
    }

    static class WhereExpression implements Expression2
    {
        private String column;
        private String operator;
        private String value;
        private String tableName;

        public WhereExpression(String inTableName, String inColumn, String inOperator, String inValue)
        {
            tableName = inTableName;
            column = inColumn;
            operator = inOperator;
            value = inValue;
        }

        @Override
        public List<Map<String, String>> interpret(Context context)
        {
            List<Map<String, String>> result = new ArrayList<>();
            List<Map<String, String>> table
                    = context.getTable(tableName);
            for(Map<String, String> row : table)
            {
                if(evaluate(row.get(column), operator, value))
                {
                    result.add(row);
                }
            }

            return result;
        }

        private boolean evaluate(String columnValue, String operator, String value)
        {
            switch(operator)
            {
                case "=":
                    return columnValue.equals(value);
                case ">":
                    return Integer.parseInt(columnValue) > Integer.parseInt(value);
                case "<":
                    return Integer.parseInt(columnValue) < Integer.parseInt(value);
                default:
                    return false;
            }
        }
    }

    static class SelectExpression implements Expression2
    {
        private String tableName;
        private List<String> columns;
        private Expression2 whereClause;

        public SelectExpression(String inTableName, List<String> inColumns,
                                Expression2 inWhereClause)
        {
            tableName = inTableName;
            columns = inColumns;
            whereClause = inWhereClause;
        }


        @Override
        public List<Map<String, String>> interpret(Context context)
        {
            List<Map<String, String>> table = context.getTable(tableName);
            List<Map<String, String>> result = new ArrayList<>();

            for(Map<String, String> row : table)
            {
                Context rowContext = new Context();
                rowContext.setTable(tableName, Collections.singletonList(row));

                if(whereClause == null || whereClause.interpret(rowContext).isEmpty() == false)
                {
                    Map<String, String> newRow = new HashMap<>();

                    for(String column : columns)
                    {
                        if(column.equals("*"))
                        {
                            newRow.putAll(row);
                        }
                        else
                        {
                            newRow.put(column, row.get(column));
                        }
                    }

                    result.add(newRow);
                }
            }

            return result;
        }
    }

    static class SQLParser
    {
        public static Expression2 parse(String query)
        {
            String[] parts = query.split("\\s+"); // \\s+ 공백?
            if(parts[0].equalsIgnoreCase("SELECT") == false)
            {
                throw new RuntimeException("Only SELECT statements are supported");
            }

            List<String> columns = Arrays.asList(parts[1].split(","));
            String tableName = parts[3];

            Expression2 whereClause = null;
            if(parts.length > 4 && parts[4].equalsIgnoreCase("WHERE"))
            {
                whereClause = new WhereExpression(tableName, parts[5], parts[6], parts[7]);
            }

            return new SelectExpression(tableName, columns, whereClause);
        }
    }

}
